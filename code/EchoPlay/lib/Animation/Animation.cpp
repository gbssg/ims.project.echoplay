#include "Animation.h"
#include <Screen.h>
#include <SimpleSoftTimer.h>

Animation::Animation(tFrame animation[], int size, bool loopEnabled)
{
    loop = loopEnabled;
    frames.resize(size);
    for (int i = 0; i < size; i++)
    {
        frames[i] = animation[i];
    }
    frameAmount = size;
    currentFrame = 0;
    framesWaited = 0;
    renderState = RENDER_INIT;
}

bool Animation::Render(Screen screen)
{
    switch (renderState)
    {
    case RENDER_INIT:
        nextFrameTimer.start(15);
        renderState = RENDER_UPDATE;
        framesWaited = 0;
        currentFrame = 0;
        break;

    case RENDER_UPDATE:
        if (nextFrameTimer.isTimeout())
        {
            if (framesWaited >= frames[currentFrame].duration)
            {
                currentFrame++;
                framesWaited = 0;

                if (currentFrame >= frameAmount)
                {
                    if (loop)
                    {
                        currentFrame = 0;
                    }
                    else
                    {
                        renderState = RENDER_DONE;
                        return true;
                    }
                }
            }
            else
            {
                framesWaited++;
            }

            screen.drawImage(frames[currentFrame].image);
            screen.update();
            nextFrameTimer.restart();
        }
        break;

    case RENDER_DONE:
        return true;
    }

    return false;
}

void Animation::Reset()
{
    currentFrame = 0;
    framesWaited = 0;
    renderState = RENDER_INIT;
}