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
    DestroyableAmount = StartDestroyableAmount;

    Balls.reserve(MaxBalls);
    BallAmount = StartBallAmount;

    ArkanoidPlatform.SetPosition((screen.GetWidth() / 2) - (ArkanoidPlatform.GetWidth() / 2), screen.GetScreenEnd());
    ArkanoidPlatform.SetMoveTimer(PlatformMoveTime);

    for (int i = 0; i < MaxBalls; i++)
    {
        Balls.emplace_back();
    }

    for (int i = 0; i < StartBallAmount; i++)
    {
        Balls[i].SetPosition(ArkanoidPlatform.GetPosition(XPOS) + PlatformWidth / 2, ArkanoidPlatform.GetPosition(YPOS) - 1);
        Balls[i].SetVelocity(Speed, -Speed);
        Balls[i].StartMoving();
        Balls[i].SetActive(true);
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

    gameOver = false;
    PlayerWon = false;
}

void Arkanoid::start(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    screen.DrawImage(TitleScreen);

    screen.Update();
}

void Arkanoid::update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    screen.EmptyImage();

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
        if (Balls[i].IsActive())
        {
            Balls[i].SetPrevPosition();
            Balls[i].MoveBall();

            int ballX = Balls[i].GetPosition(XPOS);
            int ballY = Balls[i].GetPosition(YPOS);
            int prevBallX = Balls[i].GetPrevPosition(XPOS);
            int prevBallY = Balls[i].GetPrevPosition(YPOS);

            if (ballX < screen.GetScreenStart() || ballX > screen.GetScreenEnd())
            {
                Balls[i].SetPosition(prevBallX, prevBallY);
                Balls[i].Bounce(SIDE);
                Balls[i].ForceMoveBall();
            }
            if (ballY < screen.GetScreenStart())
            {
                Balls[i].SetPosition(prevBallX, prevBallY);
                Balls[i].Bounce(TOPBOT);
                Balls[i].ForceMoveBall();
            }

            ballX = Balls[i].GetPosition(XPOS);
            ballY = Balls[i].GetPosition(YPOS);

            if (ballY > screen.GetScreenEnd())
            {
                Balls[i].SetActive(false);
                BallAmount--;
                Serial.println("Ball Destroyed");
                Serial.print("Balls left: ");
                Serial.println(BallAmount);
            }

            if ((ballX >= platformX && ballX <= (platformX + PlatformWidth - 1)) && ballY == ArkanoidPlatform.GetPosition(YPOS))
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

            screen.SetPixel(ballX, ballY, true);
        }
    }

    if (BallAmount <= 0)
    {
        gameOver = true;
    }

    for (int i = 0; i < Destroyables.size(); i++)
    {
        if (!Destroyables[i].IsDestroyed())
        {
            int destroyableX = Destroyables[i].GetPosition(XPOS);
            int destroyableY = Destroyables[i].GetPosition(YPOS);
            std::vector<uint8_t> destroyableSprite = Destroyables[i].GetSprite();
            int destroyableWidth = Destroyables[i].GetWidth();

            screen.DrawSpriteOnImage(destroyableX, destroyableY, destroyableSprite, destroyableWidth);
        }
    }

    screen.DrawSpriteOnImage(platformX, platformY, PlatformSprite, PlatformWidth);

    screen.Update();
}

void Arkanoid::end(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    if (PlayerWon)
    {
        screen.DrawImage(gameOverWinScreen);
    }
    else
    {
        screen.DrawImage(gameOverLoseScreen);
    }
    screen.Update();
}