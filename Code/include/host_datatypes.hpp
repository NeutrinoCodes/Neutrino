#ifndef host_datatypes_hpp
#define host_datatypes_hpp

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// GLfloat4 STRUCTURE: /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)) GLfloat4
{
  GLfloat x;                                                                    // "x" value.
  GLfloat y;                                                                    // "y" value.
  GLfloat z;                                                                    // "z" value.
  GLfloat w;                                                                    // "w" value.
} GLfloat4;

/////////////////////////////////////////////////////7////////////////////////////
///////////////////////////////// POINT STRUCTURE: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)) point
{
  // Position:
  GLfloat4 position;                                                            // Point coordinates.

  // Color:
  GLfloat4 color;                                                               // Point color.
} point;

#endif
