#pragma once

#include <vector>
#include <Screen.h>
#include <SimpleSoftTimer.h>
#include <EchoPlay.h>
#include <SparkFun_Qwiic_Button.h>

using namespace HolisticSolutions;

class JumpMan
{
private:
    tPoint JumpManPos;

    int startingX;
    int startingY;

    int Width;
    std::vector<uint8_t> JumpManSprite;

    enum state
    {
        STATIC,
        JUMPSTART,
        JUMPINGUP,
        FALLINGDOWN,
        FALLINGEND,
        DUCKING
    };

    state ManState;

    SimpleSoftTimer ManJumpTimer{75};

public:
    JumpMan(uint8_t x, uint8_t y, int width, std::vector<uint8_t> nextJumpManSprite);

    int GetPositionX();
    int GetPositionY();
    int GetWidth();
    std::vector<uint8_t> GetSprite();

    void SetPosition(int x, int y);
    void Start();
    void Draw(Screen &screen);
    void Jump(QwiicButton &leftButton);
    void Duck(QwiicButton &rightButton);
};