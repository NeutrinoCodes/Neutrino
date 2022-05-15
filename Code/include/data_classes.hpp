/// @file     data_classes.hpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Declarations of classes used for data storage.
///
/// @details  In Neutrino, data storage occurs in both the OpenCL host PC and the client
///           GPU device. These classes are used to transfer data between the host the client.
///           Data can be organized in these formats: @link nu::int1 @endlink,
///           @link nu::int2 @endlink, @link nu::int3 @endlink, @link nu::int4 @endlink,
///           @link nu::float1 @endlink, @link nu::float2 @endlink, @link nu::float3 @endlink and
///           @link nu::float4 @endlink.
///           The @link nu::float4 @endlink class
///           has been declared in order to represent 4xN vectors of
///           [homogeneous coordinates](https://en.wikipedia.org/wiki/Homogeneous_coordinates)
///           **GLfloat** numbers which are commonly used in
///           [projective geometry](https://en.wikipedia.org/wiki/Projective_geometry) to
///           describe points in a 3D
///           [projective space](https://en.wikipedia.org/wiki/Projective_space).

#ifndef data_classes_hpp
#define data_classes_hpp

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// Standard C/C++ header files //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <cerrno>
#include <algorithm>

#ifdef __APPLE__                                                                                    // Detecting Mac OS...
  #include <math.h>
#endif

#ifdef __linux__                                                                                    // Detecting Linux...
  #include <math.h>
#endif

#ifdef WIN32                                                                                        // Detecting Windows...
  #include <windows.h>
  #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004                                                 ///< Enabling ANSI terminal in Windows...
  #define DISABLE_NEWLINE_AUTO_RETURN        0x0008                                                 ///< Disabling new line auto return in Windows terminal...

  #include <cmath>
  #ifndef M_PI
    #define M_PI                             3.14159265358979323846f
  #endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// GLAD header files ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __APPLE__                                                                                    // Detecting Mac OS...
  #include <glad/glad.h>                                                                            // https://glad.dav1d.de
#endif

#ifdef __linux__                                                                                    // Detecting Linux...
  #include <glad/glad.h>                                                                            // https://glad.dav1d.de
#endif

#ifdef WIN32                                                                                        // Detecting Windows...
  #include <glad\glad.h>                                                                            // https://glad.dav1d.de
#endif

#ifdef WIN32                                                                                        // Detecting Windows...
  #define GLFW_EXPOSE_NATIVE_WIN32                                                                  ///< Enabling Windows native access functions...
  #define GLFW_EXPOSE_NATIVE_WGL                                                                    ///< Enabling Windows native access functions...
#endif

#ifdef __linux__                                                                                    // Detecting Linux...
  #define GLFW_EXPOSE_NATIVE_X11                                                                    ///< Enabling Linux native access functions...
  #define GLFW_EXPOSE_NATIVE_GLX                                                                    ///< Enabling Linux native access functions...
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// OpenCL/GL interoperability ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __APPLE__
  #define NU_INTEROP               "cl_APPLE_gl_sharing"
#endif

#ifdef __linux__
  #define NU_INTEROP               "cl_khr_gl_sharing"
#endif

#ifdef WIN32
  #define NU_INTEROP               "cl_khr_gl_sharing"
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// GLFW header files ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __APPLE__                                                                                    // Detecting Mac OS...
  #include <GLFW/glfw3.h>                                                                           // https://www.glfw.org
  #include <GLFW/glfw3native.h>                                                                     // https://www.glfw.org
#endif

#ifdef __linux__                                                                                    // Detecting Linux...
  #include <GLFW/glfw3.h>                                                                           // https://www.glfw.org
  #include <GLFW/glfw3native.h>                                                                     // https://www.glfw.org
#endif

#ifdef WIN32                                                                                        // Detecting Windows...
  #include <GLFW\glfw3.h>                                                                           // https://www.glfw.org
  #include <GLFW\glfw3native.h>                                                                     // https://www.glfw.org
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// OpenGL header files ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __APPLE__
  #include <OpenGL/OpenGL.h>                                                                        // Apple deprecated the OpenGL framework in 2018, OS-X 10.14 Mojave.
#endif

#ifdef __linux__                                                                                    // Detecting Linux...
  #include <GL/gl.h>                                                                                // https://www.opengl.org
#endif

#ifdef WIN32                                                                                        // Detecting Windows...
  #include <GL\gl.h>                                                                                // https://www.opengl.org
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// OpenCL header files ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define CL_TARGET_OPENCL_VERSION          120                                                       // Using OpenCL 1.2.
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS                                                           ///< Allows the usage of "OpenCL 1.2" functions in newer versions.

#ifdef __APPLE__
  #include <OpenCL/opencl.h>                                                                        // Apple deprecated the OpenCL framework in 2018, OS-X 10.14 Mojave.
#endif

#ifdef __linux__                                                                                    // Detecting Linux...
  #include <CL/cl.h>                                                                                // https://www.opengl.org
  #include <CL/cl_gl.h>                                                                             // https://www.opengl.org
#endif

#ifdef WIN32                                                                                        // Detecting Windows...
  #include <CL\cl.h>                                                                                // https://www.opengl.org
  #include <CL\cl_gl.h>                                                                             // https://www.opengl.org
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// DATA STRUCTURES ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the "nu::int2" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
typedef struct _nu_int2_structure
{
  GLint x;                                                                                          ///< "x" coordinate.
  GLint y;                                                                                          ///< "y" coordinate.
} nu_int2_structure;
#pragma pack(pop)                                                                                   // End of packing.

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the "nu::int3" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _nu_int3_structure
{
  GLint x;                                                                                          ///< "x" coordinate.
  GLint y;                                                                                          ///< "y" coordinate.
  GLint z;                                                                                          ///< "z" coordinate.
} nu_int3_structure;
#pragma pack(pop)

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the "nu::int4" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _nu_int4_structure
{
  GLint x;                                                                                          ///< "x" coordinate.
  GLint y;                                                                                          ///< "y" coordinate.
  GLint z;                                                                                          ///< "z" coordinate.
  GLint w;                                                                                          ///< "w" coordinate.
} nu_int4_structure;
#pragma pack(pop)

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the "nu::float2" class. It is tightly packed to
/// be compatible with the OpenCL requirement of having a contiguous data arrangement without
/// padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _nu_float2_structure
{
  GLfloat x;                                                                                        ///< "x" coordinate.
  GLfloat y;                                                                                        ///< "y" coordinate.
} nu_float2_structure;
#pragma pack(pop)

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the "nu::float3" class. It is tightly packed to
/// be compatible with the OpenCL requirement of having a contiguous data arrangement without
/// padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _nu_float3_structure
{
  GLfloat x;                                                                                        ///< "x" coordinate.
  GLfloat y;                                                                                        ///< "y" coordinate.
  GLfloat z;                                                                                        ///< "z" coordinate.
} nu_float3_structure;
#pragma pack(pop)

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the "nu::float4" class. It is tightly packed to
/// be compatible with the OpenCL requirement of having a contiguous data arrangement without
/// padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _nu_float4_structure
{
  GLfloat x;                                                                                        ///< "x" coordinate.
  GLfloat y;                                                                                        ///< "y" coordinate.
  GLfloat z;                                                                                        ///< "z" coordinate.
  GLfloat w;                                                                                        ///< "w" coordinate.
} nu_float4_structure;
#pragma pack(pop)

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the "nu::float16" class. It is tightly packed to
/// be compatible with the OpenCL requirement of having a contiguous data arrangement without
/// padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _nu_float16_structure
{
  GLfloat s0;                                                                                       ///< "s0" coordinate.
  GLfloat s1;                                                                                       ///< "s1" coordinate.
  GLfloat s2;                                                                                       ///< "s2" coordinate.
  GLfloat s3;                                                                                       ///< "s3" coordinate.
  GLfloat s4;                                                                                       ///< "s4" coordinate.
  GLfloat s5;                                                                                       ///< "s5" coordinate.
  GLfloat s6;                                                                                       ///< "s6" coordinate.
  GLfloat s7;                                                                                       ///< "s7" coordinate.
  GLfloat s8;                                                                                       ///< "s8" coordinate.
  GLfloat s9;                                                                                       ///< "s9" coordinate.
  GLfloat sA;                                                                                       ///< "sA" coordinate.
  GLfloat sB;                                                                                       ///< "sB" coordinate.
  GLfloat sC;                                                                                       ///< "sC" coordinate.
  GLfloat sD;                                                                                       ///< "sD" coordinate.
  GLfloat sE;                                                                                       ///< "sE" coordinate.
  GLfloat sF;                                                                                       ///< "sF" coordinate.
} nu_float16_structure;
#pragma pack(pop)

// Neutrino data types:
typedef enum
{
  NU_INT,                                                                                           ///< Neutrino "nu::int1" data type.
  NU_INT2,                                                                                          ///< Neutrino "nu::int2" data type.
  NU_INT3,                                                                                          ///< Neutrino "nu::int3" data type.
  NU_INT4,                                                                                          ///< Neutrino "nu::int4" data type.
  NU_FLOAT,                                                                                         ///< Neutrino "nu::float1" data type.
  NU_FLOAT2,                                                                                        ///< Neutrino "nu::float2" data type.
  NU_FLOAT3,                                                                                        ///< Neutrino "nu::float3" data type.
  NU_FLOAT4,                                                                                        ///< Neutrino "nu::float4" data type.
  NU_FLOAT16                                                                                        ///< Neutrino "nu::float16" data type.
} nu_type;

namespace nu
{
/// @class data
/// ### Common base class for all Neutrino data.
/// Declares a common base class for all Neutrino data.
/// Used in order to be able to define vectors of heterogeneous Neutrino data.
class data
{
public:
  nu_type                   type;                                                                   ///< Kernel argument data type.
  size_t                    layout;                                                                 ///< Kernel argument layout index.
  static std::vector<data*> container;                                                              ///< @brief **Neutrino data array.**
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int1" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class int1
/// ### 1xN vector of "GLint" data.
/// Declares a 1xN vector (N = data size) of **GLint** data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class int1 : public data                                                                            /// @brief **1xN vector of "GLint" data.**
{
private:

public:
  /// @details 1xN (N = data @link size @endlink ) **GLint** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu::int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  std::vector<GLint> data;                                                                          ///< @brief **Data [GLint].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem             buffer;                                                                        ///< @brief **Data memory buffer.**.

  /// @details [OpenGL data Vertex Array Object]
  /// (https://www.khronos.org/opengl/wiki/Vertex_Specification). Internally used by Neutrino.
  GLuint             vao;                                                                           ///< @brief **OpenGL data Vertex Array Object.**

  /// @details [OpenGL data Vertex Buffer Object]
  /// (https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object).
  /// Internally used by Neutrino.
  GLuint             ssbo;                                                                          ///< @brief **OpenGL data Shader Storage Buffer Object.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  GLuint             layout;                                                                        ///< @brief **Data layout index [#].**

  /// @details String name of the object instance. To be set by the user according to what
  /// defined in the GLSL OpenGL shaders. Used to uniquely identify the object reference as
  /// variable in the GLSL OpenGL shaders.
  std::string        name;                                                                          ///< @brief **Data name.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool               ready;                                                                         ///< @brief **Buffer "ready" flag.**

  /// @brief **Class constructor.**
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link nu::int1::init @endlink method.
  int1 (
        size_t loc_layout                                                                           ///< Kernel argument layout index.
       );

  /// @brief **Read file function.**
  /// @details Reads data from a file and fills the data variable. If the data in the file is
  /// longer than the data variable size, then the reading process is interrupted.
  /// If the data in the file is shorter, than after filling the data variable with the data from
  /// the file the data variable is filled with zeros.
  /// The data must be organized in 1 column of 1 **GLint** number per line.
  void read (
             std::string loc_file_directory,                                                        ///< File directory.
             std::string loc_file_name                                                              ///< File name.
            );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu::int1::init @endlink as data storage.
  ~int1  ();

};

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int2" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class int2
/// ### 2xN vector of "GLint" data.
/// Declares a 2xN vector (N = data size) of "GLint" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class int2 : public data                                                                            ///< @brief **2xN vector of "GLint" data.**
{
private:

public:
  /// @details 2xN (N = data @link size @endlink ) **GLint** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu::int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  std::vector<nu_int2_structure> data;                                                              ///< @brief **Data [GLint].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem                         buffer;                                                            ///< @brief **Data memory buffer.**.

  /// @details [OpenGL data Vertex Array Object]
  /// (https://www.khronos.org/opengl/wiki/Vertex_Specification). Internally used by Neutrino.
  GLuint                         vao;                                                               ///< @brief **OpenGL data Vertex Array Object.**

  /// @details [OpenGL data Vertex Buffer Object]
  /// (https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object).
  /// Internally used by Neutrino.
  GLuint                         ssbo;                                                              ///< @brief **OpenGL data Shader Storage Buffer Object.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  GLuint                         layout;                                                            ///< @brief **Data layout index [#].**

  /// @details String name of the object instance. To be set by the user according to what
  /// defined in the GLSL OpenGL shaders. Used to uniquely identify the object reference as
  /// variable in the GLSL OpenGL shaders.
  std::string                    name;                                                              ///< @brief **Data name.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool                           ready;                                                             ///< @brief **Buffer "ready" flag.**

  /// @brief **Class constructor.**
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link nu::int2::init @endlink method.
  int2 (
        size_t loc_layout                                                                           ///< Kernel argument layout index.
       );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu::int2::init @endlink as data storage.
  ~int2();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int3" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class int3
/// ### 3xN vector of "GLint" data.
/// Declares a 3xN vector (N = data size) of "GLint" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class int3 : public data                                                                            /// @brief **3xN vector of "GLint" data.**
{
private:

public:
  /// @details 3xN (N = data @link size @endlink ) **GLint** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu::int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  std::vector<nu_int3_structure> data;                                                              ///< @brief **Data [GLint].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem                         buffer;                                                            ///< @brief **Data memory buffer.**.

  /// @details [OpenGL data Vertex Array Object]
  /// (https://www.khronos.org/opengl/wiki/Vertex_Specification). Internally used by Neutrino.
  GLuint                         vao;                                                               ///< @brief **OpenGL data Vertex Array Object.**

  /// @details [OpenGL data Vertex Buffer Object]
  /// (https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object).
  /// Internally used by Neutrino.
  GLuint                         ssbo;                                                              ///< @brief **OpenGL data Shader Storage Buffer Object.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  GLuint                         layout;                                                            ///< @brief **Data layout index [#].**

  /// @details String name of the object instance. To be set by the user according to what
  /// defined in the GLSL OpenGL shaders. Used to uniquely identify the object reference as
  /// variable in the GLSL OpenGL shaders.
  std::string                    name;                                                              ///< @brief **Data name.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool                           ready;                                                             ///< @brief **Buffer "ready" flag.**

  /// @brief **Class constructor.**
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link nu::int3::init @endlink method.
  int3 (
        size_t loc_layout                                                                           ///< Kernel argument layout index.
       );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu::int3::init @endlink as data storage.
  ~int3();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int4" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class int4
/// ### 4xN vector of "GLint" data.
/// Declares a 4xN vector (N = data size) of "GLint" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class int4 : public data                                                                            /// @brief **4xN vector of "GLint" data.**
{
private:

public:
  /// @details 4xN (N = data @link size @endlink ) **GLint** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu::int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  std::vector<nu_int4_structure> data;                                                              ///< @brief **Data [GLint].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem                         buffer;                                                            ///< @brief **Data memory buffer.**.

  /// @details [OpenGL data Vertex Array Object]
  /// (https://www.khronos.org/opengl/wiki/Vertex_Specification). Internally used by Neutrino.
  GLuint                         vao;                                                               ///< @brief **OpenGL data Vertex Array Object.**

  /// @details [OpenGL data Vertex Buffer Object]
  /// (https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object).
  /// Internally used by Neutrino.
  GLuint                         ssbo;                                                              ///< @brief **OpenGL data Shader Storage Buffer Object.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  GLuint                         layout;                                                            ///< @brief **Data layout index [#].**

  /// @details String name of the object instance. To be set by the user according to what
  /// defined in the GLSL OpenGL shaders. Used to uniquely identify the object reference as
  /// variable in the GLSL OpenGL shaders.
  std::string                    name;                                                              ///< @brief **Data name.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool                           ready;                                                             ///< @brief **Buffer "ready" flag.**

  /// @brief **Class constructor.**
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link nu::int4::init @endlink method.
  int4 (
        size_t loc_layout                                                                           ///< Kernel argument layout index.
       );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu::int4::init @endlink as data storage.
  ~int4();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// "float1" class /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class float1
/// ### 1xN vector of "GLfloat" data.
/// Declares a 1xN vector (N = data size) of "GLfloat" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class float1 : public data                                                                          /// @brief **1xN vector of "GLfloat" data.**
{
private:

public:
  /// @details 1xN (N = data @link size @endlink ) **GLfloat** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu::int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  std::vector<GLfloat> data;                                                                        ///< @brief **Data [GLfloat].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem               buffer;                                                                      ///< @brief **Data memory buffer.**.

  /// @details [OpenGL data Vertex Array Object]
  /// (https://www.khronos.org/opengl/wiki/Vertex_Specification). Internally used by Neutrino.
  GLuint               vao;                                                                         ///< @brief **OpenGL data Vertex Array Object.**

  /// @details [OpenGL data Vertex Buffer Object]
  /// (https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object).
  /// Internally used by Neutrino.
  GLuint               ssbo;                                                                        ///< @brief **OpenGL data Shader Storage Buffer Object.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  GLuint               layout;                                                                      ///< @brief **Data layout index [#].**

  /// @details String name of the object instance. To be set by the user according to what
  /// defined in the GLSL OpenGL shaders. Used to uniquely identify the object reference as
  /// variable in the GLSL OpenGL shaders.
  std::string          name;                                                                        ///< @brief **Data name.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool                 ready;                                                                       ///< @brief **Buffer "ready" flag.**

  /// @brief **Class constructor.**
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link nu::float1::init @endlink method.
  float1 (
          size_t loc_layout                                                                         ///< Kernel argument layout index.
         );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu::float1::init @endlink as data storage.
  ~float1();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "float2" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class float2
/// ### 2xN vector of "GLfloat" data.
/// Declares a 2xN vector (N = data size) of "GLfloat" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended for graphics rendering.
class float2 : public data                                                                          /// @brief **2xN vector of "GLfloat" data.**
{
private:

public:
  /// @details 2xN (N = data @link size @endlink ) **GLfloat** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu::int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  std::vector<nu_float2_structure> data;                                                            ///< @brief **Data [GLfloat].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem                           buffer;                                                          ///< @brief **Data memory buffer.**.

  /// @details [OpenGL data Vertex Array Object]
  /// (https://www.khronos.org/opengl/wiki/Vertex_Specification). Internally used by Neutrino.
  GLuint                           vao;                                                             ///< @brief **OpenGL data Vertex Array Object.**

  /// @details [OpenGL data Vertex Buffer Object]
  /// (https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object).
  /// Internally used by Neutrino.
  GLuint                           ssbo;                                                            ///< @brief **OpenGL data Shader Storage Buffer Object.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  GLuint                           layout;                                                          ///< @brief **Data layout index [#].**

  /// @details String name of the object instance. To be set by the user according to what
  /// defined in the GLSL OpenGL shaders. Used to uniquely identify the object reference as
  /// variable in the GLSL OpenGL shaders.
  std::string                      name;                                                            ///< @brief **Data name.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool                             ready;                                                           ///< @brief **Buffer "ready" flag.**

  /// @brief **Class constructor.**
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link nu::float2::init @endlink method.
  float2 (
          size_t loc_layout                                                                         ///< Kernel argument layout index.
         );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu::float2::init @endlink as data storage.
  ~float2();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "float3" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class float3
/// ### 3xN vector of "GLfloat" data.
/// Declares a 3xN vector (N = data size) of "GLfloat" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended for graphics rendering.
class float3 : public data                                                                          /// @brief **3xN vector of "GLfloat" data.**
{
private:

public:
  /// @details 3xN (N = data @link size @endlink ) **GLfloat** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu::int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  std::vector<nu_float3_structure> data;                                                            ///< @brief **Data [GLfloat].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem                           buffer;                                                          ///< @brief **Data memory buffer.**.

  /// @details [OpenGL data Vertex Array Object]
  /// (https://www.khronos.org/opengl/wiki/Vertex_Specification). Internally used by Neutrino.
  GLuint                           vao;                                                             ///< @brief **OpenGL data Vertex Array Object.**

  /// @details [OpenGL data Vertex Buffer Object]
  /// (https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object).
  /// Internally used by Neutrino.
  GLuint                           ssbo;                                                            ///< @brief **OpenGL data Shader Storage Buffer Object.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  GLuint                           layout;                                                          ///< @brief **Data layout index [#].**

  /// @details String name of the object instance. To be set by the user according to what
  /// defined in the GLSL OpenGL shaders. Used to uniquely identify the object reference as
  /// variable in the GLSL OpenGL shaders.
  std::string                      name;                                                            ///< @brief **Data name.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool                             ready;                                                           ///< @brief **Buffer "ready" flag.**

  /// @brief **Class constructor.**
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link nu::float3::init @endlink method.
  float3 (
          size_t loc_layout                                                                         ///< Kernel argument layout index.
         );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu::float3::init @endlink as data storage.
  ~float3();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "float4" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class float4
/// ### 4xN vector of "GLfloat" data.
/// Declares a 4xN vector (N = data size) of "GLfloat" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended for graphics rendering.
class float4 : public data                                                                          /// @brief **4xN vector of "GLfloat" data.**
{
private:

public:
  /// @details 4xN (N = data @link size @endlink ) **GLfloat** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu::int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  std::vector<nu_float4_structure> data;                                                            ///< @brief **Data [GLfloat].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem                           buffer;                                                          ///< @brief **Data memory buffer.**.

  /// @details [OpenGL data Vertex Array Object]
  /// (https://www.khronos.org/opengl/wiki/Vertex_Specification). Internally used by Neutrino.
  GLuint                           vao;                                                             ///< @brief **OpenGL data Vertex Array Object.**

  /// @details [OpenGL data Vertex Buffer Object]
  /// (https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object).
  /// Internally used by Neutrino.
  GLuint                           ssbo;                                                            ///< @brief **OpenGL data Shader Storage Buffer Object.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  GLuint                           layout;                                                          ///< @brief **Data layout index [#].**

  /// @details String name of the object instance. To be set by the user according to what
  /// defined in the GLSL OpenGL shaders. Used to uniquely identify the object reference as
  /// variable in the GLSL OpenGL shaders.
  std::string                      name;                                                            ///< @brief **Data name.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool                             ready;                                                           ///< @brief **Buffer "ready" flag.**

  /// @brief **Class constructor.**
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link nu::float4::init @endlink method.
  float4 (
          size_t loc_layout                                                                         ///< Kernel argument layout index.
         );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu::float4::init @endlink as data storage.
  ~float4();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "float16" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class float16
/// ### 16xN vector of "GLfloat" data.
/// Declares a 16xN vector (N = data size) of "GLfloat" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended for graphics rendering.
class float16 : public data                                                                         /// @brief **16xN vector of "GLfloat" data.**
{
private:

public:
  /// @details 16xN (N = data @link size @endlink ) **GLfloat** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu::int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  std::vector<nu_float16_structure> data;                                                           ///< @brief **Data [GLfloat].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem                            buffer;                                                         ///< @brief **Data memory buffer.**.

  /// @details [OpenGL data Vertex Array Object]
  /// (https://www.khronos.org/opengl/wiki/Vertex_Specification). Internally used by Neutrino.
  GLuint                            vao;                                                            ///< @brief **OpenGL data Vertex Array Object.**

  /// @details [OpenGL data Vertex Buffer Object]
  /// (https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object).
  /// Internally used by Neutrino.
  GLuint                            ssbo;                                                           ///< @brief **OpenGL data Shader Storage Buffer Object.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  GLuint                            layout;                                                         ///< @brief **Data layout index [#].**

  /// @details String name of the object instance. To be set by the user according to what
  /// defined in the GLSL OpenGL shaders. Used to uniquely identify the object reference as
  /// variable in the GLSL OpenGL shaders.
  std::string                       name;                                                           ///< @brief **Data name.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool                              ready;                                                          ///< @brief **Buffer "ready" flag.**

  /// @brief **Class constructor.**
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link nu::float16::init @endlink method.
  float16 (
           size_t loc_layout                                                                        ///< Kernel argument layout index.
          );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu::float16::init @endlink as data storage.
  ~float16();
};
}
#endif
