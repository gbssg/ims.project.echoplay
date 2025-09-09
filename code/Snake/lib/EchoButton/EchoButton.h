#pragma once

class EchoButton
{
public:
    // Konstruktor für EchuButton, zuerst die pinNr und dann ob es invertiert ist oder nicht
    EchoButton(const char &pinNr, const bool inverted = false);
    // Überprüft ob der Knopf gedrückt ist oder nicht
    bool isPressed();

private:
    const char _pinNr;    // pinNr vom Knopf
    const bool _inverted; // bool um zu sehen ob der Knopf invertiert ist oder nicht
};