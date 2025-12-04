#pragma once

#include <stdint.h>
#include <SparkFun_Qwiic_Button.h>
#include <Screen.h>
#include <IGame.h>
#include <SimpleSoftTimer.h>

using namespace HolisticSolutions;

class CarJumpStrategy : public IGame
{
public:
    void setup(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);

    void start(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);

    void update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);

    void end(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);
};