#include "Ball.h"
#include <cmath>

void Ball::SetPrevPosition()
{
    PrevBallPos.posX = BallPos.posX;
    PrevBallPos.posY = BallPos.posY;
}

void Ball::SetPrevPosition(int x, int y)
{
    PrevBallPos.posX = x;
    PrevBallPos.posY = y;
}

int Ball::GetPrevPosition(Coordinate position)
{
    switch (position)
    {
    case XPOS:
    {
        return PrevBallPos.posX;
        break;
    }
    case YPOS:
    {
        return PrevBallPos.posY;
        break;
    }
    default:
    {
        return 0;
        break;
    }
    }
}

void Ball::MoveBall()
{
    if (xMoveTimer.isTimeout() && BallVelocity.xVel != 0)
    {
        BallVelocity.xVel < 0 ? BallPos.posX-- : BallPos.posX++;
        xMoveTimer.start(std::abs(1000 / BallVelocity.xVel));
    }

    if (yMoveTimer.isTimeout() && BallVelocity.yVel != 0)
    {
        BallVelocity.yVel < 0 ? BallPos.posY-- : BallPos.posY++;
        yMoveTimer.start(std::abs(1000 / BallVelocity.yVel));
    }
}

void Ball::ForceMoveBall()
{
    if (BallVelocity.xVel != 0)
    {
        BallVelocity.xVel < 0 ? BallPos.posX-- : BallPos.posX++;
        xMoveTimer.start(std::abs(1000 / BallVelocity.xVel));
    }

    if (BallVelocity.yVel != 0)
    {
        BallVelocity.yVel < 0 ? BallPos.posY-- : BallPos.posY++;
        yMoveTimer.start(std::abs(1000 / BallVelocity.yVel));
    }
}

void Ball::SetVelocity(float xVel, float yVel)
{
    BallVelocity.xVel = xVel;
    BallVelocity.yVel = yVel;
}

void Ball::SetPosition(int x, int y)
{
    BallPos.posX = x;
    BallPos.posY = y;
}

void Ball::StartMoving()
{
    if (BallVelocity.xVel != 0)
        xMoveTimer.start(std::abs(1000 / BallVelocity.xVel));

    if (BallVelocity.yVel != 0)
        yMoveTimer.start(std::abs(1000 / BallVelocity.yVel));
}

void Ball::Bounce(WallPos pos)
{
    switch (pos)
    {
    case TOPBOT:
    {
        BallVelocity.yVel *= -1;
        break;
    }
    case SIDE:
    {
        BallVelocity.xVel *= -1;
        break;
    }
    }
}

void Ball::HandlePlatformBounce(PlayerPlatform platform)
{
    SetPosition(PrevBallPos.posX, PrevBallPos.posY);

    int ballX = GetPosition(XPOS);
    int platformX = platform.GetPosition(XPOS);
    int width = platform.GetWidth();

    float vx = GetVelocity(XPOS);
    float vy = GetVelocity(YPOS);

    float speed = max(fabs(vx), fabs(vy));
    if (speed < 1.0f)
        speed = 1.0f;

    float center = (width - 1) * 0.5f;
    float offset = (ballX - platformX) - center;

    float maxOffset = (width * 0.5f) + 1.0f;

    float dx = offset / maxOffset;
    dx = constrain(dx, -1.0f, 1.0f);

    float dy = -1.0f;

    float maxDir = max(fabs(dx), fabs(dy));
    dx = (dx / maxDir) * speed;
    dy = (dy / maxDir) * speed;

    SetVelocity(dx, dy);
    ForceMoveBall();
}

int Ball::GetPosition(Coordinate position)
{
    switch (position)
    {
    case XPOS:
    {
        return BallPos.posX;
        break;
    }
    case YPOS:
    {
        return BallPos.posY;
        break;
    }
    default:
    {
        return 0;
        break;
    }
    }
}

bool Ball::MovingLeft()
{
    if (BallVelocity.xVel < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

float Ball::GetVelocity(Coordinate position)
{
    switch (position)
    {
    case XPOS:
    {
        return BallVelocity.xVel;
        break;
    }
    case YPOS:
    {
        return BallVelocity.yVel;
        break;
    }
    default:
    {
        return 0;
        break;
    }
    }
}

void Ball::HandleBlockBounce(Destroyable block)
{
    SetPosition(PrevBallPos.posX, PrevBallPos.posY);

    int blockX = block.GetPosition(XPOS);
    int blockY = block.GetPosition(YPOS);
    int blockWidth = block.GetWidth();
    int blockHeight = block.GetHeight();

    int ballX = BallPos.posX;
    int ballY = BallPos.posY;

    if (ballX < blockX || ballX > blockX + blockWidth - 1)
    {
        Bounce(SIDE);
    }

    if (ballY < blockY || ballY > blockY + blockHeight - 1)
    {
        Bounce(TOPBOT);
    }
}

void Ball::SetActive(bool newState)
{
    active = newState;
}

bool Ball::IsActive()
{
    return active;
}