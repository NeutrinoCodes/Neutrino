/// @file   queue.hpp
/// @author Erik ZORZIN
/// @date   24OCT2019
/// @brief  Declaration of an OpenCL "queue" class.

#ifndef queue_hpp
#define queue_hpp

#include "neutrino.hpp"
#include "data_classes.hpp"

/// @class queue
/// ### OpenCL queue class.
/// Declares an OpenCL queue. The queue is a system to accumulate OpenCL commands in a list that
/// OpenCL eventually executes in front of a @link opencl::execute @endlink instruction.
/// Commands in the queue are related to what is written in the OpenCL kernel source file(s).
class queue
{
private:
  neutrino*        baseline;                                                                        // Neutrino baseline.

public:
  cl_command_queue queue_id;                                                                        // OpenCL queue.
  cl_context       context_id;                                                                      // OpenCL context.
  cl_device_id     device_id;                                                                       // OpenCL device id.

  /// @brief pippo
  /// @details poppo
  queue ();

  /// @brief Class initializer.
  /// @details peppo.
  void init (
             neutrino* loc_baseline                                                                 ///< Neutrino object.
            );

  /// @brief read
  /// @details My read.
  void read (
             float1* loc_data,                                                                      ///< float1 object.
             cl_uint loc_layout_index                                                               ///< Layout index.
            );

  /// @overload read(int1* loc_data, cl_uint loc_layout_index)
  /// Pippo.
  void read
  (
   int1*   loc_data,                                                                                // int1 object.
   cl_uint loc_layout_index                                                                         // Layout index.
  );

  /// @overload read(float4* loc_data, cl_uint loc_layout_index)
  /// ghgfgh
  void read
  (
   float4* loc_data,                                                                                // Data object.
   cl_uint loc_layout_index                                                                         // Layout index.
  );

  /// @overload read(int4* loc_data, cl_uint loc_layout_index)
  /// fgdfg
  void read
  (
   int4*   loc_data,                                                                                // Data object.
   cl_uint loc_layout_index                                                                         // Layout index.
  );

  /// @overload read(float1G* loc_data, cl_uint loc_layout_index)
  /// gsdfg
  void read
  (
   float1G* loc_data,                                                                               // Data object.
   cl_uint  loc_layout_index                                                                        // Layout index.
  );

  /// @overload read(float4G* loc_data, cl_uint loc_layout_index)
  /// tatdrt
  void read
  (
   float4G* loc_data,                                                                               // Data object.
   cl_uint  loc_layout_index                                                                        // Layout index.
  );

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// WRITE "float1" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write
  (
   float1* loc_data,                                                                                // float1 object.
   cl_uint loc_layout_index                                                                         // Layout index.
  );

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// WRITE "int1" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write
  (
   int1*   loc_data,                                                                                // int1 object.
   cl_uint loc_layout_index                                                                         // Layout index.
  );

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// WRITE "float4" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write
  (
   float4* loc_data,                                                                                // Data object.
   cl_uint loc_layout_index                                                                         // Layout index.
  );

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// WRITE "int4" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write
  (
   int4*   loc_data,                                                                                // Data object.
   cl_uint loc_layout_index                                                                         // Layout index.
  );

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// WRITE "float1G" overload ////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write
  (
   float1G* loc_data,                                                                               // Data object.
   GLuint   loc_layout_index                                                                        // Layout index.
  );

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// WRITE "float4G" overload ////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write
  (
   float4G* loc_data,                                                                               // Data object.
   GLuint   loc_layout_index                                                                        // Layout index.
  );

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// ACQUIRE "float1G" overload ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void acquire
  (
   float1G* loc_data,                                                                               // Data object.
   GLuint   loc_layout_index                                                                        // OpenGL shader layout index.
  );

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// ACQUIRE "float4G" overload ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void acquire
  (
   float4G* loc_data,                                                                               // Data object.
   GLuint   loc_layout_index                                                                        // OpenGL shader layout index.
  );

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// RELEASE "float1G" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void release
  (
   float1G* loc_data,                                                                               // Data object.
   GLuint   loc_layout_index                                                                        // OpenGL shader layout index.
  );

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// RELEASE "float4G" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void release
  (
   float4G* loc_data,                                                                               // Data object.
   GLuint   loc_layout_index                                                                        // OpenGL shader layout index.
  );

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// DESTRUCTOR ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~queue();
};

#endif
