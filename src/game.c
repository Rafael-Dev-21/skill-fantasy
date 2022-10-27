#include <game.h>
#include <skfantasy.h>

void setupGame(GamePtr game)
{
  Position startPos = {10, 20};

  // Yes, I *do* know the evils of hardcoding
  game->player = createEntity(startPos, '@', 5);
  game->curInput = -1;
}

void updateGame(GamePtr game)
{
  Position newPos = { game->player->pos.y, game->player->pos.x };

  switch (game->curInput)
  {
    case 'k':
      newPos.y -= 1;
      break;
    case 'j':
      newPos.y += 1;
      break;
    case 'h':
      newPos.x -= 1;
      break;
    case 'l':
      newPos.x += 1;
      break;
    default:
      break;
  }

  moveEntity(game->player, newPos);
}

void nextInput(GamePtr game)
{
  game->curInput = getch();
}

void GameLoop(GamePtr game)
{
  while (game->curInput != 'q')
  {
    updateGame(game);
    nextInput(game);
  }
}

void CloseGame(GamePtr game)
{
  freeEntity(game->player);
}
