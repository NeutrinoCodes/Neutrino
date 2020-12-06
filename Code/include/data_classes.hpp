/// @file     data_classes.hpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Declarations of classes used for data storage.
///
/// @details  In Neutrino, data storage occurs in both the OpenCL host PC and the client
///           GPU device. These classes are used to transfer data between the host the client.
///           Data can be organized in these formats: @link nu_int @endlink,
///           @link nu_int2 @endlink, @link nu_int3 @endlink, @link nu_int4 @endlink,
///           @link nu_float @endlink, @link nu_float2 @endlink, @link nu_float3 @endlink and
///           @link nu_float4 @endlink.
///           The @link nu_float4 @endlink class
///           has been declared in order to represent 4xN vectors of
///           [homogeneous coordinates](https://en.wikipedia.org/wiki/Homogeneous_coordinates)
///           **GLfloat** numbers which are commonly used in
///           [projective geometry](https://en.wikipedia.org/wiki/Projective_geometry) to
///           describe points in a 3D
///           [projective space](https://en.wikipedia.org/wiki/Projective_space).

#ifndef data_classes_hpp
#define data_classes_hpp

#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// DATA STRUCTURES ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the "nu_int2" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
typedef struct _nu_int2_structure
{
  GLint x;                                                                                          ///< "x" coordinate.
  GLint y;                                                                                          ///< "y" coordinate.
} nu_int2_structure;
#pragma pack(pop)                                                                                   // End of packing.

/// @brief    **Data structure. Internally used by Neutrino.**
/// @details  This structure is used as data storage in the "nu_int3" class. It is tightly packed to be
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
/// @details  This structure is used as data storage in the "nu_int4" class. It is tightly packed to be
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
/// @details  This structure is used as data storage in the "nu_float2" class. It is tightly packed to
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
/// @details  This structure is used as data storage in the "nu_float3" class. It is tightly packed to
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
/// @details  This structure is used as data storage in the "nu_float4" class. It is tightly packed to
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

// Neutrino data types:
typedef enum
{
  NU_INT,                                                                                           ///< Neutrino "nu_int" data type.
  NU_INT2,                                                                                          ///< Neutrino "nu_int2" data type.
  NU_INT3,                                                                                          ///< Neutrino "nu_int3" data type.
  NU_INT4,                                                                                          ///< Neutrino "nu_int4" data type.
  NU_FLOAT,                                                                                         ///< Neutrino "nu_float" data type.
  NU_FLOAT2,                                                                                        ///< Neutrino "nu_float2" data type.
  NU_FLOAT3,                                                                                        ///< Neutrino "nu_float3" data type.
  NU_FLOAT4,                                                                                        ///< Neutrino "nu_float4" data type.
} nu_type;

/// @class nu_data
/// ### Common base class for all Neutrino data.
/// Declares a common base class for all Neutrino data.
/// Used in order to be able to define vectors of heterogeneous Neutrino data.
class nu_data
{
public:
  nu_type type;                                                                                     ///< Kernel argument data type.
  size_t  layout_index;                                                                             ///< Kernel argument layout index.
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// "nu_int" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class nu_int
/// ### 1xN vector of "GLint" data.
/// Declares a 1xN vector (N = data size) of **GLint** data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class nu_int : public nu_data                                                                       /// @brief **1xN vector of "GLint" data.**
{
private:

public:
  /// @details 1xN (N = data @link size @endlink ) **GLint** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu_int::init @endlink method and destroyed by the
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
  /// therefore it must be done by invoking the @link nu_int::init @endlink method.
  nu_int (
          std::vector<nu_data*> loc_nu_data,                                                        ///< Neutrino common base data class.
          size_t                loc_layout_index                                                    ///< Kernel argument layout index.
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
  /// @link nu_int::init @endlink as data storage.
  ~nu_int  ();

};

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// "nu_int2" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class nu_int2
/// ### 2xN vector of "GLint" data.
/// Declares a 2xN vector (N = data size) of "GLint" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class nu_int2 : public nu_data                                                                      ///< @brief **2xN vector of "GLint" data.**
{
private:

public:
  /// @details 2xN (N = data @link size @endlink ) **GLint** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu_int::init @endlink method and destroyed by the
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
  /// therefore it must be done by invoking the @link nu_int2::init @endlink method.
  nu_int2 (
           nu_data* loc_nu_data,                                                                    ///< Neutrino common base data class.
           size_t   loc_layout_index                                                                ///< Kernel argument layout index.
          );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu_int2::init @endlink as data storage.
  ~nu_int2();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// "nu_int3" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class nu_int3
/// ### 3xN vector of "GLint" data.
/// Declares a 3xN vector (N = data size) of "GLint" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class nu_int3 : public nu_data                                                                      /// @brief **3xN vector of "GLint" data.**
{
private:

public:
  /// @details 3xN (N = data @link size @endlink ) **GLint** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu_int::init @endlink method and destroyed by the
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
  /// therefore it must be done by invoking the @link nu_int3::init @endlink method.
  nu_int3 (
           nu_data* loc_nu_data,                                                                    ///< Neutrino common base data class.
           size_t   loc_layout_index                                                                ///< Kernel argument layout index.
          );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu_int3::init @endlink as data storage.
  ~nu_int3();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// "nu_int4" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class nu_int4
/// ### 4xN vector of "GLint" data.
/// Declares a 4xN vector (N = data size) of "GLint" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class nu_int4 : public nu_data                                                                      /// @brief **4xN vector of "GLint" data.**
{
private:

public:
  /// @details 4xN (N = data @link size @endlink ) **GLint** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu_int::init @endlink method and destroyed by the
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
  /// therefore it must be done by invoking the @link nu_int4::init @endlink method.
  nu_int4 (
           nu_data* loc_nu_data,                                                                    ///< Neutrino common base data class.
           size_t   loc_layout_index                                                                ///< Kernel argument layout index.
          );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu_int4::init @endlink as data storage.
  ~nu_int4();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// "nu_float" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class nu_float
/// ### 1xN vector of "GLfloat" data.
/// Declares a 1xN vector (N = data size) of "GLfloat" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class nu_float : public nu_data                                                                     /// @brief **1xN vector of "GLfloat" data.**
{
private:

public:
  /// @details 1xN (N = data @link size @endlink ) **GLfloat** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu_int::init @endlink method and destroyed by the
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
  /// therefore it must be done by invoking the @link nu_float::init @endlink method.
  nu_float (
            nu_data* loc_nu_data,                                                                   ///< Neutrino common base data class.
            size_t   loc_layout_index                                                               ///< Kernel argument layout index.
           );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu_float::init @endlink as data storage.
  ~nu_float();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// "nu_float2" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class nu_float2
/// ### 2xN vector of "GLfloat" data.
/// Declares a 2xN vector (N = data size) of "GLfloat" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended for graphics rendering.
class nu_float2 : public nu_data                                                                    /// @brief **2xN vector of "GLfloat" data.**
{
private:

public:
  /// @details 2xN (N = data @link size @endlink ) **GLfloat** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu_int::init @endlink method and destroyed by the
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
  /// therefore it must be done by invoking the @link nu_float2::init @endlink method.
  nu_float2 (
             nu_data* loc_nu_data,                                                                  ///< Neutrino common base data class.
             size_t   loc_layout_index                                                              ///< Kernel argument layout index.
            );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu_float2::init @endlink as data storage.
  ~nu_float2();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// "nu_float3" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class nu_float3
/// ### 3xN vector of "GLfloat" data.
/// Declares a 3xN vector (N = data size) of "GLfloat" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended for graphics rendering.
class nu_float3 : public nu_data                                                                    /// @brief **3xN vector of "GLfloat" data.**
{
private:

public:
  /// @details 3xN (N = data @link size @endlink ) **GLfloat** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu_int::init @endlink method and destroyed by the
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
  /// therefore it must be done by invoking the @link nu_float3::init @endlink method.
  nu_float3 (
             nu_data* loc_nu_data,                                                                  ///< Neutrino common base data class.
             size_t   loc_layout_index                                                              ///< Kernel argument layout index.
            );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu_float3::init @endlink as data storage.
  ~nu_float3();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// "nu_float4" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class nu_float4
/// ### 4xN vector of "GLfloat" data.
/// Declares a 4xN vector (N = data size) of "GLfloat" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended for graphics rendering.
class nu_float4 : public nu_data                                                                    /// @brief **4xN vector of "GLfloat" data.**
{
private:

public:
  /// @details 4xN (N = data @link size @endlink ) **GLfloat** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link nu_int::init @endlink method and destroyed by the
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
  /// therefore it must be done by invoking the @link nu_float4::init @endlink method.
  nu_float4 (
             nu_data* loc_nu_data,                                                                  ///< Neutrino common base data class.
             size_t   loc_layout_index                                                              ///< Kernel argument layout index.
            );

  /// @brief **Class destructor.**
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link nu_float4::init @endlink as data storage.
  ~nu_float4();
};

#endif
