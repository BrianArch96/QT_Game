#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QGraphicsView>
#include <QPainter>
#include <map>
#include <string>
#include "gamestate.h"

class GameEngine
{

public:
    explicit GameEngine();

    void render(QPainter *painter);
    void tick();

    void addGameState(std::string name, GameState *state);
    void changeGameState(std::string name);

private:

    std::map<std::string, GameState*> initMap();

    std::map<std::string, GameState*> gameStates;
    GameState *currentState;

    // The id of the previously consumed message, to make messages only take
    // effect once
    int consumedMessageId;

    int fadeDirection;      // Will be 0 (Not fading)1 (fadeOut) or -1 (fadeIn)
    double blackValue;
};

#endif // GAMEENGINE_H
