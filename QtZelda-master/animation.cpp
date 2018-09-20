#include "animation.h"
#include "globals.h"

Animation::Animation(double frameTime, std::vector<QRect> frames) :
    frameTimeMax(frameTime),
    frameTimeLeft(frameTime),
    currentFrameIndex(0),
    frames(frames)
{
}

void Animation::tick(double delta)
{
    // Decrease the current frame's timer
    frameTimeLeft -= delta;

    if (frameTimeLeft < 0) {
        // Advance the current frame by the appropriate amount
        currentFrameIndex += (ABS(frameTimeLeft) / frameTimeMax) + 1;

        // Wrap the current frame back around
        if (currentFrameIndex >= frames.size())
            currentFrameIndex %= frames.size();

        //Change the frame time left to the appropriate value
        frameTimeLeft = frameTimeMax - fmod(frameTimeLeft, frameTimeMax);
    }
}

void Animation::stop()
{
    frameTimeLeft = frameTimeMax;
    currentFrameIndex = 0;
}

QRect Animation::getFrame()
{
    return frames[currentFrameIndex];
}
