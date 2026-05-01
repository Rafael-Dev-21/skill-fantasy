#ifndef GAME_WORLD_HH
#define GAME_WORLD_HH

#include "../core/handlearray.hh"
#include "../core/xorshift.hh"
#include "../core/geom.hh"
#include "object.hh"

#include <chrono>
#include <algorithm>

class World {
public:

  HandleVector<Object, ObjectHandle> objects;
  XorShift rng{42};
  Grid2<ObjectHandle> map;

  World(const Pt& dims) :
    map(dims.x, dims.y)
  {
    auto now = std::chrono::system_clock::now();
    auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    rng = XorShift{ static_cast<uint32_t>(now_ns.time_since_epoch().count()) };

    for (int j=0; j < map.height(); j++)
      for (int i=0; i < map.width(); i++)
        map.get(i, j) = {};
  }

  inline auto& get(const ObjectHandle& h) { return objects.get(h); }

  ObjectHandle addPlayer(int x, int y)
  {
    Object player{Object::Kind::Player, x, y, 0, true, true, 31, 2, 0};
    auto h = objects.add(player);
    map[y][x] = h;
    return h;
  }

  void spawnTree(int w, int h)
  {
    int x, y;
    do {
      x = rng.next() % w;
      y = rng.next() % h;
    } while(occupied(x, y));
    Object tree{Object::Kind::Tree, x, y, 1, true, true, 5, 0, 5};
    map[y][x] = objects.add(tree);
  }

  bool occupied(int x, int y)
  {
    return objects.has(map.get(x, y));
  }

  Object& objAt(int x, int y)
  {
    return get(map.get(x, y));
  }

  void populateTrees(int w, int h)
  {
    constexpr int TREE_NUM = 15*15*4/3;
    for (int i=0; i<TREE_NUM; i++)
      spawnTree(w, h);
  }

  bool placeWall(int x, int y)
  {
    if (occupied(x, y)) return false;
    Object wall{Object::Kind::Wood, x, y, 2, true, true, 9, 0, 1};
    map.get(x, y) = objects.add(wall);
    return true;
  }
};

struct Selection {
  ObjectHandle cursor;
  ObjectHandle mark;

  void placeCursor(World &w, int x, int y)
  {
    if (w.objects.has(cursor))
      w.objects.remove(cursor);
    Object cs{Object::Kind::Cursor, x, y, 0, false, false, -1, 0, 0};
    cursor = w.objects.add(cs);
  }

  void placeMark(World &w, int x, int y)
  {
    if (w.objects.has(mark))
      w.objects.remove(mark);
    Object mk{Object::Kind::Mark, x, y, 0, false, false, -1, 0, 0};
    mark = w.objects.add(mk);
  }

  void clearMark(World &w)
  {
    w.objects.remove(mark);
    mark = {};
  }

  void clearCursorAndMark(World &w)
  {
    w.objects.remove(mark);
    mark = {};
    w.objects.remove(cursor);
    cursor = {};
  }
};

#endif
