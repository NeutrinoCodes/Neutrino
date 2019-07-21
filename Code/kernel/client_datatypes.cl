#ifndef datatypes_cl
#define datatypes_cl

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// POINT STRUCTURE: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)) _float4G
{
  // Position:
  float x;                                                                      // "x" coordinate.
  float y;                                                                      // "y" coordinate.
  float z;                                                                      // "z" coordinate.
  float w;                                                                      // "w" coordinate.
}float4G;

#endif
