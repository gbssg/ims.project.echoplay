#include "Snake.h"
#include <Arduino.h>
#include <LEDWallDriver.h>
#include <LedWallEncoder.h>
#include <SparkFun_Qwiic_Button.h>
#include <SimpleSoftTimer.h>
#include <EchoPlay.h>

using namespace HolisticSolutions;

// Malt den Titelscreen von Snake auf das gewählte Bild
void SnakeStrategy::RenderTitleScreen(Screen &screen)
{
    static uint8_t TitleScreen[16][16] = {
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

    screen.drawImage(TitleScreen);
}

// Wählt mithilfe von difficulty den Richtigen schweirigkeitsscreen
void SnakeStrategy::RenderDifficultyScreen(Screen &screen, int difficulty)
{
    static uint8_t difficultyScreenEinfach[16][16] = {
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

    static uint8_t difficultyScreenMittel[16][16] = {
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

    static uint8_t difficultyScreenSchwer[16][16] = {
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
        screen.drawImage(difficultyScreenEinfach);
    }
    else if (difficulty == 2)
    {
        screen.drawImage(difficultyScreenMittel);
    }
    else if (difficulty == 3)
    {
        screen.drawImage(difficultyScreenSchwer);
    }
}

// Zeigt ein Menü auf dem Bildschirm um die Schiwerigkeit zu wählen und gibt diesen dann zurück
// int Snake::ChooseDifficulty(Screen &screen, QwiicButton leftButton, QwiicButton rightButton)
// {
//     char button = 0;
//     difficulty = 1;
//     bool difficultyChosen = false;
//
//     while (!difficultyChosen)
//     {
//         RenderDifficultyScreen(screen, difficulty);
//         screen.update();
//         button = WaitForButtonPress(leftButton, rightButton);
//
//         if (button == 3)
//         {
//             difficultyChosen = true;
//         }
//
//         if (!difficultyChosen)
//         {
//             Serial.println("Knopf wählen");
//             if (button == 1 && difficulty > 1)
//             {
//                 Serial.println("Linker Knopf gedrückt");
//                 difficulty--;
//             }
//             else if (button == 2 && difficulty < 3)
//             {
//                 Serial.println("Rechter Knopf gedrückt");
//                 difficulty++;
//             }
//         }
//     }
//     return difficulty;
// }

// Malt ein Bild so wie es am Anfang von Snake aussehen sollte
void SnakeStrategy::SnakeSetup(Screen &screen, tPoint snake)
{
    screen.emptyScreen();

    screen.setPixel(snake.posX, snake.posY, 1);
}

// Ändert die Richtung von der Snake mit der gegebenen geschindigkeit
void SnakeStrategy::ChangeSnakeDirection(QwiicButton leftButton, QwiicButton rightButton, int &snakeDirection)
{
    unsigned long leftTime = 0;
    unsigned long rightTime = 0;

    if (!leftButton.isPressedQueueEmpty() || !rightButton.isPressedQueueEmpty() || leftButtonTime.lastPressTime != 0 || rightButtonTime.lastPressTime != 0)
    {
        if (!leftButtonTime.isPress)
        {
            leftButton.popPressedQueue();
            leftButtonTime.isPress = !leftButtonTime.isPress;
        }
        if (!rightButtonTime.isPress)
        {
            rightButton.popPressedQueue();
            rightButtonTime.isPress = !rightButtonTime.isPress;
        }

        if (leftButtonTime.lastPressTime != 0)
        {
            leftTime = leftButtonTime.lastPressTime;
        }
        else if (!leftButton.isPressedQueueEmpty())
        {
            leftTime = leftButton.popPressedQueue();
            leftButtonTime.isPress = !leftButtonTime.isPress;
        }

        if (rightButtonTime.lastPressTime != 0)
        {
            rightTime = rightButtonTime.lastPressTime;
        }
        else if (!rightButton.isPressedQueueEmpty())
        {
            rightTime = rightButton.popPressedQueue();
            rightButtonTime.isPress = !rightButtonTime.isPress;
        }

        if (leftTime > 0 && rightTime > 0)
        {
            if (leftTime < rightTime)
            {
                Serial.println("Both not null, left");
                snakeDirection--;
                rightButtonTime.lastPressTime = rightTime;
            }
            else if (rightTime < leftTime)
            {
                Serial.println("Both not null, right");
                snakeDirection++;
                leftButtonTime.lastPressTime = leftTime;
            }
        }
        else
        {
            if (leftTime != 0)
            {
                Serial.println("left null, right");
                snakeDirection--;
            }
            else if (rightTime != 0)
            {
                Serial.println("right null, left");
                snakeDirection++;
            }
            leftButtonTime.lastPressTime = 0;
            rightButtonTime.lastPressTime = 0;
        }
    }
}

// Platziert einen Apfel auf einen Gültigen Ort
void SnakeStrategy::PlantApple(tPoint *apple, tPoint *snake, tPoint snakeTail[256], int snakeLength)
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
void SnakeStrategy::UpdateSnakeTail(tPoint snake, tPoint snakeTail[256], int snakeLength, Screen &screen)
{
    screen.setPixel(snakeTail[snakeLength - 1].posX, snakeTail[snakeLength - 1].posY, 0);

    for (int i = snakeLength; 1 < i; i--)
    {
        snakeTail[i - 1].posX = snakeTail[i - 2].posX;
        snakeTail[i - 1].posY = snakeTail[i - 2].posY;
    }
    snakeTail[0].posX = snake.posX;
    snakeTail[0].posY = snake.posY;
}

// Bewegt die Schlange in die gegebene Richtung
void SnakeStrategy::MoveSnake(int &snakeDirection, tPoint *snake)
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
void SnakeStrategy::CheckForGameOver(tPoint *snake, tPoint snakeTail[], int snakeLength)
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
void SnakeStrategy::DrawSnakenApple(tPoint *snake, tPoint *apple, tPoint snakeTail[256], Screen &screen, int snakeLength)
{
    screen.setPixel(snake->posX, snake->posY, 1);
    screen.setPixel(apple->posX, apple->posY, 1);

    for (int i = 0; i < snakeLength; i++)
    {
        screen.setPixel(snakeTail[i].posX, snakeTail[i].posY, 1);
    }

    screen.update();
}

// Malt ein Bild so das es Game Over beinhaltet
void SnakeStrategy::RenderGameOverScreen(Screen &screen)
{
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

    screen.drawImage(gameOverScreen);
}

// Malt ein Bild so das es "Again?" auf dem Bild zeigt
void SnakeStrategy::RenderStartNewScreen(Screen &screen)
{
    static uint8_t startNewScreen[16][16] = {
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

    screen.drawImage(startNewScreen);
}

void SnakeStrategy::setup(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    dobbleClickTimer.start(150);
    difficulty = 1;
    gameState = DIFFICULTY_SETUP;
    gameOver = false;
}

void SnakeStrategy::start(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    // Titelscreen anzeigen
    RenderTitleScreen(screen);
    screen.update();
}

void SnakeStrategy::update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    switch (gameState)
    {
    case DIFFICULTY_SETUP:
    {
        ResetButtonQueue(leftButton);
        ResetButtonQueue(rightButton);
        gameState = DIFFICULTY_SELECT;
        break;
    }
    case DIFFICULTY_SELECT:
    {
        RenderDifficultyScreen(screen, difficulty);
        screen.update();

        if (dobbleClickTimer.isTimeout())
        {
            if (!leftButton.isClickedQueueEmpty() && !rightButton.isClickedQueueEmpty())
            {
                Serial.println("doubleklick");
                gameState = GAME_START;
            }
            else if (!leftButton.isClickedQueueEmpty() && difficulty > 1)
            {
                Serial.println("Linker Knopf gedrückt");
                leftButton.popClickedQueue();
                difficulty--;
            }
            else if (!rightButton.isClickedQueueEmpty() && difficulty < 3)
            {
                Serial.println("Rechter Knopf gedrückt");
                rightButton.popClickedQueue();
                difficulty++;
            }
            else
            {
                ResetButtonQueue(leftButton);
                ResetButtonQueue(rightButton);
            }
            dobbleClickTimer.restart();
        }
        break;
    }
    case GAME_START:
    {
        gameOver = false;
        snake = {7, 7};
        snakeLength = 0;
        snakeDirection = 0;
        apple = {0};
        speed = 300 / difficulty;

        // MoveTimer starten
        moveTimer.start(speed);

        // Button queues leeren
        ResetButtonQueue(leftButton);
        ResetButtonQueue(rightButton);

        // Screen für Snake vorbereiten
        SnakeSetup(screen, snake);
        screen.update();

        // Platziert einen Apfel auf dem Feld
        PlantApple(&apple, &snake, snakeTail, snakeLength);

        gameState = PLAYING;
    }
    case PLAYING:
    {
        if (moveTimer.isTimeout())
        {
            ChangeSnakeDirection(leftButton, rightButton, snakeDirection);

            // Alten Schlangenkopf Löschen
            screen.setPixel(snake.posX, snake.posY, false);

            // Überprüfen ob die Schlange einen Apfel berührt und einen neuen erstellen
            if (snake.posX == apple.posX && snake.posY == apple.posY)
            {
                snakeLength++;
                PlantApple(&apple, &snake, snakeTail, snakeLength);
            }

            // Schlangenschwanzarray Updaten und hintersten Teil löschen falls es einen hat.
            if (snakeLength > 0)
            {
                UpdateSnakeTail(snake, snakeTail, snakeLength, screen);
            }

            // Bewegt die Schlange in die gewählt Richtung
            MoveSnake(snakeDirection, &snake);

            // Überpüft ob die Schlange die Arena verlässt oder ob sie sich selber berührt
            CheckForGameOver(&snake, snakeTail, snakeLength);

            // Malt die Schlange, und den Apfel auf den Screen
            DrawSnakenApple(&snake, &apple, snakeTail, screen, snakeLength);

            moveTimer.restart();
        }
    }
    }
}

void SnakeStrategy::end(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    RenderGameOverScreen(screen);
    screen.update();
}

SnakeStrategy::~SnakeStrategy()
{
    Serial.print("Was geht 2");
}