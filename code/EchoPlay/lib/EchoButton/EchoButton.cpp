#include "EchoButton.h"
#include "Arduino.h"

EchoButton::EchoButton(const char &pinNr, const bool inverted) : _pinNr(pinNr), _inverted(inverted)
{
}

bool EchoButton::isPressed()
{
    bool status = digitalRead(_pinNr);

    if (_inverted)
    {
        return !status;
    }
    else
    {
        return status;
    }
}