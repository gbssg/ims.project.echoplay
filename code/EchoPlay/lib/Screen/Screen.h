#pragma once

#include <Arduino.h>
#include <vector>

class Screen
{
private:
    uint8_t image[16][16] = {0};
    uint8_t buffer[256] = {0};
    uint8_t translationTable[16][16];

    const int height = 16;
    const int width = 16;
    const int screenStart = 0;
    const int screenEnd = 15;

public:
    Screen(uint8_t translationTable[16][16]);

    void DrawImage(uint8_t newImage[16][16]);
    void EmptyImage();
    void EmptyBuffer();
    void Update();
    void ImagePrint();
    void SetPixel(int x, int y, bool lightOn);
    void DrawSpriteOnImage(int x, int y, std::vector<uint8_t> sprite, int width);
    int GetHeight();
    int GetWidth();
    int GetScreenStart();
    int GetScreenEnd();
};