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
  cl_int loc_error;                                                                                 // Local error code.

  neutrino::action ("creating OpenCL command queue...");                                            // Printing message...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  queue::context_id = neutrino::context_id;                                                         // Initializing context id...
  queue::device_id  = neutrino::device_id;                                                          // Initializing device id...

  // Creating OpenCL queue:
  queue_id          = clCreateCommandQueue
                      (
                       queue::context_id,                                                           // OpenCL context ID.
                       queue::device_id,                                                            // Device ID.
                       0,                                                                           // Queue properties (con be used for enabling profiling).
                       &loc_error
                      );                                                                            // Error code.

  neutrino::check_error (loc_error);                                                                // Checking error...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  neutrino::done ();                                                                                // Printing message...
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// "read" functions ///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void queue::read
(
 nu::int1* loc_data,                                                                                // nu::int1 object.
 GLuint    loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(GL_INT)*loc_data->data.size (),                                               // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::int2* loc_data,                                                                                // nu::int2 object.
 GLuint    loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(nu_int2_structure)*loc_data->data.size (),                                    // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::int3* loc_data,                                                                                // nu::int3 object.
 GLuint    loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(nu_int3_structure)*loc_data->data.size (),                                    // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::int4* loc_data,                                                                                // nu::int4 object.
 GLuint    loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(nu_int4_structure)*loc_data->data.size (),                                    // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::float1* loc_data,                                                                              // nu_floatloat object.
 GLuint      loc_layout_index                                                                       // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);

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
 nu::float2* loc_data,                                                                              // nu::float2 object.
 GLuint      loc_layout_index                                                                       // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(nu_float2_structure)*loc_data->data.size (),                                  // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::float3* loc_data,                                                                              // nu::float3 object.
 GLuint      loc_layout_index                                                                       // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(nu_float3_structure)*loc_data->data.size (),                                  // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::float4* loc_data,                                                                              // nu::float4 object.
 GLuint      loc_layout_index                                                                       // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(nu_float4_structure)*loc_data->data.size (),                                  // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::int1* loc_data,                                                                                // nu::int1 object.
 GLuint    loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(GL_INT)*loc_data->data.size (),                                               // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::int2* loc_data,                                                                                // nu::int2 object.
 GLuint    loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(nu_int2_structure)*loc_data->data.size (),                                    // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::int3* loc_data,                                                                                // nu::int3 object.
 GLuint    loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(nu_int3_structure)*loc_data->data.size (),                                    // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::int4* loc_data,                                                                                // nu::int4 object.
 GLuint    loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(nu_int4_structure)*loc_data->data.size (),                                    // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::float1* loc_data,                                                                              // nu::float1 object.
 GLuint      loc_layout_index                                                                       // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);

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
 nu::float2* loc_data,                                                                              // nu::float2 object.
 GLuint      loc_layout_index                                                                       // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(nu_float2_structure)*loc_data->data.size (),                                  // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::float3* loc_data,                                                                              // nu::float3 object.
 GLuint      loc_layout_index                                                                       // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(nu_float3_structure)*loc_data->data.size (),                                  // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::float4* loc_data,                                                                              // nu::float4 object.
 GLuint      loc_layout_index                                                                       // Layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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
               sizeof(nu_float4_structure)*loc_data->data.size (),                                  // Data buffer size.
               loc_data->data.data (),                                                              // Data buffer.
               0,                                                                                   // Number of events in the list.
               NULL,                                                                                // Event list.
               NULL                                                                                 // Event.
              );

  neutrino::check_error (loc_error);

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
 nu::int1* loc_data,                                                                                // Data object.
 GLuint    loc_layout_index                                                                         // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu::int2* loc_data,                                                                                // Data object.
 GLuint    loc_layout_index                                                                         // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu::int3* loc_data,                                                                                // Data object.
 GLuint    loc_layout_index                                                                         // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu::int4* loc_data,                                                                                // Data object.
 GLuint    loc_layout_index                                                                         // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu::float1* loc_data,                                                                              // Data object.
 GLuint      loc_layout_index                                                                       // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu::float2* loc_data,                                                                              // Data object.
 GLuint      loc_layout_index                                                                       // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu::float3* loc_data,                                                                              // Data object.
 GLuint      loc_layout_index                                                                       // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::acquire
(
 nu::float4* loc_data,                                                                              // Data object.
 GLuint      loc_layout_index                                                                       // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...
};

void queue::release
(
 nu::int1* loc_data,                                                                                // Data object.
 GLuint    loc_layout_index                                                                         // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

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
 nu::int2* loc_data,                                                                                // Data object.
 GLuint    loc_layout_index                                                                         // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

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
 nu::int3* loc_data,                                                                                // Data object.
 GLuint    loc_layout_index                                                                         // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

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
 nu::int4* loc_data,                                                                                // Data object.
 GLuint    loc_layout_index                                                                         // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

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
 nu::float1* loc_data,                                                                              // Data object.
 GLuint      loc_layout_index                                                                       // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

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
 nu::float2* loc_data,                                                                              // Data object.
 GLuint      loc_layout_index                                                                       // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

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
 nu::float3* loc_data,                                                                              // Data object.
 GLuint      loc_layout_index                                                                       // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

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
 nu::float4* loc_data,                                                                              // Data object.
 GLuint      loc_layout_index                                                                       // OpenGL shader layout index.
)
{
  cl_int loc_error;                                                                                 // Local error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  // Checking layout index:
  if(loc_layout_index != loc_data->layout)
  {
    neutrino::error ("Layout index mismatch!");                                                     // Printing message...
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

  neutrino::check_error (loc_error);                                                                // Checking returned error code...

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

  neutrino::action ("releasing OpenCL command queue...");                                           // Printing message...

  loc_error = clReleaseCommandQueue (queue_id);                                                     // Releasing OpenCL queue...

  neutrino::check_error (loc_error);                                                                // Checking error...

  clFinish (queue_id);                                                                              // Waiting for OpenCL to finish...

  neutrino::done ();                                                                                // Printing message...
}
