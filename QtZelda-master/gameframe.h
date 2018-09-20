#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <QFrame>
#include <QPixmap>
#include <QBasicTimer>
#include <QEvent>
#include "gameengine.h"

class GameFrame : public QFrame
{
public:
    GameFrame();

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    GameEngine *gameEngine;

    QColor bg;

    QBasicTimer timer;
};

#endif // GAMEFRAME_H
