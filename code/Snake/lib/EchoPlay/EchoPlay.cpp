#include "EchoPlay.h"
#include <Arduino.h>
#include <LEDWallDriver.h>
#include <LedWallEncoder.h>
#include <SparkFun_Qwiic_Button.h>
#include <SimpleSoftTimer.h>

using namespace HolisticSolutions;

// Malt ein das image gleich wie das newImage
void DrawImage(uint8_t image[][16], uint8_t newImage[][16])
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
void UpdateScreen(uint8_t buffer[], uint8_t image[16][16])
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
    uint8_t button = 0;

    ResetButtonQueue(rightButton);
    ResetButtonQueue(leftButton);

    while (rightButton.isClickedQueueEmpty() == true && leftButton.isClickedQueueEmpty() == true)
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

    delay(100);

    if (leftButton.isClickedQueueEmpty() == false)
    {
        leftButton.LEDoff();
        button += 1;
    }
    if (rightButton.isClickedQueueEmpty() == false)
    {
        rightButton.LEDoff();
        button += 2;
    }

    return button;
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