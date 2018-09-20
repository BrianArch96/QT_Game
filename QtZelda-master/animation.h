#ifndef ANIMATION_H
#define ANIMATION_H

/**
  An Animation contains the frame of an animation, represented by QRects, it is
  up to the object containing the Animation (Probably a Sprite) to use these
  rects as source rects when drawing the current frame of animation
*/

#include <QRect>
#include <vector>

class Animation
{
public:
    Animation(double frametime, std::vector<QRect> frames);

    void tick(double delta);
    void stop();
    QRect getFrame();

private:
    double frameTimeLeft;
    double frameTimeMax;

    int currentFrameIndex;
    std::vector<QRect> frames;
};

#endif // ANIMATION_H
