/// @file

#include "openclgl.hpp"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FONT VARIABLES //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#define ASCII_33 33
#define ASCII_126 126
#define ASCII_SCALE 0.01
#define ASCII_SPACE_LITTLE 4
#define ASCII_SPACE_BIG 16

/// Font (Hershey simplex vector font) vertex coordinates.
/// Format: {x1, y1, x2, y2, x3, y3, ... , xn, yn}
/// xn, yn = 2D coordinates of each single font vertex.
/// Later on, in OpenGL implementation, each two consecutive verteces are
/// connected by a line segment.
/// If two consecutive segments have to be joined together, the coordinates of
/// the second vertex of the first segment are equal to the coordinates of the
/// first vertex of the second segment.
/// All Ascii characters from 33 to 126 have been represented in the single
/// "font_vertex" array.
/// The "font_index" array gives the offset at which the first vertex
/// coordinates of each Ascii character in the "font_vertex" array starts.
/// The "font_numdata" array contains the total number of integer data
/// describing each Ascii character in the font.
/// The "font_width" array contains the width of each Ascii character in the
/// font.

int font_vertex[3646] = {
/* Ascii 33 */
   5,  21,   5,   7,   5,   2,   4,   1,   4,   1,   5,   0,   5,   0,   6,   1,
   6,   1,   5,   2,

/* Ascii 34 */
   4,  21,   4,  14,  12,  21,  12,  14,

/* Ascii 35 */
  11,  25,   4,  -7,  17,  25,  10,  -7,   4,  12,  18,  12,   3,   6,  17,   6,

/* Ascii 36 */
   8,  25,   8,  -4,  12,  25,  12,  -4,  17,  18,  15,  20,  15,  20,  12,  21,
  12,  21,   8,  21,   8,  21,   5,  20,   5,  20,   3,  18,   3,  18,   3,  16,
   3,  16,   4,  14,   4,  14,   5,  13,   5,  13,   7,  12,   7,  12,  13,  10,
  13,  10,  15,   9,  15,   9,  16,   8,  16,   8,  17,   6,  17,   6,  17,   3,
  17,   3,  15,   1,  15,   1,  12,   0,  12,   0,   8,   0,   8,   0,   5,   1,
   5,   1,   3,   3,

/* Ascii 37 */
  21,  21,   3,   0,   8,  21,  10,  19,  10,  19,  10,  17,  10,  17,   9,  15,
   9,  15,   7,  14,   7,  14,   5,  14,   5,  14,   3,  16,   3,  16,   3,  18,
   4,  20,   6,  21,   6,  21,   8,  21,   8,  21,  10,  20,  10,  20,  13,  19,
  13,  19,  16,  19,  16,  19,  19,  20,  19,  20,  21,  21,  17,   7,  15,   6,
  15,   6,  14,   4,  14,   4,  14,   2,  14,   2,  16,   0,  16,   0,  18,   0,
  18,   0,  20,   1,  20,   1,  21,   3,  21,   3,  21,   5,  21,   5,  19,   7,
  19,   7,  17,   7,

/* Ascii 38 */
  23,  12,  23,  13,  23,  13,  22,  14,  22,  14,  21,  14,  21,  14,  20,  13,
  20,  13,  19,  11,  19,  11,  17,   6,  17,   6,  15,   3,  15,   3,  13,   1,
  13,   1,  11,   0,  11,   0,   7,   0,   7,   0,   5,   1,   5,   1,   4,   2,
   4,   2,   3,   4,   3,   4,   3,   6,   3,   6,   4,   8,   4,   8,   5,   9,
   5,   9,  12,  13,  12,  13,  13,  14,  13,  14,  14,  16,  14,  16,  14,  18,
  14,  18,  13,  20,  13,  20,  11,  21,  11,  21,   9,  20,   9,  20,   8,  18,
   8,  18,   8,  16,   8,  16,   9,  13,   9,  13,  11,  10,  11,  10,  16,   3,
  16,   3,  18,   1,  18,   1,  20,   0,  20,   0,  22,   0,  22,   0,  23,   1,
  23,   1,  23,   2,

/* Ascii 39 */
   5,  19,   4,  20,   4,  20,   5,  21,   5,  21,   6,  20,   6,  20,   6,  18,
   6,  18,   5,  16,   5,  16,   4,  15,

/* Ascii 40 */
  11,  25,   9,  23,   9,  23,   7,  20,   7,  20,   5,  16,   5,  16,   4,  11,
   4,  11,   4,   7,   4,   7,   5,   2,   5,   2,   7,  -2,   7,  -2,   9,  -5,
   9,  -5,  11,  -7,

/* Ascii 41 */
   3,  25,   5,  23,   5,  23,   7,  20,   7,  20,   9,  16,   9,  16,  10,  11,
  10,  11,  10,   7,  10,   7,   9,   2,   9,   2,   7,  -2,   7,  -2,   5,  -5,
   5,  -5,   3,  -7,

/* Ascii 42 */
   8,  21,   8,   9,   3,  18,  13,  12,  13,  18,   3,  12,

/* Ascii 43 */
  13,  18,  13,   0,   4,   9,  22,   9,

/* Ascii 44 */
   6,   1,   5,   0,   5,   0,   4,   1,   4,   1,   5,   2,   5,   2,   6,   1,
   6,   1,   6,  -1,   6,  -1,   5,  -3,   5,  -3,   4,  -4,

/* Ascii 45 */
   4,   9,  22,   9,

/* Ascii 46 */
   5,   2,   4,   1,   4,   1,   5,   0,   5,   0,   6,   1,   6,   1,   5,   2,

/* Ascii 47 */
  20,  25,   2,  -7,

/* Ascii 48 */
   9,  21,   6,  20,   6,  20,   4,  17,   4,  17,   3,  12,   3,  12,   3,   9,
   3,   9,   4,   4,   4,   4,   6,   1,   6,   1,   9,   0,   9,   0,  11,   0,
  11,   0,  14,   1,  14,   1,  16,   4,  16,   4,  17,   9,  17,   9,  17,  12,
  17,  12,  16,  17,  16,  17,  14,  20,  14,  20,  11,  21,  11,  21,   9,  21,

/* Ascii 49 */
   6,  17,   8,  18,   8,  18,  11,  21,  11,  21,  11,   0,

/* Ascii 50 */
   4,  16,   4,  17,   4,  17,   5,  19,   5,  19,   6,  20,   6,  20,   8,  21,
   8,  21,  12,  21,  12,  21,  14,  20,  14,  20,  15,  19,  15,  19,  16,  17,
  16,  17,  16,  15,  16,  15,  15,  13,  15,  13,  13,  10,  13,  10,   3,   0,
   3,   0,  17,   0,

/* Ascii 51 */
   5,  21,  16,  21,  16,  21,  10,  13,  10,  13,  13,  13,  13,  13,  15,  12,
  15,  12,  16,  11,  16,  11,  17,   8,  17,   8,  17,   6,  17,   6,  16,   3,
  16,   3,  14,   1,  14,   1,  11,   0,  11,   0,   8,   0,   8,   0,   5,   1,
   5,   1,   4,   2,   4,   2,   3,   4,

/* Ascii 52 */
  13,  21,   3,   7,   3,   7,  18,   7,  13,  21,  13,   0,

/* Ascii 53 */
  15,  21,   5,  21,   5,  21,   4,  12,   4,  12,   5,  13,   5,  13,   8,  14,
   8,  14,  11,  14,  11,  14,  14,  13,  14,  13,  16,  11,  16,  11,  17,   8,
  17,   8,  17,   6,  17,   6,  16,   3,  16,   3,  14,   1,  14,   1,  11,   0,
  11,   0,   8,   0,   8,   0,   5,   1,   5,   1,   4,   2,   4,   2,   3,   4,

/* Ascii 54 */
  16,  18,  15,  20,  15,  20,  12,  21,  12,  21,  10,  21,  10,  21,   7,  20,
   7,  20,   5,  17,   5,  17,   4,  12,   4,  12,   4,   7,   4,   7,   5,   3,
   5,   3,   7,   1,   7,   1,  10,   0,  10,   0,  11,   0,  11,   0,  14,   1,
  14,   1,  16,   3,  16,   3,  17,   6,  17,   6,  17,   7,  17,   7,  16,  10,
  16,  10,  14,  12,  14,  12,  11,  13,  11,  13,  10,  13,  10 , 13,   7,  12,
   7,  12,   5,  10,   5,  10,   4,   7,

/* Ascii 55 */
  17,  21,   7,   0,   3,  21,  17,  21,

/* Ascii 56 */
   8,  21,   5,  20,   5,  20,   4,  18,   4,  18,   4,  16,   4,  16,   5,  14,
   5,  14,   7,  13,   7,  13,  11,  12,  11,  12,  14,  11,  14,  11,  16,   9,
  16,   9,  17,   7,  17,   7,  17,   4,  17,   4,  16,   2,  16,   2,  15,   1,
  15,   1,  12,   0,  12,   0,   8,   0,   8,   0,   5,   1,   5,   1,   4,   2,
   4,   2,   3,   4,   3,   4,   3,   7,   3,   7,   4,   9,   4,   9,   6,  11,
   6,  11,   9,  12,   9,  12,  13,  13,  13,  13,  15,  14,  15,  14,  16,  16,
  16,  16,  16,  18,  16,  18,  15,  20,  15,  20,  12,  21,  12,  21,   8,  21,

/* Ascii 57 */
  16,  14,  15,  11,  15,  11,  13,   9,  13,   9,  10,   8,  10,   8,   9,   8,
   9,   8,   6,   9,   6,   9,   4,  11,   4,  11,   3,  14,   3,  14,   3,  15,
   3,  15,   4,  18,   4,  18,   6,  20,   6,  20,   9,  21,   9,  21,  10,  21,
  10,  21,  13,  20,  13,  20,  15,  18,  15,  18,  16,  14,  16,  14,  16,   9,
  16,   9,  15,   4,  15,   4,  13,   1,  13,   1,  10,   0,  10,   0,   8,   0,
   8,   0,   5,   1,   5,   1,   4,   3,

/* Ascii 58 */
   5,  14,   4,  13,   4,  13,   5,  12,   5,  12,   6,  13,   6,  13,   5,  14,
   5,   2,   4,   1,   4,   1,   5,   0,   5,   0,   6,   1,   6,   1,   5,   2,

/* Ascii 59 */
   5,  14,   4,  13,   4,  13,   5,  12,   5,  12,   6,  13,   6,  13,   5,  14,
   6,   1,   5,   0,   5,   0,   4,   1,   4,   1,   5,   2,   5,   2,   6,   1,
   6,   1,   6,  -1,   6,  -1,   5,  -3,   5,  -3,   4,  -4,

/* Ascii 60 */
  20,  18,   4,   9,   4,   9,  20,   0,

/* Ascii 61 */
   4,  12,  22,  12,   4,   6,  22,   6,

/* Ascii 62 */
   4,  18,  20,   9,  20,  29,   4,   0,

/* Ascii 63 */
   3,  16,   3,  17,   3,  17,   4,  19,   4,  19,   5,  20,   5,  20,   7,  21,
   7,  21,  11,  21,  11,  21,  13,  20,  13,  20,  14,  19,  14,  19,  15,  17,
  15,  17,  15,  15,  15,  15,  14,  13,  14,  13,  13,  12,  13,  12,   9,  10,
   9,  10,   9,   7,   9,   2,   8,   1,   8,   1,   9,   0,   9,   0,  10,   1,
  10,   1,   9,   2,

/* Ascii 64 */
  18,  13,  17,  15,  17,  15,  15,  16,  15,  16,  12,  16,  12,  16,  10,  15,
  10,  15,   9,  14,   9,  14,   8,  11,   8,  11,   8,   8,   8,   8,   9,   6,
   9,   6,  11,   5,  11,   5,  14,   5,  14,   5,  16,   6,  16,   6,  17,   8,
  12,  16,  10,  14,  10,  14,   9,  11,   9,  11,   9,   8,   9,   8,  10,   6,
  10,   6,  11,   5,  18,  16,  17,   8,  17,   8,  17,   6,  17,   6,  19,   5,
  19,   5,  21,   5,  21,   5,  23,   7,  23,   7,  24,  10,  24,  10,  24,  12,
  24,  12,  23,  15,  23,  15,  22,  17,  22,  17,  20,  19,  20,  19,  18,  20,
  18,  20,  15,  21,  15,  21,  12,  21,  12,  21,   9,  20,   9,  20,   7,  19,
   7,  19,   5,  17,   5,  17,   4,  15,   4,  15,   3,  12,   3,  12,   3,   9,
   3,   9,   4,   6,   4,   6,   5,   4,   5,   4,   7,   2,   7,   2,   9,   1,
   9,   1,  12,   0,  12,   0,  15,   0,  15,   0,  18,   1,  18,   1,  20,   2,
  20,   2,  21,   3,  19,  16,  18,   8,  18,   8,  18,   6,  18,   6,  19,   5,

/* Ascii 65 */
   9,  21,   1,   0,   9,  21,  17,   0,   4,   7,  14,   7,

/* Ascii 66 */
   4,  21,   4,   0,   4,  21,  13,  21,  13,  21,  16,  20,  16,  20,  17,  19,
  17,  19,  18,  17,  18,  17,  18,  15,  18,  15,  17,  13,  17,  13,  16,  12,
  16,  12,  13,  11,   4,  11,  13,  11,  13,  11,  16,  10,  16,  10,  17,   9,
  17,   9,  18,   7,  18,   7,  18,   4,  18,   4,  17,   2,  17,   2,  16,   1,
  16,   1,  13,   0,  13,   0,   4,   0,

/* Ascii 67 */
  18,  16,  17,  18,  17,  18,  15,  20,  15,  20,  13,  21,  13,  21,   9,  21,
   9,  21,   7,  20,   7,  20,   5,  18,   5,  18,   4,  16,   4,  16,   3,  13,
   3,  13,   3,   8,   3,   8,   4,   5,   4,   5,   5,   3,   5,   3,   7,   1,
   7,   1,   9,   0,   9,   0,  13,   0,  13,   0,  15,   1,  15,   1,  17,   3,
  17,   3,  18,   5,

/* Ascii 68 */
   4,  21,   4,   0,   4,  21,  11,  21,  11,  21,  14,  20,  14,  20,  16,  18,
  16,  18,  17,  16,  17,  16,  18,  13,  18,  13,  18,   8,  18,   8,  17,   5,
  17,   5,  16,   3,  16,   3,  14,   1,  14,   1,  11,   0,  11,   0,   4,   0,

/* Ascii 69 */
   4,  21,   4,   0,   4,  21,  17,  21,   4,  11,  12,  11,   4,   0,  17,   0,

/* Ascii 70 */
   4,  21,   4,   0,   4,  21,  17,  21,   4,  11,  12,  11,

/* Ascii 71 */
  18,  16,  17,  18,  17,  18,  15,  20,  15,  20,  13,  21,  13,  21,   9,  21,
   9,  21,   7,  20,   7,  20,   5,  18,   5,  18,   4,  16,   4,  16,   3,  13,
   3,  13,   3,   8,   3,   8,   4,   5,   4,   5,   5,   3,   5,   3,   7,   1,
   7,   1,   9,   0,   9,   0,  13,   0,  13,   0,  15,   1,  15,   1,  17,   3,
  17,   3,  18,   5,  18,   5,  18,   8,  13,   8,  18,   8,

/* Ascii 72 */
   4,  21,   4,   0,  18,  21,  18,   0,   4,  11,  18,  11,

/* Ascii 73 */
   4,  21,   4,   0,

/* Ascii 74 */
  12,  21,  12,   5,  12,   5,  11,   2,  11,   2,  10,   1,  10,   1,   8,   0,
   8,   0,   6,   0,   6,   0,   4,   1,   4,   1,   3,   2,   3,   2,   2,   5,
   2,   5,   2,   7,

/* Ascii 75 */
   4,  21,   4,   0,  18,  21,   4,   7,   9,  12,  18,   0,

/* Ascii 76 */
   4,  21,   4,   0,   4,   0,  16,   0,

/* Ascii 77 */
   4,  21,   4,   0,   4,  21,  12,   0,  20,  21,  12,   0,  20,  21,  20,   0,

/* Ascii 78 */
   4,  21,   4,   0,   4,  21,  18,   0,  18,  21,  18,   0,

/* Ascii 79 */
   9,  21,   7,  20,   7,  20,   5,  18,   5,  18,   4,  16,   4,  16,   3,  13,
   3,  13,   3,   8,   3,   8,   4,   5,   4,   5,   5,   3,   5,   3,   7,   1,
   7,   1,   9,   0,   9,   0,   13,  0,  13,   0,  15,   1,  15,   1,  17,   3,
  17,   3,  18,   5,  18,   5,  19,   8,  19,   8,  19,  13,  19,  13,  18,  16,
  18,  16,  17,  18,  17,  18,  15,  20,  15,  20,  13,  21,  13,  21,   9,  21,

/* Ascii 80 */
   4,  21,   4,   0,   4,  21,  13,  21,  13,  21,  16,  20,  16,  20,  17,  19,
  17,  19,  18,  17,  18,  17,  18,  14,  18,  14,  17,  12,  17,  12,  16,  11,
  16,  11,  13,  10,  13,  10,   4,  10,

/* Ascii 81 */
   9,  21,   7,  20,   7,  20,   5,  18,   5,  18,   4,  16,   4,  16,   3,  13,
   3,  13,   3,   8,   3,   8,   4,   5,   4,   5,   5,   3,   5,   3,   7,   1,
   7,   1,   9,   0,   9,   0,  13,   0,  13,   0,  15,   1,  15,   1,  17,   3,
  17,   3,  18,   5,  18,   5,  19,   8,  19,   8,  19,  13,  19,  13,  18,  16,
  18,  16,  17,  18,  17,  18,  15,  20,  15,  20,  13,  21,  13,  21,   9,  21,
  12,   4,  18,  -2,

/* Ascii 82 */
   4,  21,   4,   0,   4,  21,  13,  21,  13,  21,  16,  20,  16,  20,  17,  19,
  17,  19,  18,  17,  18,  17,  18,  15,  18,  15,  17,  13,  17,  13,  16,  12,
  16,  12,  13,  11,  13,  11,   4,  11,  11,  11,  18,   0,

/* Ascii 83 */
  17,  18,  15,  20,  15,  20,  12,  21,  12,  21,   8,  21,   8,  21,   5,  20,
   5,  20,   3,  18,   3,  18,   3,  16,   3,  16,   4,  14,   4,  14,   5,  13,
   5,  13,   7,  12,   7,  12,  13,  10,  13,  10,  15,   9,  15,   9,  16,   8,
  16,   8,  17,   6,  17,   6,  17,   3,  17,   3,  15,   1,  15,   1,  12,   0,
  12,   0,   8,   0,   8,   0,   5,   1,   5,   1,   3,   3,

/* Ascii 84 */
   8,  21,   8,   0,   1,  21,  15,  21,

/* Ascii 85 */
   4,  21,   4,   6,   4,   6,   5,   3,   5,   3,   7,   1,   7,   1,  10,   0,
  10,   0,  12,   0,  12,   0,  15,   1,  15,   1,  17,   3,  17,   3,  18,   6,
  18,   6,  18,  21,

/* Ascii 86 */
   1,  21,   9,   0,  17,  21,   9,   0,

/* Ascii 87 */
   2,  21,   7,   0,  12,  21,   7,   0,  12,  21,  17,   0,  22,  21,  17,   0,

/* Ascii 88 */
   3,  21,  17,   0,  17,  21,   3,   0,

/* Ascii 89 */
   1,  21,   9,  11,   9,  11,   9,   0,  17,  21,   9,  11,

/* Ascii 90 */
  17,  21,   3,   0,   3,  21,  17,  21,   3,   0,  17,   0,

/* Ascii 91 */
   4,  25,   4,  -7,   5,  25,   5,  -7,   4,  25,  11,  25,   4,  -7,  11,  -7,

/* Ascii 92 */
   0,  21,  14,  -3,

/* Ascii 93 */
   9,  25,   9,  -7,  10,  25,  10,  -7,   3,  25,  10,  25,   3,  -7,  10,  -7,

/* Ascii 94 */
   6,  15,   8,  18,   8,  18,  10,  15,   3,  12,   8,  17,   8,  17,  13,  12,
   8,  17,   8,   0,

/* Ascii 95 */
   0,  -2,  16,  -2,

/* Ascii 96 */
   6,  21,   5,  20,   5,  20,   4,  18,   4,  18,   4,  16,   4,  16,   5,  15,
   5,  15,   6,  16,   6,  16,   5,  17,

/* Ascii 97 */
  15,  14,  15,   0,  15,  11,  13,  13,  13,  13,  11,  14,  11,  14,   8,  14,
   8,  14,   6,  13,   6,  13,   4,  11,   4,  11,   3,   8,   3,   8,   3,   6,
   3,   6,   4,   3,   4,   3,   6,   1,   6,   1,   8,   0,   8,   0,   11,  0,
  11,   0,  13,   1,  13,   1,  15,   3,

/* Ascii 98 */
   4,  21,   4,   0,   4,  11,   6,  13,   6,  13,   8,  14,   8,  14,  11,  14,
  11,  14,  13,  13,  13,  13,  15,  11,  15,  11,  16,   8,  16,   8,  16,   6,
  16,   6,  15,   3,  15,   3,  13,   1,  13,   1,  11,   0,  11,   0,   8,   0,
   8,   0,   6,   1,   6,   1,   4,   3,

/* Ascii 99 */
  15,  11,  13,  13,  13,  13,  11,  14,  11,  14,   8,  14,   8,  14,   6,  13,
   6,  13,   4,  11,   4,  11,   3,   8,   3,   8,   3,   6,   3,   6,   4,   3,
   4,   3,   6,   1,   6,   1,   8,   0,   8,   0,  11,   0,  11,   0,  13,   1,
  13,   1,  15,   3,

/* Ascii 100 */
  15,  21,  15,   0,  15,  11,  13,  13,  13,  13,  11,  14,  11,  14,   8,  14,
   8,  14,   6,  13,   6,  13,   4,  11,   4,  11,   3,   8,   3,   8,   3,   6,
   3,   6,   4,   3,   4,   3,   6,   1,   6,   1,   8,   0,   8,   0,  11,   0,
  11,   0,  13,   1,  13,   1,  15,   3,

/* Ascii 101 */
   3,   8,  15,   8,  15,   8,  15,  10,  15,  10,  14,  12,  14,  12,  13,  13,
  13,  13,  11,  14,  11,  14,   8,  14,   8,  14,   6,  13,   6,  13,   4,  11,
   4,  11,   3,   8,   3,   8,   3,   6,   3,   6,   4,   3,   4,   3,   6,   1,
   6,   1,   8,   0,   8,   0,  11,   0,  11,   0,  13,   1,  13,   1,  15,   3,

/* Ascii 102 */
  10,  21,   8,  21,   8,  21,   6,  20,   6,  20,   5,  17,   5,  17,   5,   0,
   2,  14,   9,  14,

/* Ascii 103 */
  15,  14,  15,  -2,  15,  -2,  14,  -5,  14,  -5,  13,  -6,  13,  -6,  11,  -7,
  11,  -7,   8,  -7,   8,  -7,   6,  -6,  15,  11,  13,  13,  13,  13,  11,  14,
  11,  14,   8,  14,   8,  14,   6,  13,   6,  13,   4,  11,   4,  11,   3,   8,
   3,   8,   3,   6,   3,   6,   4,   3,   4,   3,   6,   1,   6,   1,   8,   0,
   8,   0,  11,   0,  11,   0,  13,   1,  13,   1,  15,   3,

/* Ascii 104 */
   4,  21,   4,   0,   4,  10,   7,  13,   7,  13,   9,  14,   9,  14,  12,  14,
  12,  14,  14,  13,  14,  13,  15,  10,  15,  10,  15,   0,

/* Ascii 105 */
   3,  21,   4,  20,   4,  20,   5,  21,   5,  21,   4,  22,   4,  22,   3,  21,
   4,  14,   4,   0,

/* Ascii 106 */
   5,  21,   6,  20,   6,  20,   7,  21,   7,  21,   6,  22,   6,  22,   5,  21,
   6,  14,   6,  -3,   6,  -3,   5,  -6,   5,  -6,   3,  -7,   3,  -7,   1,  -7,

/* Ascii 107 */
   4,  21,   4,   0,  14,  14,   4,   4,   8,   8,  15,   0,

/* Ascii 108 */
   4,  21,   4,   0,

/* Ascii 109 */
   4,  14,   4,   0,   4,  10,   7,  13,   7,  13,   9,  14,   9,  14,  12,  14,
  12,  14,  14,  13,  14,  13,  15,  10,  15,  10,  15,   0,  15,  10,  18,  13,
  18,  13,  20,  14,  20,  14,  23,  14,  23,  14,  25,  13,  25,  13,  26,  10,
  26,  10,  26,   0,

/* Ascii 110 */
   4,  14,   4,   0,   4,  10,   7,  13,   7,  13,   9,  14,   9,  14,  12,  14,
  12,  14,  14,  13,  14,  13,  15,  10,  15,  10,  15,   0,

/* Ascii 111 */
   8,  14,   6,  13,   6,  13,   4,  11,   4,  11,   3,   8,   3,   8,   3,   6,
   3,   6,   4,   3,   4,   3,   6,   1,   6,   1,   8,   0,   8,   0,  11,   0,
  11,   0,  13,   1,  13,   1,  15,   3,  15,   3,  16,   6,  16,   6,  16,   8,
  16,   8,  15,  11,  15,  11,  13,  13,  13,  13,  11,  14,  11,  14,   8,  14,

/* Ascii 112 */
   4,  14,   4,  -7,   4,  11,   6,  13,   6,  13,   8,  14,   8,  14,  11,  14,
  11,  14,  13,  13,  13,  13,  15,  11,  15,  11,  16,   8,  16,   8,  16,   6,
  16,   6,  15,   3,  15,   3,  13,   1,  13,   1,  11,   0,  11,   0,   8,   0,
   8,   0,   6,   1,   6,   1,   4,   3,

/* Ascii 113 */
  15,  14,  15,  -7,  15,  11,  13,  13,  13,  13,  11,  14,  11,  14,   8,  14,
   8,  14,   6,  13,   6,  13,   4,  11,   4,  11,   3,   8,   3,   8,   3,   6,
   3,   6,   4,   3,   4,   3,   6,   1,   6,   1,   8,   0,   8,   0,  11,   0,
  11,   0,  13,   1,  13,   1,  15,   3,

/* Ascii 114 */
   4,  14,   4,   0,   4,   8,   5,  11,   5,  11,   7,  13,   7,  13,   9,  14,
   9,  14,  12,  14,

/* Ascii 115 */
  14,  11,  13,  13,  13,  13,  10,  14,  10,  14,   7,  14,   7,  14,   4,  13,
   4,  13,   3,  11,   3,  11,   4,   9,   4,   9,   6,   8,   6,   8,  11,   7,
  11,   7,  13,   6,  13,   6,  14,   4,  14,   4,  14,   3,  14,   3,  13,   1,
  13,   1,  10,   0,  10,   0,   7,   0,   7,   0,   4,   1,   4,   1,   3,   3,

/* Ascii 116 */
   5,  21,   5,   4,   5,   4,   6,   1,   6,   1,   8,   0,   8,   0,  10,   0,
   2,  14,   9,  14,

/* Ascii 117 */
   4,  14,   4,   4,   4,   4,   5,   1,   5,   1,   7,   0,   7,   0,  10,   0,
  10,   0,  12,   1,  12,   1,  15,   4,  15,  14,  15,   0,

/* Ascii 118 */
   2,  14,   8,   0,  14,  14,   8,   0,

/* Ascii 119 */
   3,  14,   7,   0,  11,  14,   7,   0,  11,  14,  15,   0,  19,  14,  15,   0,

/* Ascii 120 */
   3,  14,  14,   0,  14,  14,   3,   0,

/* Ascii 121 */
   2,  14,   8,   0,  14,  14,   8,   0,   8,   0,   6,  -4,   6,  -4,   4,  -6,
   4,  -6,   2,  -7,   2,  -7,   1,  -7,

/* Ascii 122 */
  14,  14,   3,   0,   3,  14,  14,  14,   3,   0,  14,   0,

/* Ascii 123 */
   9,  25,   7,  24,   7,  24,   6,  23,   6,  23,   5,  21,   5,  21,   5,  19,
   5,  19,   6,  17,   6,  17,   7,  16,   7,  16,   8,  14,   8,  14,   8,  12,
   8,  12,   6,  10,   7,  24,   6,  22,   6,  22,   6,  20,   6,  20,   7,  18,
   7,  18,   8,  17,   8,  17,   9,  15,   9,  15,   9,  13,   9,  13,   8,  11,
   8,  11,   4,   9,   4,   9,   8,   7,   8,   7,   9,   5,   9,   5,   9,   3,
   9,   3,   8,   1,   8,   1,   7,   0,   7,   0,   6,  -2,   6,  -2,   6,  -4,
   6,  -4,   7,  -6,   6,   8,   8,   6,   8,   6,   8,   4,   8,   4,   7,   2,
   7,   2,   6,   1,   6,   1,   5,  -1,   5,  -1,   5,  -3,   5,  -3,   6,  -5,
   6,  -5,   7,  -6,   7,  -6,   9,  -7,

/* Ascii 124 */
   4,  25,   4,  -7,

/* Ascii 125 */
   5,  25,   7,  24,   7,  24,   8,  23,   8,  23,   9,  21,   9,  21,   9,  19,
   9,  19,   8,  17,   8,  17,   7,  16,   7,  16,   6,  14,   6,  14,   6,  12,
   6,  12,   8,  10,   7,  24,   8,  22,   8,  22,   8,  20,   8,  20,   7,  18,
   7,  18,   6,  17,   6,  17,   5,  15,   5,  15,   5,  13,   5,  13,   6,  11,
   6,  11,  10,   9,  10,   9,   6,   7,   6,   7,   5,   5,   5,   5,   5,   3,
   5,   3,   6,   1,   6,   1,   7,   0,   7,   0,   8,  -2,   8,  -2,   8,  -4,
   8,  -4,   7,  -6,   8,   8,   6,   6,   6,   6,   6,   4,   6,   4,   7,   2,
   7,   2,   8,   1,   8,   1,   9,  -1,   9,  -1,   9,  -3,   9,  -3,   8,  -5,
   8,  -5,   7,  -6,   7,  -6,   5,  -7,

/* Ascii 126 */
   3,   6,   3,   8,   3,   8,   4,  11,   4,  11,   6,  12,   6,  12,   8,  12,
   8,  12,  10,  11,  10,  11,  14,   8,  13,   8,  16,   7,  16,   7,  18,   7,
  18,   7,  20,   8,  20,   8,  21,  10,   3,   8,   4,  10,   4,  10,   6,  11,
   6,  11,   8,  11,   8,  11,  10,  10,  10,  10,  14,   7,  14,   7,  16,   6,
  16,   6,  18,   6,  18,   6,  20,   7,  20,   7,  21,  10,  21,  10,  21,  12,
};

int font_index[94] = {
/* Ascii 33 */	0,
/* Ascii 34 */	20,
/* Ascii 35 */	28,
/* Ascii 36 */	44,
/* Ascii 37 */	128,
/* Ascii 38 */	228,
/* Ascii 39 */	360,
/* Ascii 40 */	384,
/* Ascii 41 */	420,
/* Ascii 42 */	456,
/* Ascii 43 */	468,
/* Ascii 44 */	476,
/* Ascii 45 */	504,
/* Ascii 46 */	508,
/* Ascii 47 */	524,
/* Ascii 48 */	528,
/* Ascii 49 */	592,
/* Ascii 50 */	604,
/* Ascii 51 */	656,
/* Ascii 52 */	712,
/* Ascii 53 */	724,
/* Ascii 54 */	788,
/* Ascii 55 */	876,
/* Ascii 56 */	884,
/* Ascii 57 */	996,
/* Ascii 58 */	1084,
/* Ascii 59 */	1116,
/* Ascii 60 */	1160,
/* Ascii 61 */	1168,
/* Ascii 62 */	1176,
/* Ascii 63 */	1184,
/* Ascii 64 */	1252,
/* Ascii 65 */	1444,
/* Ascii 66 */	1456,
/* Ascii 67 */	1528,
/* Ascii 68 */	1596,
/* Ascii 69 */	1644,
/* Ascii 70 */	1660,
/* Ascii 71 */	1672,
/* Ascii 72 */	1748,
/* Ascii 73 */	1760,
/* Ascii 74 */	1764,
/* Ascii 75 */	1800,
/* Ascii 76 */	1812,
/* Ascii 77 */	1820,
/* Ascii 78 */	1836,
/* Ascii 79 */	1848,
/* Ascii 80 */	1928,
/* Ascii 81 */	1968,
/* Ascii 82 */	2052,
/* Ascii 83 */	2096,
/* Ascii 84 */	2172,
/* Ascii 85 */	2180,
/* Ascii 86 */	2216,
/* Ascii 87 */	2224,
/* Ascii 88 */	2240,
/* Ascii 89 */	2248,
/* Ascii 90 */	2260,
/* Ascii 91 */	2272,
/* Ascii 92 */	2288,
/* Ascii 93 */	2292,
/* Ascii 94 */	2308,
/* Ascii 95 */	2328,
/* Ascii 96 */	2332,
/* Ascii 97 */	2356,
/* Ascii 98 */	2412,
/* Ascii 99 */	2468,
/* Ascii 100 */	2520,
/* Ascii 101 */	2576,
/* Ascii 102 */	2640,
/* Ascii 103 */	2660,
/* Ascii 104 */	2736,
/* Ascii 105 */	2764,
/* Ascii 106 */	2784,
/* Ascii 107 */	2816,
/* Ascii 108 */	2828,
/* Ascii 109 */	2832,
/* Ascii 110 */	2884,
/* Ascii 111 */	2912,
/* Ascii 112 */	2976,
/* Ascii 113 */	3032,
/* Ascii 114 */	3088,
/* Ascii 115 */	3108,
/* Ascii 116 */	3172,
/* Ascii 117 */	3192,
/* Ascii 118 */	3220,
/* Ascii 119 */	3228,
/* Ascii 120 */	3244,
/* Ascii 121 */	3252,
/* Ascii 122 */	3276,
/* Ascii 123 */	3288,
/* Ascii 124 */	3424,
/* Ascii 125 */	3428,
/* Ascii 126 */	3564
};

int font_numdata[94] = {
/* Ascii 33 */20,
/* Ascii 34 */8,
/* Ascii 35 */16,
/* Ascii 36 */84,
/* Ascii 37 */100,
/* Ascii 38 */132,
/* Ascii 39 */24,
/* Ascii 40 */36,
/* Ascii 41 */36,
/* Ascii 42 */12,
/* Ascii 43 */8,
/* Ascii 44 */28,
/* Ascii 45 */4,
/* Ascii 46 */16,
/* Ascii 47 */4,
/* Ascii 48 */64,
/* Ascii 49 */12,
/* Ascii 50 */52,
/* Ascii 51 */56,
/* Ascii 52 */12,
/* Ascii 53 */64,
/* Ascii 54 */88,
/* Ascii 55 */8,
/* Ascii 56 */112,
/* Ascii 57 */88,
/* Ascii 58 */32,
/* Ascii 59 */44,
/* Ascii 60 */8,
/* Ascii 61 */8,
/* Ascii 62 */8,
/* Ascii 63 */68,
/* Ascii 64 */192,
/* Ascii 65 */12,
/* Ascii 66 */72,
/* Ascii 67 */68,
/* Ascii 68 */48,
/* Ascii 69 */16,
/* Ascii 70 */12,
/* Ascii 71 */76,
/* Ascii 72 */12,
/* Ascii 73 */4,
/* Ascii 74 */36,
/* Ascii 75 */12,
/* Ascii 76 */8,
/* Ascii 77 */16,
/* Ascii 78 */12,
/* Ascii 79 */80,
/* Ascii 80 */40,
/* Ascii 81 */84,
/* Ascii 82 */44,
/* Ascii 83 */76,
/* Ascii 84 */8,
/* Ascii 85 */36,
/* Ascii 86 */8,
/* Ascii 87 */16,
/* Ascii 88 */8,
/* Ascii 89 */12,
/* Ascii 90 */12,
/* Ascii 91 */16,
/* Ascii 92 */6,
/* Ascii 93 */16,
/* Ascii 94 */20,
/* Ascii 95 */4,
/* Ascii 96 */24,
/* Ascii 97 */56,
/* Ascii 98 */56,
/* Ascii 99 */52,
/* Ascii 100 */56,
/* Ascii 101 */64,
/* Ascii 102 */20,
/* Ascii 103 */76,
/* Ascii 104 */28,
/* Ascii 105 */20,
/* Ascii 106 */32,
/* Ascii 107 */12,
/* Ascii 108 */4,
/* Ascii 109 */52,
/* Ascii 110 */28,
/* Ascii 111 */64,
/* Ascii 112 */56,
/* Ascii 113 */56,
/* Ascii 114 */20,
/* Ascii 115 */64,
/* Ascii 116 */20,
/* Ascii 117 */28,
/* Ascii 118 */8,
/* Ascii 119 */16,
/* Ascii 120 */8,
/* Ascii 121 */24,
/* Ascii 122 */12,
/* Ascii 123 */136,
/* Ascii 124 */4,
/* Ascii 125 */136,
/* Ascii 126 */80
};

int font_width[94] = {
/* Ascii 33 */10,
/* Ascii 34 */16,
/* Ascii 35 */21,
/* Ascii 36 */20,
/* Ascii 37 */24,
/* Ascii 38 */26,
/* Ascii 39 */10,
/* Ascii 40 */14,
/* Ascii 41 */14,
/* Ascii 42 */16,
/* Ascii 43 */26,
/* Ascii 44 */10,
/* Ascii 45 */26,
/* Ascii 46 */10,
/* Ascii 47 */22,
/* Ascii 48 */20,
/* Ascii 49 */20,
/* Ascii 50 */20,
/* Ascii 51 */20,
/* Ascii 52 */20,
/* Ascii 53 */20,
/* Ascii 54 */20,
/* Ascii 55 */20,
/* Ascii 56 */20,
/* Ascii 57 */20,
/* Ascii 58 */10,
/* Ascii 59 */10,
/* Ascii 60 */24,
/* Ascii 61 */26,
/* Ascii 62 */24,
/* Ascii 63 */18,
/* Ascii 64 */27,
/* Ascii 65 */18,
/* Ascii 66 */21,
/* Ascii 67 */21,
/* Ascii 68 */21,
/* Ascii 69 */19,
/* Ascii 70 */18,
/* Ascii 71 */21,
/* Ascii 72 */22,
/* Ascii 73 */8,
/* Ascii 74 */16,
/* Ascii 75 */21,
/* Ascii 76 */17,
/* Ascii 77 */24,
/* Ascii 78 */22,
/* Ascii 79 */22,
/* Ascii 80 */21,
/* Ascii 81 */22,
/* Ascii 82 */21,
/* Ascii 83 */20,
/* Ascii 84 */16,
/* Ascii 85 */22,
/* Ascii 86 */18,
/* Ascii 87 */24,
/* Ascii 88 */20,
/* Ascii 89 */18,
/* Ascii 90 */20,
/* Ascii 91 */14,
/* Ascii 92 */14,
/* Ascii 93 */14,
/* Ascii 94 */16,
/* Ascii 95 */16,
/* Ascii 96 */10,
/* Ascii 97 */19,
/* Ascii 98 */19,
/* Ascii 99 */18,
/* Ascii 100 */19,
/* Ascii 101 */18,
/* Ascii 102 */12,
/* Ascii 103 */19,
/* Ascii 104 */19,
/* Ascii 105 */8,
/* Ascii 106 */10,
/* Ascii 107 */17,
/* Ascii 108 */8,
/* Ascii 109 */30,
/* Ascii 110 */19,
/* Ascii 111 */19,
/* Ascii 112 */19,
/* Ascii 113 */19,
/* Ascii 114 */13,
/* Ascii 115 */17,
/* Ascii 116 */12,
/* Ascii 117 */19,
/* Ascii 118 */16,
/* Ascii 119 */22,
/* Ascii 120 */17,
/* Ascii 121 */16,
/* Ascii 122 */17,
/* Ascii 123 */14,
/* Ascii 124 */8,
/* Ascii 125 */14,
/* Ascii 126 */24
};




//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// SHADER VARIABLES ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
char*             point_vertex_source;                                          // Point vertex shader source.
size_t            point_vertex_size;                                            // Point vertex shader size [characters].
char*             point_fragment_source;                                        // Point fragment shader source.
size_t            point_fragment_size;                                          // Point fragment shader size [characters].
GLuint 						point_shader;                                                 // Point shader program.

char*             text_vertex_source;                                           // Point vertex shader source.
size_t            text_vertex_size;                                             // Point vertex shader size [characters].
char*             text_fragment_source;                                         // Point fragment shader source.
size_t            text_fragment_size;                                           // Point fragment shader size [characters].
GLuint 						text_shader;                                                  // Point shader program.

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// OPENCL VARIABLES ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
char*                   value;
cl_platform_id*         platform;
unsigned int            num_platforms;
cl_device_id*           device;
unsigned int            num_devices;
cl_context_properties*  properties;
cl_context              context;

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// OPENCL: QUEUE CLASS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
queue::queue()
{
  thequeue = NULL;
}

void queue::init()
{
  thequeue = clCreateCommandQueue(context, device[0], 0, &err);                 // Creating OpenCL queue...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }
}

queue::~queue()
{
  printf("Action: releasing the OpenCL command queue... ");

  err = clReleaseCommandQueue(thequeue);                                        // Releasing OpenCL queue...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// OPENCL: KERNEL CLASS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
kernel::kernel()
{
  thekernel = NULL;
  source = NULL;
  program = NULL;
  size = 0;
  dimension = 0;
  event = NULL;
}

void kernel::init(char* kernel_source, size_t kernel_size, cl_uint kernel_dimension)
{
  FILE* handle;                                                                 // Input file handle.

  printf("Action: loading OpenCL kernel source from file... ");

  source_file = kernel_source;
  size = kernel_size;
  dimension = kernel_dimension;

  handle = fopen(source_file, "rb");                                            // Opening OpenCL kernel source file...

  if(handle == NULL)
  {
    printf("\nError:  could not find the file!");
    exit(1);
  }

  fseek(handle, 0, SEEK_END);                                                   // Seeking end of file...
  source_size = (size_t)ftell(handle);                                          // Measuring file size...
  rewind(handle);                                                               // Rewinding to the beginning of the file...
  source = (char*)malloc(source_size + 1);                                      // Allocating buffer for reading the file...

  if (!(source))
  {
    printf("\nError:  unable to allocate buffer memory!\n");
    exit(EXIT_FAILURE);
  }

  fread(source, sizeof(char), source_size, handle);                             // Reading file (OpenCL kernel source)...
  source[source_size] = '\0';                                                   // Null-terminating buffer...
  fclose(handle);                                                               // Closing file.

  printf("DONE!\n");

  printf("Action: creating OpenCL program from kernel source... ");
  program = clCreateProgramWithSource(context,                                  // Creating OpenCL program from its source...
                                      1,
                                      (const char**)&source,
                                      &source_size, &err);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  free(source);                                                                 // Freeing OpenCL kernel buffer...
  printf("DONE!\n");

  printf("Action: building OpenCL program... ");
  err = clBuildProgram(program, 1, device, "", NULL, NULL);                     // Building OpenCL program...

  // Checking compiled kernel:
  if (err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));

    err = clGetProgramBuildInfo(program,                                        // Getting compiler information...
                                device[0],
                                CL_PROGRAM_BUILD_LOG,
                                0,
                                NULL,
                                &log_size);

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }

    log = (char*) calloc(log_size + 1, sizeof(char));                           // Allocating log buffer...

    if (!log)
    {
      printf("\nError:  unable to allocate buffer memory log!\n");
      exit(EXIT_FAILURE);
    }

    err = clGetProgramBuildInfo(program, device[0],                             // Reading log...
                                CL_PROGRAM_BUILD_LOG,
                                log_size + 1,
                                log,
                                NULL);

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }

    printf("%s\n", log);                                                        // Displaying log...
    free(log);                                                                  // Freeing log...
    exit(err);                                                                  // Exiting...
  }

  printf("DONE!\n");

  printf("Action: creating OpenCL kernel object from program... ");

  thekernel = clCreateKernel(program, KERNEL_NAME, &err);                       // Creating OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

void kernel::execute(queue* q, kernel_event k_ev)
{
  err = clEnqueueNDRangeKernel(q->thequeue,                                     // Enqueueing OpenCL kernel (as a single task)...
                               thekernel,
                               dimension,
                               NULL,
                               &size,
                               NULL,
                               0,
                               NULL,
                               &event);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  switch(k_ev)
  {
    case WAIT:
      err = clWaitForEvents(1, &event);                                         // Waiting for kernel execution to be completed (host blocking)...

      if(err != CL_SUCCESS)
      {
        printf("\nError:  %s\n", get_error(err));
        exit(err);
      }
    break;

    case DONT_WAIT:
                                                                                // Doing nothing!
    break;

    default:
      err = clWaitForEvents(1, &event);                                         // Waiting for kernel execution to be completed (host blocking)...

      if(err != CL_SUCCESS)
      {
        printf("\nError:  %s\n", get_error(err));
        exit(err);
      }
    break;
  }


}

kernel::~kernel()
{
  printf("Action: releasing OpenCL kernel... ");

  err = clReleaseKernel(thekernel);                                             // Releasing OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");

  printf("Action: releasing OpenCL kernel event... ");
  err = clReleaseEvent(event);                                                  // Releasing OpenCL event...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");

  printf("Action: releasing OpenCL program... ");

  err = clReleaseProgram(program);                                              // Releasing OpenCL program...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// FILES FUNCTIONS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void load_point_vertex(char* neutrino_path, const char* filename_vertex)
{
 printf("Action: loading OpenGL point vertex source from file... ");

 load_file(neutrino_path, filename_vertex, &point_vertex_source, &point_vertex_size);

	printf("DONE!\n");
}

void load_point_fragment(char* neutrino_path, const char* filename_fragment)
{
	printf("Action: loading OpenGL point fragment source from file... ");

 load_file(neutrino_path, filename_fragment, &point_fragment_source, &point_fragment_size);

	printf("DONE!\n");
}

void load_text_vertex(char* neutrino_path, const char* filename_vertex)
{
 printf("Action: loading OpenGL point vertex source from file... ");

 load_file(neutrino_path, filename_vertex, &text_vertex_source, &text_vertex_size);

	printf("DONE!\n");
}

void load_text_fragment(char* neutrino_path, const char* filename_fragment)
{
	printf("Action: loading OpenGL point fragment source from file... ");

 load_file(neutrino_path, filename_fragment, &text_fragment_source, &text_fragment_size);

	printf("DONE!\n");
}

void init_shaders()
{
  GLuint		point_vertex_shader;                                                // "Point" vertex shader.
	GLuint 		point_fragment_shader;                                              // "Point" fragment shader.
  GLuint    LAYOUT_0 = 0;                                                       // "layout = 0" attribute in vertex shader.
  GLuint    LAYOUT_1 = 1;                                                       // "layout = 1" attribute in vertex shader.

  GLuint		text_vertex_shader;                                                 // "Text" vertex shader.
	GLuint 		text_fragment_shader;                                               // "Text" fragment shader.

	GLint 		success;
  GLsizei 	log_size;
  GLchar*		log;

  printf("Action: initialising OpenGL shaders... ");

  // POINT SHADER:

  // Compiling point vertex shader...
  point_vertex_shader = glCreateShader(GL_VERTEX_SHADER);                       // Creating shader...
  glShaderSource(point_vertex_shader,                                           // Attaching source code to shader...
                 1,
                 (const char**)&point_vertex_source,
                 (GLint*)&point_vertex_size);
	glCompileShader(point_vertex_shader);                                         // Compiling shader...
  glGetShaderiv(point_vertex_shader, GL_COMPILE_STATUS, &success);              // Reading "GL_COMPILE_STATUS" flag...

  // Checking compiled point vertex shader code:
  if (!success)
  {
    glGetShaderiv(point_vertex_shader, GL_INFO_LOG_LENGTH, &log_size);          // Getting log length...
    log = (char*) malloc(log_size + 1);                                         // Allocating temporary buffer for log...
    log[log_size] = '\0';                                                       // Null-terminating log buffer...
    glGetShaderInfoLog(point_vertex_shader, log_size + 1, NULL, log);           // Getting log...
    printf("%s\n", log);                                                        // Printing log...
    free(log);                                                                  // Freeing log...
    exit(1);                                                                    // Exiting...
  }

	// Compiling point fragment shader...
  point_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);                   // Creating shader...
  glShaderSource(point_fragment_shader,                                         // Attaching source code to shader...
                 1,
                 (const char**)&point_fragment_source,
                 (GLint*)&point_fragment_size);
	glCompileShader(point_fragment_shader);
  glGetShaderiv(point_fragment_shader, GL_COMPILE_STATUS, &success);

  // Checking compiled point fragment shader code:
  if (!success)
  {
    glGetShaderiv(point_fragment_shader, GL_INFO_LOG_LENGTH, &log_size);        // Getting log length...
    log = (char*) malloc(log_size + 1);                                         // Allocating temporary buffer for log...
    log[log_size] = '\0';                                                       // Null-terminating log buffer...
    glGetShaderInfoLog(point_fragment_shader, log_size + 1, NULL, log);         // Getting log...
    printf("%s\n", log);                                                        // Printing log...
    free(log);                                                                  // Freeing log...
    exit(1);                                                                    // Exiting...
  }

	// Creating OpenGL shader program:
  point_shader = glCreateProgram();                                             // Creating program...
  glBindAttribLocation(point_shader, LAYOUT_0, "point");                        // Binding "point" to "layout = 0" shader attribute...
  glBindAttribLocation(point_shader, LAYOUT_1, "color");                        // Binding "vertex_color" to "layout = 1" shader attribute...
  glAttachShader(point_shader, point_vertex_shader);                            // Attaching point vertex shader to program...
  glAttachShader(point_shader, point_fragment_shader);                          // Attaching point fragment shader to program...
  glLinkProgram(point_shader);                                                  // Linking program...
  free_file(point_vertex_source);                                               // Freeing point vertex source file...
  free_file(point_fragment_source);                                             // Freeing fragment vertex source file...

  // TEXT SHADER:

  // Compiling text vertex shader...
  text_vertex_shader = glCreateShader(GL_VERTEX_SHADER);                        // Creating shader...
  glShaderSource(text_vertex_shader,                                            // Attaching source code to shader...
                 1,
                 (const char**)&text_vertex_source,
                 (GLint*)&text_vertex_size);
	glCompileShader(text_vertex_shader);                                          // Compiling shader...
  glGetShaderiv(text_vertex_shader, GL_COMPILE_STATUS, &success);               // Reading "GL_COMPILE_STATUS" flag...

  // Checking compiled text vertex shader code:
  if (!success)
  {
    glGetShaderiv(text_vertex_shader, GL_INFO_LOG_LENGTH, &log_size);           // Getting log length...
    log = (char*) malloc(log_size + 1);                                         // Allocating temporary buffer for log...
    log[log_size] = '\0';                                                       // Null-terminating log buffer...
    glGetShaderInfoLog(text_vertex_shader, log_size + 1, NULL, log);            // Getting log...
    printf("%s\n", log);                                                        // Printing log...
    free(log);                                                                  // Freeing log...
    exit(1);                                                                    // Exiting...
  }

	// Compiling text fragment shader...
  text_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);                    // Creating shader...
  glShaderSource(text_fragment_shader,                                          // Attaching source code to shader...
                 1,
                 (const char**)&text_fragment_source,
                 (GLint*)&text_fragment_size);
	glCompileShader(text_fragment_shader);
  glGetShaderiv(text_fragment_shader, GL_COMPILE_STATUS, &success);

  // Checking compiled text fragment shader code:
  if (!success)
  {
    glGetShaderiv(text_fragment_shader, GL_INFO_LOG_LENGTH, &log_size);         // Getting log length...
    log = (char*) malloc(log_size + 1);                                         // Allocating temporary buffer for log...
    log[log_size] = '\0';                                                       // Null-terminating log buffer...
    glGetShaderInfoLog(text_fragment_shader, log_size + 1, NULL, log);          // Getting log...
    printf("%s\n", log);                                                        // Printing log...
    free(log);                                                                  // Freeing log...
    exit(1);                                                                    // Exiting...
  }

	// Creating OpenGL shader program:
  text_shader = glCreateProgram();                                              // Creating program...
  glBindAttribLocation(text_shader, LAYOUT_0, "point");                         // Binding "point" to "layout = 0" shader attribute...
  glBindAttribLocation(text_shader, LAYOUT_1, "color");                         // Binding "vertex_color" to "layout = 1" shader attribute...
  glAttachShader(text_shader, text_vertex_shader);                              // Attaching point vertex shader to program...
  glAttachShader(text_shader, text_fragment_shader);                            // Attaching point fragment shader to program...
  glLinkProgram(text_shader);                                                   // Linking program...
  free_file(text_vertex_source);                                                // Freeing point vertex source file...
  free_file(text_fragment_source);                                              // Freeing fragment vertex source file...

  printf("DONE!\n");
}



//////////////////////////////////////////////////////////////////////////////////
/////////////////////////// WINDOW CALLBACK FUNCTIONS ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// GUI FUNCTIONS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


void plot(point4* points, color4* colors, plot_style ps)
{
  GLuint LAYOUT_0 = 0;                                                          // "layout = 0" attribute in vertex shader.
  GLuint LAYOUT_1 = 1;                                                          // "layout = 1" attribute in vertex shader.

  multiplicate(V, T, R);                                                        // Setting View_matrix matrix...

  switch(ps)
  {
    case STYLE_POINT:
      glUseProgram(point_shader);                                               // Using shader...
      glUniformMatrix4fv(glGetUniformLocation(point_shader,
                                              "View_matrix"),                   // Setting View_matrix matrix on shader...
                         1,                                                     // # of matrices to be modified.
                         GL_FALSE,                                              // FALSE = column major.
                         &V[0]);                                                // View matrix.

      glUniformMatrix4fv(glGetUniformLocation(point_shader,
                                              "Projection_matrix"),             // Setting Projection_matrix matrix on shader...
                         1,                                                     // # of matrices to be modified.
                         GL_FALSE,                                              // FALSE = column major.
                         &P[0]);                                                // Projection matrix.
      break;

    default:
    glUseProgram(point_shader);                                               // Using shader...
    glUniformMatrix4fv(glGetUniformLocation(point_shader,
                                            "View_matrix"),                   // Setting View_matrix matrix on shader...
                       1,                                                     // # of matrices to be modified.
                       GL_FALSE,                                              // FALSE = column major.
                       &V[0]);                                                // View matrix.

    glUniformMatrix4fv(glGetUniformLocation(point_shader,
                                            "Projection_matrix"),             // Setting Projection_matrix matrix on shader...
                       1,                                                     // # of matrices to be modified.
                       GL_FALSE,                                              // FALSE = column major.
                       &P[0]);                                                // Projection matrix.
    break;
  }

  // Binding "points" array:
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, points->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

  // Binding "colors" array:
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, colors->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

  // Drawing:
  glDrawArrays(GL_POINTS, 0, points->size);                                     // Drawing "points"...

  // Finishing:
  glDisableVertexAttribArray(LAYOUT_0);                                         // Unbinding "points" array...
  glDisableVertexAttribArray(LAYOUT_1);                                         // Unbinding "colors" array...
}

void print(text4* text)
{
  GLuint LAYOUT_0 = 0;                                                          // "layout = 0" attribute in vertex shader.
  GLuint LAYOUT_1 = 1;                                                          // "layout = 1" attribute in vertex shader.

  multiplicate(V, T, R);                                                        // Setting View_matrix matrix...
  glUseProgram(text_shader);                                                    // Using shader...
  glUniformMatrix4fv(glGetUniformLocation(text_shader, "View_matrix"),          // Setting View_matrix matrix on shader...
                     1,
                     GL_FALSE,
                     &V[0]);
  glUniformMatrix4fv(glGetUniformLocation(text_shader, "Projection_matrix"),    // Setting Projection_matrix matrix on shader...
                     1,
                     GL_FALSE,
                     &P[0]);

  // Binding "glyph" array:
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, text->glyph_vbo);                               // Binding glyph VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

  // Binding "color" array:
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, text->color_vbo);                                // Binding color VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

  // Drawing:
  glDrawArrays(GL_LINES, 0, text->size);                                        // Drawing "glyphs"...

  // Finishing:
  glDisableVertexAttribArray(LAYOUT_0);                                         // Unbinding "glyph" array...
  glDisableVertexAttribArray(LAYOUT_1);                                         // Unbinding "color" array...
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// OPENGL CONTEXT FUNCTIONS ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// OPENCL CONTEXT FUNCTIONS ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////
const char* get_error(cl_int error)
{
  switch(error)
  {
    // run-time and JIT compiler errors
    case 0: return "CL_SUCCESS";
    case -1: return "CL_DEVICE_NOT_FOUND";
    case -2: return "CL_DEVICE_NOT_AVAILABLE";
    case -3: return "CL_COMPILER_NOT_AVAILABLE";
    case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case -5: return "CL_OUT_OF_RESOURCES";
    case -6: return "CL_OUT_OF_HOST_MEMORY";
    case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case -8: return "CL_MEM_COPY_OVERLAP";
    case -9: return "CL_IMAGE_FORMAT_MISMATCH";
    case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case -11: return "CL_BUILD_PROGRAM_FAILURE";
    case -12: return "CL_MAP_FAILURE";
    case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
    case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
    case -15: return "CL_COMPILE_PROGRAM_FAILURE";
    case -16: return "CL_LINKER_NOT_AVAILABLE";
    case -17: return "CL_LINK_PROGRAM_FAILURE";
    case -18: return "CL_DEVICE_PARTITION_FAILED";
    case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

    // compile-time errors
    case -30: return "CL_INVALID_VALUE";
    case -31: return "CL_INVALID_DEVICE_TYPE";
    case -32: return "CL_INVALID_PLATFORM";
    case -33: return "CL_INVALID_DEVICE";
    case -34: return "CL_INVALID_CONTEXT";
    case -35: return "CL_INVALID_QUEUE_PROPERTIES";
    case -36: return "CL_INVALID_COMMAND_QUEUE";
    case -37: return "CL_INVALID_HOST_PTR";
    case -38: return "CL_INVALID_MEM_OBJECT";
    case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case -40: return "CL_INVALID_IMAGE_SIZE";
    case -41: return "CL_INVALID_SAMPLER";
    case -42: return "CL_INVALID_BINARY";
    case -43: return "CL_INVALID_BUILD_OPTIONS";
    case -44: return "CL_INVALID_PROGRAM";
    case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
    case -46: return "CL_INVALID_KERNEL_NAME";
    case -47: return "CL_INVALID_KERNEL_DEFINITION";
    case -48: return "CL_INVALID_KERNEL";
    case -49: return "CL_INVALID_ARG_INDEX";
    case -50: return "CL_INVALID_ARG_VALUE";
    case -51: return "CL_INVALID_ARG_SIZE";
    case -52: return "CL_INVALID_KERNEL_ARGS";
    case -53: return "CL_INVALID_WORK_DIMENSION";
    case -54: return "CL_INVALID_WORK_GROUP_SIZE";
    case -55: return "CL_INVALID_WORK_ITEM_SIZE";
    case -56: return "CL_INVALID_GLOBAL_OFFSET";
    case -57: return "CL_INVALID_EVENT_WAIT_LIST";
    case -58: return "CL_INVALID_EVENT";
    case -59: return "CL_INVALID_OPERATION";
    case -60: return "CL_INVALID_GL_OBJECT";
    case -61: return "CL_INVALID_BUFFER_SIZE";
    case -62: return "CL_INVALID_MIP_LEVEL";
    case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
    case -64: return "CL_INVALID_PROPERTY";
    case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
    case -66: return "CL_INVALID_COMPILER_OPTIONS";
    case -67: return "CL_INVALID_LINKER_OPTIONS";
    case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

    // extension errors
    case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
    default: return "Unknown OpenCL error";
  }
}

cl_uint get_platforms()
{
  cl_int err;
  cl_uint num_platforms;

  printf("Action: getting OpenCL platforms... ");

  err = clGetPlatformIDs(0, NULL, &num_platforms);                              // Getting number of existing OpenCL platforms...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  platform = (cl_platform_id*) malloc(sizeof(cl_platform_id)*num_platforms);   // Allocating platform array...

  err = clGetPlatformIDs(num_platforms, platform, NULL);                       // Getting OpenCL platform IDs...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("\n        Found %d platform(s)!\n", num_platforms);
  printf("        DONE!\n");

  return num_platforms;                                                         // Returning number of existing platforms...
}

void get_platform_info(cl_uint index_platform, cl_platform_info name_param)
{
  cl_int err;
  size_t  size_value;

  err = clGetPlatformInfo(platform[index_platform],                            // Getting platform information...
                          name_param,
                          0,
                          NULL,
                          &size_value);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  value = (char*) malloc(size_value);                                           // Allocating value array...

  err = clGetPlatformInfo(platform[index_platform],                            // Getting platform information...
                          name_param,
                          size_value,
                          value,
                          NULL);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  // Switching platform parameter type:
  switch (name_param)
  {
    case CL_PLATFORM_PROFILE:
      printf("        CL_PLATFORM_PROFILE = %s\n", value);
    break;

    case CL_PLATFORM_VERSION:
      printf("        CL_PLATFORM_VERSION = %s\n", value);
    break;

    case CL_PLATFORM_NAME:
      printf("        CL_PLATFORM_NAME = %s\n", value);
    break;

    case CL_PLATFORM_VENDOR:
      printf("        CL_PLATFORM_VENDOR = %s\n", value);
    break;

    case CL_PLATFORM_EXTENSIONS:
      printf("        CL_PLATFORM_EXTENSIONS = %s\n", value);
  }

  free(value);                                                                  // Freeing value array...
}

cl_uint get_devices(cl_uint index_platform)
{
  cl_int err;
  cl_uint num_devices;

  printf("Action: getting OpenCL devices... ");

  err = clGetDeviceIDs(platform[index_platform],                               // Getting number of existing OpenCL GPU devices...
                       CL_DEVICE_TYPE_GPU,
                       0,
                       NULL,
                       &num_devices);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  device = (cl_device_id*) malloc(sizeof(cl_device_id) * num_devices);         // Allocating device array...

  err = clGetDeviceIDs(platform[index_platform],                               // Getting OpenCL platform IDs...
                       CL_DEVICE_TYPE_GPU,
                       num_devices,
                       device,
                       NULL);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("\n        Found %d device(s)!\n", num_devices);
  printf("        DONE!\n");

  return num_devices;
}

void get_device_info(cl_uint index_device, cl_device_info name_param)
{
  cl_int err;
  size_t  size_value;

  err = clGetDeviceInfo(device[index_device],                                  // Getting device information...
                        name_param,
                        0,
                        NULL,
                        &size_value);

  if(err != CL_SUCCESS)
  {
    printf("Error:  %s\n", get_error(err));
    exit(err);
  }

  value = (char*) malloc(size_value);                                           // Allocating value array...

  err = clGetDeviceInfo(device[index_device],                                  // Getting device information...
                        name_param,
                        size_value,
                        value,
                        NULL);

  if(err != CL_SUCCESS)
  {
    printf("Error:  %s\n", get_error(err));
    exit(err);
  }

  switch (name_param)
  {
    case CL_DEVICE_ADDRESS_BITS:
      printf("        CL_DEVICE_ADDRESS_BITS = %s\n", value);
    break;

    case CL_DEVICE_AVAILABLE:
      printf("        CL_DEVICE_AVAILABLE = %s\n", value);
    break;

    case CL_DEVICE_COMPILER_AVAILABLE:
      printf("        CL_DEVICE_COMPILER_AVAILABLE = %s\n", value);
    break;

    case CL_DEVICE_ENDIAN_LITTLE:
      printf("        CL_DEVICE_ENDIAN_LITTLE = %s\n", value);
    break;

    case CL_DEVICE_ERROR_CORRECTION_SUPPORT:
      printf("        CL_DEVICE_ERROR_CORRECTION_SUPPORT = %s\n", value);
    break;

    case CL_DEVICE_EXECUTION_CAPABILITIES:
      printf("        CL_DEVICE_EXECUTION_CAPABILITIES = %s\n", value);
    break;

    case CL_DEVICE_EXTENSIONS:
      printf("        CL_DEVICE_EXTENSIONS = %s\n", value);
    break;

    case CL_DEVICE_GLOBAL_MEM_CACHE_SIZE:
      printf("        CL_DEVICE_GLOBAL_MEM_CACHE_SIZE = %s\n", value);
    break;

    case CL_DEVICE_GLOBAL_MEM_CACHE_TYPE:
      printf("        CL_DEVICE_GLOBAL_MEM_CACHE_TYPE = %s\n", value);
    break;

    case CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE:
      printf("        CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE = %s\n", value);
    break;

    case CL_DEVICE_GLOBAL_MEM_SIZE:
      printf("        CL_DEVICE_GLOBAL_MEM_SIZE = %s\n", value);
    break;

    case CL_DEVICE_IMAGE_SUPPORT:
      printf("        CL_DEVICE_IMAGE_SUPPORT = %s\n", value);
    break;

    case CL_DEVICE_IMAGE2D_MAX_HEIGHT:
      printf("        CL_DEVICE_IMAGE2D_MAX_HEIGHT = %s\n", value);
    break;

    case CL_DEVICE_IMAGE2D_MAX_WIDTH:
      printf("        CL_DEVICE_IMAGE2D_MAX_WIDTH = %s\n", value);
    break;

    case CL_DEVICE_IMAGE3D_MAX_DEPTH:
      printf("        CL_DEVICE_IMAGE3D_MAX_DEPTH = %s\n", value);
    break;

    case CL_DEVICE_IMAGE3D_MAX_HEIGHT:
      printf("        CL_DEVICE_IMAGE3D_MAX_HEIGHT = %s\n", value);
    break;

    case CL_DEVICE_IMAGE3D_MAX_WIDTH:
      printf("        CL_DEVICE_IMAGE3D_MAX_WIDTH = %s\n", value);
    break;

    case CL_DEVICE_LOCAL_MEM_SIZE:
      printf("        CL_DEVICE_LOCAL_MEM_SIZE = %s\n", value);
    break;

    case CL_DEVICE_LOCAL_MEM_TYPE:
      printf("        CL_DEVICE_LOCAL_MEM_TYPE = %s\n", value);
    break;

    case CL_DEVICE_MAX_CLOCK_FREQUENCY:
      printf("        CL_DEVICE_MAX_CLOCK_FREQUENCY = %s\n", value);
    break;

    case CL_DEVICE_MAX_COMPUTE_UNITS:
      printf("        CL_DEVICE_MAX_COMPUTE_UNITS = %d\n", (int)*value);
    break;

    case CL_DEVICE_MAX_CONSTANT_ARGS:
      printf("        CL_DEVICE_MAX_CONSTANT_ARGS = %s\n", value);
    break;

    case CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE:
      printf("        CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE = %s\n", value);
    break;

    case CL_DEVICE_MAX_MEM_ALLOC_SIZE:
      printf("        CL_DEVICE_MAX_MEM_ALLOC_SIZE = %s\n", value);
    break;

    case CL_DEVICE_MAX_PARAMETER_SIZE:
      printf("        CL_DEVICE_MAX_PARAMETER_SIZE = %s\n", value);
    break;

    case CL_DEVICE_MAX_READ_IMAGE_ARGS:
      printf("        CL_DEVICE_MAX_READ_IMAGE_ARGS = %s\n", value);
    break;

    case CL_DEVICE_MAX_SAMPLERS:
      printf("        CL_DEVICE_MAX_SAMPLERS = %s\n", value);
    break;

    case CL_DEVICE_MAX_WORK_GROUP_SIZE:
      printf("        CL_DEVICE_MAX_WORK_GROUP_SIZE = %s\n", value);
    break;

    case CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:
      printf("        CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS = %s\n", value);
    break;

    case CL_DEVICE_MAX_WORK_ITEM_SIZES:
      printf("        CL_DEVICE_MAX_WORK_ITEM_SIZES = %s\n", value);
    break;

    case CL_DEVICE_MAX_WRITE_IMAGE_ARGS:
      printf("        CL_DEVICE_MAX_WRITE_IMAGE_ARGS = %s\n", value);
    break;

    case CL_DEVICE_MEM_BASE_ADDR_ALIGN:
      printf("        CL_DEVICE_MEM_BASE_ADDR_ALIGN = %s\n", value);
    break;

    case CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE:
      printf("        CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE = %s\n", value);
    break;

    case CL_DEVICE_NAME:
      printf("        CL_DEVICE_NAME = %s\n", value);
    break;

    case CL_DEVICE_PLATFORM:
      printf("        CL_DEVICE_PLATFORM = %s\n", value);
    break;

    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR:
      printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR = %s\n", value);
    break;

    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE:
      printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE = %s\n", value);
    break;

    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT:
      printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT = %s\n", value);
    break;

    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT:
      printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT = %s\n", value);
    break;

    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG:
      printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG = %s\n", value);
    break;

    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT:
      printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT = %s\n", value);
    break;

    case CL_DEVICE_PROFILE:
      printf("        CL_DEVICE_PROFILE = %s\n", value);
    break;

    case CL_DEVICE_PROFILING_TIMER_RESOLUTION:
      printf("        CL_DEVICE_PROFILING_TIMER_RESOLUTION = %s\n", value);
    break;

    case CL_DEVICE_QUEUE_PROPERTIES:
      printf("        CL_DEVICE_QUEUE_PROPERTIES = %s\n", value);
    break;

    case CL_DEVICE_SINGLE_FP_CONFIG:
      printf("        CL_DEVICE_SINGLE_FP_CONFIG = %s\n", value);
    break;

    case CL_DEVICE_TYPE:
      printf("        CL_DEVICE_TYPE = %s\n", value);
    break;

    case CL_DEVICE_VENDOR_ID:
      printf("        CL_DEVICE_VENDOR_ID = %s\n", value);
    break;

    case CL_DEVICE_VENDOR:
      printf("        CL_DEVICE_VENDOR = %s\n", value);
    break;

    case CL_DEVICE_VERSION:
      printf("        CL_DEVICE_VERSION = %s\n", value);
    break;

    case CL_DRIVER_VERSION:
      printf("        CL_DRIVER_VERSION = %s\n", value);
  }

  free(value);                                                                  // Freeing value array...
}

void init_opencl_context()
{
  cl_uint i;                                                                    // Defining platform number [#]...
  cl_uint j;                                                                    // Defining device [#]...
  cl_int  err;                                                                  // Defining error code [#]...

  num_platforms = get_platforms();                                              // Getting number of existing platforms [#]...

  for (i = 0; i < num_platforms; i++)
  {
    printf("Action: getting OpenCL platform info for platform #%d... \n", i);   // Printing message...

    get_platform_info(i, CL_PLATFORM_NAME);                                     // Getting platform information...
    get_platform_info(i, CL_PLATFORM_PROFILE);                                  // Getting platform information...
    get_platform_info(i, CL_PLATFORM_VERSION);                                  // Getting platform information...
    get_platform_info(i, CL_PLATFORM_VENDOR);                                   // Getting platform information...
    get_platform_info(i, CL_PLATFORM_EXTENSIONS);                               // Getting platform information...

    printf("        DONE!\n");                                                  // Printing message...

    num_devices = get_devices(i);                                               // Getting # of existing devices on a platform [#]...

    for (j = 0; j < num_devices; j++)                                           // Scanning devices...
    {
      printf("Action: getting OpenCL device info for device #%d... \n", j);     // Printing message...

      get_device_info(j, CL_DEVICE_NAME);                                       // Getting device information...
      get_device_info(j, CL_DEVICE_VERSION);                                    // Getting device information...
      get_device_info(j, CL_DRIVER_VERSION);                                    // Getting device information...
      get_device_info(j, CL_DEVICE_OPENCL_C_VERSION);                           // Getting device information...
      get_device_info(j, CL_DEVICE_MAX_COMPUTE_UNITS);                          // Getting device information...

      printf("        DONE!\n");                                                // Printing message...
    }

  }

  #ifdef __APPLE__                                                              // Checking for APPLE system...
    printf("Found APPLE system!\n");                                            // Printing message...

    CGLContextObj     kCGLContext     = CGLGetCurrentContext();                 // Setting APPLE OpenCL context properties...
    CGLShareGroupObj  kCGLShareGroup  = CGLGetShareGroup(kCGLContext);          // Setting APPLE OpenCL context properties...
    cl_context_properties properties[] =                                        // Setting APPLE OpenCL context properties...
    {
      CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
      (cl_context_properties) kCGLShareGroup,
      0
    };
  #endif

  #ifdef __linux__                                                              // Checking for LINUX system...
    printf("Found LINUX system!\n");                                            // Printing message...

    cl_context_properties properties[] =                                        // Setting LINUX OpenCL context properties...
    {
      CL_GL_CONTEXT_KHR, (cl_context_properties)glfwGetGLXContext(window),
      CL_GLX_DISPLAY_KHR, (cl_context_properties)glfwGetX11Display(),
      CL_CONTEXT_PLATFORM, (cl_context_properties)platform[0],
      0
    };
  #endif

  #ifdef __WINDOWS__                                                            // Checking for WINDOWS system...
    printf("Found WINDOWS system!\n");                                          // Printing message...

    cl_context_properties properties[] =                                        // Setting WINDOWS OpenCL context properties...
    {
      CL_GL_CONTEXT_KHR, (cl_context_properties)glfwGetWGLContext(window),
      CL_WGL_HDC_KHR, (cl_context_properties)GetDC(glfwGetWin32Window(window)),
      CL_CONTEXT_PLATFORM, (cl_context_properties)platform[0],
      0
    };
  #endif

  printf("Action: creating OpenCL context for GPU... ");                        // Printing message...

  context = clCreateContextFromType(properties,                                 // Creating OpenCL context...
                                    CL_DEVICE_TYPE_GPU,
                                    NULL,
                                    NULL,
                                    &err);

  if(err != CL_SUCCESS)                                                         // Checking for error...
  {
    printf("\nError:  %s\n", get_error(err));                                   // Printing message...
    exit(err);                                                                  // Exiting...
  }

  printf("DONE!\n");                                                            // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// OPENCL KERNEL FUNCTIONS ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void get_kernel_workgroup_size(kernel* k, cl_device_id device_id, size_t* local)
{
    cl_int err;

    printf("Action: getting maximum kernel workgroup size... ");
    err = clGetKernelWorkGroupInfo(k->thekernel,                          // Getting OpenCL kern linformation...
                                   device_id,
                                   CL_KERNEL_WORK_GROUP_SIZE,
                                   sizeof(*local),
                                   local,
                                   NULL);

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }

    printf("DONE!\n");
}

void release_opencl_context()
{
  cl_int err;

  printf("Action: releasing the OpenCL context... ");

  err = clReleaseContext(context);                                              // Releasing OpenCL context...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  free(device);                                                                // Freeing OpenCL devices...
  free(platform);                                                              // Freeing OpenCL platforms...

  printf("DONE!\n");
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// TEXT FUNCTIONS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// "SAVE" FUNCTIONS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void save_float(const char* file_name, float* data, int num_data)
{
  //write_file(file_name, file_buffer);
  //...to be completed.

}
