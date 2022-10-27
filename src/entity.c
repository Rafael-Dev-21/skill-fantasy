#include <entity.h>
#include <stdlib.h>

EntityPtr createEntity(Position startPos, char ch, int color)
{
  EntityPtr entity = calloc(1, sizeof(Entity));

  if (entity != NULL)
  {
    entity->pos.y = startPos.y;
    entity->pos.x = startPos.x;
    entity->ch = ch;
    entity->color = color;
  }

  return entity;
}

void freeEntity(EntityPtr entity)
{
  free(entity);
}

void moveEntity(EntityPtr entity, Position newPos)
{
  entity->pos.y = newPos.y;
  entity->pos.x = newPos.x;
}
