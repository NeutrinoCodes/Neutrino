#include "queue.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "QUEUE" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
queue::queue()
{
  queue_id   = NULL;                                                                                // Initializing queue id...
  context_id = NULL;                                                                                // Initializing context id...
  device_id  = NULL;                                                                                // Initializing device id...
}

/// # Initialisation function
/// ### Description:
/// Creates the OpenCL command queue.
void queue::init (
                  neutrino* loc_baseline
                 )
{
  cl_int loc_error;                                                                                 // Local error code.

  baseline   = loc_baseline;                                                                        // Getting Neutrino baseline...
  baseline->action ("creating OpenCL command queue...");                                            // Printing message...

  context_id = baseline->context_id;                                                                // Initializing context id...
  device_id  = baseline->device_id;                                                                 // Initializing device id...

  // Creating OpenCL queue:
  queue_id   = clCreateCommandQueue (
                                     context_id,                                                    // OpenCL context ID.
                                     device_id,                                                     // Device ID.
                                     0,                                                             // Queue properties (con be used for enabling profiling).
                                     &loc_error
                                    );                                                              // Error code.

  baseline->check_error (loc_error);                                                                // Checking error...

  baseline->done ();                                                                                // Printing message...
}
//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// READ "float1" overload /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::read (
                  float1* loc_data,                                                                 // float1 object.
                  cl_uint loc_layout_index                                                          // Layout index.
                 )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer (
                                   queue_id,                                                        // OpenCL queue ID.
                                   loc_data->buffer,                                                // Data buffer.
                                   CL_TRUE,                                                         // Blocking write flag.
                                   0,                                                               // Data buffer offset.
                                   sizeof(cl_float)*loc_data->size,                                 // Data buffer size.
                                   loc_data->data,                                                  // Data buffer.
                                   0,                                                               // Number of events in the list.
                                   NULL,                                                            // Event list.
                                   NULL                                                             // Event.
                                  );

  baseline->check_error (loc_error);
};
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// READ "int1" overload /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::read (
                  int1*   loc_data,                                                                 // int1 object.
                  cl_uint loc_layout_index                                                          // Layout index.
                 )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer (
                                   queue_id,                                                        // OpenCL queue ID.
                                   loc_data->buffer,                                                // Data buffer.
                                   CL_TRUE,                                                         // Blocking write flag.
                                   0,                                                               // Data buffer offset.
                                   sizeof(cl_long)*loc_data->size,                                  // Data buffer size.
                                   loc_data->data,                                                  // Data buffer.
                                   0,                                                               // Number of events in the list.
                                   NULL,                                                            // Event list.
                                   NULL                                                             // Event.
                                  );

  baseline->check_error (loc_error);
};
//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// READ "float4" overload /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::read (
                  float4* loc_data,                                                                 // Data object.
                  cl_uint loc_layout_index                                                          // Layout index.
                 )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer (
                                   queue_id,                                                        // OpenCL queue ID.
                                   loc_data->buffer,                                                // Data buffer.
                                   CL_TRUE,                                                         // Blocking write flag.
                                   0,                                                               // Data buffer offset.
                                   sizeof(float4_structure)*loc_data->size,                         // Data buffer size.
                                   loc_data->data,                                                  // Data buffer.
                                   0,                                                               // Number of events in the list.
                                   NULL,                                                            // Event list.
                                   NULL                                                             // Event.
                                  );

  baseline->check_error (loc_error);
};
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// READ "int4" overload /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::read (
                  int4*   loc_data,                                                                 // Data object.
                  cl_uint loc_layout_index                                                          // Layout index.
                 )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer (
                                   queue_id,                                                        // OpenCL queue ID.
                                   loc_data->buffer,                                                // Data buffer.
                                   CL_TRUE,                                                         // Blocking write flag.
                                   0,                                                               // Data buffer offset.
                                   sizeof(int4_structure)*loc_data->size,                           // Data buffer size.
                                   loc_data->data,                                                  // Data buffer.
                                   0,                                                               // Number of events in the list.
                                   NULL,                                                            // Event list.
                                   NULL                                                             // Event.
                                  );

  baseline->check_error (loc_error);
};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// READ "float1G" overload ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::read (
                  float1G* loc_data,                                                                // Data object.
                  cl_uint  loc_layout_index                                                         // Layout index.
                 )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer (
                                   queue_id,                                                        // OpenCL queue ID.
                                   loc_data->buffer,                                                // Data buffer.
                                   CL_TRUE,                                                         // Blocking write flag.
                                   0,                                                               // Data buffer offset.
                                   sizeof(GLfloat)*loc_data->size,                                  // Data buffer size.
                                   loc_data->data,                                                  // Data buffer.
                                   0,                                                               // Number of events in the list.
                                   NULL,                                                            // Event list.
                                   NULL                                                             // Event.
                                  );

  baseline->check_error (loc_error);
};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// READ "float4G" overload ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::read (
                  float4G* loc_data,                                                                // Data object.
                  cl_uint  loc_layout_index                                                         // Layout index.
                 )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer (
                                   queue_id,                                                        // OpenCL queue ID.
                                   loc_data->buffer,                                                // Data buffer.
                                   CL_TRUE,                                                         // Blocking write flag.
                                   0,                                                               // Data buffer offset.
                                   sizeof(float4G_structure)*loc_data->size,                        // Data buffer size.
                                   loc_data->data,                                                  // Data buffer.
                                   0,                                                               // Number of events in the list.
                                   NULL,                                                            // Event list.
                                   NULL                                                             // Event.
                                  );

  baseline->check_error (loc_error);
};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// WRITE "float1" overload ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::write (
                   float1* loc_data,                                                                // float1 object.
                   cl_uint loc_layout_index                                                         // Layout index.
                  )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Writing OpenCL buffer:
  loc_error = clEnqueueWriteBuffer (
                                    queue_id,                                                       // OpenCL queue ID.
                                    loc_data->buffer,                                               // Data buffer.
                                    CL_TRUE,                                                        // Blocking write flag.
                                    0,                                                              // Data buffer offset.
                                    sizeof(cl_float)*loc_data->size,                                // Data buffer size.
                                    loc_data->data,                                                 // Data buffer.
                                    0,                                                              // Number of events in the list.
                                    NULL,                                                           // Event list.
                                    NULL                                                            // Event.
                                   );

  baseline->check_error (loc_error);
};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// WRITE "int1" overload /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::write (
                   int1*   loc_data,                                                                // int1 object.
                   cl_uint loc_layout_index                                                         // Layout index.
                  )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Writing OpenCL buffer:
  loc_error = clEnqueueWriteBuffer (
                                    queue_id,                                                       // OpenCL queue ID.
                                    loc_data->buffer,                                               // Data buffer.
                                    CL_TRUE,                                                        // Blocking write flag.
                                    0,                                                              // Data buffer offset.
                                    sizeof(cl_long)*loc_data->size,                                 // Data buffer size.
                                    loc_data->data,                                                 // Data buffer.
                                    0,                                                              // Number of events in the list.
                                    NULL,                                                           // Event list.
                                    NULL                                                            // Event.
                                   );

  baseline->check_error (loc_error);
};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// WRITE "float4" overload ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::write (
                   float4* loc_data,                                                                // Data object.
                   cl_uint loc_layout_index                                                         // Layout index.
                  )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Writing OpenCL buffer:
  loc_error = clEnqueueWriteBuffer (
                                    queue_id,                                                       // OpenCL queue ID.
                                    loc_data->buffer,                                               // Data buffer.
                                    CL_TRUE,                                                        // Blocking write flag.
                                    0,                                                              // Data buffer offset.
                                    sizeof(float4_structure)*loc_data->size,                        // Data buffer size.
                                    loc_data->data,                                                 // Data buffer.
                                    0,                                                              // Number of events in the list.
                                    NULL,                                                           // Event list.
                                    NULL                                                            // Event.
                                   );

  baseline->check_error (loc_error);
};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// WRITE "int4" overload /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::write (
                   int4*   loc_data,                                                                // Data object.
                   cl_uint loc_layout_index                                                         // Layout index.
                  )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Writing OpenCL buffer:
  loc_error = clEnqueueWriteBuffer (
                                    queue_id,                                                       // OpenCL queue ID.
                                    loc_data->buffer,                                               // Data buffer.
                                    CL_TRUE,                                                        // Blocking write flag.
                                    0,                                                              // Data buffer offset.
                                    sizeof(int4_structure)*loc_data->size,                          // Data buffer size.
                                    loc_data->data,                                                 // Data buffer.
                                    0,                                                              // Number of events in the list.
                                    NULL,                                                           // Event list.
                                    NULL                                                            // Event.
                                   );

  baseline->check_error (loc_error);
};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// WRITE "float1G" overload ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::write (
                   float1G* loc_data,                                                               // Data object.
                   cl_uint  loc_layout_index                                                        // Layout index.
                  )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Acquiring OpenGL buffer:
  acquire (
           loc_data,                                                                                // Data object.
           loc_layout_index                                                                         // OpenGL shader layout index.
          );

  // Writing OpenCL buffer:
  loc_error = clEnqueueWriteBuffer (
                                    queue_id,                                                       // OpenCL queue ID.
                                    loc_data->buffer,                                               // Data buffer.
                                    CL_TRUE,                                                        // Blocking write flag.
                                    0,                                                              // Data buffer offset.
                                    sizeof(GLfloat)*loc_data->size,                                 // Data buffer size.
                                    loc_data->data,                                                 // Data buffer.
                                    0,                                                              // Number of events in the list.
                                    NULL,                                                           // Event list.
                                    NULL                                                            // Event.
                                   );
  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release (
           loc_data,                                                                                // Data object.
           loc_layout_index                                                                         // OpenGL shader layout index.
          );
};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// WRITE "float4G" overload ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::write (
                   float4G* loc_data,                                                               // Data object.
                   cl_uint  loc_layout_index                                                        // Layout index.
                  )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Acquiring OpenGL buffer:
  acquire (
           loc_data,                                                                                // Data object.
           loc_layout_index                                                                         // OpenGL shader layout index.
          );

  // Writing OpenCL buffer:
  loc_error = clEnqueueWriteBuffer (
                                    queue_id,                                                       // OpenCL queue ID.
                                    loc_data->buffer,                                               // Data buffer.
                                    CL_TRUE,                                                        // Blocking write flag.
                                    0,                                                              // Data buffer offset.
                                    sizeof(float4G_structure)*loc_data->size,                       // Data buffer size.
                                    loc_data->data,                                                 // Data buffer.
                                    0,                                                              // Number of events in the list.
                                    NULL,                                                           // Event list.
                                    NULL                                                            // Event.
                                   );
  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release (
           loc_data,                                                                                // Data object.
           loc_layout_index                                                                         // OpenGL shader layout index.
          );
};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// ACQUIRE "float1G" overload /////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::acquire (
                     float1G* loc_data,                                                             // Data object.
                     GLuint   loc_layout_index                                                      // OpenGL shader layout index.
                    )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Setting layout index in vertex shader...
  glFinish ();                                                                                      // Ensuring that all OpenGL routines have completed all operations...

  // Acquiring OpenCL buffer:
  loc_error = clEnqueueAcquireGLObjects (
                                         queue_id,                                                  // Queue.
                                         1,                                                         // # of memory objects.
                                         &loc_data->buffer,                                         // Memory object array.
                                         0,                                                         // # of events in event list.
                                         NULL,                                                      // Event list.
                                         NULL                                                       // Event.
                                        );

  baseline->check_error (loc_error);                                                                // Checking returned error code...
};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// ACQUIRE "float4G" overload /////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::acquire (
                     float4G* loc_data,                                                             // Data object.
                     GLuint   loc_layout_index                                                      // OpenGL shader layout index.
                    )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Setting layout index in vertex shader...
  glFinish ();                                                                                      // Ensuring that all OpenGL routines have completed all operations...

  // Acquiring OpenCL buffer:
  loc_error = clEnqueueAcquireGLObjects (
                                         queue_id,                                                  // Queue.
                                         1,                                                         // # of memory objects.
                                         &loc_data->buffer,                                         // Memory object array.
                                         0,                                                         // # of events in event list.
                                         NULL,                                                      // Event list.
                                         NULL                                                       // Event.
                                        );

  baseline->check_error (loc_error);                                                                // Checking returned error code...
};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// RELEASE "float1G" overlad //////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::release (
                     float1G* loc_data,                                                             // Data object.
                     GLuint   loc_layout_index                                                      // OpenGL shader layout index.
                    )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Releasing openCL buffer:
  loc_error = clEnqueueReleaseGLObjects (
                                         queue_id,                                                  // Queue.
                                         1,                                                         // # of memory objects.
                                         &loc_data->buffer,                                         // Memory object array.
                                         0,                                                         // # of events in event list.
                                         NULL,                                                      // Event list.
                                         NULL                                                       // Event.
                                        );

  clFinish (queue_id);                                                                              // Ensuring that all OpenCL routines have completed all operations...

  //glDisableVertexAttribArray (loc_layout_index);                                // Unbinding data array...

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  // Binding data:
  glBindBuffer (GL_ARRAY_BUFFER, loc_data->vbo);                                                    // Binding VBO...
  glVertexAttribPointer (
                         loc_layout_index,                                                          // VAO index.
                         1,                                                                         // Number of components of data vector.
                         GL_FLOAT,                                                                  // Data type.
                         GL_FALSE,                                                                  // Fixed-point data normalization.
                         0,                                                                         // Data stride.
                         0                                                                          // Data offset.
                        );
  glEnableVertexAttribArray (loc_layout_index);
};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// RELEASE "float4G" overlad //////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void queue::release (
                     float4G* loc_data,                                                             // Data object.
                     GLuint   loc_layout_index                                                      // OpenGL shader layout index.
                    )
{
  cl_int loc_error;                                                                                 // Local error code.

  // Releasing openCL buffer:
  loc_error = clEnqueueReleaseGLObjects (
                                         queue_id,                                                  // Queue.
                                         1,                                                         // # of memory objects.
                                         &loc_data->buffer,                                         // Memory object array.
                                         0,                                                         // # of events in event list.
                                         NULL,                                                      // Event list.
                                         NULL                                                       // Event.
                                        );

  clFinish (queue_id);                                                                              // Ensuring that all OpenCL routines have completed all operations...

  //glDisableVertexAttribArray (loc_layout_index);                                // Unbinding data array...

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  // Binding data:
  glBindBuffer (GL_ARRAY_BUFFER, loc_data->vbo);                                                    // Binding VBO...
  glVertexAttribPointer (
                         loc_layout_index,                                                          // VAO index.
                         4,                                                                         // Number of components of data vector.
                         GL_FLOAT,                                                                  // Data type.
                         GL_FALSE,                                                                  // Fixed-point data normalization.
                         0,                                                                         // Data stride.
                         0                                                                          // Data offset.
                        );
  glEnableVertexAttribArray (loc_layout_index);
};

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DESTRUCTOR //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
queue::~queue()
{
  cl_int loc_error;                                                                                 // Local error code.

  baseline->action ("releasing OpenCL command queue...");                                           // Printing message...

  loc_error = clReleaseCommandQueue (queue_id);                                                     // Releasing OpenCL queue...

  baseline->check_error (loc_error);                                                                // Checking error...

  baseline->done ();                                                                                // Printing message...
}
