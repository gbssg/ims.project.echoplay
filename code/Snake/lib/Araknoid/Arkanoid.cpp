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

static uint8_t gameOverScreen[16][16] = {
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

void Arkanoid::setup(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    for (int i = 0; i < Balls.size(); i++)
    {
        Balls[i].SetPosition(rand() % 16, (rand() % 13));
        Balls[i].SetVelocity(Speed, -Speed);
        Balls[i].StartMoving();
    }

    ArkanoidPlatform.SetPosition(5, 15);

    gameOver = false;
}

void Arkanoid::start(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    screen.drawImage(TitleScreen);

    screen.update();
}

void Arkanoid::update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    screen.emptyImage();

    if (leftButton.isPressed())
    {
        ArkanoidPlatform.MovePlatform(true);
    }
    if (rightButton.isPressed())
    {
        ArkanoidPlatform.MovePlatform(false);
    }

    for (int i = 0; i < Balls.size(); i++)
    {
        Balls[i].SetPrevPosition();
        Balls[i].MoveBall();

        if (Balls[i].GetPosition(XPOS) < 0 || Balls[i].GetPosition(XPOS) > 15)
        {
            Balls[i].SetPosition(Balls[i].GetPrevPosition(XPOS), Balls[i].GetPrevPosition(YPOS));
            Balls[i].Bounce(SIDE);
            Balls[i].ForceMoveBall();
        }
        if (Balls[i].GetPosition(YPOS) < 0)
        {
            Balls[i].SetPosition(Balls[i].GetPrevPosition(XPOS), Balls[i].GetPrevPosition(YPOS));
            Balls[i].Bounce(TOPBOT);
            Balls[i].ForceMoveBall();
        }
        if (Balls[i].GetPosition(YPOS) > 15)
        {
            gameOver = true;
        }

        if ((Balls[i].GetPosition(XPOS) >= ArkanoidPlatform.GetPosition(XPOS) && Balls[i].GetPosition(XPOS) <= (ArkanoidPlatform.GetPosition(XPOS) + ArkanoidPlatform.GetWidth() - 1)) && Balls[i].GetPosition(YPOS) == 15)
        {
            Balls[i].HandlePlatformBounce(ArkanoidPlatform);
        }

        screen.setPixel(Balls[i].GetPosition(XPOS), Balls[i].GetPosition(YPOS), true);
    }

    screen.drawSpriteOnImage(ArkanoidPlatform.GetPosition(XPOS), ArkanoidPlatform.GetPosition(YPOS), ArkanoidPlatform.GetSprite(), ArkanoidPlatform.GetWidth());

    screen.update();
}

void Arkanoid::end(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    screen.drawImage(gameOverScreen);

    screen.update();
}