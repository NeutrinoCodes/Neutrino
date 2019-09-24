/// @file   datatypes.hpp
/// @brief  This header file contains definitions of structures and classes used for data storage.
/// @author Erik ZORZIN
/// @date   24OCT2019

#ifndef datatypes_hpp
#define datatypes_hpp

#include "neutrino.hpp"                                                                             ///< peppo

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// DATA STRUCTURES /////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// ### 2D vector of "cl_long" data.
/// This structure is used as data storage in the "int2" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
/// @f$ e^{\pi i}+1 = 0 @f$
#pragma pack(push, 1)                                                                               ///< Packing data in 1 column...
typedef struct _int2_structure
{
  cl_long x;                                                                                        ///< "x" coordinate.
  cl_long y;                                                                                        ///< "y" coordinate.
} int2_structure;
#pragma pack(pop)                                                                                   ///< End of packing.

/// # int3 structure
/// ## 3D vector of "cl_long" data.
/// This structure is used as data storage in the "int3" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _int3_structure
{
  cl_long x;                                                                                        // "x" coordinate.
  cl_long y;                                                                                        // "y" coordinate.
  cl_long z;                                                                                        // "z" coordinate.
} int3_structure;
#pragma pack(pop)

/// # int4 structure
/// ## 4D vector of "cl_long" data.
/// This structure is used as data storage in the "int4" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _int4_structure
{
  cl_long x;                                                                                        // "x" coordinate.
  cl_long y;                                                                                        // "y" coordinate.
  cl_long z;                                                                                        // "z" coordinate.
  cl_long w;                                                                                        // "w" coordinate.
} int4_structure;
#pragma pack(pop)

/// # float2 structure
/// ## 2D vector of "cl_float" data.
/// This structure is used as data storage in the "float2" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _float2_structure
{
  cl_float x;                                                                                       // "x" coordinate.
  cl_float y;                                                                                       // "y" coordinate.
} float2_structure;
#pragma pack(pop)

/// # float3 structure
/// ## 3D vector of "cl_float" data.
/// This structure is used as data storage in the "float3" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _float3_structure
{
  cl_float x;                                                                                       // "x" coordinate.
  cl_float y;                                                                                       // "y" coordinate.
  cl_float z;                                                                                       // "z" coordinate.
} float3_structure;
#pragma pack(pop)

/// # float4 structure
/// ## 4D vector of cl_float data.
/// This structure is used as data storage in the "float4" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _float4_structure
{
  cl_float x;                                                                                       // "x" coordinate.
  cl_float y;                                                                                       // "y" coordinate.
  cl_float z;                                                                                       // "z" coordinate.
  cl_float w;                                                                                       // "w" coordinate.
} float4_structure;
#pragma pack(pop)

/// # float4G structure
/// ## 4D vector of "GLfloat" data.
/// This structure is used as data storage in the "float4G" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _float4G_structure
{
  GLfloat x;                                                                                        /// "x" coordinate.
  GLfloat y;                                                                                        /// "y" coordinate.
  GLfloat z;                                                                                        /// "z" coordinate.
  GLfloat w;                                                                                        /// "w" coordinate.
} float4G_structure;
#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// DATA CLASSES ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class
/// # "int1" class
/// ## 1D vector of "cl_long" data.
/// To be used in OpenCL kernels when graphics is not necessary. It does not have graphics OpenGL
/// bindings for interoperability.
class int1
{
private:

public:
  cl_long* data;                                                                                    // Data.
  cl_mem   buffer;                                                                                  // Data memory buffer.
  size_t   size;                                                                                    // Data size.
  cl_uint  layout;                                                                                  // Data layout index.
  bool     ready;                                                                                   // "ready" flag.

  /// Constructor.
  int1
    ();
  /// Initializer.
  void init
  (
   size_t loc_size                                                                                  // Data size.
  );

  /// Destructor.
  ~int1
    ();
};

/// # "int2" class
/// ## 2D vector of "cl_long" data.
/// To be used in OpenCL kernels when graphics is not necessary. It does not have graphics OpenGL
/// bindings for interoperability.
class int2
{
private:

public:
  int2_structure* data;                                                                             // Data.
  cl_mem          buffer;                                                                           // Data memory buffer.
  size_t          size;                                                                             // Data size.
  cl_uint         layout;                                                                           // Data layout index.
  bool            ready;                                                                            // "ready" flag.

  int2 ();
  void init (
             size_t loc_size                                                                        // Data size.
            );

  ~int2();
};

/// # "int3" class
/// ## 3D vector of "cl_long" data.
/// To be used in OpenCL kernels when graphics is not necessary. It does not have graphics OpenGL
/// bindings for interoperability.
class int3
{
private:

public:
  int3_structure* data;                                                                             // Data.
  cl_mem          buffer;                                                                           // Data memory buffer.
  size_t          size;                                                                             // Data size.
  cl_uint         layout;                                                                           // Data layout index.
  bool            ready;                                                                            // "ready" flag.

  int3 ();
  void init (
             size_t loc_size                                                                        // Data size.
            );

  ~int3();
};

/// # "int4" class
/// ## 4D vector of "cl_long" data.
/// To be used in OpenCL kernels when graphics is not necessary. It does not have graphics OpenGL
/// bindings for interoperability.
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

/// # "float1" class
/// ## 1D vector of "cl_float" data.
/// To be used in OpenCL kernels when graphics is not necessary. It does not have graphics OpenGL
/// bindings for interoperability.
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

/// # "float1G" class
/// ## 1D vector of "GLfloat" data.
/// To be used in OpenCL kernels when graphics is necessary. It has got graphics OpenGL
/// bindings for interoperability.
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

/// # "float2" class
/// ## 2D vector of "cl_float" data.
/// To be used in OpenCL kernels when graphics is not necessary. It does not have graphics OpenGL
/// bindings for interoperability.
class float2
{
private:

public:
  float2_structure* data;                                                                           // Data.
  cl_mem            buffer;                                                                         // Data memory buffer.
  size_t            size;                                                                           // Data size.
  cl_uint           layout;                                                                         // Data layout index.
  bool              ready;                                                                          // "ready" flag.

  float2 ();
  void init (
             size_t loc_size                                                                        // Data size.
            );

  ~float2();
};

/// # "float3" class
/// ## 3D vector of "cl_float" data.
/// To be used in OpenCL kernels when graphics is not necessary. It does not have graphics OpenGL
/// bindings for interoperability.
class float3
{
private:

public:
  float3_structure* data;                                                                           // Data.
  cl_mem            buffer;                                                                         // Data memory buffer.
  size_t            size;                                                                           // Data size.
  cl_uint           layout;                                                                         // Data layout index.
  bool              ready;                                                                          // "ready" flag.

  float3 ();
  void init (
             size_t loc_size                                                                        // Data size.
            );

  ~float3();
};

/// # "float4" class
/// ## 4D vector of "cl_float" data.
/// To be used in OpenCL kernels when graphics is not necessary. It does not have graphics OpenGL
/// bindings for interoperability.
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

/// # "float4G" class
/// ## 4D vector of "GLfloat" data.
/// To be used in OpenCL kernels when graphics is necessary. It has got graphics OpenGL
/// bindings for interoperability.
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
