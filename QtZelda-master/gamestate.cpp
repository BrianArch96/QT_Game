#include "gamestate.h"
#include "entity.h"
#include <iostream>

GameState::GameState()
    : player(0)
{
}

void GameState::render(QPainter *painter)
{
    for (Entity *entity : entities)
        entity->render(painter);
}

void GameState::tick()
{
    for (Entity *entity : entities)
        entity->tick();
}

void GameState::addEntity(Entity *entity)
{
    entities.push_back(entity);

    if (entity->getType() == Entity::PLAYER)
        player = reinterpret_cast<EntityPlayer*>(entity);
}

std::string GameState::getMessage()
{
    return message;
}
