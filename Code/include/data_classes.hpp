/// @file   data_classes.hpp
/// @author Erik ZORZIN
/// @date   24OCT2019
/// @brief  This header file contains definitions of structures and classes used for data storage.

#ifndef data_classes_hpp
#define data_classes_hpp

#include "neutrino.hpp"
#include "data_structs.hpp"

/// @class int1
/// ### 1xN vector of "cl_long" data.
/// Defines a 1xN vector (N = data size) of "cl_long" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended for graphics rendering.
class int1
{
private:

public:
  cl_long* data;                                                                                    ///< Data.
  cl_mem   buffer;                                                                                  ///< Data memory buffer.
  size_t   size;                                                                                    ///< Data size.
  cl_uint  layout;                                                                                  ///< Data layout index.
  bool     ready;                                                                                   ///< "ready" flag.

  int1                                                                                              /// Constructor.
    ();
  void init                                                                                         /// Initializer.
  (
   size_t loc_size                                                                                  /// Data size.
  );


  ~int1                                                                                             /// Destructor.
    ();
};

/// @class int2
/// ### 2D vector of "cl_long" data.
/// To be used in OpenCL kernels when graphics is not necessary. It does not have graphics OpenGL
/// bindings for interoperability.
class int2
{
private:

public:
  int2_structure* data;                                                                             ///< Data.
  cl_mem          buffer;                                                                           ///< Data memory buffer.
  size_t          size;                                                                             ///< Data size.
  cl_uint         layout;                                                                           ///< Data layout index.
  bool            ready;                                                                            ///< "ready" flag.

  int2 ();
  void init (
             size_t loc_size                                                                        // Data size.
            );

  ~int2();
};

/// @class int3
/// ### 3D vector of "cl_long" data.
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
