#ifndef datatypes_hpp
#define datatypes_hpp

#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// "float4" STRUCTURE //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)
typedef struct _float4_structure
{
  cl_float x;                                                                   // "x" coordinate.
  cl_float y;                                                                   // "y" coordinate.
  cl_float z;                                                                   // "z" coordinate.
  cl_float w;                                                                   // "w" coordinate.
} float4_structure;
#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "int4" STRUCTURE ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)
typedef struct _int4_structure
{
  cl_long x;                                                                    // "x" coordinate.
  cl_long y;                                                                    // "y" coordinate.
  cl_long z;                                                                    // "z" coordinate.
  cl_long w;                                                                    // "w" coordinate.
} int4_structure;
#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// "float4G" STRUCTURE /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)
typedef struct _float4G_structure
{
  GLfloat x;                                                                    // "x" coordinate.
  GLfloat y;                                                                    // "y" coordinate.
  GLfloat z;                                                                    // "z" coordinate.
  GLfloat w;                                                                    // "w" coordinate.
} float4G_structure;
#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "float1" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class float1
{
private:

public:
  cl_float* data;                                                               // Data.
  cl_mem    buffer;                                                             // Data memory buffer.
  size_t    size;                                                               // Data size.
  cl_uint   layout;                                                             // Data layout index.
  bool      ready;                                                              // "ready" flag.

  float1 ();
  void init (
             size_t loc_size                                                    // Data size.
            );

  ~float1();
};

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// "int1" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class int1
{
private:

public:
  cl_long* data;                                                                // Data.
  cl_mem   buffer;                                                              // Data memory buffer.
  size_t   size;                                                                // Data size.
  cl_uint  layout;                                                              // Data layout index.
  bool     ready;                                                               // "ready" flag.

  int1 ();
  void init (
             size_t loc_size                                                    // Data size.
            );

  ~int1();
};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "float4" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class float4
{
private:

public:
  float4_structure* data;                                                       // Data structure.
  cl_mem            buffer;                                                     // Data memory buffer.
  size_t            size;                                                       // Data size.
  cl_uint           layout;                                                     // Data layout index.
  bool              ready;                                                      // "ready" flag.

  float4 ();
  void init (
             size_t loc_size                                                    // Data size.
            );

  ~float4();
};

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// "int4" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class int4
{
private:

public:
  int4_structure* data;                                                         // Data structure.
  cl_mem          buffer;                                                       // Data memory buffer.
  size_t          size;                                                         // Data size.
  cl_uint         layout;                                                       // Data layout index.
  bool            ready;                                                        // "ready" flag.

  int4 ();
  void init (
             size_t loc_size                                                    // Data size.
            );

  ~int4();
};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "float1G" CLASS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class float1G
{
private:

public:
  GLfloat*    data;                                                             // Data structure.
  cl_mem      buffer;                                                           // Data memory buffer.
  GLuint      vao;                                                              // Data VAO.
  GLuint      vbo;                                                              // Data VBO.
  GLsizeiptr  size;                                                             // Data size.
  GLuint      layout;                                                           // Data layout index.
  const char* name;                                                             // Data name.
  bool        ready;                                                            // "ready" flag.

  float1G ();
  void init (
             GLsizeiptr loc_size                                                // Data size.
            );

  ~float1G();
};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "float4G" CLASS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class float4G
{
private:

public:
  float4G_structure* data;                                                      // Data structure.
  cl_mem             buffer;                                                    // Data memory buffer.
  GLuint             vao;                                                       // Data VAO.
  GLuint             vbo;                                                       // Data VBO.
  GLsizeiptr         size;                                                      // Data size.
  GLuint             layout;                                                    // Data layout index.
  const char*        name;                                                      // Data name.
  bool               ready;                                                     // "ready" flag.

  float4G ();
  void init (
             GLsizeiptr loc_size                                                // Data size.
            );

  ~float4G();
};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "info" CLASS //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class info
{
private:

public:
  size_t size;                                                                  // Value array size.
  char*  value;                                                                 // Value array.

  info  (
         size_t loc_size                                                        // Info size.
        );

  ~info ();
};

#endif
