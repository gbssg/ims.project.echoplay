#include "Glyph.h"
#include <stdint.h>
#include <Arduino.h>

/** \file
 *  \addtogroup Glyph A glyph library
 *  @{
 *  \brief  Library of available glyphs as pixel graphics
 *
 *          # Theory of operation
 *          A collection of glyphs to use for the LED display,
 *          and fuctions to write the Glyphs into the image array.
 *
 *          # How to use the module
 *          Use WriteGlyph to print the chosen glyph into the image array.
 *
 *          # Inner workings
 *          The fuction WriteGlyph takes the array of the chosen glyph and
 *          overrides the image array at the position according to the cursor.
 */

/**
 * \brief The defenition of a possible implementation of a cursor.
 *
 * You would be able to write glyphs at the cursors position.
 */
typedef struct sCursor
{
  uint8_t posX;
  uint8_t posY;
} tCursor;

/**
 * \brief A possible implemetation of a cursor.
 *
 * You would be able to write glyphs at the cursors position.
 */
static const tCursor Cursor1 = {
    .posX = 0,
    .posY = 0};

/**
 * \brief   Initializes the glyph access module
 */
struct sGlyph
{
  uint8_t width;   ///< Width of the Glyph array
  uint8_t height;  ///< Height of the Glyph array
  char glyphName;  ///< Identifyer of the Glyph
  uint8_t glyph[]; ///< The Glyph data
};

// 0
static const tGlyph Glyph0 = {
    .width = 4,
    .height = 7,
    .glyphName = '0',
    .glyph = {
        0x00, 0xff, 0xff, 0x00,
        0xff, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0xff,
        0x00, 0xff, 0xff, 0x00}};

// 1
static const tGlyph Glyph1 = {
    .width = 4,
    .height = 7,
    .glyphName = '1',
    .glyph = {
        0x00, 0x00, 0xff, 0x00,
        0x00, 0xff, 0xff, 0x00,
        0x00, 0x00, 0xff, 0x00,
        0x00, 0x00, 0xff, 0x00,
        0x00, 0x00, 0xff, 0x00,
        0x00, 0x00, 0xff, 0x00,
        0x00, 0x00, 0xff, 0x00}};

// 2
static const tGlyph Glyph2 = {
    .width = 4,
    .height = 7,
    .glyphName = '2',
    .glyph = {
        0x00, 0xff, 0xff, 0x00,
        0xff, 0x00, 0x00, 0xff,
        0x00, 0x00, 0x00, 0xff,
        0x00, 0xff, 0xff, 0x00,
        0xff, 0x00, 0x00, 0x00,
        0xff, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0xff}};

// 3
static const tGlyph Glyph3 = {
    .width = 4,
    .height = 7,
    .glyphName = '3',
    .glyph = {
        0x00, 0xff, 0xff, 0x00,
        0x00, 0x00, 0x00, 0xff,
        0x00, 0x00, 0x00, 0xff,
        0x00, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0xff,
        0x00, 0x00, 0x00, 0xff,
        0x00, 0xff, 0xff, 0x00}};

// 4
static const tGlyph Glyph4 = {
    .width = 4,
    .height = 7,
    .glyphName = '4',
    .glyph = {
        0xff, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0xff,
        0x00, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0xff,
        0x00, 0x00, 0x00, 0xff,
        0x00, 0x00, 0x00, 0xff}};

// 5
static const tGlyph Glyph5 = {
    .width = 4,
    .height = 7,
    .glyphName = '5',
    .glyph = {
        0xff, 0xff, 0xff, 0xff,
        0xff, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0x00,
        0x00, 0x00, 0x00, 0xff,
        0x00, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0xff,
        0x00, 0xff, 0xff, 0x00}};

// 6
static const tGlyph Glyph6 = {
    .width = 4,
    .height = 7,
    .glyphName = '6',
    .glyph = {
        0x00, 0xff, 0xff, 0x00,
        0xff, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0x00,
        0xff, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0xff,
        0x00, 0xff, 0xff, 0x00}};

// 7
static const tGlyph Glyph7 = {
    .width = 4,
    .height = 7,
    .glyphName = '7',
    .glyph = {
        0xff, 0xff, 0x00, 0x00,
        0x00, 0x00, 0xff, 0x00,
        0x00, 0x00, 0xff, 0x00,
        0x00, 0x00, 0xff, 0x00,
        0x00, 0x00, 0xff, 0x00,
        0x00, 0x00, 0xff, 0x00,
        0x00, 0x00, 0xff, 0x00}};

// 8
static const tGlyph Glyph8 = {
    .width = 4,
    .height = 7,
    .glyphName = '8',
    .glyph = {
        0x00, 0xff, 0xff, 0x00,
        0xff, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0xff,
        0x00, 0xff, 0xff, 0x00,
        0xff, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0xff,
        0x00, 0xff, 0xff, 0x00}};

// 9
static const tGlyph Glyph9 = {
    .width = 4,
    .height = 7,
    .glyphName = '9',
    .glyph = {
        0x00, 0xff, 0xff, 0x00,
        0xff, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0xff,
        0x00, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0xff,
        0x00, 0x00, 0x00, 0xff,
        0x00, 0xff, 0xff, 0x00}};

// h
static const tGlyph GlyphH = {
    .width = 4,
    .height = 7,
    .glyphName = 'H',
    .glyph = {
        0xff, 0x00, 0x00, 0x00,
        0xff, 0x00, 0x00, 0x00,
        0xff, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0x00,
        0xff, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0xff,
        0xff, 0x00, 0x00, 0xff}};

// S1
static const tGlyph GlyphS1 = {
    .width = 5,
    .height = 7,
    .glyphName = 'S',
    .glyph = {
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xff, 0x00, 0xff, 0x00,
        0x00, 0xff, 0x00, 0xff, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0xff, 0x00, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0x00, 0x00}};

// S2
static const tGlyph GlyphS2 = {
    .width = 5,
    .height = 7,
    .glyphName = 's',
    .glyph = {
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xff, 0x00, 0x00, 0x00,
        0x00, 0xff, 0x00, 0xff, 0xff,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0xff, 0x00, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0x00, 0x00}};

/**
 * \brief Glyph representation of 0.
 *
 * This pointer refers to a static glyph structure representing the number 0.
 */
const tGlyph *const Glyph_0 = &Glyph0;
/**
 * \brief Glyph representation of 1.
 *
 * This pointer refers to a static glyph structure representing the number 1.
 */
const tGlyph *const Glyph_1 = &Glyph1;
/**
 * \brief Glyph representation of 2.
 *
 * This pointer refers to a static glyph structure representing the number 2.
 */
const tGlyph *const Glyph_2 = &Glyph2;
/**
 * \brief Glyph representation of 3.
 *
 * This pointer refers to a static glyph structure representing the number 3.
 */
const tGlyph *const Glyph_3 = &Glyph3;
/**
 * \brief Glyph representation of 4.
 *
 * This pointer refers to a static glyph structure representing the number 4.
 */
const tGlyph *const Glyph_4 = &Glyph4;
/**
 * \brief Glyph representation of 5.
 *
 * This pointer refers to a static glyph structure representing the number 5.
 */
const tGlyph *const Glyph_5 = &Glyph5;
/**
 * \brief Glyph representation of 6.
 *
 * This pointer refers to a static glyph structure representing the number 6.
 */
const tGlyph *const Glyph_6 = &Glyph6;
/**
 * \brief Glyph representation of 7.
 *
 * This pointer refers to a static glyph structure representing the number 7.
 */
const tGlyph *const Glyph_7 = &Glyph7;
/**
 * \brief Glyph representation of 8.
 *
 * This pointer refers to a static glyph structure representing the number 8.
 */
const tGlyph *const Glyph_8 = &Glyph8;
/**
 * \brief Glyph representation of 9.
 *
 * This pointer refers to a static glyph structure representing the number 9.
 */
const tGlyph *const Glyph_9 = &Glyph9;
/**
 * \brief Glyph representation of H.
 *
 * This pointer refers to a static glyph structure representing the number H.
 */
const tGlyph *const Glyph_H = &GlyphH;
/**
 * \brief Glyph representation of smiley 1.
 *
 * This pointer refers to a static glyph structure representing the smiley nr 1.
 */
const tGlyph *const Glyph_S1 = &GlyphS1;
/**
 * \brief Glyph representation of smiley 2.
 *
 * This pointer refers to a static glyph structure representing smiley nr 2.
 */
const tGlyph *const Glyph_S2 = &GlyphS2;

/**
 * \brief Array of pointers to all the glyphs.
 */
static const tGlyph *glyphs[] = {
    Glyph_0, Glyph_1, Glyph_2,
    Glyph_3, Glyph_4, Glyph_5,
    Glyph_6, Glyph_7, Glyph_8,
    Glyph_9, Glyph_H, Glyph_S1,
    Glyph_S2,
    0 ///< null terminator
};

/**
 * \brief   Writes one glyph to the image
 *
 * \param image Image to write the glyph
 */

void WriteGlyph(uint8_t image[][16], const tGlyph *glyph)
{
  int i = 0;
  for (int x = 0; x < glyph->height; x++)
  {
    for (int y = 0; y < glyph->width; y++)
    {
      image[y + Cursor1.posY][x + Cursor1.posX] = glyph->glyph[i];
      i++;
    }
  }
}

/*
void WriteGlyph(uint8_t image[][16], char glyphName) {
  const tGlyph *cursor = glyphs;
  const tGlyph *glyph = GlyphH;


  while (*cursor != 0) {
    if (cursor->glyphName = glyphName) {
      glyph = cursor;
      break;
    }
    cursor++;
  }

  WriteGlyph(image, glyph);
}
*/
/**
 * \brief Draws preview of led display for moblie modifications.
 *
 * \param image Uses image to print in serial monitor
 */
void ImagePrint(const uint8_t image[][16])
{
  Serial.println("+----------------------------------+");
  for (int y = 0; y < 16; y++)
  {
    Serial.print("| ");
    for (int x = 0; x < 16; x++)
    {
      Serial.print(image[y][x] > 0 ? "XX" : "  ");
    }
    Serial.println(" |");
  }
  Serial.println("+----------------------------------+");
}

/** @} */