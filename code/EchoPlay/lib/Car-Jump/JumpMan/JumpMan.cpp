#include "JumpMan.h"
#include <vector>

JumpMan::JumpMan(uint8_t x, uint8_t y, int width, std::vector<uint8_t> nextJumpManSprite) : startingX(x), startingY(y), JumpManPos{x, y}, Width(width), JumpManSprite(nextJumpManSprite)
{
}

int JumpMan::GetPositionX()
{
    return JumpManPos.posX;
}

int JumpMan::GetPositionY()
{
    return JumpManPos.posY;
}

int JumpMan::GetWidth()
{
    return Width;
}

std::vector<uint8_t> JumpMan::GetSprite()
{
    return JumpManSprite;
}

void JumpMan::SetPosition(int x, int y)
{
    JumpManPos.posX = x;
    JumpManPos.posY = y;
}

void JumpMan::Start()
{
    ManState = STATIC;
    ManJumpTimer.start(75);
    JumpManPos.posX = startingX;
    JumpManPos.posY = startingY;
}

void JumpMan::Draw(Screen &screen)
{
    screen.drawSpriteOnImage(JumpManPos.posX, JumpManPos.posY, JumpManSprite, Width);
}

void JumpMan::Jump(QwiicButton &leftButton)
{
    if (ManJumpTimer.isTimeout())
    {
        Serial.println("ManJump");
        switch (ManState)
        {
        case STATIC:
        {
            if (leftButton.isPressed())
            {
                ManState = JUMPSTART;
            }
            break;
        }
        case JUMPSTART:
        {
            JumpManPos.posY++;
            ManState = JUMPINGUP;
            break;
        }
        case JUMPINGUP:
        {
            if (JumpManPos.posY > startingY - 5)
            {
                JumpManPos.posY--;
            }
            else
            {
                ManState = FALLINGDOWN;
            }
            break;
        }
        case FALLINGDOWN:
        {
            if (JumpManPos.posY < startingY + 1)
            {
                JumpManPos.posY++;
            }
            else
            {
                ManState = FALLINGEND;
            }
            break;
        }
        case FALLINGEND:
        {
            JumpManPos.posY--;
            ManState = STATIC;
            break;
        }
        default:
            break;
        }
        ManJumpTimer.restart();
    }
}

void JumpMan::Duck(QwiicButton &rightButton)
{
    switch (ManState)
    {
    case STATIC:
    {
        if (rightButton.isPressed())
        {
            ManState = DUCKING;
        }
        break;
    }
    case DUCKING:
    {
        if (rightButton.isPressed())
        {
            JumpManPos.posY = startingY + 1;
        }
        else
        {
            JumpManPos.posY = startingY;
            ManState = STATIC;
        }
    }
    default:
        break;
    }
}
