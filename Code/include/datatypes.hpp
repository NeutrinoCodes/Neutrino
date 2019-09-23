/// @file

#ifndef datatypes_hpp
#define datatypes_hpp

#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// DATA STRUCTURES ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
/// # "float2" structure
/// ## 2D vector of "cl_float" data.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _float2_structure
{
  cl_float x;                                                                                       // "x" coordinate.
  cl_float y;                                                                                       // "y" coordinate.
} float2_structure;
#pragma pack(pop)

/// # "int2" structure
/// ## 2D CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT of "cl_long" data.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _int2_structure
{
  cl_long x;                                                                                        // "x" coordinate.
  cl_long y;                                                                                        // "y" coordinate.
} int2_structure;
#pragma pack(pop)

/// # "float3" structure
/// ## 3D vector of "cl_float" data.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _float3_structure
{
  cl_float x;                                                                                       // "x" coordinate.
  cl_float y;                                                                                       // "y" coordinate.
  cl_float z;                                                                                       // "z" coordinate.
} float3_structure;
#pragma pack(pop)

/// # "int3" structure
/// ## 3D vector of "cl_long" data.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _int3_structure
{
  cl_long x;                                                                                        // "x" coordinate.
  cl_long y;                                                                                        // "y" coordinate.
  cl_long z;                                                                                        // "z" coordinate.
} int3_structure;
#pragma pack(pop)

/// # float4 structure
/// ## 4D vector of cl_float data.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _float4_structure
{
  cl_float x;                                                                                       // "x" coordinate.
  cl_float y;                                                                                       // "y" coordinate.
  cl_float z;                                                                                       // "z" coordinate.
  cl_float w;                                                                                       // "w" coordinate.
} float4_structure;
#pragma pack(pop)

/// # **int4** structure
/// ## 4D vector of **cl_long** data.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _int4_structure
{
  cl_long x;                                                                                        // "x" coordinate.
  cl_long y;                                                                                        // "y" coordinate.
  cl_long z;                                                                                        // "z" coordinate.
  cl_long w;                                                                                        // "w" coordinate.
} int4_structure;
#pragma pack(pop)

/// # **float4G** structure
/// ## 4D vector of **GLfloat** data
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _float4G_structure
{
  GLfloat x;                                                                                        // "x" coordinate.
  GLfloat y;                                                                                        // "y" coordinate.
  GLfloat z;                                                                                        // "z" coordinate.
  GLfloat w;                                                                                        // "w" coordinate.
} float4G_structure;
#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// DATA CLASSES ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
/// # **float1** class
class float1
{
private:

public:
  cl_float* data;                                                                                   // Data.
  cl_mem    buffer;                                                                                 // Data memory buffer.
  size_t    size;                                                                                   // Data size.
  cl_uint   layout;                                                                                 // Data layout index.
  bool      ready;                                                                                  // "ready" flag.

  float1 ();
  void init (
             size_t loc_size                                                                        // Data size.
            );

  ~float1();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// "int1" CLASS ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
class int1
{
private:

public:
  cl_long* data;                                                                                    // Data.
  cl_mem   buffer;                                                                                  // Data memory buffer.
  size_t   size;                                                                                    // Data size.
  cl_uint  layout;                                                                                  // Data layout index.
  bool     ready;                                                                                   // "ready" flag.

  int1 ();
  void init (
             size_t loc_size                                                                        // Data size.
            );

  ~int1();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// "float4" CLASS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
class float4
{
private:

public:
  float4_structure* data;                                                                           // Data structure.
  cl_mem            buffer;                                                                         // Data memory buffer.
  size_t            size;                                                                           // Data size.
  cl_uint           layout;                                                                         // Data layout index.
  bool              ready;                                                                          // "ready" flag.

  float4 ();
  void init (
             size_t loc_size                                                                        // Data size.
            );

  ~float4();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// "int4" CLASS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
class int4
{
private:

public:
  int4_structure* data;                                                                             // Data structure.
  cl_mem          buffer;                                                                           // Data memory buffer.
  size_t          size;                                                                             // Data size.
  cl_uint         layout;                                                                           // Data layout index.
  bool            ready;                                                                            // "ready" flag.

  int4 ();
  void init (
             size_t loc_size                                                                        // Data size.
            );

  ~int4();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// "float1G" CLASS ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
class float1G
{
private:

public:
  GLfloat*    data;                                                                                 // Data structure.
  cl_mem      buffer;                                                                               // Data memory buffer.
  GLuint      vao;                                                                                  // Data VAO.
  GLuint      vbo;                                                                                  // Data VBO.
  GLsizeiptr  size;                                                                                 // Data size.
  GLuint      layout;                                                                               // Data layout index.
  std::string name;                                                                                 // Data name.
  bool        ready;                                                                                // "ready" flag.

  float1G ();
  void init (
             GLsizeiptr loc_size                                                                    // Data size.
            );

  ~float1G();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// "float4G" CLASS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
class float4G
{
private:

public:
  float4G_structure* data;                                                                          // Data structure.
  cl_mem             buffer;                                                                        // Data memory buffer.
  GLuint             vao;                                                                           // Data VAO.
  GLuint             vbo;                                                                           // Data VBO.
  GLsizeiptr         size;                                                                          // Data size.
  GLuint             layout;                                                                        // Data layout index.
  std::string        name;                                                                          // Data name.
  bool               ready;                                                                         // "ready" flag.

  float4G ();
  void init (
             GLsizeiptr loc_size                                                                    // Data size.
            );

  ~float4G();
};

#endif
