#include "Screen.h"
#include <LedWallEncoder.h>
#include <LEDWallDriver.h>

// Konstruktor der Screen Klasse
Screen::Screen(uint8_t newTranslationTable[16][16])
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            translationTable[i][j] = newTranslationTable[i][j];
        }
    }
}

// Malt ein das image gleich wie das newImage
void Screen::DrawImage(uint8_t newImage[16][16])
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            image[i][j] = newImage[i][j];
        }
    }
}

// Macht Bild zu nur nullen
void Screen::EmptyImage()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            image[i][j] = 0;
        }
    }
}

// Empties the buffer
void Screen::EmptyBuffer()
{
    for (int i = 0; i < 256; i++)
    {
        buffer[i] = 0;
    }
}

// Macht ein gewoltes Bild in den Buffer und dieser wird auf den Screen gemalt und angezeigt
void Screen::Update()
{
    LWC_Encode(buffer, image, translationTable);

    WD_BufferOutput(buffer);
}

// Ein Funktion von der Glyph Library um den jetzigen zustand vom Screen zu malen
void Screen::ImagePrint()
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

// Setzt ein Pixel auf dem image (lightOn bestimmt ob an oder aus)
void Screen::SetPixel(int x, int y, bool lightOn)
{
    if ((x >= screenStart && y >= screenStart) && (x <= screenEnd && y <= screenEnd))
    {
        image[y][x] = lightOn ? 1 : 0;
    }
}

void Screen::DrawSpriteOnImage(int x, int y, std::vector<uint8_t> sprite, int width)
{
    if (width <= 0)
        return;
    int height = (int)sprite.size() / width;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (sprite[i * width + j] == 1)
            {
                int pixelX = x + j;
                int pixelY = y + i;

                SetPixel(pixelX, pixelY, true);
            }
        }
    }
}

int Screen::GetHeight()
{
    return height;
}

int Screen::GetWidth()
{
    return width;
}

int Screen::GetScreenStart()
{
    return screenStart;
}

int Screen::GetScreenEnd()
{
    return screenEnd;
}