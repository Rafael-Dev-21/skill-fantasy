#ifndef GAME_OBJECT_HH
#define GAME_OBJECT_HH

#include "../core/handlearray.hh"

using ObjectHandle = Handle;

struct Object {
  enum class Kind {
    Player,
    Tree,
    Cursor,
    Mark,
    Wood
  } kind;
  int x;
  int y;
  int tile_id;
  bool solid;
  bool visible;
  int health{-1}, attack, wood;
  ObjectHandle handle{};

  bool operator==(const Object& o) const { return handle == o.handle; }
  bool operator!=(const Object& o) const { return handle != o.handle; }
};
