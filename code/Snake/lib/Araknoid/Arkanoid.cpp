#include "Arkanoid.h"
#include <vector>

static uint8_t TitleScreen[16][16] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

static uint8_t gameOverLoseScreen[16][16] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0},
    {0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
    {0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

static uint8_t gameOverWinScreen[16][16] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

void Arkanoid::setup(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    Destroyables.reserve(MaxDestroyables);
    DestroyableAmount = MaxDestroyables;

    Balls.reserve(MaxBalls);
    BallAmount = 5;

    for (int i = 0; i < MaxBalls; i++)
    {
        Balls.emplace_back();
    }

    for (int i = 0; i < BallAmount; i++)
    {
        Balls[i].SetPosition(ArkanoidPlatform.GetPosition(XPOS) + PlatformWidth / 2, ArkanoidPlatform.GetPosition(YPOS) - 1);
        Balls[i].SetVelocity(Speed, -Speed);
        Balls[i].StartMoving();
    }

    for (int i = 0; i < MaxDestroyables; i++)
    {
        Destroyables.emplace_back(DestroyableSprite, DestroyableWidth);
    }

    for (int i = 0; i < DestroyableAmount; i++)
    {
        int row = i / DestroyablesPerRow;
        int col = i % DestroyablesPreCollumn;
        int x = 1 + col * DestroyableWidth;
        int y = 1 + row;
        Destroyables[i].SetPosition(x, y);
        Destroyables[i].Contruct();
    }

    ArkanoidPlatform.SetPosition(5, 15);
    ArkanoidPlatform.SetMoveTimer(PlatformMoveTime);

    gameOver = false;
    PlayerWon = false;
}

void Arkanoid::start(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    screen.drawImage(TitleScreen);

    screen.update();
}

void Arkanoid::update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    screen.emptyImage();

    int platformX = ArkanoidPlatform.GetPosition(XPOS);
    int platformY = ArkanoidPlatform.GetPosition(YPOS);

    if (leftButton.isPressed())
    {
        ArkanoidPlatform.MovePlatform(true);
    }
    if (rightButton.isPressed())
    {
        ArkanoidPlatform.MovePlatform(false);
    }

    for (int i = 0; i < BallAmount; i++)
    {
        Balls[i].SetPrevPosition();
        Balls[i].MoveBall();

        int ballX = Balls[i].GetPosition(XPOS);
        int ballY = Balls[i].GetPosition(YPOS);
        int prevBallX = Balls[i].GetPrevPosition(XPOS);
        int prevBallY = Balls[i].GetPrevPosition(YPOS);

        if (ballX < 0 || ballX > 15)
        {
            Balls[i].SetPosition(prevBallX, prevBallY);
            Balls[i].Bounce(SIDE);
            Balls[i].ForceMoveBall();
        }
        if (ballY < 0)
        {
            Balls[i].SetPosition(prevBallX, prevBallY);
            Balls[i].Bounce(TOPBOT);
            Balls[i].ForceMoveBall();
        }

        ballX = Balls[i].GetPosition(XPOS);
        ballY = Balls[i].GetPosition(YPOS);

        if (ballY > 15)
        {
            gameOver = true;
        }

        if ((ballX >= platformX && ballX <= (platformX + PlatformWidth - 1)) && ballY == 15)
        {
            Balls[i].HandlePlatformBounce(ArkanoidPlatform);
        }

        for (int j = 0; j < Destroyables.size(); j++)
        {
            int destroyableX = Destroyables[j].GetPosition(XPOS);
            int destroyableY = Destroyables[j].GetPosition(YPOS);
            int destroyableHeight = Destroyables[j].GetHeight();
            int destroyableWidth = Destroyables[j].GetWidth();

            bool destroyableHit = (ballY >= destroyableY && ballY <= destroyableY + destroyableHeight - 1) && (ballX >= destroyableX && ballX <= destroyableX + destroyableWidth - 1);
            bool destroyableDestroyed = Destroyables[j].IsDestroyed();

            if (destroyableHit && !destroyableDestroyed)
            {
                DestroyableAmount--;
                Destroyables[j].Destroy();
                Balls[i].HandleBlockBounce(Destroyables[j]);
            }
        }

        if (DestroyableAmount <= 0)
        {
            PlayerWon = true;
            gameOver = true;
        }

        screen.setPixel(ballX, ballY, true);
    }

    for (int i = 0; i < Destroyables.size(); i++)
    {
        if (!Destroyables[i].IsDestroyed())
        {
            int destroyableX = Destroyables[i].GetPosition(XPOS);
            int destroyableY = Destroyables[i].GetPosition(YPOS);
            std::vector<uint8_t> destroyableSprite = Destroyables[i].GetSprite();
            int destroyableWidth = Destroyables[i].GetWidth();

            screen.drawSpriteOnImage(destroyableX, destroyableY, destroyableSprite, destroyableWidth);
        }
    }

    screen.drawSpriteOnImage(platformX, platformY, PlatformSprite, PlatformWidth);

    screen.update();
}

void Arkanoid::end(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    if (PlayerWon)
    {
        screen.drawImage(gameOverWinScreen);
    }
    else
    {
        screen.drawImage(gameOverLoseScreen);
    }
    screen.update();
}