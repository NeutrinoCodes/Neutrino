#ifndef device_datatypes_hpp
#define device_datatypes_hpp

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// POINT STRUCTURE: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)) point
{
  // Position:
  float4 position;                                                              //  Point coordinates.

  // Color:
  float4 color;                                                                 // Point color.
} point;

#endif
