#include "node.hpp"

node::node()
{

}

/// # OpenCL error check function
/// ### Description:
/// Checks for an OpenCL error code and print it to stdout.
void node::check_error (
                        cl_int loc_error                                        // Error code.
                       )
{
  if(loc_error != CL_SUCCESS)                                                   // Checking local error code...
  {
    baseline -> error (get_error (loc_error));                                  // Printing error message...
    exit (EXIT_FAILURE);                                                        // Exiting...
  }
}

/// # Node init function
/// ### Description:
/// Initializes node object.
void node::init (
                 neutrino*  loc_baseline,                                       // Neutrino baseline.
                 GLsizeiptr loc_data_size                                       // Data array size.
                )
{
  cl_int       loc_error;                                                       // Error code.

  #ifdef USE_GRAPHICS
    GLsizeiptr i;                                                               // Index.
  #else
    size_t     i;                                                               // Index.
  #endif

  baseline       = loc_baseline;                                                // Getting Neutrino baseline...
  position       = new size_t[baseline -> k_num];                               // Initializing kernel argument position array...

  baseline -> action ("initializing \"node\" object...");                       // Printing message...

  data_size      = loc_data_size;                                               // Array size.
  buffer         = NULL;                                                        // OpenCL data buffer.
  opencl_context = baseline -> context_id;                                      // Getting OpenCL context...
  node_data      = new node[data_size];                                         // Node data array.

  for(i = 0; i < data_size; i++)                                                // Filling data arrays with default values...
  {
    init_float4 (node_data . position);                                         // Initializing "position"...
    init_float4 (node_data . velocity);                                         // Initializing "velocity"...
    init_float4 (node_data . acceleration);                                     // Initializing "acceleration"...
    init_float4 (node_data . position_buffer);                                  // Initializing "position_buffer"...
    init_float4 (node_data . velocity_buffer);                                  // Initializing "velocity_buffer"...
    init_float4 (node_data . acceleration_buffer);                              // Initializing "acceleration_buffer"...
    init_color4 (node_data . node);                                             // Initializing node color...
    node_data . mass = 0.0;                                                     // Initializing node mass...
  }

  #ifdef USE_GRAPHICS
    node_vao = 0;                                                               // Node data VAO.
    node_vbo = 0;                                                               // Node data VBO.

    // Generating VAO...
    glGenVertexArrays (
                       1,                                                       // # of VAOs to generate.
                       &loc_vao                                                 // VAOs array.
                      );
    glBindVertexArray (loc_vao);                                                // Binding node VAO...

    // Generating VBO:
    glGenBuffers (
                  1,                                                            // # of VBOs to generate.
                  &loc_vbo                                                      // VBOs array.
                 );

    // Binding VBO:
    glBindBuffer (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  loc_vbo                                                       // VBO to bind.
                 );

    // Creating and initializing a buffer object's data store:
    glBufferData (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  (GLsizeiptr)(sizeof(loc_data)*(loc_data_size)),               // VBO size.
                  loc_data,                                                     // VBO data.
                  GL_DYNAMIC_DRAW                                               // VBO usage.
                 );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray (
                               NODE;                                            // VAO index.
                              );

    // Binding VBO:
    glBindBuffer (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  loc_vbo                                                       // VBO to bind.
                 );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer (
                           loc_data_type,                                       // VAO index.
                           sizeof(loc_data),                                    // VAO's # of components.
                           GL_FLOAT,                                            // Data type.
                           GL_FALSE,                                            // Not using normalized numbers.
                           0,                                                   // Data stride.
                           0                                                    // Data offset.
                          );

    // Creating OpenCL buffer from OpenGL buffer:
    loc_buffer = clCreateFromGLBuffer (
                                       loc_opencl_context,                      // OpenCL context.
                                       CL_MEM_READ_WRITE,                       // Memory flags.
                                       loc_vbo,                                 // VBO.
                                       &loc_error                               // Returned error.
                                      );
  #else
    // Creating OpenCL memory buffer:
    loc_buffer = clCreateBuffer (
                                 loc_opencl_context,                            // OpenCL context.
                                 CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,      // Memory flags.
                                 sizeof(loc_data)*loc_data_size,                // Data buffer size.
                                 loc_data,                                      // Data buffer.
                                 &loc_error                                     // Error code.
                                );
  #endif

  check_error (loc_error);                                                      // Checking returned error code...

  baseline -> done ();                                                          // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// HOST "SET" FUNCTIONS:  ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Kernel set function
/// ### Description:
/// Sets a kernel argument at a specified index position.
void node::set_arg (
                    kernel* loc_kernel,                                         // OpenCL kernel.
                    cl_uint loc_kernel_arg                                      // OpenCL kernel argument #.
                   )
{
  cl_int loc_error;                                                             // Error code.
  size_t kernel_index;
  size_t i;

  baseline -> action ("setting \"node\" kernel argument...");                   // Printing message...

  position[kernel_index] = loc_kernel_arg;                                      // Setting kernel argument position in current kernel...

  // Setting OpenCL buffer as kernel argument:
  loc_error              = clSetKernelArg (
                                           loc_kernel -> kernel_id,             // Kernel.
                                           NODE,                                // Kernel argument index.
                                           sizeof(cl_mem),                      // Kernel argument size.
                                           &buffer                              // Kernel argument value.
                                          );

  check_error (loc_error);                                                      // Checking returned error code...

  baseline -> done ();                                                          // Printing message...
}
/// # Node position set function
/// ### Description:
/// Sets the position in node structure.
void node::set_position (
                         GLsizeiptr loc_index,                                  // Data index.
                         GLfloat    loc_value[4]                                // Data value.
                        )
{
  node_data . position . x[loc_index] = loc_value[0];                           // Setting "x" position...
  node_data . position . y[loc_index] = loc_value[1];                           // Setting "y" position...
  node_data . position . z[loc_index] = loc_value[2];                           // Setting "z" position...
  node_data . position . w[loc_index] = loc_value[3];                           // Setting "w" position...
};

/// # Node velocity set function
/// ### Description:
/// Sets the velocity in node structure.
void node::set_velocity (
                         GLsizeiptr loc_index,                                  // Data index.
                         GLfloat    loc_value[4]                                // Data value.
                        )
{
  node_data . velocity . x[loc_index] = loc_value[0];                           // Setting "x" velocity...
  node_data . velocity . y[loc_index] = loc_value[1];                           // Setting "y" velocity...
  node_data . velocity . z[loc_index] = loc_value[2];                           // Setting "z" velocity...
  node_data . velocity . w[loc_index] = loc_value[3];                           // Setting "w" velocity...
};

/// # Node acceleration set function
/// ### Description:
/// Sets the acceleration in node structure.
void node::set_acceleration (
                             GLsizeiptr loc_index,                              // Data index.
                             GLfloat    loc_value[4]                            // Data value.
                            )
{
  node_data . acceleration . x[loc_index] = loc_value[0];                       // Setting "x" acceleration...
  node_data . acceleration . y[loc_index] = loc_value[1];                       // Setting "y" acceleration...
  node_data . acceleration . z[loc_index] = loc_value[2];                       // Setting "z" acceleration...
  node_data . acceleration . w[loc_index] = loc_value[3];                       // Setting "w" acceleration...
};

/// # Node color set function
/// ### Description:
/// Sets the color in node structure.
void node::set_color (
                      GLsizeiptr loc_index,                                     // Data index.
                      GLfloat    loc_value[4]                                   // Data value.
                     )
{
  node_data . color . r[loc_index] = loc_value[0];                              // Setting "r" color...
  node_data . color . g[loc_index] = loc_value[1];                              // Setting "g" color...
  node_data . color . b[loc_index] = loc_value[2];                              // Setting "b" color...
  node_data . color . a[loc_index] = loc_value[3];                              // Setting "a" color...
};

/// # Node mass set function
/// ### Description:
/// Sets the mass in node structure.
void node::set_mass (
                     GLsizeiptr loc_index,                                      // Data index.
                     GLfloat    loc_value                                       // Data value.
                    )
{
  node_data . mass . x[loc_index] = loc_value;                                  // Setting "x" mass...
  node_data . mass . y[loc_index] = loc_value;                                  // Setting "y" mass...
  node_data . mass . z[loc_index] = loc_value;                                  // Setting "z" mass...
  node_data . mass . w[loc_index] = 1.0;                                        // Setting "w" mass...
};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// HOST "GET" FUNCTIONS:  ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Kernel get function:
/// ### Description:
/// Gets the index position of a kernel argument.
size_t point4::get_arg (
                        kernel* loc_kernel                                      // OpenCL kernel.
                       )
{
  cl_int loc_error;                                                             // Error code.
  size_t kernel_index;
  size_t i;

  // Getting kernel index:
  for(i = 0; i < baseline -> k_num; i++)                                        // Scanning OpenCL kernel id array...
  {
    if(baseline -> kernel_id[i] == loc_kernel -> kernel_id)                     // Finding current kernel id...
    {
      kernel_index = i;                                                         // Setting kernel index...
    }
  }

  return(position[kernel_index]);                                               // Returning index of current argument in current kernel...
}

/// # "x" get function
/// ### Description:
/// Gets the "x" point data value in point data array.
GLfloat point4::get_x (
                       GLsizeiptr loc_index                                     // Data index.
                      )
{
  GLfloat loc_value;                                                            // Value.

  loc_value = data[4*loc_index + 0];                                            // Getting data value...

  return(loc_value);                                                            // Returning data value...
}

/// # "y" get function
/// ### Description:
/// Gets the "y" point data value in point data array.
GLfloat point4::get_y (
                       GLsizeiptr loc_index                                     // Data index.
                      )
{
  GLfloat loc_value;                                                            // Value.

  loc_value = data[4*loc_index + 1];                                            // Getting data value...

  return(loc_value);                                                            // Returning data value...
}

/// # "z" get function
/// ### Description:
/// Gets the "z" point data value in point data array.
GLfloat point4::get_z (
                       GLsizeiptr loc_index                                     // Data index.
                      )
{
  GLfloat loc_value;                                                            // Value.

  loc_value = data[4*loc_index + 2];                                            // Getting data value...

  return(loc_value);                                                            // Returning data value...
}

/// # "w" get function
/// ### Description:
/// Gets the "w" point data value in point data array.
GLfloat point4::get_w (
                       GLsizeiptr loc_index                                     // Data index.
                      )
{
  GLfloat loc_value;                                                            // Value.

  loc_value = data[4*loc_index + 3];                                            // Getting data value...

  return(loc_value);                                                            // Returning data value...
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CLIENT FUNCTIONS:  /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # OpenCL push function:
/// ### Description:
/// Writes to an OpenCL client.
void cell::load (
                 queue*  loc_queue,                                             // Queue.
                 cl_uint loc_kernel_arg                                         // Kernel argument index.
                )
{
  cl_int loc_error;                                                             // Local error code.

  #ifdef USE_GRAPHICS
    glFinish ();                                                                // Ensuring that all OpenGL routines have completed all operations...

    // Passing buffer to OpenCL kernel:
    loc_error = clEnqueueAcquireGLObjects (
                                           loc_queue -> queue_id,               // Queue.
                                           1,                                   // # of memory objects.
                                           &buffer,                             // Memory object array.
                                           0,                                   // # of events in event list.
                                           NULL,                                // Event list.
                                           NULL                                 // Event.
                                          );

    check_error (loc_error);                                                    // Checking returned error code...
  #endif

  loc_error = clEnqueueWriteBuffer (
                                    loc_queue -> queue_id,                      // OpenCL queue ID.
                                    buffer,                                     // Data buffer.
                                    CL_TRUE,                                    // Blocking write flag.
                                    0,                                          // Data buffer offset.
                                    (size_t)(4*sizeof(GLfloat)*size),           // Data buffer size.
                                    data,                                       // Data buffer.
                                    0,                                          // Number of events in the list.
                                    NULL,                                       // Event list.
                                    NULL                                        // Event.
                                   );

  check_error (loc_error);

  #ifdef USE_GRAPHICS
    // Releasing buffer from OpenCL kernel:
    loc_error = clEnqueueReleaseGLObjects (
                                           loc_queue -> queue_id,               // Queue.
                                           1,                                   // # of memory objects.
                                           &buffer,                             // Memory object array.
                                           0,                                   // # of events in event list.
                                           NULL,                                // Event list.
                                           NULL                                 // Event.
                                          );

    clFinish (loc_queue -> queue_id);                                           // Ensuring that all OpenCL routines have completed all operations...

    check_error (loc_error);                                                    // Checking returned error code...
  #endif
}

/// # OpenCL pull function:
/// ### Description:
/// Reads from an OpenCL client.
void point4::pull (
                   queue*  loc_queue,                                           // Queue.
                   cl_uint loc_kernel_arg                                       // Kernel argument index.
                  )
{
  cl_int loc_error;                                                             // Local error code.

  loc_error = clEnqueueReadBuffer (
                                   loc_queue -> queue_id,                       // OpenCL queue ID.
                                   buffer,                                      // Data buffer.
                                   CL_TRUE,                                     // Blocking write flag.
                                   0,                                           // Data buffer offset.
                                   (size_t)(4*sizeof(GLfloat)*size),            // Data buffer size.
                                   data,                                        // Data buffer.
                                   0,                                           // Number of events in the list.
                                   NULL,                                        // Event list.
                                   NULL                                         // Event.
                                  );

  check_error (loc_error);
}

point4::~point4()
{
  cl_int loc_error;                                                             // Local error.

  baseline -> action ("releasing \"point4\" object...");                        // Printing message...

  if(buffer != NULL)                                                            // Checking buffer...
  {
    loc_error = clReleaseMemObject (buffer);                                    // Releasing OpenCL buffer object...

    check_error (loc_error);                                                    // Checking returned error code...
  }

  if(baseline -> use_cl_gl_interop)
  {
    glDeleteBuffers (1, &vbo);                                                  // Releasing OpenGL VBO...
  }

  delete[] data;                                                                // Deleting array for unfolded data...
  delete[] position;                                                            // Deleting kernel argument position array...

  baseline -> done ();                                                          // Printing message...
}
