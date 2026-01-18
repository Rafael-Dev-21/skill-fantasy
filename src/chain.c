#include "chain.h"
#include "vec.h"
#include "util.h"
#include "render.h"

void
Chain_init(Chain * restrict self, const v2 origin, const size_t jointCount,
    const int linkSize, const float angleConstraint)
{
  self->linkSize = linkSize;
  self->count = jointCount;
  self->angleConstraint = angleConstraint;
  self->angles[0] = 0.0f;
  self->joints[0] = origin;
  for (size_t i = 1; i < jointCount; i++) {
    self->joints[i] = v2_add(self->joints[i-1], (v2){0, linkSize});
    self->angles[i] = 0.0f;
  }
}
void
Chain_resolve(Chain * restrict self, const v2 pos)
{
  self->angles[0] = v2_angle(v2_sub(pos, self->joints[0]));
  self->joints[0] = pos;
  for (size_t i = 1; i < self->count; i++) {
    float curAngle = v2_angle(v2_sub(self->joints[i-1], self->joints[i]));
    self->angles[i] = constrainAngle(curAngle, self->angles[i-1], self->angleConstraint);
    self->joints[i] = v2_sub(self->joints[i-1],
        v2_polar(self->angles[i], self->linkSize));
  }
}
void
Chain_fabrikResolve(Chain * restrict self,
    const v2 pos, const v2 anchor)
{
  self->joints[0] = pos;
  for (size_t i=1; i<self->count; i++)
    self->joints[i] = constrainDistance(self->joints[i], self->joints[i-1], self->linkSize);

  self->joints[self->count-1] = anchor;
  for (int i=(int)self->count-2; i>=0; i--)
    self->joints[i] = constrainDistance(self->joints[i], self->joints[i+1], self->linkSize);
}

void
Chain_display(const Chain * restrict self)
{
  for (size_t i = 0; i < self->count-1; i++) {
    v2 start = self->joints[i];
    v2 end = self->joints[i+1];
    strokeLine((int)start.x, (int)start.y,
        (int)end.x, (int)end.y, WHITE);
  }

  for (size_t i = 0; i < self->count; i++) {
    v2 joint = self->joints[i];
    strokeCircle((int)joint.x, (int)joint.y, 10, WHITE);
  }
}
