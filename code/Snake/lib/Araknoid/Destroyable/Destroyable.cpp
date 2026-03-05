#include "Destroyable.h"

Destroyable::Destroyable(std::vector<uint8_t> newSprite, int width) : ObjectSprite(newSprite), Width(width)
{
}

void Destroyable::SetPosition(int x, int y)
{
    ObjectPos.posX = x;
    ObjectPos.posY = y;
}

std::vector<uint8_t> Destroyable::GetSprite()
{
    return ObjectSprite;
}

int Destroyable::GetPosition(Coordinate position)
{
    switch (position)
    {
    case XPOS:
    {
        return ObjectPos.posX;
        break;
    }
    case YPOS:
    {
        return ObjectPos.posY;
        break;
    }
    default:
    {
        return -1;
        break;
    }
    }
}

int Destroyable::GetWidth()
{
    return Width;
}

int Destroyable::GetHeight()
{
    return ObjectSprite.size() / Width;
}

bool Destroyable::IsDestroyed()
{
    return Destroyed;
}

void Destroyable::Destroy()
{
    Destroyed = true;
}

void Destroyable::Contruct()
{
    Destroyed = false;
}