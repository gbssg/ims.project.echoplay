#include "Snake.h"
#include <Arduino.h>
#include <LEDWallDriver.h>
#include <LedWallEncoder.h>
#include <SparkFun_Qwiic_Button.h>
#include <SimpleSoftTimer.h>
#include <EchoPlay.h>

using namespace HolisticSolutions;

// Allgemeine Statische Variablen für das Spiel deklarieren
static int difficulty = 1;            // 1 = Easy, 2 = Medium, 3 = Hard
static bool gameOver = false;         // Variable, die angibt, ob das Spiel vorbei ist
static bool difficultyChosen = false; // Variable, die angibt ob die Schwierigkeits selektion abgeschlossen ist.
static int button = 0;                // Variable welche sagt welcher Knopf gedrückt wurde (leftButton = 1, rightButton = 2, both = 3)
unsigned long tempTime[4] = {0};      // Variable deklarieren um eine Temporäre Zeit anzugeben [0](0 = nichts, leftButton = 1, rightButton = 2) [1](Zeit des angegebenen Knopfes) [2/3](2 = right, 3 = left | Variabeln um zu zählen ob es ein Press ist oder Konpf losgelassen)

// Statisch Variablen für die Snake deklarieren
static int snakeLength = 0;    // Länge der Schlange
static tPoint snake = {7, 7};  // Position des Schlangenkopfes
static int snakeX = 7;         // X-Position der Schlange
static int snakeY = 7;         // Y-Position der Schlange
static int snakeDirection = 0; // Richtung der Schlange (0 = oben, 1 = rechts, 2 = unten, 3 = links)
static int speed = 0;          // Die Geschindigkeit der Snake
// Statische Variablen für den Schlangenschwanz
static tPoint snakeTail[256] = {0}; // Positionen der Schlangenschwanzpixel.
static int snakeTailX[256] = {0};   // X-Position der Schlangenschwanz-Pixel
static int snakeTailY[256] = {0};   // Y-Position der Schlangenschwanz-Pixel

// Statische Variablen für das Essen deklarieren
static tPoint apple = {0}; // Position des Apfels
static int appleX = 0;     // X-Position des Apfels
static int appleY = 0;     // Y-Position des Apfels

// Timers for certain events
SimpleSoftTimer playAgainTimer(2000);

// Malt den Titelscreen von Snake auf das gewählte Bild
void SnakeTitleScreen(uint8_t image[16][16])
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

// Zeigt ein Menü auf dem Bildschirm um die Schiwerigkeit zu wählen und gibt diesen dann zurück
int ChooseDifficulty(uint8_t image[][16], uint8_t buffer[], QwiicButton leftButton, QwiicButton rightButton)
{
    difficulty = 1;
    difficultyChosen = false;

    while (!difficultyChosen)
    {
        SchweirigskeitScreen(image, difficulty);
        UpdateScreen(buffer, image);
        button = WaitForButtonPress(leftButton, rightButton);

        if (button == 3)
        {
            difficultyChosen = true;
        }

        if (!difficultyChosen)
        {
            Serial.println("Knopf wählen");
            if (button == 1 && difficulty > 1)
            {
                Serial.println("Linker Knopf gedrückt");
                difficulty--;
            }
            else if (button == 2 && difficulty < 3)
            {
                Serial.println("Rechter Knopf gedrückt");
                difficulty++;
            }
        }
    }
    return difficulty;
}

// Malt ein Bild so wie es am Anfang von Snake aussehen sollte
void SnakeSetup(uint8_t image[16][16], tPoint snake)
{
    EmptyScreen(image);

    image[snake.posY][snake.posX] = 1;
}

// Ändert die Richtung von der Snake mit der gegebenen geschindigkeit
void ChangeSnakeDirection(QwiicButton leftButton, QwiicButton rightButton, int &snakeDirection, unsigned long tempTime[4])
{
    unsigned long leftTime = 0;
    unsigned long rightTime = 0;

    bool validTime = false;

    Serial.print("leftbutton queue empty?: ");
    Serial.println(leftButton.isPressedQueueEmpty());
    Serial.print("rightbutton queue empty?: ");
    Serial.println(rightButton.isPressedQueueEmpty());
    Serial.println("tempTime 0, 1, 2, 3: ");
    Serial.println(tempTime[0]);
    Serial.println(tempTime[1]);
    Serial.println(tempTime[2]);
    Serial.println(tempTime[3]);

    if (!leftButton.isPressedQueueEmpty() || !rightButton.isPressedQueueEmpty() || tempTime[0] != 0)
    {
        while (!validTime)
        {
            if (tempTime[0] == 1)
            {
                leftTime = tempTime[1];
                validTime = true;
            }
            else if (!leftButton.isPressedQueueEmpty())
            {
                leftTime = leftButton.popPressedQueue();
                if (tempTime[2] > 0)
                {
                    leftTime = 0;
                    tempTime[2] = 0;
                }
                else
                {
                    validTime = true;
                    tempTime[2]++;
                }
            }
            else
            {
                validTime = true;
            }
        }

        validTime = false;

        while (!validTime)
        {
            if (tempTime[0] == 2)
            {
                rightTime = tempTime[1];
                validTime = true;
            }
            else if (!rightButton.isPressedQueueEmpty())
            {
                rightTime = rightButton.popPressedQueue();
                if (tempTime[3] > 0)
                {
                    rightTime = 0;
                    tempTime[3] = 0;
                }
                else
                {
                    validTime = true;
                    tempTime[3]++;
                }
            }
            else
            {
                validTime = true;
            }
        }

        if (leftTime > 0 && rightTime > 0)
        {
            if (leftTime < rightTime)
            {
                Serial.println("Both not null, left");
                snakeDirection--;
                tempTime[0] = 2;
                tempTime[1] = rightTime;
            }
            else if (rightTime < leftTime)
            {
                Serial.println("Both not null, right");
                snakeDirection++;
                tempTime[0] = 1;
                tempTime[1] = leftTime;
            }
        }
        else
        {
            if (leftTime != 0)
            {
                Serial.println("left null, right");
                snakeDirection--;
                tempTime[0] = 0;
                tempTime[1] = 0;
            }
            else if (rightTime != 0)
            {
                Serial.println("right null, left");
                snakeDirection++;
                tempTime[0] = 0;
                tempTime[1] = 0;
            }
        }
    }
}

// Platziert einen Apfel auf einen Gültigen Ort
void PlantApple(tPoint *apple, tPoint *snake, tPoint snakeTail[], int snakeLength)
{
    bool goodApple = false;

    apple->posX = rand() % 16;
    apple->posY = rand() % 16;
    while (!goodApple)
    {
        if (apple->posX == snake->posX && apple->posY == snake->posY)
        {
            apple->posX = rand() % 16;
            apple->posY = rand() % 16;
        }
        else
        {
            for (int i = 0; i < snakeLength; i++)
            {
                if (apple->posX == snakeTail[i].posX && apple->posY == snakeTail[i].posY)
                {
                    apple->posX = rand() % 16;
                    apple->posY = rand() % 16;
                    break;
                }
            }
            goodApple = true;
        }
    }
}

// Löscht den letzten Teil des Schlangenschwanzes und bewegt den Schwanz
void UpdateSnakeTail(tPoint snake, tPoint snakeTail[], int snakeLength, uint8_t image[][16])
{
    image[snakeTail[snakeLength - 1].posY][snakeTail[snakeLength - 1].posX] = 0;

    for (int i = snakeLength; 1 < i; i--)
    {
        snakeTail[i - 1].posX = snakeTail[i - 2].posX;
        snakeTail[i - 1].posY = snakeTail[i - 2].posY;
    }
    snakeTail[0].posX = snake.posX;
    snakeTail[0].posY = snake.posY;
}

// Bewegt die Schlange in die gegebene Richtung
void SnakeMovement(int &snakeDirection, tPoint *snake)
{
    if (snakeDirection < 0)
    {
        snakeDirection = 3;
    }
    else if (snakeDirection > 3)
    {
        snakeDirection = 0;
    }

    if (snakeDirection == 0)
    {
        snake->posX--;
    }
    else if (snakeDirection == 1)
    {
        snake->posY--;
    }
    else if (snakeDirection == 2)
    {
        snake->posX++;
    }
    else if (snakeDirection == 3)
    {
        snake->posY++;
    }
}

// Überprüft ob die Schlange das Spiel beendet hat
void CheckForGameOver(tPoint *snake, tPoint snakeTail[], int snakeLength, bool &gameOver)
{

    if (snake->posX < 0 || snake->posX >= 16 || snake->posY < 0 || snake->posY >= 16)
    {
        Serial.println("Snake ist aus dem Spiel feld.. Game Over");
        gameOver = true;
    }

    for (int i = 0; i < snakeLength; i++)
    {
        if (snake->posX == snakeTail[i].posX && snake->posY == snakeTail[i].posY)
        {
            Serial.println("Schlange berührt sich selbst... Game Over");
            gameOver = true;
        }
    }
}

// Zeichnet den Apfel, den Schlangenkopf und den Schlangenschwanz
void DrawSnakenApple(tPoint *snake, tPoint *apple, tPoint snakeTail[], uint8_t image[][16], uint8_t buffer[], int snakeLength)
{
    image[snake->posY][snake->posX] = 1;
    image[apple->posY][apple->posX] = 1;

    for (int i = 0; i < snakeLength; i++)
    {
        image[snakeTail[i].posY][snakeTail[i].posX] = 1;
    }

    UpdateScreen(buffer, image);
}

// Malt ein Bild so das es Game Over beinhaltet
void SnakeGameOverScreen(uint8_t image[16][16])
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
void SnakeStartNewScreen(uint8_t image[16][16])
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

// Startet das Spiel Snake
void PlaySnake(uint8_t image[][16], uint8_t buffer[], QwiicButton leftButton, QwiicButton rightButton)
{
    // Titelscreen anzeigen
    SnakeTitleScreen(image);
    UpdateScreen(buffer, image);

    // Auf einen Input warten
    WaitForButtonPress(leftButton, rightButton);

    // Schweirigkeitsgrad auswählen
    difficulty = ChooseDifficulty(image, buffer, leftButton, rightButton);

    // Spiel Variabeln zurücksetzen
    gameOver = false;
    snake = {7, 7};
    snakeLength = 0;
    snakeDirection = 0;
    apple = {0};
    speed = 500 / difficulty;
    tempTime[4] = {0};

    // Timer für den Moveevent
    SimpleSoftTimer moveTimer(speed);

    // Button queues leeren
    ResetButtonQueue(leftButton);
    ResetButtonQueue(rightButton);

    // Screen für Snake vorbereiten
    SnakeSetup(image, snake);
    UpdateScreen(buffer, image);

    // Platziert einen Apfel auf dem Feld
    PlantApple(&apple, &snake, snakeTail, snakeLength);

    // MoveTimer starten
    moveTimer.start(speed);

    // Die Haupt Spiel Schleife für Snake
    while (!gameOver)
    {
        // LEDs vom Controller einschalten falls gedrückt
        LEDOnPress(leftButton, rightButton);

        // Put Red Button Handler here

        // Put Yellow Button Handler here

        // Ändert die Richtung von der Snake
        if (moveTimer.isTimeout())
        {
            ChangeSnakeDirection(leftButton, rightButton, snakeDirection, tempTime);

            // Alten SchlangenKnopf Löschen
            image[snake.posY][snake.posX] = 0;

            // Überprüfen ob die Schlange einen Apfel berührt und einen neuen erstellen
            if (snake.posX == apple.posX && snake.posY == apple.posY)
            {
                snakeLength++;
                PlantApple(&apple, &snake, snakeTail, snakeLength);
            }

            // Schlangenschwanzarray Updaten und hintersten Teil löschen falls es einen hat.
            if (snakeLength > 0)
            {
                UpdateSnakeTail(snake, snakeTail, snakeLength, image);
            }

            // Bewegt die Schlange in die gewählt Richtung
            SnakeMovement(snakeDirection, &snake);

            // Überpüft ob die Schlange die Arena verlässt oder ob sie sich selber berührt
            CheckForGameOver(&snake, snakeTail, snakeLength, gameOver);

            // Malt die Schlange, und den Apfel auf den Screen
            DrawSnakenApple(&snake, &apple, snakeTail, image, buffer, snakeLength);

            moveTimer.restart();
        }
    }

    // Spiel beenden
    SnakeGameOverScreen(image);
    UpdateScreen(buffer, image);

    playAgainTimer.start(2000);
    while (!playAgainTimer.isTimeout())
    {
        // Put Red Button Handler here

        // Put Yellow Button Handler here
    }

    leftButton.LEDoff();
    rightButton.LEDoff();

    // Spielwiederhol Screen anzeigen und auf Benutzereinegabe warten
    SnakeStartNewScreen(image);
    UpdateScreen(buffer, image);
    WaitForButtonPress(leftButton, rightButton);
}