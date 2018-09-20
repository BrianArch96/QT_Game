#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <string>
#include "entity.h"
#include "entityplayer.h"

class GameState
{

public:
    GameState();

    virtual void render(QPainter *painter);
    virtual void tick();

    void addEntity(Entity *entity);

    std::string getMessage();

protected:
    std::vector<Entity*> entities;

    // keep a reference to the player
    EntityPlayer *player;

    // A message which can be passed up to the GameEngine which updates this
    std::string message;
};

#endif // GAMESTATE_H
