#include <Arduino.h>
#include <SparkFun_Qwiic_Button.h>
#include <Wire.h>
#include <Snake.h>
#include <LedWallEncoder.h>
#include <ClockProvider.h>
#include <LEDWallDriver.h>
#include <Glyph.h>

QwiicButton leftButton;  // linken Knopf initialisieren
QwiicButton rightButton; // Rechten Knipf initialisieren

// Eine Variable für die Pins definieren
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
static int difficulty = 1;            // 1 = Easy, 2 = Medium, 3 = Hard
static bool gameOver = false;         // Variable, die angibt, ob das Spiel vorbei ist
static bool again = false;            // Variable, die angibt, ob das Spiel erneut gestartet werden soll
static bool difficultyChosen = false; // Variable, die angibt ob die Schwierigkeits selektion abgeschlossen ist.
static bool goodApple = false;        // Variable, die angibt ob die Position vom Apfel gültig ist.
static int button = 0;                // Variable welche sagt welcher Knopf gedrückt wurde (leftButton = 1, rightButton = 2, both = 3)

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

void setup()
{
  // prepares GPIO's for further instructions
  pinMode(pin_enable, OUTPUT);
  pinMode(pin_latch, OUTPUT);
  pinMode(pin_data, OUTPUT);
  pinMode(pin_clock, OUTPUT);
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
  //  Überprüfen ob der Rechten Knopf gefunden wurde, wenn ja starten, sonst Fehlermeldung
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
  // Titelscreen anzeigen
  TitleScreen(image);
  UpdateScreen(buffer, image);

  // Auf einen Input warten
  WaitForButtonPress(leftButton, rightButton);

  // Schwierigkeitsgrad variabeln zurücksetzen
  difficulty = 1;
  difficultyChosen = false;

  // Schweirigkeitsgrad auswählen
  Serial.println("Schwierigkeit am wählen");
  while (!difficultyChosen)
  {
    SchweirigskeitScreen(image, difficulty);
    UpdateScreen(buffer, image);
    button = WaitForButtonPress(leftButton, rightButton);

    if (button == 3)
    {
      difficultyChosen = true;
    }

    if (!difficultyChosen)
    {
      Serial.println("Knopf wählen");
      if (button == 1 && difficulty > 1)
      {
        Serial.println("Linker Knopf gedrückt");
        difficulty--;
      }
      else if (button == 2 && difficulty < 3)
      {
        Serial.println("Rechter Knopf gedrückt");
        difficulty++;
      }
    }
  }

  Serial.println("Schwierigkeit gewählt!");
  Serial.print("Schwierigkeit: ");
  Serial.println(difficulty);

  // Spiel Variabeln zurücksetzen
  gameOver = false;
  snakeX = 7;
  snakeY = 7;
  snakeLength = 0;
  snakeDirection = 0;
  appleX = 0;
  appleY = 0;
  goodApple = false;
  speed = 1000 / difficulty;
  leftButton.clearEventBits();
  rightButton.clearEventBits();

  // Screen für Snake vorbereiten
  SnakeSetup(image, snakeX, snakeY);
  UpdateScreen(buffer, image);

  // Platziert einen Apfel auf dem Feld
  PlantApple(appleX, appleY, snakeX, snakeY, snakeTailX, snakeTailY, snakeLength);

  // Die Haupt Spiel Schleife für Snake
  while (!gameOver)
  {
    // Änder die Richtung von der Snake
    ChangeSnakeDirection(leftButton, rightButton, snakeDirection, speed);

    // Alten SchlangenKnopf Löschen
    image[snakeY][snakeX] = 0;

    // Überprüfen ob die Schlange einen Apfel berührt und einen neuen erstellen
    goodApple = false;
    if (snakeX == appleX && snakeY == appleY)
    {
      snakeLength++;
      PlantApple(appleX, appleY, snakeX, snakeY, snakeTailX, snakeTailY, snakeLength);
    }

    // Schlangenschwanzarray Updaten und hintersten Teil löschen
    if (snakeLength > 0)
    {
      UpdateSnakeTail(snakeX, snakeY, snakeTailX, snakeTailY, snakeLength, image);
    }

    SnakeMovement(snakeDirection, snakeX, snakeY);

    CheckForGameOver(snakeX, snakeY, snakeTailX, snakeTailY, snakeLength, gameOver);

    // Malt die Schlange, und den Apfel auf den Screen
    DrawSnakenApple(snakeX, snakeY, appleX, appleY, snakeTailX, snakeTailY, image, buffer, snakeLength);
  }

  // Spiel beenden
  GameOverScreen(image);
  UpdateScreen(buffer, image);
  delay(3000);
  leftButton.LEDoff();
  rightButton.LEDoff();

  // Spielwiederhol Screen anzeigen und auf Benutzereinegabe warten
  StartNewScreen(image);
  UpdateScreen(buffer, image);
  WaitForButtonPress(leftButton, rightButton);
}