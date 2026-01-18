#include "game.h"
#include "memory.h"
#include "vec.h"
#include "chain.h"
#include "model.h"
#include "render.h"
#include "surface.h"
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define FPS 30

uint32_t display[DISPLAY_WIDTH * DISPLAY_HEIGHT];
static int display_dirty = 0, mouseX = 0, mouseY = 0;
static Chain worm;

static Surface dst;
static Surface plr;
static Surface grd;

const static uint32_t plrSpr[] = {
  0, 0, RED, 0, 0,
  0, 0, RED, 0, 0,
  0, RED, 0, RED, 0,
  RED, 0, RED, 0, RED,
  0, RED, 0, RED, 0
};

static uint32_t grdTl[7*7];

static uint32_t getGroundColor(int x, int y)
{
  unsigned int h = (unsigned int)(x * 374761393 + y * 668265263);
  h = (h ^ (h >> 13)) * 1274126177;
  int brightness = (h % 30);
  return 0xFF004400 | (brightness << 8);
}

Model pose;

Game Game_init(void)
{
  v2 origin = { DISPLAY_WIDTH /2.0, DISPLAY_HEIGHT /2.0 };
  display_dirty = 1;
  Chain_init(&worm, origin, 48, 21, M_PI/8);
  Model_init(&pose);
  Model_load(&pose, "data/diablo3_pose.obj");
  for (int i = 0; i < 7; i++)
    for (int j = 0; j < 7; j++)
      grdTl[i * 7 + j] = getGroundColor(j, i);
  Surface_init(&dst, DISPLAY_WIDTH, DISPLAY_HEIGHT, display, DISPLAY_WIDTH);
  Surface_init(&plr, 5, 5, plrSpr, 5);
  Surface_init(&grd, 7, 7, grdTl, 7);
  clearDisplay(BLACK);
  Game g = {
    FPS,
    display,
    DISPLAY_WIDTH,
    DISPLAY_HEIGHT
  };
  return g;
}

static v2 ortho(const v3 v)
{
  return (v2){
    (v.x+1.f) * DISPLAY_WIDTH/2,
    (1.f-v.y) * DISPLAY_HEIGHT/2
  };
}

static v2 cabinet(const v3 v)
{
  float cos45 = 0.7071f;
  float sin45 = 0.7071f;
  float depthScale = 0.5f;
  v2 r;
  r.x = v.x + (v.y * cos45 * depthScale);
  r.y = v.z - (v.y * sin45 * depthScale);

  r.x *= 64.0f;
  r.y *= 64.0f;
  r.x += DISPLAY_WIDTH/2;
  r.y += DISPLAY_HEIGHT/2;
  return r;
}

void Game_update(void)
{
  v2 target =  {mouseX, mouseY};
  v2 diff = v2_sub(target, worm.joints[0]);
  float dist = v2_len(diff);
  if (dist > 1.0f) {
    float moveDist = (dist > 12.0f) ? 12.0f : dist;
    v2 next = v2_add(worm.joints[0], v2_with_len(diff, moveDist));
    Chain_resolve(&worm, next);
    display_dirty = 1;
  }

  if (display_dirty) {
    display_dirty = 0;
    for (int y = 0; y <= (DISPLAY_HEIGHT/7+1); y++)
      for (int x = 0; x <= (DISPLAY_WIDTH/7+1); x++)
        Surface_blit(&dst, x*7, y*7, &grd, 0, 0, 7, 7);
    Model_renderFlatRC(&pose, ortho);
    Chain_display(&worm);
    Surface_blit(&dst, (int)worm.joints[0].x, (int)worm.joints[0].y, &plr, 0, 0, 5, 5);
  }
}

void Game_mouseMove(int x, int y)
{
  mouseX = iclamp(x, 0, DISPLAY_WIDTH-1);
  mouseY = iclamp(y, 0, DISPLAY_HEIGHT-1);
}
