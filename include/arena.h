#pragma once

#include <stdbool.h>
#include <stddef.h>

#define KB(x) ((x)*1024)
#define MB(x) KB(KB((x)))
#define GB(x) KB(KB(KB((x))))

#define ArenaNew(arena, ptr) \
  ArenaAlloc((arena), sizeof(*(ptr)), (void**)&(ptr))
#define ArenaNewZ(arena, ptr) \
  ArenaAllocZ((arena), sizeof(*(ptr)), (void**)&(ptr))
#define ArenaArray(arena, ptr, n) \
  ArenaAlloc((arena), sizeof(*(ptr)) * (n), (void**)&(ptr))
#define ArenaArrayZ(arena, ptr, n) \
  ArenaAllocZ((arena), sizeof(*(ptr)) * (n), (void**)&(ptr))

typedef enum {
  ARENA_OK = 0,
  ARENA_NULL_ERROR,
  ARENA_FULL_ERROR,
  ARENA_OUT_NULL_ERROR
} ArenaStatus;

typedef struct {
  void *pointer; /* NON OWNING */
  size_t capacity;
  size_t length;
} Arena;

typedef struct {
  Arena base;
  size_t mark;
} SubArena;

ArenaStatus initArena(Arena *arena, void *ptr, size_t cap);
void clearArena(Arena *arena);
ArenaStatus ArenaAlloc(Arena *arena, size_t size, void **out);
ArenaStatus ArenaAllocZ(Arena *arena, size_t size, void **out);
size_t ArenaCapacity(const Arena *arena);
size_t ArenaLength(const Arena *arena);
bool ArenaEmpty(const Arena *arena);
bool ArenaFull(const Arena *arena);

size_t ArenaMark(const Arena *arena);
void ArenaRestore(Arena *arena, size_t mark);

ArenaStatus initSubArena(Arena *arena, SubArena *sub, size_t cap);
void clearSubArena(Arena *arena, SubArena *sub);

void ArenaErrStr(char *buf, size_t len, ArenaStatus err, Arena *arena);
