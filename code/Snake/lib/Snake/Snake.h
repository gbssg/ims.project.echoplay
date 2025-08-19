#pragma once

#include <stdint.h>
#include <SparkFun_Qwiic_Button.h>
#include <EchoPlay.h>

// Malt den Titelscreen von Snake auf das gewählte Bild
void SnakeTitleScreen(uint8_t image[16][16]);

// Wählt mithilfe von difficulty den Richtigen schweirigkeitsscreen
void SchweirigskeitScreen(uint8_t image[16][16], int difficulty);

// Malt ein Bild so wie es am Anfang von Snake aussehen sollte
void SnakeSetup(uint8_t image[16][16], tPoint snake);

// Malt ein Bild so das es Game Over beinhaltet
void SnakeGameOverScreen(uint8_t image[16][16]);

// Malt ein Bild so das es Again? auf dem Bild zeigt
void StartNewScreen(uint8_t image[16][16]);

// Ändert die Richtung von der Snake mit der gegebenen geschindigkeit
void ChangeSnakeDirection(QwiicButton leftButton, QwiicButton rightButton, int &snakeDirection, int speed, unsigned long tempTime[3]);

// Platziert einen Appfel auf einen Gültigen Ort
void PlantApple(tPoint *apple, tPoint *snake, tPoint snakeTail[], int snakeLength);

// Updatet den Schlangenschwanz
void UpdateSnakeTail(tPoint snake, tPoint snakeTail[], int snakeLength, uint8_t image[][16]);

// Bewegt die Schlange in die gegebene Richtung
void SnakeMovement(int &snakeDirection, tPoint *snake);

// Überprüft ob die Schlange das Spiel beendet hat
void CheckForGameOver(tPoint snake, tPoint snakeTail[], int snakeLength, bool &gameOver);

// Zeichnet den Appfel, den Schlangenkopf und den Schlangenschwanz
void DrawSnakenApple(tPoint snake, tPoint apple, tPoint snakeTail[], uint8_t image[][16], uint8_t buffer[], int snakeLength);

// Startet das Spiel Snake
void PlaySnake(uint8_t image[][16], uint8_t buffer[], QwiicButton leftButton, QwiicButton rightButton);