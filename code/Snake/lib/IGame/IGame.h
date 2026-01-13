#pragma once

#include <Screen.h>
#include <SparkFun_Qwiic_Button.h>
#include <IProgramm.h>

// class um Spiele zu erstellen
class IGame : public IProgramm
{
protected:
    bool gameOver = false;

public:
    bool isGame() const override { return true; }
    virtual void start(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton) = 0;
    virtual void end(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton) = 0;
    virtual bool isGameOver() const { return gameOver; }
};