/**
 * skfantasy -- ASCII survival game
 * Copyright (C) 2023 Rafael-Dev-21
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * Includes
 */

#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#include <skfantasy.h>

/**
 * Main
 */

int main(int argc, char **argv)
{
	position_t playerPos = {10, 20};

	int playerSpeed = 1;

	position_t levelPos = {5, 5};

	level_t *level = newLevel(levelPos, 20, 20);

	time_t last = time(NULL);

	struct timespec dt;

	long long fps = 0;

	int input = 0;

	initCurses();

	while (1) {
		input = getch();

		position_t lastPlayerPos = playerPos;

		if (input == 'q')
			break;

		switch (input) {
		case 'h':
			playerPos.x -= playerSpeed;
			break;
		case 'j':
			playerPos.y += playerSpeed;
			break;
		case 'k':
			playerPos.y -= playerSpeed;
			break;
		case 'l':
			playerPos.x += playerSpeed;
			break;
		}

		mvaddch(lastPlayerPos.y, lastPlayerPos.x, ' ');

		drawLevel(level);

		mvaddch(playerPos.y, playerPos.x, 'o');

		mvprintw(1, 1, "FPS: %lld", fps);
                mvprintw(2, 1, "%c", input);

		refresh();

		 dt.tv_nsec = FRAMES - (int)(difftime(time(NULL), last) * NSEC);

                if (dt.tv_nsec > FRAMES)
                        nanosleep(&dt, NULL);

		fps = NSEC / dt.tv_nsec;

                last = time(NULL);
	}

	freeLevel(level);
	endCurses();

	return 0;
}
