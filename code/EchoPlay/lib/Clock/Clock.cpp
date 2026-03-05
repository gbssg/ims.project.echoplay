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
std::vector<uint8_t> number0Sprite = {0, 1, 1, 1, 1, 0,
                                      1, 1, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      1, 1, 0, 0, 1, 1,
                                      0, 1, 1, 1, 1, 0};

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

int x, y;

int yOffsetTop = 0;
int yOffsetBottom = 0;

void Clock::setup(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    timeClient.begin();

    ClockState = SHOW_TIME;
}

void Clock::update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton)
{
    timeClient.update();

    screen.emptyImage();

    if (leftButton.hasBeenClicked() && ClockState == SHOW_TIME)
    {
        ClockState = SHOW_DATE;
        leftButton.clearEventBits();
    }
    else if (rightButton.hasBeenClicked() && ClockState == SHOW_DATE)
    {
        ClockState = SHOW_TIME;
        rightButton.clearEventBits();
    }

    switch (ClockState)
    {
    case SHOW_TIME:
    {
        Serial.println("SHOW TIME");
        int hour = timeClient.getHours();
        int minute = timeClient.getMinutes();
        int second = timeClient.getSeconds();

        if (second < 16)
        {
            x = second;
            y = 0;
            yOffsetTop = 1;
        }
        else if (second < 31)
        {
            x = 15;
            y = second - 15;
            yOffsetTop = 0;
        }
        else if (second < 46)
        {
            x = 45 - second;
            y = 15;
            yOffsetBottom = -1;
        }
        else
        {
            x = 0;
            y = 60 - second;
            yOffsetBottom = 0;
        }

        screen.drawSpriteOnImage(TopLeftPos.posX, TopLeftPos.posY + yOffsetTop, numberSprites[hour / 10], numberWidth);
        screen.drawSpriteOnImage(TopRightPos.posX, TopRightPos.posY + yOffsetTop, numberSprites[hour % 10], numberWidth);
        screen.drawSpriteOnImage(BottomLeftPos.posX, BottomLeftPos.posY + yOffsetBottom, numberSprites[minute / 10], numberWidth);
        screen.drawSpriteOnImage(BottomRightPos.posX, BottomRightPos.posY + yOffsetBottom, numberSprites[minute % 10], numberWidth);

        screen.setPixel(x, y, 1);

        break;
    }
    case SHOW_DATE:
    {
        String formatedDate = timeClient.getFormattedDate();
        int splitT = formatedDate.indexOf("T");

        String dayDate = formatedDate.substring(0, splitT);

        int month = (dayDate[5] - '0') * 10 + (dayDate[6] - '0');
        int day = (dayDate[8] - '0') * 10 + (dayDate[9] - '0');

        screen.drawSpriteOnImage(TopLeftPos.posX, TopLeftPos.posY, numberSprites[day / 10], numberWidth);
        screen.drawSpriteOnImage(TopRightPos.posX, TopRightPos.posY, numberSprites[day % 10], numberWidth);
        screen.drawSpriteOnImage(BottomLeftPos.posX, BottomLeftPos.posY, numberSprites[month / 10], numberWidth);
        screen.drawSpriteOnImage(BottomRightPos.posX, BottomRightPos.posY, numberSprites[month % 10], numberWidth);

        break;
    }
    }

    screen.update();
}