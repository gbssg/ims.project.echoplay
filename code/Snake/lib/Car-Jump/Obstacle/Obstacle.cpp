#include "Obstacle.h"
#include <vector>

Obstacle::Obstacle(int width, int yPosition, std::vector<uint8_t> nextObstacleSprite) : Width(width), StartingYPos(yPosition), ObstacleSprite(nextObstacleSprite)
{
}

void Obstacle::SetPosition(int x, int y)
{
    if (x < 16 && x >= 0)
    {
        ObstaclePos.posX = x;
    }
    if (y < 16 && y >= 0)
    {
        ObstaclePos.posY = y;
    }
}

void Obstacle::ResetPosition()
{
    ObstaclePos.posX = 16;
    ObstaclePos.posY = StartingYPos;
    Active = true;
    MoveTimer.start(MoveTimerSpeed);
}

void Obstacle::SetMoveTimer(int newMoveTimer)
{
    if (newMoveTimer > 0)
    {
        MoveTimerSpeed = newMoveTimer;
    }
}

void Obstacle::SetMoveTimerWDifficulty(int difficulty)
{
    MoveTimerSpeed = MaxMoveSpeed - (MaxMoveSpeed - MinMoveSpeed) * difficulty / 30;
    Serial.print("ObstacleSpeed");
    Serial.println(MoveTimerSpeed);
}

void Obstacle::MoveObstacleLeft()
{
    if (MoveTimer.isTimeout() && Active)
    {
        ObstaclePos.posX--;
        MoveTimer.restart();
    }
    if (ObstaclePos.posX < 0 - Width)
    {
        Active = false;
    }
}

void Obstacle::DrawObstacle(Screen &screen)
{
    screen.drawSpriteOnImage(ObstaclePos.posX, ObstaclePos.posY, ObstacleSprite, Width);
}

bool Obstacle::CheckBoxCollision(int collidingX, int collidingY, std::vector<uint8_t> &collidingSprite, int collidingWidth)
{
    if (collidingWidth == 0)
        return false;

    int collidingHeight = collidingSprite.size() / collidingWidth;

    int Height = ObstacleSprite.size() / Width;

    return (
        ObstaclePos.posX < collidingX + collidingWidth &&
        ObstaclePos.posX + Width > collidingX &&
        ObstaclePos.posY < collidingY + collidingHeight &&
        ObstaclePos.posY + Height > collidingY);
}

bool Obstacle::CheckPixelCollision(int ToCheckX, int ToCheckY, std::vector<uint8_t> ToCheckSprite, int ToCheckWidth)
{
    if (!CheckBoxCollision(ToCheckX, ToCheckY, ToCheckSprite, ToCheckWidth))
        return false;

    int ToCheckHeight = ToCheckSprite.size() / ToCheckWidth;
    int Height = ObstacleSprite.size() / Width;

    int collidingLeft = std::max(ObstaclePos.posX, ToCheckX);
    int collidingRight = std::max(ObstaclePos.posX + Width, ToCheckX + ToCheckWidth);
    int collidingTop = std::max(ObstaclePos.posY, ToCheckY);
    int collidingBottom = std::max(ObstaclePos.posY + Height, ToCheckY + ToCheckHeight);

    for (int y = collidingTop; y < collidingBottom; y++)
    {
        for (int x = collidingLeft; x < collidingRight; x++)
        {
            int ObstaclePixelX = x - ObstaclePos.posX;
            int ObstaclePixelY = y - ObstaclePos.posY;
            int ToCheckPixelX = x - ToCheckX;
            int ToCheckPixelY = y - ToCheckY;

            uint8_t ObstaclePixel = ObstacleSprite[ObstaclePixelY * Width + ObstaclePixelX];
            uint8_t ToCheckPixel = ToCheckSprite[ToCheckPixelY * ToCheckWidth + ToCheckPixelX];

            if (ObstaclePixel != 0 && ToCheckPixel != 0)
                return true;
        }
    }
    return false;
}