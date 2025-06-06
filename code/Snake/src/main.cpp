#include <Arduino.h>
#include <SparkFun_Qwiic_Button.h>
#include <Wire.h>
#include <Snake.h>
#include <LedWallEncoder.h>
#include <ClockProvider.h>
#include <LEDWallDriver.h>
#include <SimpleSoftTimer.h>

using namespace HolisticSolutions;

QwiicButton leftButton;  // Pin für den linken Knopf
QwiicButton rightButton; // Pin für den rechten Knopf

// Die Pins für die FrekvensPanel-Bibliothek definieren
const char pin_enable = GPIO_NUM_15;
const char pin_data = GPIO_NUM_25;
const char pin_clock = GPIO_NUM_26;
const char pin_latch = GPIO_NUM_17;
// const char pin_SW1 = GPIO_NUM_16; Optional, falls man den Gelben Knopf verwenden möchte
// const char pin_SW2 = GPIO_NUM_32; Optional, falls man den Roten Knopf verwenden möchte
// const char microphone_pin = GPIO_NUM_34; // Optional, falls ein Mikrofon verwendet wird

// Statische Variablen für den Bildschirm deklarieren
static uint8_t buffer[256] = {0};
static uint8_t image[16][16] = {0};

// Allgemeine Statische Variablen für das Spiel deklarieren
static int difficulty = 0;            // 0 = Easy, 1 = Medium, 2 = Hard
static bool gameOver = false;         // Variable, die angibt, ob das Spiel vorbei ist
static bool again = false;            // Variable, die angibt, ob das Spiel erneut gestartet werden soll
static bool difficultyChosen = false; // Variable, die angibt ob die Schwierigkeits selektion abgeschlossen ist.
static bool goodApple = false;        // Variable, die angibt ob die Position vom Apfel gültig ist.

// Statisch Variablen für die Snake deklarieren
static int snakeLength = 0;    // Länge der Schlange
static int snakeX = 7;         // X-Position der Schlange
static int snakeY = 7;         // Y-Position der Schlange
static int snakeDirection = 0; // Richtung der Schlange (0 = oben, 1 = rechts, 2 = unten, 3 = links)
static int speed = 0;
// Statische Variablen für den Schlangenschwanz
static int snakeTailX[256] = {0}; // X-Position der Schlangenschwanz-Pixel
static int snakeTailY[256] = {0}; // Y-Position der Schlangenschwanz-Pixel

// Statische Variablen für das Essen deklarieren
static int appleX = 0; // X-Position des Apfels
static int appleY = 0; // Y-Position des Apfels

// Timers
SimpleSoftTimer timer(30);

void setup()
{
  Wire.begin();         // I2C-Bus initialisieren
  Serial.begin(115200); // Serielle Kommunikation initialisieren

  leftButton.begin(0x10);  // Initialisiere den roten Knopf
  rightButton.begin(0x11); // Initialisiere den gelben Knopf
}

void loop()
{
  // Titelscreen anzeigen
  TitleScreen(image);
  UpdateScreen(buffer, image);

  // Warten bis ein Kopf drückt wird
  while (!leftButton.isPressed() || !rightButton.isPressed())
    ;

  // Schwierigkeitsgrad wählen
  difficulty = 1;
  timer.start(30);

  // Geht in den Schweirigkeits auswähle Modus
  while (!difficultyChosen)
  {
    timer.restart();
    while (!timer.isTimeout())
    {
      if (leftButton.isPressed() && rightButton.isPressed())
      {
        difficultyChosen = true;
      }
    }
    if (!difficultyChosen)
    {
      if (leftButton.isPressed() && difficulty > 1)
      {
        difficulty--;
      }
      else if (rightButton.isPressed() && difficulty < 3)
      {
        difficulty++;
      }
    }

    SchweirigskeitScreen(image, difficulty);
    UpdateScreen(buffer, image);
  }

  // Spiel Variabeln zurücksetzen
  gameOver = false;
  snakeX = 7;
  snakeY = 7;
  snakeLength = 0;
  snakeDirection = 0;
  appleX = 0;
  appleY = 0;
  goodApple = false;
  speed = 500 / difficulty;
  timer.start(speed);

  SnakeSetup(image, snakeX, snakeY);
  UpdateScreen(buffer, image);

  // Platziert einen Apfel auf dem Feld
  while (!goodApple)
  {
    appleX = rand() % 16;
    appleY = rand() % 16;
    if (appleX == snakeX && appleY == snakeY)
    {
      continue;
    }
    else
    {
      goodApple = true;
    }
  }

  // Die Haupt Spiel Schleife für Snake
  while (!gameOver)
  {
    // Änder die Richtung von der Snake
    timer.restart();
    while (!timer.isTimeout())
    {
      if (leftButton.isPressed())
      {
        if (snakeDirection == 0)
        {
          snakeDirection = 3;
        }
        else
        {
          snakeDirection--;
        }
        delay(speed - timer.timePassed());
      }
      else if (rightButton.isPressed())
      {
        if (snakeDirection == 3)
        {
          snakeDirection = 0;
        }
        else
        {
          snakeDirection++;
        }
        delay(speed - timer.timePassed());
      }
    }

    // Alten SchlangenKnopf Löschen
    image[snakeY][snakeX] = 0;

    // Überprüfen ob die Schlange einen Apfel berührt und einen neuen erstellen
    goodApple = false;
    if (snakeX == appleX && snakeY == appleY)
    {
      snakeLength++;
      appleX = rand() % 16;
      appleY = rand() % 16;
      while (!goodApple)
      {
        if (appleX == snakeX && appleY == snakeY)
        {
          appleX = rand() % 16;
          appleY = rand() % 16;
        }
        else
        {
          for (int i = 0; i < snakeLength; i++)
          {
            if (appleX == snakeTailX[i] && appleY == snakeTailY[i])
            {
              appleX = rand() % 16;
              appleY = rand() % 16;
              break;
            }
          }
          goodApple = true;
        }
      }
    }

    if (snakeLength > 0)
    {
      image[snakeTailY[snakeLength - 1]][snakeTailX[snakeLength - 1]];

      for (int i = snakeLength; 1 < i; i--)
      {
        snakeTailX[i - 1] = snakeTailX[i - 2];
        snakeTailY[i - 1] = snakeTailY[i - 2];
      }
      snakeTailX[0] = snakeX;
      snakeTailY[0] = snakeY;
    }

    if (snakeDirection == 0)
    {
      snakeX--;
    }
    else if (snakeDirection == 1)
    {
      snakeY--;
    }
    else if (snakeDirection == 2)
    {
      snakeX++;
    }
    else if (snakeDirection == 3)
    {
      snakeY++;
    }

    if (snakeX < 0 || snakeX >= 16 || snakeY < 0 || snakeY >= 16)
      ;
    {
      gameOver = true;
    }

    for (int i = 0; i < snakeLength; i++)
    {
      if (snakeX == snakeTailX[i] && snakeY == snakeTailY[i])
      {
        gameOver = true;
      }
    }

    image[snakeY][snakeX] = 1;
    image[appleY][appleX] = 1;

    for (int i = 0; i < snakeLength; i++)
    {
      image[snakeTailY[i]][snakeTailX[i]] = 1;
    }

    UpdateScreen(buffer, image);
  }
  // Spiel beenden
  GameOverScreen(image);
  UpdateScreen(buffer, image);
  delay(3000);

  // Spielwiederhol Screen anzeigen und auf Benutzerinegabe warten
  StartNewScreen(image);
  UpdateScreen(buffer, image);
  while (!leftButton.isPressed() || !rightButton.isPressed())
    ;
}