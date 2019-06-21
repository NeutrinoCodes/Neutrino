#include "queue.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "QUEUE" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
queue::queue()
{
  queue_id   = NULL;                                                            // Initializing queue id...
  context_id = NULL;                                                            // Initializing context id...
  device_id  = NULL;                                                            // Initializing device id...
}

/// # Initialisation function
/// ### Description:
/// Creates the OpenCL command queue.
void queue::init (
                  neutrino* loc_baseline
                 )
{
  cl_int loc_error;                                                             // Local error code.

  baseline   = loc_baseline;                                                    // Getting Neutrino baseline...
  baseline->action ("creating OpenCL command queue...");                        // Printing message...

  context_id = baseline->context_id;                                            // Initializing context id...
  device_id  = baseline->device_id;                                             // Initializing device id...

  // Creating OpenCL queue:
  queue_id   = clCreateCommandQueue (
                                     context_id,                                // OpenCL context ID.
                                     device_id,                                 // Device ID.
                                     0,                                         // Queue properties (con be used for enabling profiling).
                                     &loc_error
                                    );                                          // Error code.

  baseline->check_error (loc_error);                                            // Checking error...

  baseline->done ();                                                            // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// ACQUIRE ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::acquire (
                     point* loc_data,                                           // Data object.
                     GLuint loc_layout_index                                    // OpenGL shader layout index.
                    )
{
  cl_int loc_error;                                                             // Local error code.

  // Binding data:
  glBindBuffer (GL_ARRAY_BUFFER, loc_data->vbo);                                // Binding VBO...
  glVertexAttribPointer (
                         loc_layout_index,                                      // VAO index.
                         sizeof(point_structure)/sizeof(GLfloat),               // Number of components of data vector.
                         GL_FLOAT,                                              // Data type.
                         GL_FALSE,                                              // Fixed-point data normalization.
                         sizeof(point_structure),                               // Data stride.
                         0                                                      // Data offset.
                        );
  glEnableVertexAttribArray (loc_layout_index);                                 // Setting layout index in vertex shader...
  glFinish ();                                                                  // Ensuring that all OpenGL routines have completed all operations...

  // Acquiring OpenCL buffer:
  loc_error = clEnqueueAcquireGLObjects (
                                         queue_id,                              // Queue.
                                         1,                                     // # of memory objects.
                                         &loc_data->buffer,                     // Memory object array.
                                         0,                                     // # of events in event list.
                                         NULL,                                  // Event list.
                                         NULL                                   // Event.
                                        );

  baseline->check_error (loc_error);                                            // Checking returned error code...
};

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// RELEASE /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::release (
                     point* loc_data,                                           // Data object.
                     GLuint loc_layout_index                                    // OpenGL shader layout index.
                    )
{
  cl_int loc_error;                                                             // Local error code.

  // Releasing openCL buffer:
  loc_error = clEnqueueReleaseGLObjects (
                                         queue_id,                              // Queue.
                                         1,                                     // # of memory objects.
                                         &loc_data->buffer,                     // Memory object array.
                                         0,                                     // # of events in event list.
                                         NULL,                                  // Event list.
                                         NULL                                   // Event.
                                        );

  clFinish (queue_id);                                                          // Ensuring that all OpenCL routines have completed all operations...

  glDisableVertexAttribArray (loc_layout_index);                                // Unbinding data array...

  baseline->check_error (loc_error);                                            // Checking returned error code...
};

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DESTRUCTOR //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
queue::~queue()
{
  cl_int loc_error;                                                             // Local error code.

  baseline->action ("releasing OpenCL command queue...");                       // Printing message...

  loc_error = clReleaseCommandQueue (queue_id);                                 // Releasing OpenCL queue...

  baseline->check_error (loc_error);                                            // Checking error...

  baseline->done ();                                                            // Printing message...
}
