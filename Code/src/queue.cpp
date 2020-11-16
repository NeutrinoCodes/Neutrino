/// @file     queue.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definition of an OpenCL "queue" class.

#include "queue.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "queue" class //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
queue::queue()
{
  queue_id   = NULL;                                                                                // Initializing queue id...
  context_id = NULL;                                                                                // Initializing context id...
  device_id  = NULL;                                                                                // Initializing device id...
}

void queue::init
(
 neutrino* loc_baseline
)
{
  cl_int loc_error;                                                                                 // Local error code.

  baseline   = loc_baseline;                                                                        // Getting Neutrino baseline...
  baseline->action ("creating OpenCL command queue...");                                            // Printing message...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  context_id = baseline->context_id;                                                                // Initializing context id...
  device_id  = baseline->device_id;                                                                 // Initializing device id...

  // Creating OpenCL queue:
  queue_id   = clCreateCommandQueue
               (
                context_id,                                                                         // OpenCL context ID.
                device_id,                                                                          // Device ID.
                0,                                                                                  // Queue properties (con be used for enabling profiling).
                &loc_error
               );                                                                                   // Error code.

  baseline->check_error (loc_error);                                                                // Checking error...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  baseline->done ();                                                                                // Printing message...
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// "read" functions ///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void queue::read
(
 nu_int* loc_data,                                                                                  // nu_int object.
 GLuint  loc_layout_index                                                                           // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(GL_INT)*loc_data->size,                                                       // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::read
(
 nu_int2* loc_data,                                                                                 // nu_int2 object.
 GLuint   loc_layout_index                                                                          // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(nu_int2_structure)*loc_data->size,                                            // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::read
(
 nu_int3* loc_data,                                                                                 // nu_int3 object.
 GLuint   loc_layout_index                                                                          // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(nu_int3_structure)*loc_data->size,                                            // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::read
(
 nu_int4* loc_data,                                                                                 // nu_int4 object.
 GLuint   loc_layout_index                                                                          // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(nu_int4_structure)*loc_data->size,                                            // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::read
(
 nu_float* loc_data,                                                                                // nu_floatloat object.
 GLuint    loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(GL_FLOAT)*loc_data->data.size (),                                             // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::read
(
 nu_float2* loc_data,                                                                               // nu_float2 object.
 GLuint     loc_layout_index                                                                        // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(nu_float2_structure)*loc_data->size,                                          // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::read
(
 nu_float3* loc_data,                                                                               // nu_float3 object.
 GLuint     loc_layout_index                                                                        // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(nu_float3_structure)*loc_data->size,                                          // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::read
(
 nu_float4* loc_data,                                                                               // nu_float4 object.
 GLuint     loc_layout_index                                                                        // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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

  // Reading OpenCL buffer:
  loc_error = clEnqueueReadBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(nu_float4_structure)*loc_data->size,                                          // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// write "functions" ////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void queue::write
(
 nu_int* loc_data,                                                                                  // nu_int object.
 GLuint  loc_layout_index                                                                           // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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
  loc_error = clEnqueueWriteBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(GL_INT)*loc_data->size,                                                       // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::write
(
 nu_int2* loc_data,                                                                                 // nu_int2 object.
 GLuint   loc_layout_index                                                                          // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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
  loc_error = clEnqueueWriteBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(nu_int2_structure)*loc_data->size,                                            // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::write
(
 nu_int3* loc_data,                                                                                 // nu_int3 object.
 GLuint   loc_layout_index                                                                          // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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
  loc_error = clEnqueueWriteBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(nu_int3_structure)*loc_data->size,                                            // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::write
(
 nu_int4* loc_data,                                                                                 // nu_int4 object.
 GLuint   loc_layout_index                                                                          // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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
  loc_error = clEnqueueWriteBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(nu_int4_structure)*loc_data->size,                                            // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::write
(
 nu_float* loc_data,                                                                                // nu_float object.
 GLuint    loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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
  loc_error = clEnqueueWriteBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(GL_FLOAT)*loc_data->data.size (),                                             // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::write
(
 nu_float2* loc_data,                                                                               // nu_float2 object.
 GLuint     loc_layout_index                                                                        // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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
  loc_error = clEnqueueWriteBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(nu_float2_structure)*loc_data->size,                                          // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::write
(
 nu_float3* loc_data,                                                                               // nu_float3 object.
 GLuint     loc_layout_index                                                                        // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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
  loc_error = clEnqueueWriteBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(nu_float3_structure)*loc_data->size,                                          // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::write
(
 nu_float4* loc_data,                                                                               // nu_float4 object.
 GLuint     loc_layout_index                                                                        // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

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
  loc_error = clEnqueueWriteBuffer
              (
               queue_id,                                                                            // OpenCL queue ID.
               loc_data->buffer,                                                                    // Data buffer.
               CL_TRUE,                                                                             // Blocking write flag.
               0,                                                                                   // Data buffer offset.
               sizeof(nu_float4_structure)*loc_data->size,                                          // Data buffer size.
               loc_data->data,                                                                      // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);

  // Releasing OpenGL buffer:
  release
  (
   loc_data,                                                                                        // Data object.
   loc_layout_index                                                                                 // OpenGL shader layout index.
  );

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu_int* loc_data,                                                                                  // Data object.
 GLuint  loc_layout_index                                                                           // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Setting layout index in vertex shader...
  glDisableVertexAttribArray (loc_layout_index);                                                    // Unbinding data array...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Acquiring OpenCL buffer:
  loc_error = clEnqueueAcquireGLObjects
              (
               queue_id,                                                                            // Queue.
               1,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu_int2* loc_data,                                                                                 // Data object.
 GLuint   loc_layout_index                                                                          // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Setting layout index in vertex shader...
  glDisableVertexAttribArray (loc_layout_index);                                                    // Unbinding data array...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Acquiring OpenCL buffer:
  loc_error = clEnqueueAcquireGLObjects
              (
               queue_id,                                                                            // Queue.
               2,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu_int3* loc_data,                                                                                 // Data object.
 GLuint   loc_layout_index                                                                          // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Setting layout index in vertex shader...
  glDisableVertexAttribArray (loc_layout_index);                                                    // Unbinding data array...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Acquiring OpenCL buffer:
  loc_error = clEnqueueAcquireGLObjects
              (
               queue_id,                                                                            // Queue.
               3,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu_int4* loc_data,                                                                                 // Data object.
 GLuint   loc_layout_index                                                                          // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Setting layout index in vertex shader...
  glDisableVertexAttribArray (loc_layout_index);                                                    // Unbinding data array...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Acquiring OpenCL buffer:
  loc_error = clEnqueueAcquireGLObjects
              (
               queue_id,                                                                            // Queue.
               4,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu_float* loc_data,                                                                                // Data object.
 GLuint    loc_layout_index                                                                         // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Setting layout index in vertex shader...
  glDisableVertexAttribArray (loc_layout_index);                                                    // Unbinding data array...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Acquiring OpenCL buffer:
  loc_error = clEnqueueAcquireGLObjects
              (
               queue_id,                                                                            // Queue.
               1,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu_float2* loc_data,                                                                               // Data object.
 GLuint     loc_layout_index                                                                        // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Setting layout index in vertex shader...
  glDisableVertexAttribArray (loc_layout_index);                                                    // Unbinding data array...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Acquiring OpenCL buffer:
  loc_error = clEnqueueAcquireGLObjects
              (
               queue_id,                                                                            // Queue.
               2,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu_float3* loc_data,                                                                               // Data object.
 GLuint     loc_layout_index                                                                        // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Setting layout index in vertex shader...
  glDisableVertexAttribArray (loc_layout_index);                                                    // Unbinding data array...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Acquiring OpenCL buffer:
  loc_error = clEnqueueAcquireGLObjects
              (
               queue_id,                                                                            // Queue.
               3,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu_float4* loc_data,                                                                               // Data object.
 GLuint     loc_layout_index                                                                        // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Setting layout index in vertex shader...
  glDisableVertexAttribArray (loc_layout_index);                                                    // Unbinding data array...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Acquiring OpenCL buffer:
  loc_error = clEnqueueAcquireGLObjects
              (
               queue_id,                                                                            // Queue.
               1,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::release
(
 nu_int* loc_data,                                                                                  // Data object.
 GLuint  loc_layout_index                                                                           // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Releasing openCL buffer:
  loc_error = clEnqueueReleaseGLObjects
              (
               queue_id,                                                                            // Queue.
               1,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Ensuring that all OpenCL has completed all operations...

  glEnableVertexAttribArray (loc_layout_index);

  // Binding data:
  glBindBuffer (GL_SHADER_STORAGE_BUFFER, loc_data->ssbo);                                          // Binding SSBO...
  glVertexAttribPointer
  (
   loc_layout_index,                                                                                // VAO index.
   1,                                                                                               // Number of components of data vector.
   GL_INT,                                                                                          // Data type.
   GL_FALSE,                                                                                        // Fixed-point data normalization.
   0,                                                                                               // Data stride.
   0                                                                                                // Data offset.
  );

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
};

void queue::release
(
 nu_int2* loc_data,                                                                                 // Data object.
 GLuint   loc_layout_index                                                                          // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Releasing openCL buffer:
  loc_error = clEnqueueReleaseGLObjects
              (
               queue_id,                                                                            // Queue.
               1,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Ensuring that all OpenCL has completed all operations...

  glEnableVertexAttribArray (loc_layout_index);

  // Binding data:
  glBindBuffer (GL_SHADER_STORAGE_BUFFER, loc_data->ssbo);                                          // Binding SSBO...
  glVertexAttribPointer
  (
   loc_layout_index,                                                                                // VAO index.
   2,                                                                                               // Number of components of data vector.
   GL_INT,                                                                                          // Data type.
   GL_FALSE,                                                                                        // Fixed-point data normalization.
   0,                                                                                               // Data stride.
   0                                                                                                // Data offset.
  );

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
};

void queue::release
(
 nu_int3* loc_data,                                                                                 // Data object.
 GLuint   loc_layout_index                                                                          // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Releasing openCL buffer:
  loc_error = clEnqueueReleaseGLObjects
              (
               queue_id,                                                                            // Queue.
               1,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Ensuring that all OpenCL has completed all operations...

  glEnableVertexAttribArray (loc_layout_index);

  // Binding data:
  glBindBuffer (GL_SHADER_STORAGE_BUFFER, loc_data->ssbo);                                          // Binding SSBO...
  glVertexAttribPointer
  (
   loc_layout_index,                                                                                // VAO index.
   3,                                                                                               // Number of components of data vector.
   GL_INT,                                                                                          // Data type.
   GL_FALSE,                                                                                        // Fixed-point data normalization.
   0,                                                                                               // Data stride.
   0                                                                                                // Data offset.
  );

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
};

void queue::release
(
 nu_int4* loc_data,                                                                                 // Data object.
 GLuint   loc_layout_index                                                                          // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Releasing openCL buffer:
  loc_error = clEnqueueReleaseGLObjects
              (
               queue_id,                                                                            // Queue.
               1,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Ensuring that all OpenCL has completed all operations...

  glEnableVertexAttribArray (loc_layout_index);

  // Binding data:
  glBindBuffer (GL_SHADER_STORAGE_BUFFER, loc_data->ssbo);                                          // Binding SSBO...
  glVertexAttribPointer
  (
   loc_layout_index,                                                                                // VAO index.
   4,                                                                                               // Number of components of data vector.
   GL_INT,                                                                                          // Data type.
   GL_FALSE,                                                                                        // Fixed-point data normalization.
   0,                                                                                               // Data stride.
   0                                                                                                // Data offset.
  );

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
};

void queue::release
(
 nu_float* loc_data,                                                                                // Data object.
 GLuint    loc_layout_index                                                                         // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Releasing openCL buffer:
  loc_error = clEnqueueReleaseGLObjects
              (
               queue_id,                                                                            // Queue.
               1,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Ensuring that all OpenCL has completed all operations...

  glEnableVertexAttribArray (loc_layout_index);

  // Binding data:
  glBindBuffer (GL_SHADER_STORAGE_BUFFER, loc_data->ssbo);                                          // Binding SSBO...
  glVertexAttribPointer
  (
   loc_layout_index,                                                                                // VAO index.
   1,                                                                                               // Number of components of data vector.
   GL_FLOAT,                                                                                        // Data type.
   GL_FALSE,                                                                                        // Fixed-point data normalization.
   0,                                                                                               // Data stride.
   0                                                                                                // Data offset.
  );

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
};

void queue::release
(
 nu_float2* loc_data,                                                                               // Data object.
 GLuint     loc_layout_index                                                                        // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Releasing openCL buffer:
  loc_error = clEnqueueReleaseGLObjects
              (
               queue_id,                                                                            // Queue.
               1,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Ensuring that all OpenCL has completed all operations...

  glEnableVertexAttribArray (loc_layout_index);

  // Binding data:
  glBindBuffer (GL_SHADER_STORAGE_BUFFER, loc_data->ssbo);                                          // Binding SSBO...
  glVertexAttribPointer
  (
   loc_layout_index,                                                                                // VAO index.
   2,                                                                                               // Number of components of data vector.
   GL_FLOAT,                                                                                        // Data type.
   GL_FALSE,                                                                                        // Fixed-point data normalization.
   0,                                                                                               // Data stride.
   0                                                                                                // Data offset.
  );

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
};

void queue::release
(
 nu_float3* loc_data,                                                                               // Data object.
 GLuint     loc_layout_index                                                                        // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Releasing openCL buffer:
  loc_error = clEnqueueReleaseGLObjects
              (
               queue_id,                                                                            // Queue.
               1,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Ensuring that all OpenCL has completed all operations...

  glEnableVertexAttribArray (loc_layout_index);

  // Binding data:
  glBindBuffer (GL_SHADER_STORAGE_BUFFER, loc_data->ssbo);                                          // Binding SSBO...
  glVertexAttribPointer
  (
   loc_layout_index,                                                                                // VAO index.
   3,                                                                                               // Number of components of data vector.
   GL_FLOAT,                                                                                        // Data type.
   GL_FALSE,                                                                                        // Fixed-point data normalization.
   0,                                                                                               // Data stride.
   0                                                                                                // Data offset.
  );

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
};

void queue::release
(
 nu_float4* loc_data,                                                                               // Data object.
 GLuint     loc_layout_index                                                                        // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    baseline->error ("Layout index mismatch!");                                                     // Printing message...
    exit (EXIT_FAILURE);                                                                            // Exiting...
  }

  // Releasing openCL buffer:
  loc_error = clEnqueueReleaseGLObjects
              (
               queue_id,                                                                            // Queue.
               1,                                                                                   // Number of memory objects.
               &loc_data->buffer,                                                                   // Memory object array.
               0,                                                                                   // Number of events in event list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  baseline->check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Ensuring that all OpenCL has completed all operations...

  glEnableVertexAttribArray (loc_layout_index);

  // Binding data:
  glBindBuffer (GL_SHADER_STORAGE_BUFFER, loc_data->ssbo);                                          // Binding SSBO...
  glVertexAttribPointer
  (
   loc_layout_index,                                                                                // VAO index.
   4,                                                                                               // Number of components of data vector.
   GL_FLOAT,                                                                                        // Data type.
   GL_FALSE,                                                                                        // Fixed-point data normalization.
   0,                                                                                               // Data stride.
   0                                                                                                // Data offset.
  );

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
};

queue::~queue()
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  baseline->action ("releasing OpenCL command queue...");                                           // Printing message...

  loc_error = clReleaseCommandQueue (queue_id);                                                     // Releasing OpenCL queue...

  baseline->check_error (loc_error);                                                                // Checking error...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  baseline->done ();                                                                                // Printing message...
}
