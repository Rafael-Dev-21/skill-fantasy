#include <common.h>
#include <game.h>
#include <colors.h>
#include <draw.h>

void setup_game(struct game *game)
{
	game->map = create_map();
	struct position start_pos = setup_map(game->map);

	game->player = create_entity(start_pos, '@', SKPAIR_PLAYER);
	game->current_input = -1;
}

void update_game(struct game *game)
{
	struct position new_pos = { game->player->pos.y, game->player->pos.x };

	switch (game->current_input) {
	case 'k':
		new_pos.y -= 1;
		break;
	case 'j':
		new_pos.y += 1;
		break;
	case 'h':
		new_pos.x -= 1;
		break;
	case 'l':
		new_pos.x += 1;
		break;
	default:
		break;
	}
	if (new_pos.y >= 0 && new_pos.y < MAP_HEIGHT && new_pos.x >= 0 && new_pos.x < MAP_WIDTH)
	if (game->map[new_pos.y][new_pos.x].walkable)
		move_entity(game->player, new_pos);
}

void next_input(struct game *game)
{
	game->current_input = getch();
}

void game_loop(struct game *game)
{
	while (game->current_input != 'q') {
		update_game(game);
		draw_game(game);
		next_input(game);
  }
}

void close_game(struct game *game)
{
	draw_close();
	free_entity(game->player);
	free_map(game->map);
}
