class Player {
  constructor(x, y, health) {
    // int
    this.x = x;
    // int
    this.y = y;
    // int
    this.health = health;
    // int
    this.maxHealth = health;
    // 'place' || 'unplace'
    this.mode = 'place';
    // Array<Note>
    this.notes = [];
    // Array<Alarm>
    this.alarms = [];
  }
  // (V)->int
  get hp() {
    return this.health;
  }
  // (int)->V
  set hp(newHealth) {
    let oldHealth = this.health;
    this.health = Math.max(0, Math.min(this.maxHealth, newHealth));
    eventBus.emit('player.healthChanged', {
      newHp: this.health,
      fracHp: this.fracHp,
      maxHp: this.maxHealth,
      who: this
    });
    if (this.health <= 0 && oldHealth > 0) {
      eventBus.emit('player.died', {
        fracHp: this.fracHp,
        who: this
      });
    }
  }
  // (int)->V
  modifyHp(amt) {
    this.hp += amt;
  }
  // ()->bool
  get isAlive() {
    return this.health > 0;
  }
  // ()->float
  get fracHp() {
    return this.health / this.maxHealth;
  }
  // ()->int
  get maxHp() {
    return this.maxHealth;
  }
  // (int, int)->bool
  move(dx, dy) {
    if (!this.isAlive) return false;
    let oldPos = Point(this.x, this.y);
    this.x = clamp(this.x+dx, 0, WORLD_WIDTH-1);
    this.y = clamp(this.y+dy, 0, WORLD_HEIGHT-1);
    let newPos = Point(this.x, this.y);
    eventBus.emit('player.moved', {
      oldPos,
      newPos,
      who: this
    });
    return true;
  }
  // ()->V
  toggleMode() {
    let old = this.mode;
    this.mode = (old==='place')
      ? 'unplace'
      : 'place';
    eventBus.emit('player.modeChanged', {
      oldMode: old,
      newMode: this.mode,
      who: this
    });
  }
}