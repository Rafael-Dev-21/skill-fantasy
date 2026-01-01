const world = new WORLD();

const view = TableView({w: 25, h: 25, world});

const Game = {
  world,
  view,

  step() {
    this.world.tick();
    this.view.update({
      ...this.world.player,
      w: WORLD_WIDTH,
      h: WORLD_HEIGHT,
    });
  },

  handleKey(key) {
    switch (key) {
    case 'h': this.world.player.move(-1, 0); break;
    case 'j': this.world.player.move(0, 1); break;
    case 'k': this.world.player.move(0, -1); break;
    case 'l': this.world.player.move(1, 0); break;
    case ' ': world.player.toggleMode(); break;
    }
    this.step();
  }
};

view.update({
  ...world.player,
  w: WORLD_WIDTH,
  h: WORLD_HEIGHT,
});

document.addEventListener("keydown", event => Game.handleKey(event.key));

$click("move-left", () => Game.handleKey('h'));
$click("move-down", () => Game.handleKey('j'));
$click("move-up", () => Game.handleKey('k'));
$click("move-right", () => Game.handleKey('l'));
$click("switch-mode", () => Game.handleKey(' '));

$click('respawn', () => {
  Game.world.player = PLAYER(32, 32, 31);
  Game.step();
});
