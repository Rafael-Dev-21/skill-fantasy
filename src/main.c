#ifndef _WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif

#include "rng32.h"

#define UNUSED(x) ((void)(x))
#define CNTRL(x) ((x)&0x1F)

#define AQUIT() ((action_t){ .type = ACT_QUIT })
#define AMOVE(nx, ny) ((action_t){ .type = ACT_MOVE, .dx = (nx), .dy = (ny) })

#define MAX_ENTS 256
#define NO_ENT -1

typedef struct {
  enum {
    ACT_NONE,
    ACT_QUIT,
    ACT_MOVE
  } type;

  int dx;
  int dy;
} action_t;

typedef struct {
  int x[MAX_ENTS];
  int y[MAX_ENTS];
  int ch[MAX_ENTS];
  enum {
    ENT_ST_NONE,
    ENT_ST_WANDER,
    ENT_ST_COUNT
  } state[MAX_ENTS];
  unsigned mask[MAX_ENTS];
  int count;
} ents_t;

static inline
action_t do_ent_st_none(
    ents_t* ents,
    int i)
{
  return (action_t){0};
}

static inline
action_t do_ent_st_wander(
    ents_t* ents,
    int i)
{
  if ((rng32() & 0x3) < 3) {
    return (action_t){0};
  }
  return AMOVE(
      rng32()%3-1,
      rng32()%3-1);
}

static action_t (* const do_ent_st_table[ENT_ST_COUNT])(ents_t*, int) = {
  &do_ent_st_none,
  &do_ent_st_wander
};

void ents_init(ents_t *ents)
{
  ents->count = 0;
  for (int i = 0; i < MAX_ENTS; i++) {
    ents->x[i] = 0;
    ents->y[i] = 0;
    ents->ch[i] = 0;
    ents->state[i] = ENT_ST_NONE;
    ents->mask[i] = 0;
  }
}
int ents_spawn(ents_t *ents)
{
  if (ents->count >= MAX_ENTS) {
    return NO_ENT;
  }
  int i = ents->count++;
  return i;
}
void ents_despawn(ents_t *ents, int i)
{
  if (i <= NO_ENT || i >= ents->count) {
    return;
  }
  if (i == ents->count-1) {
    ents->count--;
    return;
  }
  ents->x[i] = ents->x[ents->count-1];
  ents->y[i] = ents->y[ents->count-1];
  ents->ch[i] = ents->ch[ents->count-1];
  ents->state[i] = ents->state[ents->count-1];
  ents->mask[i] = ents->mask[ents->count-1];
  ents->count--;
}

int spawn_colonist(ents_t *ents, int x, int y)
{
  int i;
  if ((i = ents_spawn(ents)) < 0)
    return i;
  ents->x[i] = x;
  ents->y[i] = y;
  ents->ch[i] = '@';
  ents->state[i] = ENT_ST_WANDER;
  ents->mask[i] = 0x0003;
  return i;
}

void draw_ents(ents_t *ents, int cam_x, int cam_y)
{
  int *x = ents->x;
  int *y = ents->y;
  int *ch = ents->ch;
  unsigned *mask = ents->mask;
  for (int i = 0; i < ents->count; i++) {
    if (~*(mask+i) & 0x3)
      continue;
    int screen_x = *(x+i) - cam_x;
    int screen_y = *(y+i) - cam_y;

    if (screen_x < 0 || screen_x >= COLS
        || screen_y < 0 || screen_y >= LINES)
      continue;
    move(screen_y, screen_x);
    addch(*(ch+i));
  }
}

static inline
void ent_act_perform(
    ents_t *ents, int i, action_t act)
{
  switch (act.type) {
  case ACT_MOVE:
    ents->x[i] += act.dx;
    ents->y[i] += act.dy;
    break;
  }
}

void update_ents(ents_t* ents)
{
  int *state = ents->state;
  unsigned *mask = ents->mask;
  for (int i = 0; i < ents->count; i++) {
    action_t act = do_ent_st_table[*(state + i)](ents, i);
    ent_act_perform(ents, i, act);
  }
}

void on_getch(action_t *act, int ch)
{
  switch (ch) {
  case CNTRL('q'):
    *act = AQUIT();
    break;
  case 'k':
    *act = AMOVE(0, -1);
    break;
  case 'j':
    *act = AMOVE(0, 1);
    break;
  case 'h':
    *act = AMOVE(-1, 0);
    break;
  case 'l':
    *act = AMOVE(1, 0);
    break;
  }
}

int main(int argc, char **argv)
{
  UNUSED(argc); UNUSED(argv);
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  nodelay(stdscr, true);

  int running = 1;
  int cam_x = COLS/2;
  int cam_y = LINES/2;

  ents_t ents;
  ents_init(&ents);

  for (int i = 0; i < 12; i++) {
    UNUSED(spawn_colonist(&ents,
        cam_x + rng32()%7 - 3,
        cam_y + rng32()%7 - 3));
  }

  while (running) {
    clear();
    draw_ents(&ents, cam_x - COLS/2, cam_y - LINES/2);
    refresh();

    action_t act = {0};
    on_getch(&act, getch());
    switch (act.type) {
    case ACT_QUIT:
      running = false;
      break;
    case ACT_MOVE:
      cam_x += act.dx;
      cam_y += act.dy;
      break;
    }
    update_ents(&ents);
    napms(15);
  }

  endwin();
  return 0;
}
