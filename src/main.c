#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>

#define MAPWIDTH 64
#define MAPHEIGHT 64

#define GRASS 0
#define TREE 1
#define WALL 2
#define PEBBLE 3
#define STICK 4
#define ROCK 5
#define BUSH 6

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define CLAMP(v,mn,mx) (MAX((mn), (MIN((mx), (v)))))
#define HZ(x) (1000.0/(x))
#define CTRL_KEY(k) (0x1f&(k))

struct resources {
  int wood;
  int stone;
  int food;
};

struct state {
  int py, px;
  int pmode;
  struct resources pres;
  int map[MAPHEIGHT][MAPWIDTH];
  int vis[MAPHEIGHT][MAPWIDTH];
};

void UpdVis(void);

struct state S;

unsigned int Hash(int y, int x)
{
	const size_t w = 8 * sizeof(size_t);
	const size_t s = w / 2;

	size_t a = x, b = y;

	a *= 3284157443; b ^= a << s | a >> (w-s);
	b *= 1911520717; a ^= b << s | b >> (w-s);
	a *= 2048419325;

	return a;
}

float Hashf(int y, int x)
{
  return Hash(y, x) * (1.0 / ~0u);
}

void EndCurses(void)
{
  endwin();
}

void InitCurses(void)
{
  atexit(EndCurses);
  initscr();
  raw();
  noecho();
  curs_set(0);
  timeout(0);
}

void MovePlayer(int input)
{
  if (input == 'h' && S.px > 0)
    S.px--;
  if (input == 'j' && S.py < MAPHEIGHT-1)
    S.py++;
  if (input == 'k' && S.py > 0)
    S.py--;
  if (input == 'l' && S.px < MAPWIDTH-1)
    S.px++;
	UpdVis();
}

void BreakTile(int py, int px)
{
  int tile = S.map[py][px];
  if (tile && !(tile == PEBBLE || tile == STICK)) {
    S.map[py][px] = GRASS;
    if (tile == TREE || tile == WALL)
      S.pres.wood += Hash(py, px)%5+5;
    if (tile == ROCK)
      S.pres.stone += Hash(py, px)%5+5;
    if (tile == BUSH) {
      S.pres.food += Hash(py, px)%3+1;
      S.pres.wood += Hash(py, px)%3+1;
    }
		UpdVis();
  }
}

void PlaceWall(int py, int px)
{
  int tile = S.map[py][px];
  if (tile == 0 && S.pres.wood >= 2) {
    S.map[py][px] = 2;
    S.pres.wood -= 2;
		UpdVis();
  }
}

void CollectTile(int py, int px)
{
  int tile = S.map[py][px];
  if (tile == STICK || tile == PEBBLE) {
    S.map[py][px] = 0;
    if (tile == STICK) {
      S.pres.wood++;
    } else {
      S.pres.stone++;
    }
		UpdVis();
  } else if (tile == BUSH) {
    S.pres.food += Hash(py, px)%2;
    S.pres.wood += Hash(py, px)%3==0;
		UpdVis();
  }
}

void MovePlayerOrBreak(int input)
{
  int px = S.px;
  int py = S.py;
  if (input == 'h' && px > 0)
    px--;
  if (input == 'j' && py < MAPHEIGHT-1)
    py++;
  if (input == 'k' && py > 0)
    py--;
  if (input == 'l' && px < MAPWIDTH-1)
    px++;
  if (S.map[py][px])
    BreakTile(py, px);
  else
    MovePlayer(input);
}

int LimitCoord(int val, int r, int m)
{
  if (val < r) r = val;
  else if (val > m - r) r += val-(m-r);
  return r;
}

void DrawPlayer(void)
{
  int ry = LINES/2;
  int rx = COLS/4;
  ry = LimitCoord(S.py, ry, MAPHEIGHT);
  rx = LimitCoord(S.px, rx, MAPWIDTH);
  mvaddch(ry, rx*2, '@');
}

void DrawTile(int tile, int y, int x)
{
  static const char tile_chars[] = ".T#o/O*";
  static const int tclen = (sizeof(tile_chars)-1)/sizeof(char);
  int c = (tile < 0 || tile >= tclen) ? ' ' : tile_chars[tile];
  mvaddch(y, x, c);
}

void DrawMap(void)
{
  int ry = LINES/2;
  int rx = COLS/4;
  ry = LimitCoord(S.py, ry, MAPHEIGHT);
  rx = LimitCoord(S.px, rx, MAPWIDTH);
  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLS/2; j++) {
      int mapx = j + S.px - rx;
      int mapy = i + S.py - ry;
      if (mapx<0||mapy<0||mapx>=MAPWIDTH||mapy>=MAPHEIGHT || !S.vis[mapy][mapx]) {
        mvaddch(i, j*2, ' ');
        continue;
      }
      DrawTile(S.map[mapy][mapx], i, j*2);
    }
  }
}

void Load(char file)
{
  char fn[32] = {0};
  snprintf(fn, 31, "%c.sav", file);
  FILE *pF = fopen(fn, "rb");
  if (pF == NULL)
    return;
  fread(&S, sizeof(S), 1, pF);
  fclose(pF);
}

void Save(char file)
{
  char fn[32] = {0};
  snprintf(fn, 31, "%c.sav", file);
  FILE *pF = fopen(fn, "wb");
  if (pF == NULL)
    return;
  fwrite(&S, sizeof(S), 1, pF);
  fclose(pF);
}

void ProcessNormalInput(int input)
{
  switch (input) {
  case 'h':
  case 'j':
  case 'k':
  case 'l':
    MovePlayer(input);
    break;
  case 'w':
  case 'r': {
      timeout(-1);
      char file = getch();
      timeout(0);
      if (input == 'w')
        Save(file);
      else
        Load(file);
    }
    break;
  case 'b':
    S.pmode = 1;
    break;
  case 'p':
    S.pmode = 2;
    break;
  case 'c':
    S.pmode = 3;
    break;
  case CTRL_KEY('q'):
    exit(0);
  }
}

void ProcessBreakInput(int input)
{
  switch (input) {
  case 'h':
  case 'j':
  case 'k':
  case 'l':
    MovePlayerOrBreak(input);
    break;
  case '\x1b':
    S.pmode = 0;
    break;
  case CTRL_KEY('q'):
    exit(0);
  }
}

void ProcessPlaceInput(int input)
{
  switch (input) {
  case 'h':
  case 'j':
  case 'k':
  case 'l':
    MovePlayer(input);
    break;
  case '\n':
    PlaceWall(S.py, S.px);
    break;
  case '\x1b':
    S.pmode = 0;
    break;
  case CTRL_KEY('q'):
    exit(0);
  }
}

void ProcessCollectInput(int input)
{
  switch (input) {
  case 'h':
  case 'j':
  case 'k':
  case 'l':
    MovePlayer(input);
    CollectTile(S.py, S.px);
    break;
  case '\x1b':
    S.pmode = 0;
    break;
  case CTRL_KEY('q'):
    exit(0);
  }
}

void ProcessInput(void)
{
  int input = getch();

  switch (S.pmode) {
  case 0:
    ProcessNormalInput(input);
    break;
  case 1:
    ProcessBreakInput(input);
    break;
  case 2:
    ProcessPlaceInput(input);
    break;
  case 3:
    ProcessCollectInput(input);
    break;
  }
}

float Diff(float a, float b)
{
  return MAX(a-b, b-a);
}

double DeltaTime(struct timespec a, struct timespec b)
{
  struct timeval D = {a.tv_sec-b.tv_sec, a.tv_nsec-b.tv_nsec};
  return D.tv_sec*1000.0 + D.tv_usec/1e6f;
}

void GenMap(void)
{
  float scale = 1/2.0;
  for (int i = 0; i < MAPHEIGHT; i++) {
    for (int j = 0; j < MAPWIDTH; j++) {
      float hash = Hashf(Hash(Hash(i*scale, j*scale), 0), 0xF9B31A00);
      if (Diff(hash, 0.9)<0.01) {
        S.map[i][j] = TREE;
      } else if (Diff(hash, 0.8)<0.01) {
        S.map[i][j] = ROCK;
      } else if (Diff(hash, 0.5)<0.01) {
        S.map[i][j] = BUSH;
      } else if (Diff(hash, 0.25)<0.01) {
        S.map[i][j] = PEBBLE;
      } else if (Diff(hash, 0.15)<0.01) {
        S.map[i][j] = STICK;
      }
    }
  }
}

void CastLight(struct state *s, int angle, int radius) {
  static const char tile_trprn[] = { 1, 0, 0, 1, 1, 0, 0};
  static const int ttlen = sizeof(tile_trprn)/sizeof(char);
  int dx = angle;
	int dy = angle + 256;
	if (dy > 512) {
		dy = -512 + (dy - 512);
	}

	if (dx > 256) {
		dx = 512 - dx;
	}
	if (dx < -256) {
		dx = -512 - dx;
	}
	if (dy > 256) {
		dy = 512 - dy;
	}
	if (dy < -256) {
		dy = -512 - dy;
	}

	int mx = s->px;
	int my = s->py;

	int mr = radius * radius;

	long long int sdx, sdy;

	int ddx = !dx ? 0xFFFF : MAX(0xFFFF/dx, 0xFFFF/-dx);
	int ddy = !dy ? 0xFFFF : MAX(0xFFFF/dy, 0xFFFF/-dy);
	int pwd = 0;

	int sx, sy;
	sdx = 0; sdy = 0;
	sx = dx == 0 ? 0 : (dx < 0 ? -1 : 1);
	sy = dy == 0 ? 0 : (dy < 0 ? -1 : 1);

	while (pwd < mr) {
		{
			int mdx = mx - s->px;
			int mdy = my - s->py;
			pwd = mdx * mdx + mdy * mdy;
		}
		if (sdx < sdy) {
			sdx += ddx;
			mx += sx;
		} else {
			sdy += ddy;
			my += sy;
		}
		if (mx < 0 || my < 0 || MAPWIDTH < mx || MAPHEIGHT < my)
			break;
		s->vis[my][mx] = 1;
		int t = s->map[my][mx];
		if (t < 0 || t >= ttlen || !tile_trprn[t])
			break;
	}
}
 
void UpdVis(void) {
	memset(S.vis, 0, sizeof(S.vis));
	S.vis[S.py][S.px] = 1;
	for (int i = 0; i < MAPWIDTH; i++) {
		int angle = 1024 * i / MAPWIDTH - 512;
		CastLight(&S, angle, 8);
	}
}

void InitState(void)
{
  S.px = 32;
  S.py = 32;
  S.pmode = 0;
  memset(S.map, 0, sizeof(S.map));
  memset(S.vis, 0, sizeof(S.vis));
  GenMap();
  UpdVis();
}

int main(void)
{
  char modes[] = "nbpc";
  struct timespec last, now;
  double delta, accumulated = 0.0;
  InitCurses();
  InitState();

  clock_gettime(CLOCK_MONOTONIC, &last);
  while (1) {
    clock_gettime(CLOCK_MONOTONIC, &now);
    delta = DeltaTime(now, last);
    accumulated += delta;
    last = now;
    while (accumulated>HZ(24)) {
      accumulated -= HZ(24);
      ProcessInput();
    }
    DrawMap();
    DrawPlayer();
    mvprintw(1, 1, "Y=%d,X=%d,M=%c ",S.py,S.px,modes[S.pmode]);
    mvprintw(2, 1, "WOOD=%d  ", S.pres.wood);
    mvprintw(3, 1, "STONE=%d ", S.pres.stone);
    mvprintw(4, 1, "FOOD=%d  ", S.pres.food);
  }

	return EXIT_SUCCESS;
}
