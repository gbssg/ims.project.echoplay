#include "Snake.h"
#include <Arduino.h>
#include <LEDWallDriver.h>
#include <LedWallEncoder.h>
#include <SparkFun_Qwiic_Button.h>
#include <SimpleSoftTimer.h>

using namespace HolisticSolutions;

typedef struct sPoint
{
    uint8_t posX;
    uint8_t posY;
} tPoint;

// Malt ein das image gleich wie das newImage
void DrawImage(uint8_t image[][16], uint8_t newImage[][16])
{
    for (int y = 0; y < 16; ++y)
    {
        for (int x = 0; x < 16; ++x)
        {
            image[y][x] = newImage[y][x];
        }
    }
}

// Macht ein gewähltes Bild zu nur nullen
void EmptyScreen(uint8_t image[16][16])
{
    for (int y = 0; y < 16; ++y)
    {
        for (int x = 0; x < 16; ++x)
        {
            image[y][x] = 0;
        }
    }
}

// Macht ein gewoltes Bild in den Buffer und dieser wird auf den Screen gemalt und angezeigt
void UpdateScreen(uint8_t buffer[], uint8_t image[16][16])
{
    LWC_Encode(buffer, image);

    WD_BufferOutput(buffer);
}

// Malt den Titelscreen von Snake auf das gewählte Bild
void TitleScreen(uint8_t image[16][16])
{
    uint8_t TitleScreen[16][16] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    DrawImage(image, TitleScreen);
}

// Wählt mithilfe von difficulty den Richtigen schweirigkeitsscreen
void SchweirigskeitScreen(uint8_t image[16][16], int difficulty)
{
    uint8_t difficultyScreenEinfach[16][16] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    uint8_t difficultyScreenMittel[16][16] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    uint8_t difficultyScreenSchwer[16][16] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0},
        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    if (difficulty == 1)
    {
        DrawImage(image, difficultyScreenEinfach);
    }
    else if (difficulty == 2)
    {
        DrawImage(image, difficultyScreenMittel);
    }
    else if (difficulty == 3)
    {
        DrawImage(image, difficultyScreenSchwer);
    }
}

// Malt ein Bild so wie es am Anfang von Snake aussehen sollte
void SnakeSetup(uint8_t image[16][16], int snakeX, int snakeY)
{
    EmptyScreen(image);

    image[snakeY][snakeX] = 1;
}

// Malt ein Bild so das es Game Over beinhaltet
void GameOverScreen(uint8_t image[16][16])
{
    uint8_t gameOverScreen[16][16] = {
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

    DrawImage(image, gameOverScreen);
}

// Malt ein Bild so das es Again? auf dem Bild zeigt
void StartNewScreen(uint8_t image[16][16])
{
    uint8_t startNewScreen[16][16] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    DrawImage(image, startNewScreen);
}

// Auf einen Knopfdruck warten mit LED, Gibt zurück welcher Knopf gedrückt worde. (leftButton = 1, rightButton = 2, both = 3)
int WaitForButtonPress(QwiicButton leftButton, QwiicButton rightButton)
{
    uint8_t button = 0;
    rightButton.clearEventBits();
    leftButton.clearEventBits();

    while (!leftButton.hasBeenClicked() && !rightButton.hasBeenClicked())
    {
        if (leftButton.isPressed())
        {
            leftButton.LEDon(255);
        }
        else
        {
            leftButton.LEDoff();
        }
        if (rightButton.isPressed())
        {
            rightButton.LEDon(255);
        }
        else
        {
            rightButton.LEDoff();
        }
    }

    delay(50); // Warten falls beide Knöpfe gedrückt werden;

    if (leftButton.hasBeenClicked())
    {
        leftButton.LEDoff();
        button += 1;
    }
    if (rightButton.hasBeenClicked())
    {
        rightButton.LEDoff();
        button += 2;
    }

    return button;
}

// Ändert die Richtung von der Snake mit der gegebenen geschindigkeit
void ChangeSnakeDirection(QwiicButton leftButton, QwiicButton rightButton, int &snakeDirection, int speed)
{
    SimpleSoftTimer timer(speed);
    bool buttonPressed = false;

    timer.restart();
    while (!timer.isTimeout())
    {
        if (!buttonPressed)
        {
            Serial.print("ok");
            if (leftButton.hasBeenClicked())
            {
                Serial.println();
                Serial.println("Linker Knopf");
                snakeDirection--;
                buttonPressed = true;
            }
            else if (rightButton.hasBeenClicked())
            {
                Serial.println();
                Serial.println("Rechter Knopf");
                snakeDirection++;
                buttonPressed = true;
            }
        }
        if (leftButton.isPressed())
        {
            leftButton.LEDon(255);
        }
        else
        {
            leftButton.LEDoff();
        }
        if (rightButton.isPressed())
        {
            rightButton.LEDon(255);
        }
        else
        {
            rightButton.LEDoff();
        }
    }
    Serial.println();
    Serial.println();

    leftButton.LEDoff();
    rightButton.LEDoff();
    leftButton.clearEventBits();
    rightButton.clearEventBits();

    if (snakeDirection < 0)
    {
        snakeDirection = 3;
    }
    else if (snakeDirection > 3)
    {
        snakeDirection = 0;
    }
}

// Platziert einen Appfel auf einen Gültigen Ort
void PlantApple(int &appleX, int &appleY, int snakeX, int snakeY, int snakeTailX[], int snakeTailY[], int snakeLength)
{
    bool goodApple = false;

    appleX = rand() % 16;
    appleY = rand() % 16;
    while (!goodApple)
    {
        if (appleX == snakeX && appleY == snakeY)
        {
            appleX = rand() % 16;
            appleY = rand() % 16;
        }
        else
        {
            for (int i = 0; i < snakeLength; i++)
            {
                if (appleX == snakeTailX[i] && appleY == snakeTailY[i])
                {
                    appleX = rand() % 16;
                    appleY = rand() % 16;
                    break;
                }
            }
            goodApple = true;
        }
    }
}

// Löscht den letzten Teil des Schlangenschwanzes und bewegt den Schwanz
void UpdateSnakeTail(int snakeX, int snakeY, int snakeTailX[], int snakeTailY[], int snakeLength, uint8_t image[][16])
{
    image[snakeTailY[snakeLength - 1]][snakeTailX[snakeLength - 1]] = 0;

    for (int i = snakeLength; 1 < i; i--)
    {
        snakeTailX[i - 1] = snakeTailX[i - 2];
        snakeTailY[i - 1] = snakeTailY[i - 2];
    }
    snakeTailX[0] = snakeX;
    snakeTailY[0] = snakeY;
}

// Bewegt die Schlange in die gegebene Richtung
void SnakeMovement(int snakeDirection, int &snakeX, int &snakeY)
{
    if (snakeDirection == 0)
    {
        snakeX--;
    }
    else if (snakeDirection == 1)
    {
        snakeY--;
    }
    else if (snakeDirection == 2)
    {
        snakeX++;
    }
    else if (snakeDirection == 3)
    {
        snakeY++;
    }
}

// Überprüft ob die Schlange das Spiel beendet hat
void CheckForGameOver(int snakeX, int snakeY, int snakeTailX[], int snakeTailY[], int snakeLength, bool &gameOver)
{

    if (snakeX < 0 || snakeX >= 16 || snakeY < 0 || snakeY >= 16)
    {
        Serial.println("Snake ist aus dem Spiel feld.. Game Over");
        gameOver = true;
    }

    for (int i = 0; i < snakeLength; i++)
    {
        if (snakeX == snakeTailX[i] && snakeY == snakeTailY[i])
        {
            Serial.println("Schlange berührt sich selbst... Game Over");
            gameOver = true;
        }
    }
}

// Zeichnet den Appfel, den Schlangenkopf und den Schlangenschwanz
void DrawSnakenApple(int snakeX, int snakeY, int appleX, int appleY, int snakeTailX[], int snakeTailY[], uint8_t image[][16], uint8_t buffer[], int snakeLength)
{
    image[snakeY][snakeX] = 1;
    image[appleY][appleX] = 1;

    for (int i = 0; i < snakeLength; i++)
    {
        image[snakeTailY[i]][snakeTailX[i]] = 1;
    }

    UpdateScreen(buffer, image);
}