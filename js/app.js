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
  let color = `rgb(${255*(1-fracHp)}, ${255*fracHp}, 0)`;
  $('player-health-bar').style.color = color;
  $('player-health-hp').style.color = color;
  $setContent('player-health-max', maxHp);
  $setContent('player-health-hp', newHp);
  $setEnabled('respawn', newHp <= 0);
});

eventBus.on('world.tick', ({player, w, h}) => {
  view.update({
    x: player.x,
    y: player.y,
    w,
    h
  });
});

eventBus.on('player.modeChanged', ({oldMode, newMode}) => {
  $setContent('switch-button-mode-name', oldMode);
  $setContent('info-mode-name', newMode);
});

view.update({
  ...world.player,
  w: WORLD_WIDTH,
  h: WORLD_HEIGHT,
});

setInterval(() => Game.step(), 1000/5);

world.player.hp -= 1;
world.player.hp += 1;

document.addEventListener("keydown", event => Game.handleKey(event.key));

$click("move-left", () => Game.handleKey('h'));
$click("move-down", () => Game.handleKey('j'));
$click("move-up", () => Game.handleKey('k'));
$click("move-right", () => Game.handleKey('l'));
$click("switch-mode", () => Game.handleKey(' '));

$click('respawn', () => {
  Game.world.player.hp = Game.world.player.maxHp;
  Game.world.player.x = 32;
  Game.world.player.y = 32;
  Game.step();
});

const Saver = (game, bus, localStorage) => {
  function saveGame() {
    let saveFile = {};
    saveFile.player = {
      x: game.world.player.x,
      y: game.world.player.y,
      hp: game.world.player.hp,
    };
    saveFile.mobs = game.world.mobs;
    saveFile.objs = game.world.objs;

    let saveCode = JSON.stringify(saveFile);
    localStorage.setItem('save', saveCode);
  }

  function loadGame() {
    const saveCode = localStorage.getItem('save');
    if (!saveCode) return;
    const saveFile = JSON.parse(saveCode);
    game.world.player.x = saveFile.player.x;
    game.world.player.y = saveFile.player.y;
    game.world.player.hp = saveFile.player.hp;
    game.world.objs = saveFile.objs;
    game.world.mobs = saveFile.mobs.map(m => {
      const h = m.health;
      m.health = Health(h.maxHp);
      m.health.hp = h.hp;
      return m;
    });
    bus.emit("game.loaded", game);
  }

  return {
    saveGame,
    loadGame
  };
};

const saver = Saver(Game, eventBus, localStorage);

eventBus.on('world.tick', () => saver.saveGame());
eventBus.on('game.loaded', game => {
  game.view.update({
    x: game.world.player.x,
    y: game.world.player.y,
    w: WORLD_WIDTH,
    h: WORLD_HEIGHT,
  });
});

saver.loadGame();
