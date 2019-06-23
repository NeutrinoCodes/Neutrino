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
  void             init (
                         neutrino* loc_baseline
                        );

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////// READ ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  template <typename T> void read (
                                   T loc_data                                   // Data object.
                                  )
  {
    cl_int loc_error;                                                           // Local error code.

    loc_error = clEnqueueReadBuffer (
                                     queue_id,                                  // OpenCL queue ID.
                                     loc_data.buffer,                           // Data buffer.
                                     CL_TRUE,                                   // Blocking write flag.
                                     0,                                         // Data buffer offset.
                                     sizeof(loc_data.data)*loc_data.size,       // Data buffer size.
                                     loc_data.data,                             // Data buffer.
                                     0,                                         // Number of events in the list.
                                     NULL,                                      // Event list.
                                     NULL                                       // Event.
                                    );

    check_error (loc_error);
  };

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// WRITE ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  template <typename T1, typename T2> void write (
                                                  T1 loc_data,                  // Data object.
                                                  T2 loc_layout_index           // OpenGL GLSL layout index.
                                                 )
  {
    cl_int loc_error;                                                           // Local error code.

    // Writing OpenCL buffer:

    if(loc_layout_index != loc_data->layout)
    {
      baseline->error ("Layout index mismatch!");                               // Printing message...
      exit (EXIT_FAILURE);                                                      // Exiting...
    }

    loc_error = clEnqueueWriteBuffer (
                                      queue_id,                                 // OpenCL queue ID.
                                      loc_data.buffer,                          // Data buffer.
                                      CL_TRUE,                                  // Blocking write flag.
                                      0,                                        // Data buffer offset.
                                      sizeof(loc_data.data)*loc_data.size,      // Data buffer size.
                                      loc_data.data,                            // Data buffer.
                                      0,                                        // Number of events in the list.
                                      NULL,                                     // Event list.
                                      NULL                                      // Event.
                                     );

    check_error (loc_error);

    baseline->done ();                                                          // Printing message...
  };

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// ACQUIRE //////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void acquire (
                point* loc_data,                                                // Data object.
                GLuint loc_layout_index                                         // OpenGL shader layout index.
               );


  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// RELEASE //////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void release (
                point* loc_data,                                                // Data object.
                GLuint loc_layout_index                                         // OpenGL shader layout index.
               );

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// DESTRUCTOR ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~queue();

#endif
