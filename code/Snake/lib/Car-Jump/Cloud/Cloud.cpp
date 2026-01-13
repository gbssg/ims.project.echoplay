#include "Cloud.h"
#include <vector>

Cloud::Cloud(int width, int yRange, std::vector<uint8_t> nextCloudSprite) : Width(width), YRange(yRange), CloudSprite(nextCloudSprite)
{
}

void Cloud::SetPosition(int x, int y)
{
    if (x < 16 && x >= 0)
    {
        CloudPos.posX = x;
    }
    if (y < 16 && y >= 0)
    {
        CloudPos.posY = y;
    }
}

void Cloud::ResetPosition()
{
    CloudPos.posX = 16;
    CloudPos.posY = (rand() % YRange) + 1;
    Active = true;
    MoveTimer.start(MoveTimerSpeed);
}

void Cloud::SetMoveTimer(int newMoveTimer)
{
    if (newMoveTimer > 0)
    {
        MoveTimerSpeed = newMoveTimer;
    }
}

void Cloud::SetMoveTimerWDifficulty(int difficulty)
{
    MoveTimerSpeed = CloudMoveTimeMax - (CloudMoveTimeMax - CloudMoveTimeMin) * difficulty / 30;
    MoveTimerSpeed += rand() % 21;
    Serial.print("CloudSpeed");
    Serial.println(MoveTimerSpeed);
}

void Cloud::MoveCloudLeft()
{
    if (MoveTimer.isTimeout() && Active)
    {
        CloudPos.posX--;
        MoveTimer.restart();
    }
    if (CloudPos.posX < 0 - Width)
    {
        Active = false;
    }
}

void Cloud::drawCloud(Screen &screen)
{
    screen.drawSpriteOnImage(CloudPos.posX, CloudPos.posY, CloudSprite, Width);
}