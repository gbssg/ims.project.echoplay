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