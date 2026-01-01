const WORLD_WIDTH = 64;
const WORLD_HEIGHT = 64;
const TILE_GRASS = 0;

class WORLD {
  constructor() {
    this.tiles = new Array(WORLD_WIDTH * WORLD_HEIGHT).fill(TILE_GRASS);
    this.objs = [];
    this.player = Player(32, 32, 31);
    this.mobs = [...new Array(rng32()&15)].map(_ => ({
        x: rng32()&WORLD_WIDTH-1,
        y: rng32()&WORLD_HEIGHT-1,
        state: 'wander',
        chooser: (rng32()%3==0? 'fng' : (rng32()%2==0 ? 'zmb' : 'pig')),
        health: Health(11),
      })).map(m => ({...m, sprite: m.chooser[0].toUpperCase(), damage_player: ((m.chooser=='zmb')?true:undefined)}));
  }

  tick() {
    this.mobs.forEach((m, idx, ms) => {
      const ctx = {m, idx, ms, w: this, p: this.player};
      choosers[m.chooser](ctx);
      states[m.state](ctx);
    });
  }

  mobAt(x, y) {
    return this.mobs.filter(m => Point.eq(m, {x, y}))[0] || false;
  }

  objAt(x, y) {
    return this.objs.filter(o => Point.eq(o, {x, y}))[0] || false;
  }

  place(pos) {
    if (!this.objAt(pos.x, pos.y) && !this.mobAt(pos.x, pos.y)) {
      this.objs = [...this.objs, pos];
    }
    Game.step();
  }

  unplace(pos) {
    if (this.objAt(pos.x, pos.y)) {
      this.objs = this.objs.filter(o => !Point.eq(o, pos));
    }
    Game.step();
  }
}
