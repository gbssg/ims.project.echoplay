#pragma once

#include <stdint.h>
#include <SparkFun_Qwiic_Button.h>
#include <EchoPlay.h>
#include <Screen.h>
#include <SimpleSoftTimer.h>
#include <IGame.h>

using namespace HolisticSolutions;

class Snake : public IGame
{
private:
    // Allgemeine Variablen für das Spiel deklarieren
    int difficulty; // 1 = Easy, 2 = Medium, 3 = Hard

    typedef struct sButtonTime
    {
        double lastPressTime = 0;
        bool isPress = true;
    } tButtonTime;

    tButtonTime leftButtonTime;
    tButtonTime rightButtonTime;

    // Teigt den Status des Spieles
    enum state
    {
        DIFFICULTY_SETUP,
        DIFFICULTY_SELECT,
        GAME_START,
        PLAYING
    };
    state gameState;

    // Statisch Variablen für die Snake deklarieren
    int snakeLength;    // Länge der Schlange
    tPoint snake;       // Position des Schlangenkopfes
    int snakeDirection; // Richtung der Schlange (0 = oben, 1 = rechts, 2 = unten, 3 = links)
    int speed;          // Die Geschindigkeit der Snake

    SimpleSoftTimer dobbleClickTimer{150};

    SimpleSoftTimer moveTimer{0};

    // Variablen für den Schlangenschwanz
    tPoint snakeTail[256]; // Positionen der Schlangenschwanzpixel.

    // Variablen für den Appfel deklarieren
    tPoint apple; // Position des Apfels

    // Malt den Titelscreen von Snake auf das gewählte Bild
    void RenderTitleScreen(Screen &Screen);

    // Wählt mithilfe von difficulty den Richtigen schweirigkeitsscreen
    void RenderDifficultyScreen(Screen &screen, int difficulty);

    // Zeigt ein Menü auf dem Bildschirm um die Schiwerigkeit zu wählen und gibt diesen dann zurück
    int ChooseDifficulty(Screen &screen, QwiicButton leftButton, QwiicButton rightButton);

    // Malt ein Bild so wie es am Anfang von Snake aussehen sollte
    void SnakeSetup(Screen &screen, tPoint snake);

    // Ändert die Richtung von der Snake mit der gegebenen geschindigkeit
    void ChangeSnakeDirection(QwiicButton leftButton, QwiicButton rightButton, int &snakeDirection);

    // Platziert einen Apfel auf einen Gültigen Ort
    void PlantApple(tPoint *apple, tPoint *snake, tPoint snakeTail[], int snakeLength);

    // Löscht den letzten Teil des Schlangenschwanzes und bewegt den Schwanz
    void UpdateSnakeTail(tPoint snake, tPoint snakeTail[], int snakeLength, Screen &screen);

    // Bewegt die Schlange in die gegebene Richtung
    void MoveSnake(int &snakeDirection, tPoint *snake);

    // Überprüft ob die Schlange das Spiel beendet hat
    void CheckForGameOver(tPoint *snake, tPoint snakeTail[], int snakeLength);

    // Zeichnet den Apfel, den Schlangenkopf und den Schlangenschwanz
    void DrawSnakenApple(tPoint *snake, tPoint *apple, tPoint snakeTail[], Screen &screen, int snakeLength);

    // Malt ein Bild so das es Game Over beinhaltet
    void RenderGameOverScreen(Screen &screen);

    // Malt ein Bild so das es Again? auf dem Bild zeigt
    void RenderStartNewScreen(Screen &screen);

    // Startet das Spiel Snake
    void PlaySnake(Screen &screen, QwiicButton leftButton, QwiicButton rightButton);

public:
    void setup(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);

    void start(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);

    void update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);

    void end(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);

    ~Snake();
};
