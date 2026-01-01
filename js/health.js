const Health = (max, base={}) => {
  let maxHp = max;
  let currentHp = max;
  Object.defineProperty(base, 'hp', {
    get: () => currentHp,
    set: (val) => {
      currentHp = clamp(val, 0, base.maxHp);
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
