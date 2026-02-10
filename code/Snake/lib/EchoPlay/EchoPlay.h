#pragma once

#include <stdint.h>
#include <Screen.h>
#include <SparkFun_Qwiic_Button.h>

// Ein Punkt auf dem 16x16 Pixel Screen;
typedef struct sPoint
{
    int posX;
    int posY;
} tPoint;

typedef struct sVelocity
{
    int xVel;
    int yVel;
} tVelocity;

// Setzt ein Button Queue zurück
void ResetButtonQueue(QwiicButton button);

// Auf einen Knopfdruck warten mit LED, Gibt zurück welcher Knopf gedrückt worde. (leftButton = 1, rightButton = 2, both = 3)
int WaitForButtonPress(QwiicButton leftButton, QwiicButton rightButton);

// Überprüft ob ein Knopfgedrückt ist und aktiviert die LED für den Knopf
void LEDOnPress(QwiicButton leftButton, QwiicButton rightButton);