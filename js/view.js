const defineCellLook = (c, w) => {
  c.style.removeProperty('background-color');
  if (w.player.x == c.x && w.player.y == c.y) {
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
};

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
        ruler_cell.upd = function(rct) {
          this.innerText = '' + (this.i + rct.start_x);
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
        ruler_cell.upd = function(rct) {
          this.innerText = '' + (this.j + rct.start_y);
        };
        this.left_ruler[j] = ruler_cell;
        for (let i = 0; i < this.w; i++) {
          let cell = document.createElement('td');
          row.appendChild(cell);
          cell.i = i;
          cell.j = j;
          cell.w = world;
          cell.upd = function(rct) {
            this.x = this.i + rct.start_x;
            this.y = this.j + rct.start_y;
            defineCellLook(this, this.w);
          };
          cell.onclick = function() {
            if (!this.w.player.isAlive) return;
            if (!this.w[this.w.player.mode]({
                x: this.x,
                y: this.y
              })) return;
            this.upd({
              start_x: this.x - this.i,
              start_y: this.y - this.j,
            });
          };
          this.cells[this.idx(i,j)]=cell;
        }
      }
      this.update({...world.player, w: WORLD_WIDTH, h: WORLD_HEIGHT});
    },
    update(grid) {
      let rct = this.rct(grid);
      this.top_ruler.forEach(r => r.upd(rct));
      this.left_ruler.forEach(r => r.upd(rct));
      this.cells.forEach(c => c.upd(rct));
    }
  };
  r.init(world);
  return r;
};
