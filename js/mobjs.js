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
    const distx = p.x-m.x, disty = p.y-m.y;
    if (m.x!=0&&distx<0&&!w.objAt(m.x-1, m.y)) m.x--;
    else if (m.x!=WORLD_WIDTH-1&&distx>0&&!w.objAt(m.x+1, m.y)) m.x++;
    else if (m.y!=0&&disty<0&&!w.objAt(m.x, m.y-1)) m.y--;
    else if (m.y!=WORLD_HEIGHT-1&&disty>0&&!w.objAt(m.x, m.y+1)) m.y++;
  },
  flee({m, idx, ms, w, p}) {
    const distx = p.x-m.x, disty = p.y-m.y;
    if (m.x!=WORLD_WIDTH-1&&distx<0&&!w.objAt(m.x+1, m.y)) m.x++;
    else if (m.x!=0&&distx>0&&!w.objAt(m.x-1, m.y)) m.x--;
    else if (m.y!=WORLD_HEIGHT-1&&disty<0&&!w.objAt(m.x, m.y+1)) m.y++;
    else if (m.y!=0&&disty>0&&!w.objAt(m.x, m.y-1)) m.y--;
  },
  attack({p}) {
    p.modifyHp(-2);
  },
  idle(_) {
    // do nothing and mop here
  },
  spread({m, w, p}) {
    let rnx = rng32()&15 - 7 + m.x;
    let rny = rng32()&15 - 7 + m.y;
    let r = Point(rnx, rny);
    if (Point.eq(r, p)) return;
    if (w.mobAt(rnx, rny)) return;
    if (w.objAt(rnx, rny)) return;
    let clone = Object.assign({}, m);
    clone.x = rnx;
    clone.y = rny;
    w.mobs.push(clone);
  }
};

const choosers = {
  zmb({m, idx, ms, w, p}) {
    const distx = m.x - p.x;
    const disty = m.y - p.y;
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
    const distx = m.x - p.x;
    const disty = m.y - p.y;
    const dist = Math.abs(distx) + Math.abs(disty);
    if (dist < 6) {
      m.state = 'flee';
    } else {
      m.state = 'wander';
    }
  },
  fng({m}) {
    let r = rng32();
    let c = r & 65535;
    if (!c) {
      m.state = 'spread';
    } else {
      m.state = 'idle';
    }
  }
};
