const world = new WORLD();

const view = TableView({w: 25, h: 25, world});

const Game = {
  world,
  view,

  step() {
    this.world.tick();
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

eventBus.on('player.moved', ({newPos}) => {
  view.update({
    ...newPos,
    w: WORLD_WIDTH,
    h: WORLD_HEIGHT
  });
});

eventBus.on('player.healthChanged', ({fracHp, maxHp, newHp, who}) => {
  const barLen = +$('player-health-bar').dataset.len;
  $setContent('player-health-bar', '[' + '@'.repeat(barLen * fracHp).padEnd(barLen, '.') + ']');
  $setContent('player-health-max', maxHp);
  $setContent('player-health-hp', newHp);
  $setEnabled('respawn', !who.isAlive);
});

view.update({
  ...world.player,
  w: WORLD_WIDTH,
  h: WORLD_HEIGHT,
});

world.player.hp -= 1;
world.player.hp += 1;

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
