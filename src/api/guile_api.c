#include "guile_api.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <libguile.h>

static SCM on_tick_proc = SCM_BOOL_F;

static World *g_world;
static Creature *g_player;

static SCM skf_log(SCM msg) {
  move(5,1);
  printw("[scheme] %s",
      scm_to_locale_string(msg));

  return SCM_UNSPECIFIED;
}

static SCM skf_player_x(void)
{
  return scm_from_int(g_player->position.x);
}
static SCM skf_player_y(void)
{
  return scm_from_int(g_player->position.y);
}

bool skfantasy_api_guile_init(void)
{
  scm_t_subr q;
  SCM (*f)(void) = 0;
  SCM (*f1)(SCM) = 0;
  scm_init_guile();
  scm_c_primitive_load("./scripts/main.scm");

  assert(sizeof(scm_t_subr) == sizeof(SCM (*)(SCM))); 
  assert(sizeof(scm_t_subr) == sizeof(SCM (*)(void))); 

  f1 = skf_log;
  memcpy(&q, &f1, sizeof(scm_t_subr));
  scm_c_define_gsubr(
      "skf-log",
      1, 0, 0,
      q);

  f = skf_player_x;
  memcpy(&q, &f, sizeof(scm_t_subr));
  scm_c_define_gsubr(
      "player-x",
      0, 0, 0,
      q);
  f = skf_player_y;
  memcpy(&q, &f, sizeof(scm_t_subr));
  scm_c_define_gsubr(
      "player-y",
      0, 0, 0,
      q);

  SCM init_proc =
    scm_variable_ref(
        scm_c_lookup("on-init"));

  on_tick_proc =
    scm_variable_ref(
        scm_c_lookup("on-tick"));
 
  if (scm_is_false(init_proc))
    return false;

  scm_call_0(init_proc);
  return true;
}

void skfantasy_api_guile_update(World *world, Creature *player)
{
  g_world = world;
  g_player = player;

  if (!scm_is_false(on_tick_proc))
    scm_call_0(on_tick_proc);
}
