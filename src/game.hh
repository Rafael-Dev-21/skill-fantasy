#pragma once

#include "handlevector.hh"
#include "xorshift.hh"
#include "geom.hh"
#include "ui.hh"

#include <algorithm>
#include <functional>

using ObjectHandle = Handle;

class Game;
struct Object {
  enum {
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

  void move(Game& g, int dx, int dy, int w, int h);
  void kill(Game& g, const ObjectHandle& h);

  bool operator==(const Object& o) const { return handle == o.handle; }
  bool operator!=(const Object& o) const { return handle != o.handle; }
};

class Game {
public:

  struct Tile {
    int glyph;
    int attr;
    int pair;
    int fg, bg;
  };

  HandleVector<Object, ObjectHandle> objects;
  std::vector<Tile> tiles;
  XorShift rng{42};
  Grid2<ObjectHandle> map;
  enum class Mode {
    Normal,
    Visual,
    InvMenu
  } mode = Mode::Normal;
  ObjectHandle cursor{};
  ObjectHandle mark{};

  Game(const Pt& dims) :
    map(dims.x, dims.y)
  {
    auto now = std::chrono::system_clock::now();
    auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    rng = XorShift{ static_cast<uint32_t>(now_ns.time_since_epoch().count()) };
    tiles = {
      { '@', A_BOLD, 1, COLOR_WHITE, COLOR_BLACK },
      { 't', 0, 2, COLOR_GREEN, COLOR_BLACK },
      { 'W', A_BOLD, 3, COLOR_YELLOW, COLOR_BLACK }
    };

    if (has_colors()) {
      start_color();
      for (auto& t : tiles)
        init_pair(t.pair, t.fg, t.bg);
    }

    for (int j=0; j < map.height(); j++)
      for (int i=0; i < map.width(); i++)
        map.get(i, j) = {};
  }

  inline auto& get(const ObjectHandle& h) { return objects.get(h); }

  void drawObj(CursesWindow& w, const ObjectHandle& h)
  {
    if (!objects.has(h)) return;
    auto& v = objects.get(h);
    auto t = tiles[v.tile_id];
    int attr = t.attr;
    if (has_colors()) attr |= COLOR_PAIR(t.pair);
    {
      int minx = std::clamp(get(cursor).x, 0, get(mark).x);
      int miny = std::clamp(get(cursor).y, 0, get(mark).y);
      int maxx = std::clamp(get(cursor).x, get(mark).x, 30);
      int maxy = std::clamp(get(cursor).y, get(mark).y, 30);
      if ((objects.has(cursor) && objects.has(mark) && v.x >= minx && v.x <= maxx && v.y >= miny && v.y  <= maxy)
          || (objects.has(cursor) && v.x == get(cursor).x && v.y == get(cursor).y))
        attr |= A_REVERSE;
    }
    CursesAttrGuard guard(w, attr);
    w.move_cursor(v.x*2, v.y);
    w.putch(t.glyph);
  }

  void drawEmpty(CursesWindow& w) {
    for (int y = 0; y < map.height(); y++) {
      for (int x = 0; x < map.width(); x++) {
        if (occupied(x, y))
          continue;
        int attr = A_BOLD;
        int minx = std::clamp(get(cursor).x, 0, get(mark).x);
        int miny = std::clamp(get(cursor).y, 0, get(mark).y);
        int maxx = std::clamp(get(cursor).x, get(mark).x, map.width());
        int maxy = std::clamp(get(cursor).y, get(mark).y, map.height());
        if ((objects.has(cursor) && objects.has(mark) && x >= minx && x <= maxx && y >= miny && y  <= maxy)
            || (objects.has(cursor) && x == get(cursor).x && y == get(cursor).y))
          attr |= A_REVERSE;

        CursesAttrGuard guard(w, attr);
        w.move_cursor(x*2, y);
        w.putch('.');
      }
    }
  }

  void drawStats(CursesWindow& w, const ObjectHandle& h)
  {
    if (!objects.has(h)) return;
    auto& v = objects.get(h);

    w.reset();
    w.move_cursor(1, 1);
    w.putstr("H = %d W = %d", v.health, v.wood);
    w.flush();
  }

  void drawAll(CursesWindow& w)
  {
    w.reset();
    drawEmpty(w);
    for (const auto& obj : objects)
      if (objects.has(obj.handle) && obj.visible)
        drawObj(w, obj.handle);
    w.flush();
  }

  ObjectHandle addPlayer(int x, int y)
  {
    Object player{Object::Player, x, y, 0, true, true, 31, 2, 0};
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
    Object tree{Object::Tree, x, y, 1, true, true, 5, 0, 5};
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

  void placeCursor(int x, int y)
  {
    if (objects.has(cursor))
      objects.remove(cursor);
    Object cs{Object::Cursor, x, y, 0, false, false, -1, 0, 0};
    cursor = objects.add(cs);
  }

  void placeMark(int x, int y)
  {
    if (objects.has(mark))
      objects.remove(mark);
    Object mk{Object::Mark, x, y, 0, false, false, -1, 0, 0};
    mark = objects.add(mk);
  }

  void clearMark()
  {
    objects.remove(mark);
    mark = {};
  }

  void clearCursorAndMark()
  {
    objects.remove(mark);
    mark = {};
    objects.remove(cursor);
    cursor = {};
  }

  void mapFnOverArea(std::function<void(ObjectHandle, int, int)> fn)
  {
    if (!objects.has(cursor))
      return;
    fn(map.get(get(cursor).x, get(cursor).y), get(cursor).x, get(cursor).y);
    if (!objects.has(mark))
      return;
    int minx = std::clamp(get(cursor).x, 0, get(mark).x);
    int miny = std::clamp(get(cursor).y, 0, get(mark).y);
    int maxx = std::clamp(get(cursor).x, get(mark).x, map.width());
    int maxy = std::clamp(get(cursor).y, get(mark).y, map.height());

    for (int y = miny; y <= maxy; y++) {
      for (int x = minx; x <= maxx; x++) {
        fn(map.get(x, y), x, y);
      }
    }
  }

  bool placeWall(int x, int y)
  {
    if (occupied(x, y)) return false;
    Object wall{Object::Wood, x, y, 2, true, true, 9, 0, 1};
    map.get(x, y) = objects.add(wall);
    return true;
  }
};
