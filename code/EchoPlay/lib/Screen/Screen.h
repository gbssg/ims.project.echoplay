#pragma once

#include <Arduino.h>
#include <vector>

class Screen
{
public:
    Screen(uint8_t translationTable[16][16]);

    void drawImage(uint8_t newImage[16][16]);
    void emptyImage();
    void emptyBuffer();
    void update();
    void imagePrint();
    void setPixel(int x, int y, bool lightOn);
    void drawSpriteOnImage(int x, int y, std::vector<uint8_t> sprite, int width);

private:
    uint8_t _image[16][16] = {0};
    uint8_t _buffer[256] = {0};
    uint8_t _translationTable[16][16];
};