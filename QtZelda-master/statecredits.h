#ifndef STATECREDITS_H
#define STATECREDITS_H

#include "gamestate.h"
#include <QPixmap>

class StateCredits : public GameState
{
public:
    StateCredits();

    void render(QPainter *painter) override;
    void tick() override;

private:
    QPixmap image;

    double pos;

    const double SCROLL_SPEED = 0.75;
};

#endif // STATECREDITS_H

