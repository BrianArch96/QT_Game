#include "statecredits.h"
#include <iostream>

StateCredits::StateCredits() :
    pos(100)
{
    image.load(":End.png");
}

void StateCredits::render(QPainter *painter)
{
    GameState::render(painter);

    double clampedPos = pos;
    if (clampedPos > 0) clampedPos = 0;
    else if (clampedPos < -(image.height() - 480)) clampedPos = -(image.height() - 480);

    painter->drawPixmap(0, clampedPos, image);
}

void StateCredits::tick()
{
    GameState::tick();

    pos -= SCROLL_SPEED;
}
