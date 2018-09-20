#include "statedungeon.h"
#include "globals.h"
#include <iostream>
#include <string>

StateDungeon::StateDungeon()
    : GameState(),
      gameplayState(WAITING)
{
}

StateDungeon::StateDungeon(DungeonData *dungeonData)
    : GameState(),
      gameplayState(WAITING)
{
    this->dungeonData = dungeonData;
}

StateDungeon::~StateDungeon()
{
    delete this->dungeonData;
}

void StateDungeon::tick()
{
    GameState::tick();

    // Get message from player
    message = player->getMessage();

    // Handle gameplay based on state
    switch (gameplayState) {

    case WAITING:
        if (player->getMoving())
            gameplayState = PLAYER_MOVE;
        break;

    case PLAYER_MOVE:
        if (!player->getMoving())
            gameplayState = ENEMY_MOVE;
        break;

    case ENEMY_MOVE:
        // stub which just reverts back to the player's turn for now
        gameplayState = WAITING;
        player->setCanMove(true);
        break;
    }
}

void StateDungeon::render(QPainter *painter)
{
    // Draw the background
    painter->drawPixmap(0, 0, *dungeonData->getBg());

    // Draw special tiles, ones that dynamically change like levers, doors etc.
    DungeonData::TileType *tiles;
    int w, h;
    dungeonData->getData(&tiles, &w, &h);

    // Draw special tiles
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            QPixmap *texture = DungeonData::getTileTexture(tiles[i + j * w]);
            if (texture != 0)
                painter->drawPixmap(
                    i * globals::CELL_SIZE,
                    j * globals::CELL_SIZE,
                    globals::CELL_SIZE,
                    globals::CELL_SIZE,
                    *texture);
        }
    }

    // Do the rest of the state's drawing
    GameState::render(painter);
}
