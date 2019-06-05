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
                 GLsizeiptr loc_node_size                                       // Data array size.
                )
{
  cl_int       loc_error;                                                       // Error code.

  #ifdef USE_GRAPHICS
    GLsizeiptr i;                                                               // Index.
  #else
    size_t     i;                                                               // Index.
  #endif

  baseline       = loc_baseline;                                                // Getting Neutrino baseline...

  baseline -> action ("initializing \"node\" object...");                       // Printing message...

  node_size      = loc_node_size;                                               // Array size.
  node_buffer    = NULL;                                                        // OpenCL data buffer.
  opencl_context = baseline -> context_id;                                      // Getting OpenCL context...
  node_data      = new node[node_size];                                         // Node data array.

  for(i = 0; i < node_size; i++)                                                // Filling data arrays with default values...
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
                       &node_vao                                                // VAOs array.
                      );
    glBindVertexArray (node_vao);                                               // Binding node VAO...

    // Generating VBO:
    glGenBuffers (
                  1,                                                            // # of VBOs to generate.
                  &node_vbo                                                     // VBOs array.
                 );

    // Binding VBO:
    glBindBuffer (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  node_vbo                                                      // VBO to bind.
                 );

    // Creating and initializing a buffer object's data store:
    glBufferData (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  (GLsizeiptr)(sizeof(node_data)*(node_size)),                  // VBO size.
                  node_data,                                                    // VBO data.
                  GL_DYNAMIC_DRAW                                               // VBO usage.
                 );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray (
                               NODE;                                            // VAO index.
                              );

    // Binding VBO:
    glBindBuffer (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  node_vbo                                                      // VBO to bind.
                 );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer (
                           NODE,                                                // VAO index.
                           sizeof(node_data),                                   // VAO's # of components.
                           GL_FLOAT,                                            // Data type.
                           GL_FALSE,                                            // Not using normalized numbers.
                           0,                                                   // Data stride.
                           0                                                    // Data offset.
                          );

    // Creating OpenCL buffer from OpenGL buffer:
    node_buffer = clCreateFromGLBuffer (
                                        opencl_context,                         // OpenCL context.
                                        CL_MEM_READ_WRITE,                      // Memory flags.
                                        node_vbo,                               // VBO.
                                        &loc_error                              // Returned error.
                                       );
  #else
    // Creating OpenCL memory buffer:
    node_buffer = clCreateBuffer (
                                  opencl_context,                               // OpenCL context.
                                  CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,     // Memory flags.
                                  sizeof(node_data)*node_size,                  // Data buffer size.
                                  node_data,                                    // Data buffer.
                                  &loc_error                                    // Error code.
                                 );
  #endif

  check_error (loc_error);                                                      // Checking returned error code...

  baseline -> done ();                                                          // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// HOST "SET" FUNCTIONS:  ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
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
/// # Node position get function
/// ### Description:
/// Gets the position from node structure.
float4 node::get_position (
                           GLsizeiptr loc_index,                                // Data index.
                          )
{
  float4 data;

  data . x = node_data . position . x[loc_index];                               // Getting "x" position...
  data . y = node_data . position . y[loc_index];                               // Getting "y" position...
  data . z = node_data . position . z[loc_index];                               // Getting "z" position...
  data . w = node_data . position . w[loc_index];                               // Getting "w" position...

  return data;
};

/// # Node velocity get function
/// ### Description:
/// Gets the velocity from node structure.
float4 node::get_velocity (
                           GLsizeiptr loc_index,                                // Data index.
                          )
{
  float4 data;

  data . x = node_data . velocity . x[loc_index];                               // Getting "x" velocity...
  data . y = node_data . velocity . y[loc_index];                               // Getting "y" velocity...
  data . z = node_data . velocity . z[loc_index];                               // Getting "z" velocity...
  data . w = node_data . velocity . w[loc_index];                               // Getting "w" velocity...

  return data;
};

/// # Node acceleration get function
/// ### Description:
/// Gets the acceleration from node structure.
float4 node::get_acceleration (
                               GLsizeiptr loc_index,                            // Data index.
                              )
{
  float4 data;

  data . x = node_data . acceleration . x[loc_index];                           // Getting "x" acceleration...
  data . y = node_data . acceleration . y[loc_index];                           // Getting "y" acceleration...
  data . z = node_data . acceleration . z[loc_index];                           // Getting "z" acceleration...
  data . w = node_data . acceleration . w[loc_index];                           // Getting "w" acceleration...

  return data;
};



//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CLIENT FUNCTIONS:  /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # OpenCL push function:
/// ### Description:
/// Writes to an OpenCL client.
void node::push (
                 queue* loc_queue,                                              // Queue.
                )
{
  cl_int loc_error;                                                             // Local error code.

  baseline -> action ("setting \"node\" kernel argument...");                   // Printing message...

  // Setting OpenCL buffer as kernel argument:
  loc_error = clSetKernelArg (
                              loc_kernel -> kernel_id,                          // Kernel.
                              NODE,                                             // Kernel argument index.
                              sizeof(cl_mem),                                   // Kernel argument size.
                              &node_buffer                                      // Kernel argument value.
                             );

  check_error (loc_error);                                                      // Checking returned error code...

  baseline -> done ();                                                          // Printing message...

  #ifdef USE_GRAPHICS
    baseline -> action ("acquiring \"node\" OpenCL buffer...");                 // Printing message...

    glFinish ();                                                                // Ensuring that all OpenGL routines have completed all operations...

    // Acquiring OpenCL buffer:
    loc_error = clEnqueueAcquireGLObjects (
                                           loc_queue -> queue_id,               // Queue.
                                           1,                                   // # of memory objects.
                                           &node_buffer,                        // Memory object array.
                                           0,                                   // # of events in event list.
                                           NULL,                                // Event list.
                                           NULL                                 // Event.
                                          );

    check_error (loc_error);                                                    // Checking returned error code...

    baseline -> done ();                                                        // Printing message...
  #endif

  baseline -> action ("writing \"node\" OpenCL buffer...");                     // Printing message...

  // Writing OpenCL buffer:
  loc_error = clEnqueueWriteBuffer (
                                    loc_queue -> queue_id,                      // OpenCL queue ID.
                                    node_buffer,                                // Data buffer.
                                    CL_TRUE,                                    // Blocking write flag.
                                    0,                                          // Data buffer offset.
                                    (size_t)(4*sizeof(GLfloat)*node_size),      // Data buffer size.
                                    node_data,                                  // Data buffer.
                                    0,                                          // Number of events in the list.
                                    NULL,                                       // Event list.
                                    NULL                                        // Event.
                                   );

  check_error (loc_error);

  baseline -> done ();                                                          // Printing message...

  #ifdef USE_GRAPHICS
    baseline -> action ("releasing \"node\" OpenCL buffer...");                 // Printing message...

    // Releasing openCL buffer:
    loc_error = clEnqueueReleaseGLObjects (
                                           loc_queue -> queue_id,               // Queue.
                                           1,                                   // # of memory objects.
                                           &node_buffer,                        // Memory object array.
                                           0,                                   // # of events in event list.
                                           NULL,                                // Event list.
                                           NULL                                 // Event.
                                          );

    clFinish (loc_queue -> queue_id);                                           // Ensuring that all OpenCL routines have completed all operations...

    check_error (loc_error);                                                    // Checking returned error code...

    baseline -> done ();                                                        // Printing message...
  #endif
}

/// # OpenCL pull function:
/// ### Description:
/// Reads from an OpenCL client.
void node::pull (
                 queue* loc_queue,                                              // Queue.
                )
{
  cl_int loc_error;                                                             // Local error code.

  loc_error = clEnqueueReadBuffer (
                                   loc_queue -> queue_id,                       // OpenCL queue ID.
                                   node_buffer,                                 // Data buffer.
                                   CL_TRUE,                                     // Blocking write flag.
                                   0,                                           // Data buffer offset.
                                   (size_t)(4*sizeof(GLfloat)*node_size),       // Data buffer size.
                                   node_data,                                   // Data buffer.
                                   0,                                           // Number of events in the list.
                                   NULL,                                        // Event list.
                                   NULL                                         // Event.
                                  );

  check_error (loc_error);
}

node::~node()
{
  cl_int loc_error;                                                             // Local error.

  baseline -> action ("releasing \"node\" object...");                          // Printing message...

  if(node_buffer != NULL)                                                       // Checking buffer...
  {
    loc_error = clReleaseMemObject (node_buffer);                               // Releasing OpenCL buffer object...

    check_error (loc_error);                                                    // Checking returned error code...
  }

  #ifdef USE_GRAPHICS
    {
      glDeleteBuffers (1, &node_vbo);                                           // Releasing OpenGL VBO...
    }
  #endif

  delete[] node_data;                                                           // Deleting array for unfolded data...

  baseline -> done ();                                                          // Printing message...
}
