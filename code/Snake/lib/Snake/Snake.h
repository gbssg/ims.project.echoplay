#pragma once

#include <stdint.h>
#include <SparkFun_Qwiic_Button.h>

// Ein Punkt auf dem 16x16 Pixel Screen;
typedef struct sPoint tPoint;

// Malt ein das image gleich wie das newImage
void DrawImage(uint8_t image[16][16], uint8_t newImage[16][16]);

// Macht ein gewähltes Bild zu nur nullen
void EmptyScreen(uint8_t image[16][16]);

// Macht ein gewoltes Bild in den Buffer und dieser wird auf den Screen gemalt und angezeigt
void UpdateScreen(uint8_t buffer[], uint8_t image[16][16]);

// Malt den Titelscreen von Snake auf das gewählte Bild
void TitleScreen(uint8_t image[16][16]);

// Wählt mithilfe von difficulty den Richtigen schweirigkeitsscreen
void SchweirigskeitScreen(uint8_t image[16][16], int difficulty);

// Malt ein Bild so wie es am Anfang von Snake aussehen sollte
void SnakeSetup(uint8_t image[16][16], int snakeX, int snakeY);

// Malt ein Bild so das es Game Over beinhaltet
void GameOverScreen(uint8_t image[16][16]);

// Malt ein Bild so das es Again? auf dem Bild zeigt
void StartNewScreen(uint8_t image[16][16]);

// Auf einen Knopfdruck warten mit LED, Gibt zurück welcher Knopf gedrückt worde. (leftButton = 1, rightButton = 2, both = 3)
int WaitForButtonPress(QwiicButton leftButton, QwiicButton rightButton);

// Ändert die Richtung von der Snake mit der gegebenen geschindigkeit
void ChangeSnakeDirection(QwiicButton leftButton, QwiicButton rightButton, int &snakeDirection, int speed);

// Platziert einen Appfel auf einen Gültigen Ort
void PlantApple(int &appleX, int &appleY, int snakeX, int snakeY, int snakeTailX[], int snakeTailY[], int snakeLength);

// Updatet den Schlangenschwanz
void UpdateSnakeTail(int snakeX, int snakeY, int snakeTailX[], int snakeTailY[], int snakeLength, uint8_t image[][16]);

// Bewegt die Schlange in die gegebene Richtung
void SnakeMovement(int snakeDirection, int &snakeX, int &snakeY);

// Überprüft ob die Schlange das Spiel beendet hat
void CheckForGameOver(int snakeX, int snakeY, int snakeTailX[], int snakeTailY[], int snakeLength, bool &gameOver);

// Zeichnet den Appfel, den Schlangenkopf und den Schlangenschwanz
void DrawSnakenApple(int snakeX, int snakeY, int appleX, int appleY, int snakeTailX[], int snakeTailY[], uint8_t image[][16], uint8_t buffer[], int snakeLength);