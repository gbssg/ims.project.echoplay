#include <Arduino.h>
#include <SparkFun_Qwiic_Button.h>
#include <Wire.h>
#include <Snake.h>
#include <LedWallEncoder.h>
#include <ClockProvider.h>
#include <LEDWallDriver.h>
#include <Glyph.h>
#include <SimpleSoftTimer.h>
#include <EchoPlay.h>

using namespace HolisticSolutions;

QwiicButton leftButton;  // linken Knopf initialisieren
QwiicButton rightButton; // Rechten Knipf initialisieren

// Eine Variable für die Pins definieren
const char pin_enable = GPIO_NUM_15;
const char pin_data = GPIO_NUM_25;
const char pin_clock = GPIO_NUM_26;
const char pin_latch = GPIO_NUM_17;
const char pin_SW1 = GPIO_NUM_16; // Gelber Knopf auf der Hinterseite der LED-Box
const char pin_SW2 = GPIO_NUM_32; // Optional, falls man den Roten Knopf verwenden möchte
// const char microphone_pin = GPIO_NUM_34; // Optional, falls ein Mikrofon verwendet wird

// Statische Variablen für den Bildschirm deklarieren
static uint8_t buffer[256] = {0};
static uint8_t image[16][16] = {0};

void setup()
{
  // prepares GPIO's for further instructions
  pinMode(pin_enable, OUTPUT);
  pinMode(pin_latch, OUTPUT);
  pinMode(pin_data, OUTPUT);
  pinMode(pin_clock, OUTPUT);
  pinMode(pin_SW1, INPUT_PULLUP);
  pinMode(pin_SW2, INPUT_PULLUP);
  digitalWrite(pin_enable, LOW);
  digitalWrite(pin_data, HIGH);

  WD_BufferOutput(buffer);

  Wire.begin();         // I2C-Bus initialisieren
  Serial.begin(115200); // Serielle Kommunikation initialisieren

  //  Überprüfen ob der Linke Knopf gefunden wurde, wenn ja starten, sonst Fehlermeldung
  if (leftButton.begin(0x11) == false)
  {
    Serial.println("Left Button did not acknowledge! Freezing.");
    while (1)
      ;
  }
  Serial.println("Left button acknowledged.");
  //  Überprüfen ob der Rechte Knopf gefunden wurde, wenn ja starten, sonst Fehlermeldung
  if (rightButton.begin(0x10) == false)
  {
    Serial.println("Right Button did not acknowledge! Freezing.");
    while (1)
      ;
  }
  Serial.println("Right button acknowledged.");
}

void loop()
{
  PlaySnake(image, buffer, leftButton, rightButton);
}