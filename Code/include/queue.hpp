/// @file

#ifndef queue_hpp
#define queue_hpp

#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "QUEUE" CLASS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class queue
{
private:
  neutrino*        baseline;                                                    // Neutrino baseline.

public:
  cl_command_queue queue_id;                                                    // OpenCL queue.
  cl_context       context_id;                                                  // OpenCL context.
  cl_device_id     device_id;                                                   // OpenCL device id.

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// CONSTRUCTOR ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  queue();
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////// INIT ///////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void init (
             neutrino* loc_baseline
            );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// READ "float4" overload ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void read (
             float4* loc_data,                                                  // Data object.
             cl_uint loc_layout_index                                           // Layout index.
            );
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// READ "int4" overload ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void read (
             int4*   loc_data,                                                  // Data object.
             cl_uint loc_layout_index                                           // Layout index.
            );
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// READ "point" overload ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void read (
             point* loc_data,                                                   // Data object.
             GLuint loc_layout_index                                            // Layout index.
            );
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// READ "color" overload ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void read (
             color* loc_data,                                                   // Data object.
             GLuint loc_layout_index                                            // Layout index.
            );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// WRITE "float4" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write (
              float4* loc_data,                                                 // Data object.
              cl_uint loc_layout_index                                          // Layout index.
             );
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// WRITE "int4" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write (
              int4*   loc_data,                                                 // Data object.
              cl_uint loc_layout_index                                          // Layout index.
             );
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// WRITE "point" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write (
              point* loc_data,                                                  // Data object.
              GLuint loc_layout_index                                           // Layout index.
             );
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// WRITE "color" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void write (
              color* loc_data,                                                  // Data object.
              GLuint loc_layout_index                                           // Layout index.
             );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// ACQUIRE "point" overload /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void acquire (
                point* loc_data,                                                // Data object.
                GLuint loc_layout_index                                         // OpenGL shader layout index.
               );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// ACQUIRE "color" overload /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void acquire (
                color* loc_data,                                                // Data object.
                GLuint loc_layout_index                                         // OpenGL shader layout index.
               );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// RELEASE "point" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void release (
                point* loc_data,                                                // Data object.
                GLuint loc_layout_index                                         // OpenGL shader layout index.
               );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// RELEASE "color" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void release (
                color* loc_data,                                                // Data object.
                GLuint loc_layout_index                                         // OpenGL shader layout index.
               );

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// DESTRUCTOR ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~queue();
};

#endif
