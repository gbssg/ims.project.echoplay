#pragma once

#include <stdint.h>
#include <SparkFun_Qwiic_Button.h>
#include <EchoPlay.h>

class Snake : public Compositor
{
public:
    Snake();

    void startProgramm(uint8_t image[16][16], uint8_t buffer[256], QwiicButton leftButton, QwiicButton rightButton);
};

// Malt den Titelscreen von Snake auf das gewählte Bild
void SnakeTitleScreen(uint8_t image[16][16]);

// Wählt mithilfe von difficulty den Richtigen schweirigkeitsscreen
void SchweirigskeitScreen(uint8_t image[16][16], int difficulty);

// Zeigt ein Menü auf dem Bildschirm um die Schiwerigkeit zu wählen und gibt diesen dann zurück
int ChooseDifficulty(uint8_t image[16][16], uint8_t buffer[256], QwiicButton leftButton, QwiicButton rightButton);

// Malt ein Bild so wie es am Anfang von Snake aussehen sollte
void SnakeSetup(uint8_t image[16][16], tPoint snake);

// Ändert die Richtung von der Snake mit der gegebenen geschindigkeit
void ChangeSnakeDirection(QwiicButton leftButton, QwiicButton rightButton, int &snakeDirection, unsigned long tempTime[4]);

// Platziert einen Apfel auf einen Gültigen Ort
void PlantApple(tPoint *apple, tPoint *snake, tPoint snakeTail[], int snakeLength);

// Löscht den letzten Teil des Schlangenschwanzes und bewegt den Schwanz
void UpdateSnakeTail(tPoint snake, tPoint snakeTail[], int snakeLength, uint8_t image[16][16]);

// Bewegt die Schlange in die gegebene Richtung
void SnakeMovement(int &snakeDirection, tPoint *snake);

// Überprüft ob die Schlange das Spiel beendet hat
void CheckForGameOver(tPoint *snake, tPoint snakeTail[], int snakeLength, bool &gameOver);

// Zeichnet den Apfel, den Schlangenkopf und den Schlangenschwanz
void DrawSnakenApple(tPoint *snake, tPoint *apple, tPoint snakeTail[], uint8_t image[16][16], uint8_t buffer[256], int snakeLength);

// Malt ein Bild so das es Game Over beinhaltet
void SnakeGameOverScreen(uint8_t image[16][16]);

// Malt ein Bild so das es Again? auf dem Bild zeigt
void SnakeStartNewScreen(uint8_t image[16][16]);

// Startet das Spiel Snake
void PlaySnake(uint8_t image[][16], uint8_t buffer[], QwiicButton leftButton, QwiicButton rightButton);