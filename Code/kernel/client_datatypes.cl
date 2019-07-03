#ifndef datatypes_cl
#define datatypes_cl

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// POINT STRUCTURE: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)) _point
{
  // Position:
  float x;                                                                      // "x" coordinate.
  float y;                                                                      // "y" coordinate.
  float z;                                                                      // "z" coordinate.
  float w;                                                                      // "w" coordinate.
} point;

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// COLOR STRUCTURE: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)) _color
{
  // Color:
  float r;                                                                      // "r" color.
  float g;                                                                      // "g" color.
  float b;                                                                      // "b" color.
  float a;                                                                      // "a" color.
} color;

#endif
