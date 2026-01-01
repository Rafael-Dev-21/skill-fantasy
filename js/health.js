const Health = (max, base={}) => {
  let maxHp = max;
  let currentHp = max;
  Object.defineProperty(base, 'hp', {
    get: () => currentHp,
    set: (val) => {
      const oldHp = currentHp;
      currentHp = clamp(val, 0, base.maxHp);
      const newHp = currentHp;
      if (oldHp != newHp) {
        if (newHp == 0) {
          eventBus.emit('health.died', {
            who: base
          });
        }
        eventBus.emit('health.changed', {
          who: base,
          oldHp,
          newHp,
          maxHp
        });
      }
    },
  });
  Object.defineProperty(base, 'maxHp', {
    get: () => maxHp,
  });
  Object.defineProperty(base, 'aliveStatus', {
    get: () => (base.hp<=0) ? 'dead' : 'alive',
  });
  Object.defineProperty(base, 'isAlive', {
    get: () => base.hp > 0,
  });
  Object.defineProperty(base, 'fracHp', {
    get: () => base.hp / base.maxHp,
  });
  base.modifyHp = (amt) => base.hp += amt;
  return base;
};
