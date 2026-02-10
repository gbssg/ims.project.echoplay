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
    PlayerPlatform ArkanoidPlatform{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 16};
    int Speed = 20;

    std::vector<Ball> Balls = {
        Ball(),
        Ball(),
        Ball(),
        Ball(),
        Ball(),
        Ball(),
        Ball(),
        Ball(),
        Ball(),
        Ball(),
        Ball(),
        Ball(),
        Ball(),
        Ball()};

    Destroyable Object1{{1, 1, 1, 1}, 4};

    std::vector<Destroyable *> Destroyables{
        &Object1};

public:
    void setup(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);
    void start(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);
    void update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);
    void end(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);
};
