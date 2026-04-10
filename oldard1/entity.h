#ifndef ENTITY_H
#define ENTITY_H

#include "position.h"

struct entity {
	struct position pos;
	char ch;
	int color;
};

struct entity *create_entity(struct position start_pos, char ch, int color);
void free_entity(struct entity *ent);
void move_entity(struct entity *ent, struct position new_pos);

#endif
