#ifndef _ECS_H_
#define _ECS_H_

#include <stdatomic.h>
#include <stdint.h>
#include <sys/types.h>

#define ENTITY_COUNT 256
#define SYSTEM_COUNT 64
#define ECS_ERR -1

typedef int Entity;

typedef uint64_t ComponentMask;
typedef uint64_t TagMask;

typedef enum {
  COMPONENT_NONE = 0,
  COMPONENT_POSITION = 1<<0,
  COMPONENT_VISUAL = 1<<1,
  COMPONENT_SPREAD = 1<<2
} Component;

typedef enum {
  TAG_NONE = 0,
  TAG_PLAYER = 1<<0
} Tag;

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  uint32_t glyph;
  uint32_t color;
} Visual;

typedef struct {
  float cooldown;
  float timer;
  int radius;
  int chance;
  int limit;
  int count;
} Spread;

typedef struct {
  ComponentMask components[ENTITY_COUNT];
  TagMask tags[ENTITY_COUNT];
  Position positions[ENTITY_COUNT];
  Visual visuals[ENTITY_COUNT];
  Entity entityCount;
} EcsWorld;

void EcsInit(EcsWorld *ecs);

Entity CreateEntity(EcsWorld *ecs);

void MoveSystem(EcsWorld *ecs, float dt);
void RenderSystem(EcsWorld *ecs, float dt);
void SpreadSystem(EcsWorld *ecs, float dt);

#endif
