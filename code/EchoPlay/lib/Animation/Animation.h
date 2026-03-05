#pragma once

#include <SimpleSoftTimer.h>
#include <Screen.h>
#include <vector>

using namespace HolisticSolutions;

typedef struct sFrame
{
    uint8_t image[16][16];
    int duration;
} tFrame;

class Animation
{
private:
    int frameAmount;
    int currentFrame;
    int framesWaited;
    bool finished;
    bool loop;
    std::vector<tFrame> frames;
    enum RenderState
    {
        RENDER_INIT,
        RENDER_UPDATE,
        RENDER_DONE
    };
    RenderState renderState = RENDER_INIT;
    RenderState singleRenderState = RENDER_INIT;

    SimpleSoftTimer nextFrameTimer{15};

public:
    Animation(tFrame animation[], int size, bool loopEnabled);

    bool Render(Screen screen);

    void RenderFrame(int frameIndex);

    void Reset();
};