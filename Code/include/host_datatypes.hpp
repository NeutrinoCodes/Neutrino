#ifndef host_datatypes_hpp
#define host_datatypes_hpp

#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// "POINT" STRUCTURE ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)) _point_structure
{
  // Position:
  GLfloat x;                                                                    // "x" coordinate.
  GLfloat y;                                                                    // "y" coordinate.
  GLfloat z;                                                                    // "z" coordinate.
  GLfloat w;                                                                    // "w" coordinate.

  // Color:
  GLfloat r;                                                                    // "r" color.
  GLfloat g;                                                                    // "g" color.
  GLfloat b;                                                                    // "b" color.
  GLfloat a;                                                                    // "a" color.
} point_structure;

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "POINT" CLASS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class point
{
private:

public:
  point_structure* data;                                                        // Point data structure.
  cl_mem           buffer;                                                      // OpenCL data memory buffer.
  GLuint           vao;                                                         // Node VAO.
  GLuint           vbo;                                                         // Node VBO.
  GLsizeiptr       size;                                                        // Data size.
  GLuint           layout;                                                      // Layout index.

  point();

  init (
        GLsizeiptr loc_size                                                     // Data size.
       );

  ~point();
};

#endif
