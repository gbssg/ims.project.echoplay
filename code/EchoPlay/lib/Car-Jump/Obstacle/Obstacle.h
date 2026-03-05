#pragma once

#include <vector>
#include <Screen.h>
#include <SimpleSoftTimer.h>
#include <EchoPlay.h>

using namespace HolisticSolutions;

class Obstacle
{
public:
    tPoint ObstaclePos;
    int StartingYPos;
    bool Active = true;
    int Width;

    int MaxMoveSpeed = 100;
    int MinMoveSpeed = 40;

    int MoveTimerSpeed = 220;

    SimpleSoftTimer MoveTimer{100};

    std::vector<uint8_t> ObstacleSprite;

    Obstacle(int width, int yPosition, std::vector<uint8_t> nextObstacleSprite);

    void SetPosition(int x, int y);

    void ResetPosition();

    void SetMoveTimer(int newMoveTimer);

    void SetMoveTimerWDifficulty(int difficulty);

    void MoveObstacleLeft();

    void DrawObstacle(Screen &screen);

    bool CheckBoxCollision(int collidingX, int collidingY, std::vector<uint8_t> &collidingSprite, int collidingWidth);

    bool CheckPixelCollision(int ToCheckX, int ToCheckY, std::vector<uint8_t> ToCheckSprite, int ToCheckWidth);
};