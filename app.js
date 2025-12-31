const WORLD_WIDTH = 64;
const WORLD_HEIGHT = 64;
const TILE_GRASS = 0;

class POINT {
  constructor(x, y) {
    this.x = x;
    this.y = y;
  }
}

POINT.eq = (a, b) => a.x == b.x && a.y == b.y;

const Health = (max) => ({
  max,
  current: max,
  get hp() {
    return this.current;
  },
  set hp(val) {
    this.current = clamp(val, 0, this.max);
  },
  modify(amt) {
    this.hp += amt;
  },
  get status() {
    if (this.hp <= 0) return "dead";
    else return "alive";
  },
  get isAlive() {
    return this.hp > 0;
  },
  get maxHp() {
    return this.max;
  },
  get frac() {
    return this.hp / this.maxHp;
  }
});

class PLAYER {
  constructor(x, y, health) {
    this.position = new POINT(x, y);
    this.health = Health(health);
    this.mode = "place";
  }

  Move(dx, dy) {
    if (!this.health.isAlive) return;
    this.position.x = clamp(this.position.x + dx, 0, WORLD_WIDTH-1);
    this.position.y = clamp(this.position.y + dy, 0, WORLD_HEIGHT-1);
  }

  switchMode() {
    let old = this.mode;
    this.mode = this.mode == "place"
      ? "unplace"
      : "place";
    document.getElementById("switch-mode").innerText = `Switch to ${old} mode`;
  }
}

let seed = 0x1234567;

function rng32() {
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  return seed;
}

function hsh32(x, y) {
  let result = 0x1234567;
  result = result * 631 + x;
  result = result * 631 + y;
  result ^= result << 13;
  result ^= result >> 17;
  result ^= result << 5;
  return result;
}

function val8(x, y) {
  let ix = Math.floor(x);
  let iy = Math.floor(y);
  let fx = x - ix;
  let fy = y - iy;
  let u = smoothQuintic(fx);
  let v = smoothQuintic(fy);
  let h00 = hsh32(ix, iy)&255;
  let h10 = hsh32(ix+1, iy)&255;
  let h01 = hsh32(ix, iy+1)&255;
  let h11 = hsh32(ix+1, iy+1)&255;
  return lerp(lerp(h00, h10, u), lerp(h01, h11, u), v);
}

function val8o(x, y) {
  let xa = x;
  let ya = y;
  let a = 1.0;
  let div = 0;
  let fin = 0;
  for (let o = 0; o < 3; o++) {
    fin += (val8(xa, ya)*2-255) * a;
    div += a;
    xa *= 2;
    ya *= 2;
    a *= 0.58;
  }
  fin = fin * 0.5 + 0.5;
  return Math.floor(fin / div);
}

function hsh3d32(x, y, z) {
  let result = 0x1234567;
  result = result * 631 + x;
  result = result * 631 + y;
  result = result * 631 + z;
  result ^= result << 13;
  result ^= result >> 17;
  result ^= result << 5;
  return result;
}

function val3d8(x, y, z) {
  let ix = Math.floor(x);
  let iy = Math.floor(y);
  let iz = Math.floor(z);
  let fx = x - ix;
  let fy = y - iy;
  let fz = z - iz;
  let u = smoothQuintic(fx);
  let v = smoothQuintic(fy);
  let r = smoothQuintic(fz);
  let h000 = hsh3d32(ix, iy, iz)&255;
  let h100 = hsh3d32(ix+1, iy, iz)&255;
  let h010 = hsh3d32(ix, iy+1, iz)&255;
  let h110 = hsh3d32(ix+1, iy+1, iz)&255;
  let h001 = hsh3d32(ix, iy, iz+1)&255;
  let h101 = hsh3d32(ix+1, iy, iz+1)&255;
  let h011 = hsh3d32(ix, iy+1, iz+1)&255;
  let h111 = hsh3d32(ix+1, iy+1, iz+1)&255;
  return lerp(
    lerp(
      lerp(h000, h100, u),
      lerp(h010, h110, u),
      v),
    lerp(
      lerp(h001, h101, u),
      lerp(h011, h111, u),
      v),
    r);
}

function val3d8o(x, y, z) {
  let xa = x;
  let ya = y;
  let za = z;
  let a = 1.0;
  let div = 0;
  let fin = 0;
  for (let o = 0; o < 3; o++) {
    fin += (val3d8(xa, ya, za)*2-255) * a;
    div += a;
    xa *= 2;
    ya *= 2;
    za *= 2;
    a *= 0.58;
  }
  fin = fin * 0.5 + 0.5;
  return Math.floor(fin / div);
}

rng32(); rng32();

class WORLD {
  constructor() {
    this.tiles = new Array(WORLD_WIDTH * WORLD_HEIGHT).fill(TILE_GRASS);
    this.objs = [];
    this.player = new PLAYER(32, 32, 31);
    this.mobs = [...new Array(rng32()&15)].map(_ => ({
        x: rng32()&WORLD_WIDTH-1,
        y: rng32()&WORLD_HEIGHT-1,
        state: 'wander',
        chooser: (rng32()%2==0 ? 'zmb' : 'pig'),
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
    return this.mobs.filter(m => POINT.eq(m, {x, y}))[0] || false;
  }

  objAt(x, y) {
    return this.objs.filter(o => POINT.eq(o, {x, y}))[0] || false;
  }

  place(pos) {
    if (!this.objAt(pos.x, pos.y) && !this.mobAt(pos.x, pos.y)) {
      this.objs = [...this.objs, pos];
    }
    Game.step();
  }

  unplace(pos) {
    if (this.objAt(pos.x, pos.y)) {
      this.objs = this.objs.filter(o => !POINT.eq(o, pos));
    }
    Game.step();
  }
}

const world = new WORLD();

const states = {
  wander({m, idx, ms, w, p}) {
    switch (rng32()&3) {
    case 0: if (m.x!=0&&!w.objAt(m.x-1, m.y)) m.x--;
      break;
    case 1: if (m.x!=WORLD_WIDTH-1&&!w.objAt(m.x+1, m.y)) m.x++;
      break;
    case 2: if (m.y!=0&&!w.objAt(m.x, m.y-1)) m.y--;
      break;
    case 3: if (m.y!=WORLD_HEIGHT-1&&!w.objAt(m.x, m.y+1)) m.y++;
      break;
    }
  },
  follow({m, idx, ms, w, p}) {
    const distx = p.position.x-m.x, disty = p.position.y-m.y;
    if (m.x!=0&&distx<0&&!w.objAt(m.x-1, m.y)) m.x--;
    else if (m.x!=WORLD_WIDTH-1&&distx>0&&!w.objAt(m.x+1, m.y)) m.x++;
    else if (m.y!=0&&disty<0&&!w.objAt(m.x, m.y-1)) m.y--;
    else if (m.y!=WORLD_HEIGHT-1&&disty>0&&!w.objAt(m.x, m.y+1)) m.y++;
  },
  flee({m, idx, ms, w, p}) {
    const distx = p.position.x-m.x, disty = p.position.y-m.y;
    if (m.x!=WORLD_WIDTH-1&&distx<0&&!w.objAt(m.x+1, m.y)) m.x++;
    else if (m.x!=0&&distx>0&&!w.objAt(m.x-1, m.y)) m.x--;
    else if (m.y!=WORLD_HEIGHT-1&&disty<0&&!w.objAt(m.x, m.y+1)) m.y++;
    else if (m.y!=0&&disty>0&&!w.objAt(m.x, m.y-1)) m.y--;
  },
  attack({p}) {
    p.health.modify(-2);
  }
};

const choosers = {
  zmb({m, idx, ms, w, p}) {
    const distx = m.x - p.position.x;
    const disty = m.y - p.position.y;
    const dist = Math.abs(distx) + Math.abs(disty);
    if (dist < 2) {
      m.state = 'attack';
    } else if (dist < 6) {
      m.state = 'follow';
    } else {
      m.state = 'wander';
    }
  },
  pig({m, idx, ms, w, p}) {
    const distx = m.x - p.position.x;
    const disty = m.y - p.position.y;
    const dist = Math.abs(distx) + Math.abs(disty);
    if (dist < 6) {
      m.state = 'flee';
    } else {
      m.state = 'wander';
    }
  }
};

const defineCellLook = (c, w) => {
  c.style.removeProperty('background-color');
  if (w.player.position.x == c.x && w.player.position.y == c.y) {
    c.className = "player";
    c.innerText = "@/";
  } else if (w.mobAt(c.x, c.y)) {
    const mob = w.mobAt(c.x, c.y);
    c.className = mob.chooser;
    c.innerText = mob.sprite;
  } else if (w.objAt(c.x, c.y)) {
    c.className = "wall";
    c.innerText = "##";
  } else if (w.tiles[c.y * WORLD_WIDTH + c.x] == TILE_GRASS) {
    c.className = "grass";
    c.innerText = ",,";
    const nx = c.x / 8.0 - 0.5;
    const ny = c.y / 8.0 - 0.5;
    const sampler = val8o(nx, ny)/8.0 - 0.5;
    const sample = (val3d8o(nx, ny, sampler)&127)+128;
    const i = sample;
    c.style.backgroundColor = `rgb(${i*0.5}, ${i*0.9}, ${i*0.6})`;
  }
}

const TableView = ({w, h, world}) => {
  let r = {
    w,
    h,
    hw: Math.floor(w/2),
    hh: Math.floor(h/2),
    cells: [],
    left_ruler: [],
    top_ruler: [],
    rct({x, y, w, h}) {
      return {
        start_x: clamp(x-this.hw, 0, w-this.w),
        start_y: clamp(y-this.hh, 0, h-this.h),
        end_x: clamp(x+this.hw+1, this.w+1, w),
        end_y: clamp(y+this.hh+1, this.h+1, h),
      };
    },
    idx(i, j) {
      return j * this.w + i;
    },
    init(world) {
      this.$table = $('world');
      let top_ruler = document.createElement('tr');
      this.$table.appendChild(top_ruler);
      top_ruler.appendChild(document.createElement('td'));
      for (let i = 0; i < this.w; i++) {
        let ruler_cell = document.createElement('th');
        top_ruler.appendChild(ruler_cell);
        ruler_cell.i = i;
        ruler_cell.className = 'ruler';
        ruler_cell.upd = (rct) => {
          ruler_cell.innerText = '' + (i + rct.start_x);
        };
        this.top_ruler[i] = ruler_cell;
      }
      for (let j = 0; j < this.h; j++) {
        let row = document.createElement('tr');
        this.$table.appendChild(row);
        let ruler_cell = document.createElement('th');
        row.appendChild(ruler_cell);
        ruler_cell.j = j;
        ruler_cell.className = 'ruler';
        ruler_cell.upd = (rct) => {
          ruler_cell.innerText = '' + (j + rct.start_y);
        };
        this.left_ruler[j] = ruler_cell;
        for (let i = 0; i < this.w; i++) {
          let cell = document.createElement('td');
          row.appendChild(cell);
          cell.i = i;
          cell.j = j;
          cell.upd = (rct) => {
            cell.x = cell.i + rct.start_x;
            cell.y = cell.j + rct.start_y;
            defineCellLook(cell, world);
          }
          cell.onclick = () => {
            if (world.player.health.isAlive) {
              world[world.player.mode]({
                x: cell.x,
                y: cell.y
              });
            }
          };
          this.cells[this.idx(i,j)]=cell;
        }
      }
      this.update({...world.player.position, w: WORLD_WIDTH, h: WORLD_HEIGHT});
    },
    update(grid) {
      let rct = this.rct(grid);
      this.top_ruler.forEach(r => r.upd(rct));
      this.left_ruler.forEach(r => r.upd(rct));
      this.cells.forEach(c => c.upd(rct));
      let player_bar = '[';
      let len = +$('player-health-bar').dataset.len;
      let frac = world.player.health.frac;
      let real = len * frac;
      for (let i = 0; i < len; i++)
        player_bar += (i < real) ? '@' : '.';
      player_bar += ']';
      $setContent('player-health-bar', player_bar);
      $setContent('player-health-max', world.player.health.maxHp);
      $setContent('player-health-hp', world.player.health.hp);
      $setEnabled('respawn', !world.player.health.isAlive);
    }
  };
  r.init(world);
  return r;
}

const view = TableView({w: 25, h: 25, world});

const Game = {
  world,
  view,

  step() {
    this.world.tick();
    this.view.update({
      ...this.world.player.position,
      w: WORLD_WIDTH,
      h: WORLD_HEIGHT,
    });
  },

  handleKey(key) {
    switch (key) {
    case 'h': this.world.player.Move(-1, 0); break;
    case 'j': this.world.player.Move(0, 1); break;
    case 'k': this.world.player.Move(0, -1); break;
    case 'l': this.world.player.Move(1, 0); break;
    case ' ': world.player.switchMode(); break;
    }
    this.step();
  }
};

view.update({
  ...world.player.position,
  w: WORLD_WIDTH,
  h: WORLD_HEIGHT,
})

document.addEventListener("keydown", event => Game.handleKey(event.key));

$click("move-left", () => Game.handleKey('h'));
$click("move-down", () => Game.handleKey('j'));
$click("move-up", () => Game.handleKey('k'));
$click("move-right", () => Game.handleKey('l'));
$click("switch-mode", () => Game.handleKey(' '));

$click('respawn', () => {
  Game.world.player = new PLAYER(32, 32, 31);
  Game.step();
});
