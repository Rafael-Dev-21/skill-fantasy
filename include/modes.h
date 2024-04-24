#ifndef MODES_H
#define MODES_H

#include "position.h"
#include "map.h"
#include "creature.h"

typedef struct ModeData {
	Creature *player;
	Map *map;
	char version[256];
} ModeData;

typedef struct Mode *ModeFunc(ModeData*);

typedef struct Mode {
	ModeFunc *next;
} Mode;

Mode *start_mode(ModeData *data);
Mode *generate_mode(ModeData *data);
Mode *play_mode(ModeData *data);

#endif
