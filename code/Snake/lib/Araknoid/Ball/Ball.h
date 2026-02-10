#pragma once

#include <EchoPlay.h>
#include <SimpleSoftTimer.h>
#include "../PlayerPlatform/PlayerPlatform.h"
#include "../SharedEnums.h"

using namespace HolisticSolutions;

enum WallPos
{
    TOPBOT,
    SIDE
};

class Ball
{
private:
    tPoint PrevBallPos;
    tPoint BallPos;
    // Velocity in pixel per seconds
    tVelocity BallVelocity;

    SimpleSoftTimer xMoveTimer{1000};
    SimpleSoftTimer yMoveTimer{1000};

public:
    void SetPrevPosition();
    void SetPrevPosition(int x, int y);
    int GetPrevPosition(Coordinate position);
    void MoveBall();
    void ForceMoveBall();
    void SetVelocity(float xVel, float yVel);
    void SetPosition(int x, int y);
    void StartMoving();
    void Bounce(WallPos pos);
    void HandlePlatformBounce(PlayerPlatform platform);
    int GetPosition(Coordinate position);
    bool MovingLeft();
    float GetVelocity(Coordinate position);
};