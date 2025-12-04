#include "EchoPlay.h"
#include <Arduino.h>
#include <LEDWallDriver.h>
#include <LedWallEncoder.h>
#include <SparkFun_Qwiic_Button.h>
#include <SimpleSoftTimer.h>

using namespace HolisticSolutions;

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