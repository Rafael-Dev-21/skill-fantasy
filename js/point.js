const Point = (x, y, base={}) => {
  base.x = x;
  base.y = y;
  return base;
};

Point.eq = (a, b) => a.x == b.x && a.y == b.y;

Point.dist = (a, b) => ({
  get x() { return b.x - a.x },
  get y() { return b.y - a.y },
  get dist() { return Math.abs(this.x) + Math.abs(this.y) }
});
