/// @file     queue.hpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Declaration of an OpenCL "queue" class.
///
/// @details  A Neutrino "queue" is an [OpenCL queue]
/// (https://en.wikipedia.org/wiki/OpenCL#OpenCL_C_language). The @link queue @endlink class has
/// got methods to @link read @endlink or @link write @endlink arguments from or to the OpenCL
/// queue: these operations tell Neutrino what commands to execute. The @link acquire @endlink
/// and @link release @endlink methods are reserved for the @link float1G @endlink and the
/// @link float4G @endlink data classes. These last two are the ones used for rendering graphics
/// using OpenGL from the corresponding data on the GPU client managed by the OpenCL kernel.
/// Before the invocation of the @link opencl::execute @endlink method, the @link acquire @endlink
/// method must be used on all data objects of interest. Similarly, the @link release @endlink
/// methods must be used afterwards. They do some operations which are necessary to the Neutrino
/// framework.

#ifndef queue_hpp
#define queue_hpp

#include "neutrino.hpp"
#include "data_classes.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// "queue" class /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class queue
/// ### OpenCL queue class.
/// Declares an OpenCL queue. The queue is a system to accumulate OpenCL commands in a list that
/// OpenCL eventually executes in front of a @link opencl::execute @endlink instruction.
/// Commands in the queue are related to what is written in the OpenCL kernel source file(s).
class queue : public neutrino                                                                       /// @brief **OpenCL queue.**
{
private:

public:
  cl_command_queue queue_id;                                                                        ///< @brief **OpenCL queue.**
  cl_context       context_id;                                                                      ///< @brief **OpenCL context.**
  cl_device_id     device_id;                                                                       ///< @brief **OpenCL device id.**

  /// @brief **Class constructor.**
  /// @details Sets queue_id, context_id and device_id to NULL default values.
  queue ();

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////// "read" functions ///////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **OpenCL queue read function.**
  /// @details Reads data from the OpenCL queue.
  void read
  (
   nu::int1* loc_data,                                                                              ///< nu::int1 object.
   GLuint    loc_layout_index                                                                       ///< Layout index.
  );

  /// @overload read(nu::int2* loc_data, cl_uint loc_layout_index)
  /// @details Reads data from the OpenCL queue.
  void read
  (
   nu::int2* loc_data,                                                                              ///< nu::int2 object.
   GLuint    loc_layout_index                                                                       ///< Layout index.
  );

  /// @overload read(nu::int3* loc_data, cl_uint loc_layout_index)
  /// @details Reads data from the OpenCL queue.
  void read
  (
   nu::int3* loc_data,                                                                              ///< nu::int3 object.
   GLuint    loc_layout_index                                                                       ///< Layout index.
  );

  /// @overload read(nu::int4* loc_data, cl_uint loc_layout_index)
  /// @details Reads data from the OpenCL queue.
  void read
  (
   nu::int4* loc_data,                                                                              ///< nu::int4 object.
   GLuint    loc_layout_index                                                                       ///< Layout index.
  );

  /// @overload read(nu::float1* loc_data, cl_uint loc_layout_index)
  /// @details Reads data from the OpenCL queue.
  void read
  (
   nu::float1* loc_data,                                                                            ///< nu::float1 object.
   GLuint      loc_layout_index                                                                     ///< Layout index.
  );

  /// @overload read(nu::float2* loc_data, cl_uint loc_layout_index)
  /// @details Reads data from the OpenCL queue.
  void read
  (
   nu::float2* loc_data,                                                                            ///< nu::float2 object.
   GLuint      loc_layout_index                                                                     ///< Layout index.
  );

  /// @overload read(nu::float3* loc_data, cl_uint loc_layout_index)
  /// @details Reads data from the OpenCL queue.
  void read
  (
   nu::float3* loc_data,                                                                            ///< nu::float3 object.
   GLuint      loc_layout_index                                                                     ///< Layout index.
  );

  /// @overload read(nu::float4* loc_data, cl_uint loc_layout_index)
  /// @details Reads data from the OpenCL queue.
  void read
  (
   nu::float4* loc_data,                                                                            ///< nu::float4 object.
   GLuint      loc_layout_index                                                                     ///< Layout index.
  );

  /// @overload read(nu::float16* loc_data, cl_uint loc_layout_index)
  /// @details Reads data from the OpenCL queue.
  void read
  (
   nu::float16* loc_data,                                                                           ///< nu::float16 object.
   GLuint       loc_layout_index                                                                    ///< Layout index.
  );

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////// write "functions" ////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **OpenCL queue write function.**
  /// @details Writes data to the OpenCL queue.
  void write
  (
   nu::int1* loc_data,                                                                              ///< nu::int1 object.
   GLuint    loc_layout_index                                                                       ///< Layout index.
  );

  /// @overload write(nu::int2* loc_data, cl_uint loc_layout_index)
  /// @details Writes data from the OpenCL queue.
  void write
  (
   nu::int2* loc_data,                                                                              ///< nu::int2 object.
   GLuint    loc_layout_index                                                                       ///< Layout index.
  );

  /// @overload write(nu::int3* loc_data, cl_uint loc_layout_index)
  /// @details Writes data from the OpenCL queue.
  void write
  (
   nu::int3* loc_data,                                                                              ///< nu::int3 object.
   GLuint    loc_layout_index                                                                       ///< Layout index.
  );

  /// @overload write(nu::int4* loc_data, cl_uint loc_layout_index)
  /// @details Writes data from the OpenCL queue.
  void write
  (
   nu::int4* loc_data,                                                                              ///< nu::int4 object.
   GLuint    loc_layout_index                                                                       ///< Layout index.
  );

  /// @overload write(nu::float1* loc_data, cl_uint loc_layout_index)
  /// @details Writes data from the OpenCL queue.
  void write
  (
   nu::float1* loc_data,                                                                            ///< nu::float1 object.
   GLuint      loc_layout_index                                                                     ///< Layout index.
  );

  /// @overload write(nu::float2* loc_data, cl_uint loc_layout_index)
  /// @details Writes data from the OpenCL queue.
  void write
  (
   nu::float2* loc_data,                                                                            ///< nu::float2 object.
   GLuint      loc_layout_index                                                                     ///< Layout index.
  );

  /// @overload write(nu::float3* loc_data, cl_uint loc_layout_index)
  /// @details Writes data from the OpenCL queue.
  void write
  (
   nu::float3* loc_data,                                                                            ///< nu::float3 object.
   GLuint      loc_layout_index                                                                     ///< Layout index.
  );

  /// @overload write(nu::float4* loc_data, cl_uint loc_layout_index)
  /// @details Writes data from the OpenCL queue.
  void write
  (
   nu::float4* loc_data,                                                                            ///< nu::float4 object.
   GLuint      loc_layout_index                                                                     ///< Layout index.
  );

  /// @overload write(nu::float16* loc_data, cl_uint loc_layout_index)
  /// @details Writes data from the OpenCL queue.
  void write
  (
   nu::float16* loc_data,                                                                           ///< nu::float16 object.
   GLuint       loc_layout_index                                                                    ///< Layout index.
  );

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////// acquire "functions" ///////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **OpenCL queue acquire function.**
  /// @details Enables OpenCL exclusive data access. It locks data access to OpenGL.
  void acquire
  (
   nu::int1* loc_data,                                                                              ///< Data object.
   GLuint    loc_layout_index                                                                       ///< OpenGL shader layout index.
  );

  /// @overload acquire(nu::int2* loc_data, GLuint loc_layout_index)
  /// @details Enables OpenCL exclusive data access. It locks data access to OpenGL.
  void acquire
  (
   nu::int2* loc_data,                                                                              ///< Data object.
   GLuint    loc_layout_index                                                                       ///< OpenGL shader layout index.
  );

  /// @overload acquire(nu::int3* loc_data, GLuint loc_layout_index)
  /// @details Enables OpenCL exclusive data access. It locks data access to OpenGL.
  void acquire
  (
   nu::int3* loc_data,                                                                              ///< Data object.
   GLuint    loc_layout_index                                                                       ///< OpenGL shader layout index.
  );

  /// @overload acquire(nu::int4* loc_data, GLuint loc_layout_index)
  /// @details Enables OpenCL exclusive data access. It locks data access to OpenGL.
  void acquire
  (
   nu::int4* loc_data,                                                                              ///< Data object.
   GLuint    loc_layout_index                                                                       ///< OpenGL shader layout index.
  );

  /// @overload acquire(nu::float1* loc_data, GLuint loc_layout_index)
  /// @details Enables OpenCL exclusive data access. It locks data access to OpenGL.
  void acquire
  (
   nu::float1* loc_data,                                                                            ///< Data object.
   GLuint      loc_layout_index                                                                     ///< OpenGL shader layout index.
  );

  /// @overload acquire(nu::float2* loc_data, GLuint loc_layout_index)
  /// @details Enables OpenCL exclusive data access. It locks data access to OpenGL.
  void acquire
  (
   nu::float2* loc_data,                                                                            ///< Data object.
   GLuint      loc_layout_index                                                                     ///< OpenGL shader layout index.
  );

  /// @overload acquire(nu::float3* loc_data, GLuint loc_layout_index)
  /// @details Enables OpenCL exclusive data access. It locks data access to OpenGL.
  void acquire
  (
   nu::float3* loc_data,                                                                            ///< Data object.
   GLuint      loc_layout_index                                                                     ///< OpenGL shader layout index.
  );

  /// @overload acquire(nu::float4* loc_data, GLuint loc_layout_index)
  /// @details Enables OpenCL exclusive data access. It locks data access to OpenGL.
  void acquire
  (
   nu::float4* loc_data,                                                                            ///< Data object.
   GLuint      loc_layout_index                                                                     ///< OpenGL shader layout index.
  );

  /// @overload acquire(nu::float16* loc_data, GLuint loc_layout_index)
  /// @details Enables OpenCL exclusive data access. It locks data access to OpenGL.
  void acquire
  (
   nu::float16* loc_data,                                                                           ///< Data object.
   GLuint       loc_layout_index                                                                    ///< OpenGL shader layout index.
  );

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////// release "functions" ///////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **OpenCL queue release function.**
  /// @details Disables OpenCL exclusive data access. It opens data access to OpenGL.
  void release
  (
   nu::int1* loc_data,                                                                              ///< Data object.
   GLuint    loc_layout_index                                                                       ///< OpenGL shader layout index.
  );

  /// @overload release(nu::int2* loc_data, GLuint loc_layout_index)
  /// @details Disables OpenCL exclusive data access. It opens data access to OpenGL.
  void release
  (
   nu::int2* loc_data,                                                                              ///< Data object.
   GLuint    loc_layout_index                                                                       ///< OpenGL shader layout index.
  );

  /// @overload release(nu::int3* loc_data, GLuint loc_layout_index)
  /// @details Disables OpenCL exclusive data access. It opens data access to OpenGL.
  void release
  (
   nu::int3* loc_data,                                                                              ///< Data object.
   GLuint    loc_layout_index                                                                       ///< OpenGL shader layout index.
  );

  /// @overload release(nu::int4* loc_data, GLuint loc_layout_index)
  /// @details Disables OpenCL exclusive data access. It opens data access to OpenGL.
  void release
  (
   nu::int4* loc_data,                                                                              ///< Data object.
   GLuint    loc_layout_index                                                                       ///< OpenGL shader layout index.
  );

  /// @overload release(nu::float1* loc_data, GLuint loc_layout_index)
  /// @details Disables OpenCL exclusive data access. It opens data access to OpenGL.
  void release
  (
   nu::float1* loc_data,                                                                            ///< Data object.
   GLuint      loc_layout_index                                                                     ///< OpenGL shader layout index.
  );

  /// @overload release(nu::float2* loc_data, GLuint loc_layout_index)
  /// @details Disables OpenCL exclusive data access. It opens data access to OpenGL.
  void release
  (
   nu::float2* loc_data,                                                                            ///< Data object.
   GLuint      loc_layout_index                                                                     ///< OpenGL shader layout index.
  );

  /// @overload release(nu::float3* loc_data, GLuint loc_layout_index)
  /// @details Disables OpenCL exclusive data access. It opens data access to OpenGL.
  void release
  (
   nu::float3* loc_data,                                                                            ///< Data object.
   GLuint      loc_layout_index                                                                     ///< OpenGL shader layout index.
  );

  /// @overload release(nu::float4* loc_data, GLuint loc_layout_index)
  /// @details Disables OpenCL exclusive data access. It opens data access to OpenGL.
  void release
  (
   nu::float4* loc_data,                                                                            ///< Data object.
   GLuint      loc_layout_index                                                                     ///< OpenGL shader layout index.
  );

  /// @overload release(nu::float16* loc_data, GLuint loc_layout_index)
  /// @details Disables OpenCL exclusive data access. It opens data access to OpenGL.
  void release
  (
   nu::float16* loc_data,                                                                           ///< Data object.
   GLuint       loc_layout_index                                                                    ///< OpenGL shader layout index.
  );

  /// @brief **Class destructor.**
  /// @details Releases the OpenCL queue.
  ~queue();
};

#endif
