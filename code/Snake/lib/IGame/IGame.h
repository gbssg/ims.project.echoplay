#pragma once

#include <Screen.h>
#include <SparkFun_Qwiic_Button.h>

// class um Spiele zu erstellen
class IGame
{
protected:
    bool gameOver = false;

public:
    virtual void setup(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton) = 0;
    virtual void start(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton) = 0;
    virtual void update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton) = 0;
    virtual void end(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton) = 0;

    bool isGameOver() const { return gameOver; }
};