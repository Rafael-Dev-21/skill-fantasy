#include <common.h>
#include <entity.h>

struct entity *create_entity(struct position start_pos, char ch, int color)
{
  struct entity *entity = calloc(1, sizeof(*entity));

  if (entity != NULL)
  {
    entity->pos.y = start_pos.y;
    entity->pos.x = start_pos.x;
    entity->ch = ch;
    entity->color = color;
  }

  return entity;
}

void free_entity(struct entity *entity)
{
  free(entity);
}

void move_entity(struct entity *entity, struct position new_pos)
{
  entity->pos.y = new_pos.y;
  entity->pos.x = new_pos.x;
}
