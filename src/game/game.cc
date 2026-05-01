#include "game.hh"

void Object::move(Game& g, int dx, int dy, int w, int h)
{
  int nx = std::clamp(x+dx, 0, w-1);
  int ny = std::clamp(y+dy, 0, h-1);
  Object& o = g.objAt(nx, ny);
  if (g.objects.has(o.handle) && o != *this && o.solid) {
    if (o.health != -1) {
      o.health = std::clamp(o.health-attack, 0, 127);
    }
    if (o.health == 0) {
      kill(g, o.handle);
    }
    return;
  }
  g.map.get(x, y) = {};
  g.map.get(nx, ny) = handle;
  x = nx;
  y = ny;
}
void Object::kill(Game& g, const ObjectHandle& h)
{
  if (!g.objects.has(h) || h == handle) return;
  Object& o = g.objects.get(h);
  int amt = o.wood;
  wood = std::clamp(wood + amt, 0, 999);
  g.map.get(o.x, o.y) = {};
  g.objects.remove(h);
}
