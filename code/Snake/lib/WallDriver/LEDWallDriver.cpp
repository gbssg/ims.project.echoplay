#include <Arduino.h>

/** \file
 *  \addtogroup LEDWD LED-Wall-Driver
 *  @{
 *  \brief the bare minimum to controll the Input to the LED-Wall
 * 
 *          # Theory of operation
 *          The LED Wall Driver gets the imput from the buffer array and translates it into PIN inputs.
 * 
 *          # How to use the module
 *          Use the BufferOutput with the buffer array to iniciate the transmition to the LED Wall.
 * 
 *          # Inner workings
 *          The function buffer output calls WD_PixelPush 256 times to insert all of the pixels into the LED Wall.
 */         

/**
 *  \brief Sets GPIO(General Purpous Input Output) Ports as easily readable abreviations.
 *  OE = Output Enable
 */
const uint8_t OE = GPIO_NUM_15;
/**
 *  \brief Sets GPIO(General Purpous Input Output) Ports as easily readable abreviations.
 *  LA = Latch
 */
const uint8_t LA = GPIO_NUM_17;
/**
 *  \brief Sets GPIO(General Purpous Input Output) Ports as easily readable abreviations.
 *  SDI = Serial Data In
 */
const uint8_t SDI = GPIO_NUM_25;
/**
 *  \brief Sets GPIO(General Purpous Input Output) Ports as easily readable abreviations.
 * CLK = Clock
 */
const uint8_t CLK = GPIO_NUM_26;

static void WD_PixelPush(uint8_t value);

/**
 * \brief Cycles through buffer array, extracts every value and runs Pixelpush per value
 * 
 * \param buffer reads the buffer array one by one and pushes them one by one
 */
void WD_BufferOutput(const uint8_t *buffer) {
  digitalWrite(LA, LOW);

  for (int i = 0;i < 256;i++) {
    uint8_t pixel = buffer[i];
    WD_PixelPush(pixel);
  }

  delay(1);
  digitalWrite(LA, HIGH);
}

/**
 * \brief Uses digitalWrite (Arduino.h's Funktion) to input signals into Display
 * 
 * \param[in] value buffer values either on or off.
 */
static void WD_PixelPush(uint8_t value) {
                // one-line if statment.
  digitalWrite(SDI, value > 0 ? HIGH : LOW);
  delayMicroseconds(1);
  digitalWrite(CLK, HIGH);
  delayMicroseconds(1);
  digitalWrite(CLK, LOW);
}
/** @} */