#include "EchoPlay.h"
#include <Arduino.h>
#include <LEDWallDriver.h>
#include <LedWallEncoder.h>
#include <SparkFun_Qwiic_Button.h>
#include <SimpleSoftTimer.h>

using namespace HolisticSolutions;

Compositor::Compositor()
{
}

void Compositor::startProgramm(uint8_t image[16][16], uint8_t buffer[256], QwiicButton leftButton, QwiicButton rightButton)
{
}

Composition::Composition(Compositor *compositor) : _compositor(compositor)
{
}

void Composition::startProgramm(uint8_t image[16][16], uint8_t buffer[256], QwiicButton leftButton, QwiicButton rightButton)
{
    _compositor->startProgramm(image, buffer, leftButton, rightButton);
}

// Malt ein das image gleich wie das newImage
void DrawImage(uint8_t image[16][16], uint8_t newImage[][16])
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
void UpdateScreen(uint8_t buffer[256], uint8_t image[16][16])
{
    LWC_Encode(buffer, image);

    WD_BufferOutput(buffer);
}

// Setzt ein Button Queue zurück
void ResetButtonQueue(QwiicButton button)
{
    while (!button.isClickedQueueEmpty())
    {
        button.popClickedQueue();
    }
    while (!button.isPressedQueueEmpty())
    {
        button.popPressedQueue();
    }
}

// Auf einen Knopfdruck warten mit LED, Gibt zurück welcher Knopf gedrückt worde. (leftButton = 1, rightButton = 2, both = 3)
int WaitForButtonPress(QwiicButton leftButton, QwiicButton rightButton)
{
    SimpleSoftTimer dobbleClickTimer(200);

    ResetButtonQueue(rightButton);
    ResetButtonQueue(leftButton);

    while (rightButton.isPressedQueueEmpty() && leftButton.isPressedQueueEmpty())
    {
        LEDOnPress(leftButton, rightButton);

        // Put Red Button Handler here

        // Put Yellow Button Handler here
    }

    dobbleClickTimer.start(200);

    while (!dobbleClickTimer.isTimeout())
    {
        if (!rightButton.isPressedQueueEmpty() && !leftButton.isPressedQueueEmpty())
        {
            return 3;
        }
        // Put Red Button Handler here

        // Put Yellow Button Handler here
    }

    if (leftButton.isPressedQueueEmpty() == false)
    {
        leftButton.LEDoff();
        return 1;
    }
    if (rightButton.isPressedQueueEmpty() == false)
    {
        rightButton.LEDoff();
        return 2;
    }

    return 0;
}

// Überprüft ob ein Knopfgedrückt ist und aktiviert die LED für den Knopf
void LEDOnPress(QwiicButton leftButton, QwiicButton rightButton)
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

// Ein Funktion von der Glyph Library um den jetzigen zustand vom Screen zu malen
void ImagePrint(const uint8_t image[16][16])
{
    Serial.println("+----------------------------------+");
    for (int y = 0; y < 16; y++)
    {
        Serial.print("| ");
        for (int x = 0; x < 16; x++)
        {
            Serial.print(image[y][x] > 0 ? "XX" : "  ");
        }
        Serial.println(" |");
    }
    Serial.println("+----------------------------------+");
}