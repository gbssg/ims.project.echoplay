#include "Screen.h"
#include <LedWallEncoder.h>
#include <LEDWallDriver.h>

// Konstruktor der Screen Klasse
Screen::Screen(uint8_t translationTable[16][16])
{
    for (uint8_t i = 0; i < 16; i++)
    {
        for (uint8_t j = 0; j < 16; j++)
        {
            _translationTable[i][j] = translationTable[i][j];
        }
    }
}

// Malt ein das image gleich wie das newImage
void Screen::drawImage(uint8_t newImage[16][16])
{
    for (uint8_t i = 0; i < 16; i++)
    {
        for (uint8_t j = 0; j < 16; j++)
        {
            _image[i][j] = newImage[i][j];
        }
    }
}

// Macht ein gewähltes Bild zu nur nullen
void Screen::emptyScreen()
{
    for (uint8_t i = 0; i < 16; i++)
    {
        for (uint8_t j = 0; j < 16; j++)
        {
            _image[i][j] = 0;
        }
    }
}

// Empties the buffer
void Screen::emptyBuffer()
{
    for (int i = 0; i < 256; i++)
    {
        _buffer[i] = 0;
    }
}

// Macht ein gewoltes Bild in den Buffer und dieser wird auf den Screen gemalt und angezeigt
void Screen::update()
{
    LWC_Encode(_buffer, _image, _translationTable);

    WD_BufferOutput(_buffer);
}

// Ein Funktion von der Glyph Library um den jetzigen zustand vom Screen zu malen
void Screen::imagePrint()
{
    Serial.println("+----------------------------------+");
    for (int y = 0; y < 16; y++)
    {
        Serial.print("| ");
        for (int x = 0; x < 16; x++)
        {
            Serial.print(_image[y][x] > 0 ? "XX" : "  ");
        }
        Serial.println(" |");
    }
    Serial.println("+----------------------------------+");
}

// Setzt ein Pixel auf dem image (lightOn bestimmt ob an oder aus)
void Screen::setPixel(int x, int y, bool lightOn)
{
    _image[y][x] = lightOn ? 1 : 0;
}