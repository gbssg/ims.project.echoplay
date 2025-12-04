#pragma once

#include <Arduino.h>

class Screen
{
public:
    Screen(uint8_t translationTable[16][16]);

    void drawImage(uint8_t newImage[16][16]);
    void emptyScreen();
    void emptyBuffer();
    void update();
    void imagePrint();
    void setPixel(int x, int y, bool lightOn);

private:
    uint8_t _image[16][16] = {0};
    uint8_t _buffer[256] = {0};
    uint8_t _translationTable[16][16];
};