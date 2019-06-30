#ifndef host_datatypes_hpp
#define host_datatypes_hpp

#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// "FLOAT4" STRUCTURE //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)) _float4
{
  cl_float x;                                                                   // "x" coordinate.
  cl_float y;                                                                   // "y" coordinate.
  cl_float z;                                                                   // "z" coordinate.
  cl_float w;                                                                   // "w" coordinate.
} float4;

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "INT4" STRUCTURE ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)) _int4
{
  cl_long x;                                                                    // "x" coordinate.
  cl_long y;                                                                    // "y" coordinate.
  cl_long z;                                                                    // "z" coordinate.
  cl_long w;                                                                    // "w" coordinate.
} int4;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// "POINT" STRUCTURE ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)) _point_structure
{
  GLfloat x;                                                                    // "x" coordinate.
  GLfloat y;                                                                    // "y" coordinate.
  GLfloat z;                                                                    // "z" coordinate.
  GLfloat w;                                                                    // "w" coordinate.
} point_structure;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// "COLOR" STRUCTURE ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)) _color_structure
{
  GLfloat r;                                                                    // "r" color.
  GLfloat g;                                                                    // "g" color.
  GLfloat b;                                                                    // "b" color.
  GLfloat a;                                                                    // "a" color.
} color_structure;

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "POINT" CLASS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class point
{
private:

public:
  point_structure* data;                                                        // Point data structure.
  cl_mem           buffer;                                                      // Data memory buffer.
  GLuint           vao;                                                         // Data VAO.
  GLuint           vbo;                                                         // Data VBO.
  GLsizeiptr       size;                                                        // Data size.
  GLuint           layout;                                                      // Data layout index.
  const char*      name;                                                        // Data name.

  point();
  void init (
             GLsizeiptr loc_size                                                // Data size.
            );

  ~point();
};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "COLOR" CLASS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class color
{
private:

public:
  color_structure* data;                                                        // Color data structure.
  cl_mem           buffer;                                                      // Data memory buffer.
  GLuint           vao;                                                         // Data VAO.
  GLuint           vbo;                                                         // Data VBO.
  GLsizeiptr       size;                                                        // Data size.
  GLuint           layout;                                                      // Data layout index.
  const char*      name;                                                        // Data name.

  color();
  void init (
             GLsizeiptr loc_size                                                // Data size.
            );

  ~color();
};

#endif
