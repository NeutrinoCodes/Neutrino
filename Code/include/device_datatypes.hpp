#ifndef device_datatypes_hpp
#define device_datatypes_hpp

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

  // Color:
  float r;                                                                      // "r" color.
  float g;                                                                      // "g" color.
  float b;                                                                      // "b" color.
  float a;                                                                      // "a" color.
} point;

typedef struct __attribute__ ((packed)) _point
{
  // Position:
  float x;                                                                      // "x" coordinate.
  float y;                                                                      // "y" coordinate.
  float z;                                                                      // "z" coordinate.
  float w;                                                                      // "w" coordinate.

  // Color:
  float r;                                                                      // "r" color.
  float g;                                                                      // "g" color.
  float b;                                                                      // "b" color.
  float a;                                                                      // "a" color.
} point;

#endif
