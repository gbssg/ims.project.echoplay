#pragma once

#include <EchoPlay.h>
#include <SimpleSoftTimer.h>
#include <vector>
#include "../SharedEnums.h"

using namespace HolisticSolutions;

class PlayerPlatform
{
private:
    SimpleSoftTimer moveTimer{100};
    int moveTime;
    tPoint PlatformPos;
    std::vector<uint8_t> PlatformSprite;
    int Width;

public:
    PlayerPlatform(std::vector<uint8_t> newSprite, int width);
    void MovePlatform(bool moveLeft);
    void SetPosition(int x, int y);
    void SetMoveTimer(int newTime);
    int GetPosition(Coordinate position);
    std::vector<uint8_t> GetSprite();
    int GetWidth();
};