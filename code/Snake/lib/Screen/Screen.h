#pragma once

#include <Arduino.h>

class Screen
{
public:
    uint8_t _image[16][16] = {0};
    uint8_t _buffer[256] = {0};

    Screen(uint8_t translationTable[16][16]);

    void drawImage(uint8_t image[16][16], uint8_t newImage[16][16]);
    void emptyScreen(uint8_t image[16][16]);
    void updateScreen(uint8_t image[16][16], uint8_t buffer[256]);
    void imagePrint(uint8_t image[16][16]);

private:
    uint8_t _translationTable[16][16];
};