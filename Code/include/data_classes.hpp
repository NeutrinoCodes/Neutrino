/// @file     data_classes.hpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Declarations of classes used for data storage.
///
/// @details  In Neutrino, data storage occurs in both the OpenCL host PC and the client
///           GPU device. These classes are used to transfer data between the host the client.
///           Data can be organized in various formats: @link int1 @endlink,
///           @link int2 @endlink, @link int3 @endlink and @link int4 @endlink
///           classes are for sharing **cl_long** data, while @link float1 @endlink,
///           @link float2 @endlink, @link float3 @endlink
///           and @link float4 @endlink are for **cl_float** data.
///           Both type of classes do not have bindings for OpenGL/CL interoperability, therefore
///           they cannot be used for direct GPU 3D rendering. The reason of this is that OpenGL
///           is better designed to do graphics using GLSL's
///           [vec4](https://www.khronos.org/opengl/wiki/Data_Type_(GLSL))
///           4xN vectors of **GLfloat** numbers.
///           For this reason, a specific @link float4G @endlink ("G" stands for "graphics") class
///           has been declared in order to represent 4xN vectors of
///           [homogeneous coordinates](https://en.wikipedia.org/wiki/Homogeneous_coordinates)
///           **GLfloat** numbers which are commonly used in
///           [projective geometry](https://en.wikipedia.org/wiki/Projective_geometry) to
///           describe points in a 3D
///           [projective space](https://en.wikipedia.org/wiki/Projective_space).
///           This class can be also used e.g. to represent the components 3D vector field.
///           Similarly, a @link float1G @endlink class has been declared in order to e.g. describe
///           the intensity of a scalar field.

#ifndef data_classes_hpp
#define data_classes_hpp

#include "neutrino.hpp"
#include "data_structs.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int1" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class int1
/// ### 1xN vector of "cl_long" data.
/// Declares a 1xN vector (N = data size) of **cl_long** data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class int1
{
private:

public:
  /// @details 1xN (N = data @link size @endlink ) **cl_long** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  cl_long* data;                                                                                    ///< @brief **Data [cl_long].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem   buffer;                                                                                  ///< @brief **Data memory buffer.**

  /// @details Size, in numbers of elements, of the user's data to be allocated as data storage.
  size_t   size;                                                                                    ///< @brief **Data size [#].**

  /// @details Index used by the @link queue @endlink , @link kernel @endlink and
  /// @link shader @endlink
  /// classes in order to verify the correct sequence of the arguments in the OpenCL queue.
  /// The number is a **cl_uint** number starting from 0 and is incrementally assigned by the user
  /// during each @link kernel::setarg @endlink statement, in order to define the sequence of the
  /// operations. It is responsibility of the user to maintain the sequence numbering convention
  /// during all subsequent calls of the methods @link kernel::setarg @endlink ,
  /// @link shader::setarg @endlink , @link queue::read @endlink , @link queue::write @endlink ,
  /// @link queue:acquire @endlink and @link queue:release @endlink.
  cl_uint layout;                                                                                   ///< @brief **Data layout index [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool    ready;                                                                                    ///< @brief **Buffer "ready" flag.**

  /// @brief Class constructor.
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link int1::init @endlink method.
  int1 ();

  /// @brief Class initializer.
  /// @details Creates a "1 x size" data storage of **cl_long** allocated on the host PC memory
  /// and initializes all data to 0.
  void init (
             size_t loc_size                                                                        ///< @brief **Data size [#].**
            );

  /// @brief Class destructor.
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link int1::init @endlink as data storage.
  ~int1  ();

};

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int2" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class int2
/// ### 2xN vector of "cl_long" data.
/// Declares a 2xN vector (N = data size) of "cl_long" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class int2
{
private:

public:
  /// @details 2xN (N = data @link size @endlink ) **cl_long** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  int2_structure* data;                                                                             ///< @brief **Data [cl_long].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem          buffer;                                                                           ///< @brief **Data memory buffer.**

  /// @details Size, in numbers of elements, of the user's data to be allocated as data storage.
  size_t          size;                                                                             ///< @brief **Data size [#].**

  /// @details Index used by the @link queue @endlink , @link kernel @endlink and
  /// @link shader @endlink
  /// classes in order to verify the correct sequence of the arguments in the OpenCL queue.
  /// The number is a **cl_uint** number starting from 0 and is incrementally assigned by the user
  /// during each @link kernel::setarg @endlink statement, in order to define the sequence of the
  /// operations. It is responsibility of the user to maintain the sequence numbering convention
  /// during all subsequent calls of the methods @link kernel::setarg @endlink ,
  /// @link shader::setarg @endlink , @link queue::read @endlink , @link queue::write @endlink ,
  /// @link queue:acquire @endlink and @link queue:release @endlink.
  cl_uint layout;                                                                                   ///< @brief **Data layout index [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool    ready;                                                                                    ///< @brief **Buffer "ready" flag.**

  /// @brief Class constructor.
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link int2::init @endlink method.
  int2 ();

  /// @brief Class initializer.
  /// @details Creates a "2 x size" data storage of **cl_long** allocated on the host PC memory
  /// and initializes all data to 0.
  void init (
             size_t loc_size                                                                        ///< @brief **Data size [#].**
            );

  /// @brief Class destructor.
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link int2::init @endlink as data storage.
  ~int2();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int3" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class int3
/// ### 3xN vector of "cl_long" data.
/// Declares a 3xN vector (N = data size) of "cl_long" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class int3
{
private:

public:
  /// @details 3xN (N = data @link size @endlink ) **cl_long** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  int3_structure* data;                                                                             ///< @brief **Data [cl_long].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem          buffer;                                                                           ///< @brief **Data memory buffer.**

  /// @details Size, in numbers of elements, of the user's data to be allocated as data storage.
  size_t          size;                                                                             ///< @brief **Data size [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  cl_uint         layout;                                                                           ///< @brief **Data layout index [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool            ready;                                                                            ///< @brief **Buffer "ready" flag.**

  /// @brief Class constructor.
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link int3::init @endlink method.
  int3 ();

  /// @brief Class initializer.
  /// @details Creates a "3 x size" data storage of **cl_long** allocated on the host PC memory
  /// and initializes all data to 0.
  void init (
             size_t loc_size                                                                        ///< @brief **Data size [#].**
            );

  /// @brief Class destructor.
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link int3::init @endlink as data storage.
  ~int3();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int4" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class int4
/// ### 4xN vector of "cl_long" data.
/// Declares a 4xN vector (N = data size) of "cl_long" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class int4
{
private:

public:
  /// @details 4xN (N = data @link size @endlink ) **cl_long** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  int4_structure* data;                                                                             ///< @brief **Data [cl_long].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem          buffer;                                                                           ///< @brief **Data memory buffer.**

  /// @details Size, in numbers of elements, of the user's data to be allocated as data storage.
  size_t          size;                                                                             ///< @brief **Data size [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  cl_uint         layout;                                                                           ///< @brief **Data layout index [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool            ready;                                                                            ///< @brief **Buffer "ready" flag.**

  /// @brief Class constructor.
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link int4::init @endlink method.
  int4 ();

  /// @brief Class initializer.
  /// @details Creates a "4 x size" data storage of **cl_long** allocated on the host PC memory
  /// and initializes all data to 0.
  void init (
             size_t loc_size                                                                        ///< @brief **Data size [#].**
            );

  /// @brief Class destructor.
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link int4::init @endlink as data storage.
  ~int4();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "float1" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class float1
/// ### 1xN vector of "cl_float" data.
/// Declares a 1xN vector (N = data size) of "cl_float" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended to be used for graphics rendering.
class float1
{
private:

public:
  /// @details 1xN (N = data @link size @endlink ) **cl_float** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  cl_float* data;                                                                                   ///< @brief **Data [cl_float].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem    buffer;                                                                                 ///< @brief **Data memory buffer.**

  /// @details Size, in numbers of elements, of the user's data to be allocated as data storage.
  size_t    size;                                                                                   ///< @brief **Data size [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  cl_uint   layout;                                                                                 ///< @brief **Data layout index [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool      ready;                                                                                  ///< @brief **Buffer "ready" flag.**

  /// @brief Class constructor.
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link float1::init @endlink method.
  float1 ();

  /// @brief Class initializer.
  /// @details Creates a "1 x size" data storage of **cl_float** allocated on the host PC memory
  /// and initializes all data to 0.0f.
  void init (
             size_t loc_size                                                                        ///< @brief **Data size [#].**
            );

  /// @brief Class destructor.
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link float1::init @endlink as data storage.
  ~float1();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// "float1G" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class float1G
/// ### 1xN vector of "GLfloat" data.
/// Declares a 1xN vector (N = data size) of "GLfloat" data numbers.
/// To be used to transfer memory between host and client. It has bindings for
/// OpenGL/CL interoperability. Intended to be usde for graphics rendering.
class float1G
{
private:

public:
  /// @details 1xN (N = data @link size @endlink ) **GLfloat** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  GLfloat*    data;                                                                                 ///< @brief **Data size [#].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem      buffer;                                                                               ///< @brief **Data memory buffer.**

  /// @details [OpenGL data Vertex Array Object]
  /// (https://www.khronos.org/opengl/wiki/Vertex_Specification). Internally used by Neutrino.
  GLuint      vao;                                                                                  ///< @brief **OpenGL data Vertex Array Object.**

  /// @details [OpenGL data Vertex Buffer Object]
  /// (https://www.khronos.org/opengl/wiki/Vertex_Specification). Internally used by Neutrino.
  GLuint      vbo;                                                                                  ///< @brief **OpenGL data Vertex Buffer Object.**

  /// @details Size, in numbers of elements, of the user's data to be allocated as data storage.
  GLsizeiptr  size;                                                                                 ///< @brief **Data size [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  GLuint      layout;                                                                               ///< @brief **Data layout index [#].**

  /// @details String name of the object instance. To be set by the user according to what
  /// defined in the GLSL OpenGL shaders. Used to uniquely identify the object reference as
  /// variable in the GLSL OpenGL shaders.
  std::string name;                                                                                 ///< @brief **Data name.**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool        ready;                                                                                ///< @brief **Buffer "ready" flag.**

  /// @brief Class constructor.
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link float1G::init @endlink method.
  float1G ();

  /// @brief Class initializer.
  /// @details Creates a "1 x size" data storage of **GLfloat** allocated on the host PC memory
  /// and initializes all data to 0.0f.
  void init (
             GLsizeiptr loc_size                                                                    ///< @brief **Data size [#].**
            );

  /// @brief Class destructor.
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link float1G::init @endlink as data storage.
  ~float1G();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "float2" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class float2
/// ### 2xN vector of "cl_float" data.
/// Declares a 2xN vector (N = data size) of "cl_float" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended for graphics rendering.
class float2
{
private:

public:
  /// @details 2xN (N = data @link size @endlink ) **cl_float** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  float2_structure* data;                                                                           ///< @brief **Data [cl_float].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem            buffer;                                                                         ///< @brief **Data memory buffer.**

  /// @details Size, in numbers of elements, of the user's data to be allocated as data storage.
  size_t            size;                                                                           ///< @brief **Data size [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  cl_uint           layout;                                                                         ///< @brief **Data layout index [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool              ready;                                                                          ///< @brief **Buffer "ready" flag.**

  /// @brief Class constructor.
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link float2::init @endlink method.
  float2 ();

  /// @brief Class initializer.
  /// @details Creates a "2 x size" data storage of **GLfloat** allocated on the host PC memory
  /// and initializes all data to 0.0f.
  void init (
             size_t loc_size                                                                        ///< @brief **Data size [#].**
            );

  /// @brief Class destructor.
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link float2::init @endlink as data storage.
  ~float2();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "float3" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class float3
/// ### 3xN vector of "cl_float" data.
/// Declares a 3xN vector (N = data size) of "cl_float" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended for graphics rendering.
class float3
{
private:

public:
  /// @details 3xN (N = data @link size @endlink ) **cl_float** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  float3_structure* data;                                                                           ///< @brief **Data [cl_float].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem            buffer;                                                                         ///< @brief **Data memory buffer.**

  /// @details Size, in numbers of elements, of the user's data to be allocated as data storage.
  size_t            size;                                                                           ///< @brief **Data size [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  cl_uint           layout;                                                                         ///< @brief **Data layout index [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool              ready;                                                                          ///< @brief **Buffer "ready" flag.**

  /// @brief Class constructor.
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link float3::init @endlink method.
  float3 ();

  /// @brief Class initializer.
  /// @details Creates a "3 x size" data storage of **GLfloat** allocated on the host PC memory
  /// and initializes all data to 0.0f.
  void init (
             size_t loc_size                                                                        ///< @brief **Data size [#].**
            );

  /// @brief Class destructor.
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link float3::init @endlink as data storage.
  ~float3();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "float4" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class float4
/// ### 4xN vector of "cl_float" data.
/// Declares a 4xN vector (N = data size) of "cl_float" data numbers.
/// To be used to transfer memory between host and client. It does not have bindings for
/// OpenGL/CL interoperability. Not intended for graphics rendering.
class float4
{
private:

public:
  /// @details 4xN (N = data @link size @endlink ) **cl_float** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  float4_structure* data;                                                                           ///< @brief **Data [cl_float].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem            buffer;                                                                         ///< @brief **Data memory buffer.**

  /// @details Size, in numbers of elements, of the user's data to be allocated as data storage.
  size_t            size;                                                                           ///< @brief **Data size [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  cl_uint           layout;                                                                         ///< @brief **Data layout index [#].**

  /// @details This flag serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method. It is internally managed by Neutrino.
  bool              ready;                                                                          ///< @brief **Buffer "ready" flag.**

  /// @brief Class constructor.
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link float4::init @endlink method.
  float4 ();

  /// @brief Class initializer.
  /// @details Creates a "4 x size" data storage of **GLfloat** allocated on the host PC memory
  /// and initializes all data to 0.0f.
  void init (
             size_t loc_size                                                                        ///< @brief **Data size [#].**
            );

  /// @brief Class destructor.
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link float4::init @endlink as data storage.
  ~float4();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// "float4G" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class float4G
/// ### 4xN vector of "GLfloat" data.
/// Declares a 4xN vector (N = data size) of "GLfloat" data numbers.
/// To be used to transfer memory between host and client. It has bindings for
/// OpenGL/CL interoperability. Intended for graphics rendering.
class float4G
{
private:

public:
  /// @details 4xN (N = data @link size @endlink ) **GLfloat** data storage.
  /// These data are stored in the host PC memory.
  /// They can be eventually exchanged between the client GPU by using the @link queue::init
  /// @endlink and @link write @endlink methods of the @link queue @endlink class.
  /// The data storage is created by the @link int1::init @endlink method and destroyed by the
  /// class destructor. An OpenCL **cl_mem** @link buffer @endlink object is initialized by the
  /// @link kernel::setarg @endlink method upon the verification of the status of the @link ready
  /// @endlink flag. The latter one serves as an indicator (internally managed by Neutrino) in order
  /// allow the @link buffer @endlink initialization and to impede it during subsequents
  /// calls of the @link kernel::setarg @endlink method.
  float4G_structure* data;                                                                          ///< @brief **Data size [#].**

  /// @details **cl_mem** OpenCL memory buffer object. It does not contain user data. It is
  /// internally used by Neutrino within the OpenCL mechanisms to define the properties of
  /// the memory allocation on the client GPU.
  cl_mem             buffer;                                                                        ///< @brief **Data memory buffer.**.

  /// @details [OpenGL data Vertex Array Object]
  /// (https://www.khronos.org/opengl/wiki/Vertex_Specification). Internally used by Neutrino.
  GLuint             vao;                                                                           ///< @brief **OpenGL data Vertex Array Object.**

  /// @details [OpenGL data Vertex Buffer Object]
  /// (https://www.khronos.org/opengl/wiki/Vertex_Specification). Internally used by Neutrino.
  GLuint             vbo;                                                                           ///< @brief **OpenGL data Vertex Buffer Object.**

  /// @details Size, in numbers of elements, of the user's data to be allocated as data storage.
  GLsizeiptr         size;                                                                          ///< @brief **Data size [#].**

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

  /// @brief Class constructor.
  /// @details It resets the @link ready @endlink. The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link float4G::init @endlink method.
  float4G ();

  /// @brief Class initializer.
  /// @details Creates a "4 x size" data storage of **GLfloat** allocated on the host PC memory
  /// and initializes all data to 0.0f.
  void init (
             GLsizeiptr loc_size                                                                    ///< @brief **Data size [#].**
            );

  /// @brief Class destructor.
  /// @details It deallocates the host PC memory previously allocated by the
  /// @link float4G::init @endlink as data storage.
  ~float4G();
};

#endif
