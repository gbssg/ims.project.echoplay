#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

void DrawScreen(int screenState[16][16], int newScreenState[16][16], int screenHoehe, int screenBreite)
{
    for (int i = 0; i < screenHoehe; i++)
    {
        for (int j = 0; j < screenBreite; j++)
        {
            screenState[i][j] = newScreenState[i][j];
        }
    }
}

// Schreibt den aktuellen Zustand des Bildschirms in die Konsole
// Die Funktion erwartet ein 2D-Array, das den Zustand des Bildschirms darstellt
void UpdateScreen(int screenState[16][16], int screenHoehe, int screenBreite)
{
    system("cls");
    for (int i = 0; i < screenHoehe; i++)
    {
        for (int j = 0; j < screenBreite; j++)
        {
            if (screenState[i][j] == 0)
            {
                printf("\xb0\xb0");
            }
            else
            {
                printf("\xb2\xb2");
            }
        }
        printf("\n");
    }
    return;
}

// Erstellt den Titelbildschirm
// Die Funktion erwartet ein 2D-Array, das den Zustand des Bildschirms darstellt
// und füllt es mit dem Titelbildschirm
void TitleScreen(int screenState[16][16], int screenHoehe, int screenBreite)
{
    int titleScreen[16][16] = {
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

    DrawScreen(screenState, titleScreen, screenHoehe, screenBreite);
}

int SchwierigkeitsWahl(int screenState[16][16], int screenHoehe, int screenBreite)
{
    int difficulty = 1;
    int difficultyScreenEinfach[16][16] = {
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

    int difficultyScreenMittel[16][16] = {
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

    int difficultyScreenSchwer[16][16] = {
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

    DrawScreen(screenState, difficultyScreenEinfach, screenHoehe, screenBreite);
    UpdateScreen(screenState, screenHoehe, screenBreite);

    // Warte auf Benutzereingabe
    // Die Eingabe wird mit der getch()-Funktion gelesen
    // und die Schwierigkeit wird entsprechend angepasst
    while (1)
    {
        int key = getch();

        if (key == 13)
        {
            break;
        }
        else if ((key == 65 || key == 97) && difficulty > 1)
        {
            difficulty--;
        }
        else if ((key == 68 || key == 100) && difficulty < 3)
        {
            difficulty++;
        }

        // Aktualisiere den Bildschirm basierend auf der Schwierigkeit
        if (difficulty == 1)
        {
            DrawScreen(screenState, difficultyScreenEinfach, screenHoehe, screenBreite);
        }
        else if (difficulty == 2)
        {
            DrawScreen(screenState, difficultyScreenMittel, screenHoehe, screenBreite);
        }
        else if (difficulty == 3)
        {
            DrawScreen(screenState, difficultyScreenSchwer, screenHoehe, screenBreite);
        }
        // Aktualisiere den Bildschirm
        UpdateScreen(screenState, screenHoehe, screenBreite);
    }

    return difficulty;
}

// Setzt den Bildschirmzustand für das Snake-Spiel
// Die Funktion erwartet ein 2D-Array, das den Zustand des Bildschirms darstellt
void SnakeSetup(int screenState[16][16], int screenHoehe, int screenBreite, int snakeX, int snakeY)
{
    for (int i = 0; i < screenHoehe; i++)
    {
        for (int j = 0; j < screenBreite; j++)
        {
            screenState[i][j] = 0;
        }
    }
    // Setzt den Schlangenkopf in die Mitte des Bildschirms
    screenState[snakeY][snakeX] = 1;
}

void GameOverScreen(int screenState[16][16], int screenHoehe, int screenBreite)
{
    int gameOverScreen[16][16] = {
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

    DrawScreen(screenState, gameOverScreen, screenHoehe, screenBreite);
}

void StartNewScreen(int screenState[16][16], int screenHoehe, int screenBreite)
{
    int startNewScreen[16][16] = {
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

    DrawScreen(screenState, startNewScreen, screenHoehe, screenBreite);
}

int main()
{
    // Deklarationen
    int difficulty = 0;
    int screenBreite = 16;
    int screenHoehe = 16;
    int direction = 0;
    int snakeLength = 0;
    int snakeX = 7;
    int snakeY = 7;
    int gameOver = 0;
    int appleX = 0;
    int appleY = 0;
    int snakeTailX[256] = {0};
    int snakeTailY[256] = {0};
    int gameOn = 1;
    int again = 0;
    int screenState[16][16] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    while (gameOn)
    {
        // Setze den Bildschirmzustand auf den Titelbildschirm
        TitleScreen(screenState, screenHoehe, screenBreite);
        // Aktualisiere den Bildschirm
        UpdateScreen(screenState, screenHoehe, screenBreite);
        // Warte auf Benutzereingabe
        while (getchar() != '\n')
            ;
        // Setze den Bildschirmzustand auf den difficulty-Bildschirm
        difficulty = SchwierigkeitsWahl(screenState, screenHoehe, screenBreite);
        // Setze den Bildschirmzustand für das Snake-Spiel
        SnakeSetup(screenState, screenHoehe, screenBreite, snakeX, snakeY);
        // Setzt den Apfel in eine zufällige Position
        gameOver = 0;
        // Setze die Schlange zurück
        snakeX = 7;
        snakeY = 7;
        snakeLength = 0;
        direction = 0;
        // Setze den Bildschirmzustand für das Snake-Spiel
        SnakeSetup(screenState, screenHoehe, screenBreite, snakeX, snakeY);
        // Setze den Apfel in eine zufällige Position
        int gueltigeNummer = 0;
        while (!gueltigeNummer)
        {
            appleX = rand() % screenBreite;
            appleY = rand() % screenHoehe;
            if (appleX == snakeX && appleY == snakeY)
            {
                continue;
            }
            else
            {
                gueltigeNummer = 1;
            }
        }
        screenState[appleY][appleX] = 1;
        // Setze den Bildschirmzustand auf den Spielbildschirm
        UpdateScreen(screenState, screenHoehe, screenBreite);
        while (!gameOver)
        {
            int key = -1;
            int waited = 0;

            // Warte eine Zeit lang, die von der Schwierigkeit abhängt bis man
            // in der man die Richtung ändern kann
            while (waited < (30 / difficulty))
            {
                if (kbhit())
                {
                    key = getch();
                    if (key == 27)
                    {
                        gameOver = 1;
                        gameOn = 0;
                        break;
                    }
                    else if (key == 97 || key == 65)
                    {
                        if (direction == 0)
                        {
                            direction = 3;
                        }
                        else
                        {
                            direction--;
                        }
                        Sleep((300 / difficulty) - waited);
                        break;
                    }
                    else if (key == 68 || key == 100)
                    {
                        if (direction == 3)
                        {
                            direction = 0;
                        }
                        else
                        {
                            direction++;
                        }
                        Sleep((300 / difficulty) - waited);
                        break;
                    }
                }
                Sleep(1);
                waited++;
            }

            if (snakeX == appleX && snakeY == appleY)
            {
                snakeLength++;
                appleX = rand() % screenBreite;
                appleY = rand() % screenHoehe;

                // Stelle sicher, dass der Apfel nicht auf dem Schlangenkopf oder auf dem Schlangeschwanz erscheint
                for (int i = 0; i < snakeLength; i++)
                {
                    if (appleX == snakeTailX[i] && appleY == snakeTailY[i])
                    {
                        appleX = rand() % screenBreite;
                        appleY = rand() % screenHoehe;
                        i = -1; // Überprüfe erneut alle Segmente
                    }
                }
            }

            // Alten Schlangenkopf löschen
            screenState[snakeY][snakeX] = 0;

            if (snakeLength > 0)
            {
                // Alten letzen Schlangenschwanzteil löschen
                screenState[snakeTailY[snakeLength - 1]][snakeTailX[snakeLength - 1]] = 0;
                // Setze den Schlangenschwanz auf die alte Position
                for (int i = snakeLength; 1 < i; i--)
                {
                    snakeTailX[i - 1] = snakeTailX[i - 2];
                    snakeTailY[i - 1] = snakeTailY[i - 2];
                }
                snakeTailX[0] = snakeX;
                snakeTailY[0] = snakeY;
            }

            if (direction == 0)
            {
                snakeX--;
            }
            else if (direction == 1)
            {
                snakeY--;
            }
            else if (direction % 4 == 2)
            {
                snakeX++;
            }
            else if (direction == 3)
            {
                snakeY++;
            }

            if (snakeX < 0 || snakeX >= screenBreite || snakeY < 0 || snakeY >= screenHoehe)
            {
                gameOver = 1;
            }
            // Überprüfe, ob die Schlange sich selbst beißt
            for (int i = 0; i < snakeLength; i++)
            {
                if (snakeX == snakeTailX[i] && snakeY == snakeTailY[i])
                {
                    gameOver = 1;
                }
            }

            // Setze den Schlangenkopf auf die neue Position
            screenState[snakeY][snakeX] = 1;
            // Setze den Apfel auf die neue Position
            screenState[appleY][appleX] = 1;
            // Setze den Schlangenschwanz auf die alte Position
            for (int i = 0; i < snakeLength; i++)
            {
                screenState[snakeTailY[i]][snakeTailX[i]] = 1;
            }

            UpdateScreen(screenState, screenHoehe, screenBreite);
        }
        // Spiel beendet
        GameOverScreen(screenState, screenHoehe, screenBreite);
        UpdateScreen(screenState, screenHoehe, screenBreite);
        Sleep(3000);
        // Warte auf Benutzereingabe
        StartNewScreen(screenState, screenHoehe, screenBreite);
        UpdateScreen(screenState, screenHoehe, screenBreite);
        again = 0;
        while (!again)
        {
            if (kbhit())
            {
                int key = getch();
                if (key == 13)
                {
                    again = 1;
                }
                else if (key == 27)
                {
                    gameOn = 0;
                    again = 1;
                }
            }
        }
    }

    return 0;
}
