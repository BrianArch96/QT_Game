#ifndef STATEDUNGEON_H
#define STATEDUNGEON_H

#include "gamestate.h"
#include "dungeondata.h"

class StateDungeon : public GameState
{
public:
    StateDungeon();
    StateDungeon(DungeonData *dungeonData);
    ~StateDungeon();

    void tick() override;
    void render(QPainter *painter) override;

private:
    enum GameplayState {
        WAITING,
        PLAYER_MOVE,
        ENEMY_MOVE,
        FADE_TO_BLACK,
        FADE_FROM_BLACK
    };
    GameplayState gameplayState;

    DungeonData *dungeonData;
};

#endif // STATEDUNGEON_H
