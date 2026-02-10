#pragma once

#include <EchoPlay.h>
#include <SimpleSoftTimer.h>
#include <vector>
#include "../SharedEnums.h"

using namespace HolisticSolutions;

class Destroyable
{
private:
    tPoint ObjectPos;
    std::vector<uint8_t> ObjectSprite;
    int Width;
    bool Destroyed = false;

public:
    Destroyable(std::vector<uint8_t> newSprite, int width);
    void SetPosition(int x, int y);
    std::vector<uint8_t>
    GetSprite();
};