const Player = (x, y, health, base={}) => {
  base = Point(x, y, base);
  base = Health(health, base);
  base.mode = 'place';
  base.move = (dx, dy) => {
    if (!base.isAlive) return false;
    let oldPos = Point(base.x, base.y);
    base.x = clamp(base.x+dx, 0, WORLD_WIDTH-1);
    base.y = clamp(base.y+dy, 0, WORLD_HEIGHT-1);
    let newPos = Point(base.x, base.y);
    eventBus.emit('player.moved', {
      oldPos,
      newPos,
      who: base
    });
    return true;
  };
  base.toggleMode = () => {
    let old = base.mode;
    base.mode = (old==='place')
      ? 'unplace'
      : 'place';
    eventBus.emit('player.modeChanged', {
      oldMode: old,
      newMode: base.mode,
      who: base
    });
  };
  eventBus.on('health.changed', e => {
    if (e.who == base) {
      eventBus.emit('player.healthChanged', { ...e, fracHp: base.fracHp });
    }
  });
  eventBus.on('health.died', e => {
    if (e.who == base) {
      eventBus.emit('player.died', { ...e, fracHp: base.fracHp });
    }
  });
  return base;
};
