#pragma once

#include <Screen.h>
#include <IProgramm.h>
#include <SparkFun_Qwiic_Button.h>

// class um Spiele zu erstellen
class IProgramm
{
protected:
    bool gameOver = false;

public:
    virtual void setup(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton) = 0;
    virtual void update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton) = 0;
    virtual bool isGame() const { return false; }
};