#ifndef ENTITY_H
#define ENTITY_H

/**
 * The Entity class, which all entities in the game will inherit from
 *
 * The player, enemies, items etc. in the game screen will all be Entities
 *
 * Entities will be drawn and updated once per frame, and must belong to a
 * GameState (be in the vector `entities` in a GameState)
 */

#include <QPainter>
#include <QPixmap>
#include <string>

#include "animation.h"

class Entity
{
public:
    Entity(std::string imgFileName);
    Entity(std::string imgFileName, float w, float h);
    ~Entity();

    enum EntityType { PLAYER, ENEMY, STATIC };

    virtual void render(QPainter *painter);
    virtual void tick() = 0;
    virtual EntityType getType() = 0;

    void setPos(float x, float y);
    void getPos(float *x, float *y);

private:
    QPixmap *img;

protected:
    float posX = 0, posY = 0;
    float width, height;
    float rotation = 0;

    Animation *animation;
};

#endif // ENTITY_H
