#include <common.h>
#include <game.h>
#include <colors.h>

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
		next_input(game);
  }
}

void close_game(struct game *game)
{
	free_entity(game->player);
	free_map(game->map);
}
