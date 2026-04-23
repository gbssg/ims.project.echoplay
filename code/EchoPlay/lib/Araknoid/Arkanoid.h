#pragma once

#include <stdint.h>
#include <SparkFun_Qwiic_Button.h>
#include <EchoPlay.h>
#include <Screen.h>
#include <SimpleSoftTimer.h>
#include <IGame.h>
#include <vector>
#include "PlayerPlatform/PlayerPlatform.h"
#include "Ball/Ball.h"
#include "Destroyable/Destroyable.h"

using namespace HolisticSolutions;

class Arkanoid : public IGame
{
private:
    std::vector<uint8_t> PlatformSprite = {1, 1, 1, 1, 1, 1};
    const int PlatformWidth = 6;
    const int PlatformMoveTime = 50;

    PlayerPlatform ArkanoidPlatform{PlatformSprite, PlatformWidth};
    int Speed = 20;

    std::vector<Ball> Balls;

    const int MaxBalls = 15;
    const int StartBallAmount = 1;
    int BallAmount;

    std::vector<uint8_t> DestroyableSprite = {1, 1};
    int DestroyableWidth = 2;

    const int DestroyablesPerRow = 7;
    const int DestroyablesPreCollumn = 7;

    const int MaxDestroyables = 49;
    const int StartDestroyableAmount = 49;
    int DestroyableAmount;

    std::vector<Destroyable> Destroyables;

    bool PlayerWon = false;

public:
    void setup(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);
    void start(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);
    void update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);
    void end(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);
};
