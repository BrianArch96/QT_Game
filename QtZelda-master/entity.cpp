#include "entity.h"
#include <QTextItem>

Entity::Entity(std::string imgFileName)
    : img(new QPixmap)
{
    img->load(imgFileName.c_str());
    width = img->width();
    height = img->height();

    animation = 0;
}

Entity::Entity(std::string imgFileName, float w, float h)
    : img(new QPixmap)
{
    img->load(imgFileName.c_str());
    width = w;
    height = h;

    animation = 0;
}

Entity::~Entity()
{
    delete img;
}

// Draw the entity
void Entity::render(QPainter *painter)
{
    // Apply transformations to the painter
    painter->translate(posX, posY);
    painter->rotate(rotation);
    painter->translate(-width/2, -height/2);


    // Draw the entity's image
    if (animation == 0)
        painter->drawPixmap(0, 0, width, height, *img);
    else
    {
        QRect target(0, 0, width, height);
        QRect source = animation->getFrame();
        painter->drawPixmap(target, *img, source);
    }

    // Reset transformations
    painter->resetTransform();
}

// Set the entity's position
void Entity::setPos(float x, float y)
{
    posX = x;
    posY = y;
}

// Get the entity's position
void Entity::getPos(float *x, float *y)
{
    *x = posX;
    *y = posY;
}
