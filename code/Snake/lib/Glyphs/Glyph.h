#pragma once

/**
 *  \file
 *  \addtogroup Glyph A glyph library
 *  @{
 */

#include <stdint.h>
#include <Arduino.h>

/**
 * \brief The defenitionof a possible implemetation of a cursor.
 * 
 * You would be able to write glyphs at the cursors position.
 */
typedef struct sGlyph tGlyph;

extern const tGlyph * const Glyph_0;
extern const tGlyph * const Glyph_1;
extern const tGlyph * const Glyph_2;
extern const tGlyph * const Glyph_3;
extern const tGlyph * const Glyph_4;
extern const tGlyph * const Glyph_5;
extern const tGlyph * const Glyph_6;
extern const tGlyph * const Glyph_7;
extern const tGlyph * const Glyph_8;
extern const tGlyph * const Glyph_9;
extern const tGlyph * const Glyph_H;
extern const tGlyph * const Glyph_S1;
extern const tGlyph * const Glyph_S2;


void WriteGlyph(uint8_t image[][16], const tGlyph *glyph);

void ImagePrint(const uint8_t image[][16]);

/** @} */