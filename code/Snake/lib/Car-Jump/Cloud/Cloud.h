#pragma once

#include <vector>
#include <Screen.h>
#include <SimpleSoftTimer.h>
#include <EchoPlay.h>

using namespace HolisticSolutions;

class Cloud
{
private:
    int YRange;

public:
    tPoint CloudPos;

    int CloudMoveTimeMin = 80;
    int CloudMoveTimeMax = 220;

    int MoveTimerSpeed;

    SimpleSoftTimer MoveTimer{0};
    SimpleSoftTimer SpawnTimer{0};

    bool Active = true;

    int Width;

    std::vector<uint8_t> CloudSprite;

    Cloud(int width, int yRange, std::vector<uint8_t> nextCloudSprite);

    void SetPosition(int x, int y);

    void ResetPosition();

    void SetMoveTimer(int newMovetimer);

    void SetMoveTimerWDifficulty(int difficulty);

    void MoveCloudLeft();

    void drawCloud(Screen &screen);
};