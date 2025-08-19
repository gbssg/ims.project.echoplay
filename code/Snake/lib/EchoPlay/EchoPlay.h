#pragma once

#include <stdint.h>
#include <SparkFun_Qwiic_Button.h>

// Ein Punkt auf dem 16x16 Pixel Screen;
typedef struct sPoint
{
    uint8_t posX;
    uint8_t posY;
} tPoint;

// Malt ein das image gleich wie das newImage
void DrawImage(uint8_t image[16][16], uint8_t newImage[16][16]);

// Macht ein gewähltes Bild zu nur nullen
void EmptyScreen(uint8_t image[16][16]);

// Macht ein gewoltes Bild in den Buffer und dieser wird auf den Screen gemalt und angezeigt
void UpdateScreen(uint8_t buffer[], uint8_t image[16][16]);

// Setzt ein Button Queue zurück
void ResetButtonQueue(QwiicButton button);

// Auf einen Knopfdruck warten mit LED, Gibt zurück welcher Knopf gedrückt worde. (leftButton = 1, rightButton = 2, both = 3)
int WaitForButtonPress(QwiicButton leftButton, QwiicButton rightButton);

// Überprüft ob ein Knopfgedrückt ist und aktiviert die LED für den Knopf
void LEDOnPress(QwiicButton leftButton, QwiicButton rightButton);