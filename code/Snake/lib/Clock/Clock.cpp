#include "Clock.h"
#include <WifiUdp.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <vector>

std::vector<uint8_t> number1Sprite = {0, 0, 1, 1, 0, 0,
                                      0, 1, 1, 1, 0, 0,
                                      0, 0, 1, 1, 0, 0,
                                      0, 0, 1, 1, 0, 0,
                                      0, 0, 1, 1, 0, 0,
                                      0, 0, 1, 1, 0, 0,
                                      0, 0, 1, 1, 0, 0};
std::vector<uint8_t> number2Sprite = {0, 1, 1, 1, 1, 0,
                                      1, 1, 0, 0, 1, 1,
                                      0, 0, 0, 0, 1, 1,
                                      0, 0, 1, 1, 1, 0,
                                      1, 1, 0, 0, 0, 0,
                                      1, 1, 0, 0, 0, 0,
                                      1, 1, 1, 1, 1, 1};
std::vector<uint8_t> number3Sprite = {0, 1, 1, 1, 1, 0,
                                      1, 1, 0, 0, 1, 1,
                                      0, 0, 0, 0, 1, 1,
                                      0, 0, 1, 1, 1, 0,
                                      0, 0, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      0, 1, 1, 1, 1, 0};
std::vector<uint8_t> number4Sprite = {1, 1, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      1, 1, 1, 1, 1, 1,
                                      0, 0, 0, 0, 1, 1,
                                      0, 0, 0, 0, 1, 1,
                                      0, 0, 0, 0, 1, 1};
std::vector<uint8_t> number5Sprite = {1, 1, 1, 1, 1, 1,
                                      1, 1, 0, 0, 0, 0,
                                      1, 1, 1, 1, 0, 0,
                                      0, 0, 0, 0, 1, 1,
                                      0, 0, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      0, 1, 1, 1, 1, 0};
std::vector<uint8_t> number6Sprite = {0, 1, 1, 1, 1, 0,
                                      1, 1, 0, 0, 0, 0,
                                      1, 1, 1, 1, 1, 0,
                                      1, 1, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      0, 1, 1, 1, 1, 0};
std::vector<uint8_t> number7Sprite = {1, 1, 1, 1, 1, 1,
                                      0, 0, 0, 0, 1, 1,
                                      0, 0, 0, 0, 1, 1,
                                      0, 0, 0, 1, 1, 0,
                                      0, 0, 1, 1, 0, 0,
                                      0, 0, 1, 1, 0, 0,
                                      0, 0, 1, 1, 0, 0};
std::vector<uint8_t> number8Sprite = {0, 1, 1, 1, 1, 0,
                                      1, 1, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      0, 1, 1, 1, 1, 0,
                                      1, 1, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      0, 1, 1, 1, 1, 0};
std::vector<uint8_t> number9Sprite = {0, 1, 1, 1, 1, 0,
                                      1, 1, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      0, 1, 1, 1, 1, 1,
                                      0, 0, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      0, 1, 1, 1, 1, 0};
std::vector<uint8_t> number0Sprite = {0, 1, 1, 1, 1, 1, 0,
                                      1, 1, 1, 1, 1, 1, 1,
                                      1, 1, 0, 0, 0, 1, 1,
                                      1, 1, 0, 0, 0, 1, 1,
                                      1, 1, 0, 0, 0, 1, 1,
                                      1, 1, 1, 1, 1, 1, 1,
                                      0, 1, 1, 1, 1, 1, 0};

std::vector<uint8_t> numberSprites[10]{
    number0Sprite,
    number1Sprite,
    number2Sprite,
    number3Sprite,
    number4Sprite,
    number5Sprite,
    number6Sprite,
    number7Sprite,
    number8Sprite,
    number9Sprite};

void Clock::setup(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    timeClient.begin();
}

void Clock::update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    timeClient.update();

    int hour = timeClient.getHours();
    int minute = timeClient.getMinutes();

    screen.emptyImage();

    screen.drawSpriteOnImage(TopLeftPos.posX, TopLeftPos.posY, numberSprites[hour / 10], numberWidth);
    screen.drawSpriteOnImage(TopRightPos.posX, TopRightPos.posY, numberSprites[hour % 10], numberWidth);
    screen.drawSpriteOnImage(BottomLeftPos.posX, BottomLeftPos.posY, numberSprites[minute / 10], numberWidth);
    screen.drawSpriteOnImage(BottomRightPos.posX, BottomRightPos.posY, numberSprites[minute % 10], numberWidth);

    screen.update();

    Serial.println(timeClient.getFormattedDate());
}