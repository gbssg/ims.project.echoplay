#include "PlayerPlatform.h"

PlayerPlatform::PlayerPlatform(std::vector<uint8_t> newSprite, int width) : PlatformSprite(newSprite), Width(width)
{
}

void PlayerPlatform::MovePlatform(bool moveLeft)
{
    if (moveTimer.isTimeout())
    {
        if (moveLeft)
        {
            if (PlatformPos.posX > 0)
            {
                PlatformPos.posX--;
            }
        }
        else
        {
            if (PlatformPos.posX < 15 - Width + 1)
            {
                PlatformPos.posX++;
            }
        }
        moveTimer.start(moveTime);
    }
}

void PlayerPlatform::SetPosition(int x, int y)
{
    PlatformPos.posX = x;
    PlatformPos.posY = y;
}

void PlayerPlatform::SetMoveTimer(int newTime)
{
    if (newTime > 0)
    {
        moveTime = newTime;
    }
}

int PlayerPlatform::GetPosition(Coordinate position)
{
    switch (position)
    {
    case XPOS:
    {
        return PlatformPos.posX;
        break;
    }
    case YPOS:
    {
        return PlatformPos.posY;
        break;
    }
    default:
    {
        return -1;
        break;
    }
    }
}

std::vector<uint8_t> PlayerPlatform::GetSprite()
{
    return PlatformSprite;
}

int PlayerPlatform::GetWidth()
{
    return Width;
}