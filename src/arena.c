#include "arena.h"
#include <string.h>
#include <assert.h>

ArenaStatus initArena(Arena *arena, void *ptr, size_t cap)
{
  if (!ptr || !cap) {
    return ARENA_NULL_ERROR;
  }
  arena->pointer = ptr;
  arena->capacity = cap;
  arena->length = 0;
  return ARENA_OK;
}
void clearArena(Arena *arena)
{
  arena->length = 0;
}
ArenaStatus ArenaAlloc(Arena *arena, size_t size, void **out)
{
  if (!out) {
    return ARENA_OUT_NULL_ERROR;
  }
  size = (size + 7) & ~7;
  if (size > arena->capacity - arena->length) {
    return ARENA_FULL_ERROR;
  }
  *out = (uint8_t*)arena->pointer + arena->length;
  arena->length += size;
  return ARENA_OK;
}
ArenaStatus ArenaAllocZ(Arena *arena, size_t size, void **out) {
  ArenaStatus err = ArenaAlloc(arena, size, out);
  if (err != ARENA_OK) {
    return err;
  }
  memset(*out, 0, size);
  return ARENA_OK;
}
size_t ArenaCapacity(const Arena *arena)
{
  return arena->capacity;
}
size_t ArenaLength(const Arena *arena)
{
  return arena->length;
}
bool ArenaEmpty(const Arena *arena)
{
  return arena->length == 0;
}
bool ArenaFull(const Arena *arena)
{
  return arena->length >= arena->capacity;
}

size_t ArenaMark(const Arena *arena)
{
  return ArenaLength(arena);
}

void ArenaRestore(Arena *arena, size_t mark)
{
  if (mark > arena->length)
    return;
  arena->length = mark;
}

ArenaStatus initSubArena(Arena *arena, SubArena *sub, size_t cap)
{
  sub->mark = ArenaMark(arena);
  void *ptr;
  int err;
  if ((err = ArenaAlloc(arena, cap, &ptr)) != ARENA_OK) {
    return err;
  }
  return initArena((Arena*)sub, ptr, cap);
}

void clearSubArena(Arena *arena, SubArena *sub)
{
  clearArena((Arena*)sub);
  ArenaRestore(arena, sub->mark);
}

void ArenaErrStr(char *buf, size_t len, ArenaStatus err, Arena *arena)
{
  if (arena == NULL)
  {
    strncpy(buf, "Arena is null!", len);
  } else {
    switch (err) {
    case ARENA_OK:
      strncpy(buf, "All ok!", len);
      break;
    case ARENA_FULL_ERROR:
      strncpy(buf, "Arena is full!", len);
      break;
    case ARENA_NULL_ERROR:
      strncpy(buf, "Arena buffer is null!", len);
      break;
    case ARENA_OUT_NULL_ERROR:
      strncpy(buf, "Output pointer is null!", len);
      break;
    }
  }
}
