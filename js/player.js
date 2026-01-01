const Player = (x, y, health, base={}) => {
  base = Point(x, y, base);
  base = Health(health, base);
  base.mode = 'place';
  base.move = (dx, dy) => {
    if (!base.isAlive) return false;
    base.x = clamp(base.x+dx, 0, WORLD_WIDTH-1);
    base.y = clamp(base.y+dy, 0, WORLD_HEIGHT-1);
    return true;
  };
  base.toggleMode = () => {
    let old = base.mode;
    base.mode = (old==='place')
      ? 'unplace'
      : 'place';
    $setContent('switch-mode', `Switch to ${old} mode`);
  };
  return base;
};
