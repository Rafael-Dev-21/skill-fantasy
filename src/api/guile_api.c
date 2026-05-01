#include "guile_api.h"

#include <stdbool.h>
#include <stdio.h>

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
  scm_init_guile();
  scm_c_primitive_load("./scripts/main.scm");

  scm_c_define_gsubr(
      "skf-log",
      1, 0, 0,
      skf_log);
  
  scm_c_define_gsubr(
      "player-x",
      0, 0, 0,
      skf_player_x);
  scm_c_define_gsubr(
      "player-y",
      0, 0, 0,
      skf_player_y);

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
