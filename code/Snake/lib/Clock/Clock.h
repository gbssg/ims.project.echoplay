#pragma once

#include <stdint.h>
#include <SparkFun_Qwiic_Button.h>
#include <EchoPlay.h>
#include <Screen.h>
#include <SimpleSoftTimer.h>
#include <IProgramm.h>
#include <WifiUdp.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <vector>

using namespace HolisticSolutions;

class Clock : public IProgramm
{
private:
    int UTC_OFFSET_SECONDS = 3600;
    WiFiUDP ntpUDP;

    NTPClient timeClient{ntpUDP, "pool.ntp.org", UTC_OFFSET_SECONDS, 60000};

    int numberWidth = 6;

    tPoint TopLeftPos{1, 0};
    tPoint TopRightPos{8, 0};
    tPoint BottomLeftPos{2, 9};
    tPoint BottomRightPos{9, 9};

public:
    void setup(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);

    void update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);
};
