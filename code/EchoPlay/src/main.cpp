#include <Arduino.h>
#include <SparkFun_Qwiic_Button.h>
#include <Wire.h>
#include <IProgramm.h>
#include <Snake.h>
#include <LedWallEncoder.h>
#include <LEDWallDriver.h>
#include <SimpleSoftTimer.h>
#include <EchoPlay.h>
#include <EchoButton.h>
#include <Screen.h>
#include <Car-Jump.h>
#include <WifiConnection.h>
#include <Clock.h>
#include <IGame.h>
#include <Arkanoid.h>

using namespace HolisticSolutions;

// Eine Variable für die Pins definieren
const char pin_enable = GPIO_NUM_15;
const char pin_data = GPIO_NUM_25;
const char pin_clock = GPIO_NUM_26;
const char pin_latch = GPIO_NUM_17;
const char pin_SW1 = GPIO_NUM_16; // Gelber Knopf auf der Hinterseite der LED-Box
const char pin_SW2 = GPIO_NUM_32; // Optional, falls man den Roten Knopf verwenden möchte
// const char mic_pin = GPIO_NUM_34; // Optional, falls ein Mikrofon verwendet wird

enum state
{
  PROGRAMM_SELECTION,

  PROGRAMM_SETUP,
  PROGRAMM_UPDATE,

  GAME_SETUP,
  GAME_START,
  GAME_UPDATE,
  GAME_END
};

bool screenIsOn = true;
bool lastScreenState = true;

state programmState;

QwiicButton leftButton;
QwiicButton rightButton;

EchoButton yellowButton(pin_SW1, true);
EchoButton redButton(pin_SW2, true);

// chooser Objekte
IGame *selectedGame;
IProgramm *selectedProgramm;

// Ausgewähltes Spiel im Array
int selectedProgrammNumber = 0;

// Array mit allen Programmen
IProgramm *programms[] = {
    new Snake(),
    new CarJump(),
    new Clock(),
    new Arkanoid()};

// Anzahl Programme im Array
int programmAmount = sizeof(programms) / sizeof(programms[0]);

// TranslationTable für den Screen
uint8_t TranslationTable[16][16] = {
    {0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0x7F, 0x7E, 0x7D, 0x7C, 0x7B, 0x7A, 0x79, 0x78},
    {0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0, 0x77, 0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70},
    {0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8, 0x6F, 0x6E, 0x6D, 0x6C, 0x6B, 0x6A, 0x69, 0x68},
    {0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0, 0x67, 0x66, 0x65, 0x64, 0x63, 0x62, 0x61, 0x60},
    {0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0x5F, 0x5E, 0x5D, 0x5C, 0x5B, 0x5A, 0x59, 0x58},
    {0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0, 0x57, 0x56, 0x55, 0x54, 0x53, 0x52, 0x51, 0x50},
    {0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0x4F, 0x4E, 0x4D, 0x4C, 0x4B, 0x4A, 0x49, 0x48},
    {0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0, 0x47, 0x46, 0x45, 0x44, 0x43, 0x42, 0x41, 0x40},
    {0xBF, 0xBE, 0xBD, 0xBC, 0xBB, 0xBA, 0xB9, 0xB8, 0x3F, 0x3E, 0x3D, 0x3C, 0x3B, 0x3A, 0x39, 0x38},
    {0xB7, 0xB6, 0xB5, 0xB4, 0xB3, 0xB2, 0xB1, 0xB0, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30},
    {0xAF, 0xAE, 0xAD, 0xAC, 0xAB, 0xAA, 0xA9, 0xA8, 0x2F, 0x2E, 0x2D, 0x2C, 0x2B, 0x2A, 0x29, 0x28},
    {0xA7, 0xA6, 0xA5, 0xA4, 0xA3, 0xA2, 0xA1, 0xA0, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20},
    {0x9F, 0x9E, 0x9D, 0x9C, 0x9B, 0x9A, 0x99, 0x98, 0x1F, 0x1E, 0x1D, 0x1C, 0x1B, 0x1A, 0x19, 0x18},
    {0x97, 0x96, 0x95, 0x94, 0x93, 0x92, 0x91, 0x90, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10},
    {0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x88, 0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08},
    {0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00},
};

Screen echoScreen(TranslationTable);

// Pins vorbereiten
void PreparePins()
{
  pinMode(pin_enable, OUTPUT);
  pinMode(pin_latch, OUTPUT);
  pinMode(pin_data, OUTPUT);
  pinMode(pin_clock, OUTPUT);
  pinMode(pin_SW1, INPUT_PULLUP);
  pinMode(pin_SW2, INPUT_PULLUP);
  digitalWrite(pin_enable, LOW);
  digitalWrite(pin_data, HIGH);
}

void setup()
{
  Wire.begin();
  Serial.begin(115200);

  PreparePins();

  if (leftButton.begin(0x0C, Wire) == false)
  {
    Serial.print("Left Button is Connected: ");
    Serial.println(leftButton.isConnected());

    Serial.print("Left Button has same Adress: ");
    Serial.println(leftButton.checkDeviceID());
  }
  else
  {
    Serial.println("Left Button is ready!");
  }

  if (rightButton.begin(0x10, Wire) == false)
  {
    Serial.print("Right Button is Connected: ");
    Serial.println(rightButton.isConnected());

    Serial.print("right Button has same Adress: ");
    Serial.println(rightButton.checkDeviceID());
  }
  else
  {
    Serial.println("Right Button is ready!");
  }

  connectWifi();

  echoScreen.emptyBuffer();
  echoScreen.update();

  leftButton.clearEventBits();
  rightButton.clearEventBits();

  leftButton.enablePressedInterrupt();
  leftButton.enableClickedInterrupt();
  rightButton.enablePressedInterrupt();
  rightButton.enableClickedInterrupt();

  selectedProgramm = programms[selectedProgrammNumber];
  if (selectedProgramm->isGame())
    selectedGame = static_cast<IGame *>(selectedProgramm);
  else
    selectedGame = nullptr;

  programmState = PROGRAMM_SELECTION;
}

void loop()
{
  LEDOnPress(leftButton, rightButton);

  if (redButton.isPressed() && redButton.hasBeenReleased)
  {
    screenIsOn = !screenIsOn;
    redButton.hasBeenReleased = false;
  }
  else if (!redButton.isPressed())
  {
    redButton.hasBeenReleased = true;
  }

  if (screenIsOn)
  {
    if (yellowButton.isPressed() && yellowButton.hasBeenReleased)
    {
      selectedProgrammNumber++;
      if (selectedProgrammNumber > programmAmount - 1)
      {
        selectedProgrammNumber = 0;
      }
      selectedProgramm = programms[selectedProgrammNumber];

      if (selectedProgramm->isGame())
        selectedGame = static_cast<IGame *>(selectedProgramm);
      else
        selectedGame = nullptr;

      programmState = PROGRAMM_SELECTION;

      leftButton.clearEventBits();
      rightButton.clearEventBits();
      ResetButtonQueue(leftButton);
      ResetButtonQueue(rightButton);

      yellowButton.hasBeenReleased = false;
    }
    else if (!yellowButton.isPressed())
    {
      yellowButton.hasBeenReleased = true;
    }

    switch (programmState)
    {
    case PROGRAMM_SELECTION:
    {
      if (selectedGame)
      {
        programmState = GAME_SETUP;
      }
      else
      {
        programmState = PROGRAMM_UPDATE;
      }

      break;
    }
    case PROGRAMM_SETUP:
    {
      selectedProgramm->setup(echoScreen, leftButton, rightButton);
      programmState = PROGRAMM_UPDATE;
      break;
    }
    case PROGRAMM_UPDATE:
    {
      selectedProgramm->update(echoScreen, leftButton, rightButton);
      break;
    }
    case GAME_SETUP:
    {
      selectedGame->setup(echoScreen, leftButton, rightButton);

      programmState = GAME_START;
      break;
    }
    case GAME_START:
    {
      selectedGame->start(echoScreen, leftButton, rightButton);

      if (leftButton.hasBeenClicked() || rightButton.hasBeenClicked())
      {
        programmState = GAME_UPDATE;
        leftButton.clearEventBits();
        rightButton.clearEventBits();
      }
      break;
    }
    case GAME_UPDATE:
    {
      selectedGame->update(echoScreen, leftButton, rightButton);

      if (selectedGame->isGameOver())
      {
        leftButton.clearEventBits();
        rightButton.clearEventBits();

        programmState = GAME_END;
      }
      break;
    }
    case GAME_END:
    {
      selectedGame->end(echoScreen, leftButton, rightButton);

      if (leftButton.hasBeenClicked() || rightButton.hasBeenClicked())
      {
        programmState = GAME_SETUP;

        leftButton.clearEventBits();
        rightButton.clearEventBits();
      }
      break;
    }
    }
  }
  else
  {
    if (lastScreenState == true)
    {
      programmState = PROGRAMM_SELECTION;

      echoScreen.emptyImage();

      echoScreen.update();
    }
  }

  lastScreenState = screenIsOn;
}