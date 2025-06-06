#pragma once

#include <stdint.h>

// Fuktionen um verschidene Bilder für das Spiel zu zeichnen
void DrawImage(uint8_t image[16][16], uint8_t newImage[16][16]);
void EmptyScreen(uint8_t image[16][16]);
void UpdateScreen(uint8_t buffer[], uint8_t image[16][16]);
void TitleScreen(uint8_t image[16][16]);
void SchweirigskeitScreen(uint8_t image[16][16], int difficulty);
void SnakeSetup(uint8_t image[16][16], int snakeX, int snakeY);
void GameOverScreen(uint8_t image[16][16]);
void StartNewScreen(uint8_t image[16][16]);

// Funktion um