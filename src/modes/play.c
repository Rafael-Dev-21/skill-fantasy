#include "skfantasy.h"

#define BLOCK_LENGTH 10

static void print_instructions(void)
{
	for (int i = 0; i < BLOCK_LENGTH; i++)
		for (int j = 0; j < BLOCK_LENGTH; j++)
			mvaddch(i, j, ' ');

	mvprintw(0, 0, "(r)egen");
	mvprintw(1, 0, "ESC back");
	mvprintw(2, 0, "hjkl move");
	mvprintw(3, 0, "(p)lace");
	mvprintw(4, 0, "(b)reak");
}

static void print_creature_stats(Creature const * const creature, int x, int y)
{
	for (int i = 0; i < BLOCK_LENGTH; i++)
		for (int j = 0; j < BLOCK_LENGTH; j++)
			mvaddch(i+y, j+x, ' ');

	mvprintw(y + 0, x + 1, "STR: %d", get_stat_value(creature, STAT_STR));
	mvprintw(y + 1, x + 1, "MBL: %d", get_stat_value(creature, STAT_MBL));
	mvprintw(y + 2, x + 1, "MND: %d", get_stat_value(creature, STAT_MND));
	mvprintw(y + 3, x + 1, "FHT: %d", get_stat_value(creature, STAT_FHT));
	mvprintw(y + 4, x + 1, "HRT: %d", get_stat_value(creature, STAT_HRT));

}

int play_mode(ModeData *data)
{
	if (data->player == NULL || data->world == NULL) {
		return 1;
	}

	Direction old_dir = data->player->facing;
	Point cell = data->player->position;
	
	move_from(&cell, data->player->facing);

	Creature *it = data->world->creatures;
	while (it != NULL) {
		brains[it->brain].update(it,data->world);
		it = it->next;
	}

	draw_world(data->world, data->player->position);

	print_instructions();
	print_creature_stats(data->player, COLS-BLOCK_LENGTH-1, 0);

	int ch = getch();
	switch (ch) {
	case 'l':
	case 'j':
	case 'k':
	case 'h':
		data->player->facing = dir_from_ch(ch, data->player->facing);
		if (data->player->facing == old_dir) {
			creature_move_by(data->player, data->world);
		}
		break;
	case 'p':
		place_wall(data->world, cell);
		break;
	case 'b':
		break_wall(data->world, cell);
		break;
	case 'r':
		return 1;
	case ESC:
		free_world(data->world);
		data->world = NULL;
		data->player = NULL;
		return 0;
	}

	return 2;
}
