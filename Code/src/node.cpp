#include "node.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CONSTRUCTOR: /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
node::node()
{
// Doing nothing because we need a deferred init after OpenGL and OpenCL initialization.
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "INIT" FUNCTION: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Node init function
/// ### Description:
/// Initializes node object.
void node::init (
                 neutrino* loc_baseline,                                        // Neutrino baseline.
                 int1      loc_node_size                                        // Data array size.
                )
{
  cl_int loc_error;                                                             // Error code.

  int1   i;                                                                     // Data index.
  baseline        = loc_baseline;                                               // Getting Neutrino baseline...

  baseline->action ("initializing \"node\" object...");                         // Printing message...

  node_size.value = loc_node_size.value;                                        // Array size.

  node_buffer     = NULL;                                                       // OpenCL data buffer.
  opencl_context  = baseline->context_id;                                       // Getting OpenCL context...
  node_data       = new node_structure[node_size.value];                        // Node data array.

  for(i.value = 0; i.value < node_size.value; (i.value)++)                      // Filling data arrays with default values...
  {
    init_float4 (node_data[i.value].position);                                  // Initializing "position"...
    init_float4 (node_data[i.value].velocity);                                  // Initializing "velocity"...
    init_float4 (node_data[i.value].acceleration);                              // Initializing "acceleration"...
    init_float4 (node_data[i.value].position_buffer);                           // Initializing "position_buffer"...
    init_float4 (node_data[i.value].velocity_buffer);                           // Initializing "velocity_buffer"...
    init_float4 (node_data[i.value].acceleration_buffer);                       // Initializing "acceleration_buffer"...
    init_color4 (node_data[i.value].color);                                     // Initializing node color...
    init_int1 (node_data[i.value].mass);                                        // Initializing node mass...
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
                  sizeof(node_data)*node_size.value,                            // VBO size.
                  node_data,                                                    // VBO data.
                  GL_DYNAMIC_DRAW                                               // VBO usage.
                 );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray (
                               LAYOUT_NODE;                                     // VAO index.
                              );

    // Binding VBO:
    glBindBuffer (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  node_vbo                                                      // VBO to bind.
                 );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer (
                           LAYOUT_NODE,                                         // VAO index.
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
                                  sizeof(node_data)*node_size.value,            // Data buffer size.
                                  node_data,                                    // Data buffer.
                                  &loc_error                                    // Error code.
                                 );
  #endif

  check_error (loc_error);                                                      // Checking returned error code...

  baseline->done ();                                                            // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "SET" FUNCTIONS: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Node position set function
/// ### Description:
/// Sets the position in node structure.
void node::set_position (
                         int1   loc_index,                                      // Data index.
                         float4 loc_value                                       // Data value.
                        )
{
  node_data[loc_index.value].position.x = loc_value.x;                          // Setting "x" position...
  node_data[loc_index.value].position.y = loc_value.y;                          // Setting "y" position...
  node_data[loc_index.value].position.z = loc_value.z;                          // Setting "z" position...
  node_data[loc_index.value].position.w = loc_value.w;                          // Setting "w" position...
};

/// # Node velocity set function
/// ### Description:
/// Sets the velocity in node structure.
void node::set_velocity (
                         int1   loc_index,                                      // Data index.
                         float4 loc_value                                       // Data value.
                        )
{
  node_data[loc_index.value].velocity.x = loc_value.x;                          // Setting "x" velocity...
  node_data[loc_index.value].velocity.y = loc_value.y;                          // Setting "y" velocity...
  node_data[loc_index.value].velocity.z = loc_value.z;                          // Setting "z" velocity...
  node_data[loc_index.value].velocity.w = loc_value.w;                          // Setting "w" velocity...
};

/// # Node acceleration set function
/// ### Description:
/// Sets the acceleration in node structure.
void node::set_acceleration (
                             int1   loc_index,                                  // Data index.
                             float4 loc_value                                   // Data value.
                            )
{
  node_data[loc_index.value].acceleration.x = loc_value.x;                      // Setting "x" acceleration...
  node_data[loc_index.value].acceleration.y = loc_value.y;                      // Setting "y" acceleration...
  node_data[loc_index.value].acceleration.z = loc_value.z;                      // Setting "z" acceleration...
  node_data[loc_index.value].acceleration.w = loc_value.w;                      // Setting "w" acceleration...
};

/// # Node color set function
/// ### Description:
/// Sets the color in node structure.
void node::set_color (
                      int1   loc_index,                                         // Data index.
                      color4 loc_value                                          // Data value.
                     )
{
  node_data[loc_index.value].color.r = loc_value.r;                             // Setting "r" color...
  node_data[loc_index.value].color.g = loc_value.g;                             // Setting "g" color...
  node_data[loc_index.value].color.b = loc_value.b;                             // Setting "b" color...
  node_data[loc_index.value].color.a = loc_value.a;                             // Setting "a" color...
};

/// # Node mass set function
/// ### Description:
/// Sets the mass in node structure.
void node::set_mass (
                     int1   loc_index,                                          // Data index.
                     float1 loc_value                                           // Data value.
                    )
{
  node_data[loc_index.value].mass.value = loc_value.value;                      // Setting mass...
};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "GET" FUNCTIONS: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # Node position get function
/// ### Description:
/// Gets the position from node structure.
float4 node::get_position (
                           int1 loc_index,                                      // Data index.
                          )
{
  float4 data;

  data.x = node_data[loc_index.value].position.x;                               // Getting "x" position...
  data.y = node_data[loc_index.value].position.y;                               // Getting "y" position...
  data.z = node_data[loc_index.value].position.z;                               // Getting "z" position...
  data.w = node_data[loc_index.value].position.w;                               // Getting "w" position...

  return data;
};

/// # Node velocity get function
/// ### Description:
/// Gets the velocity from node structure.
float4 node::get_velocity (
                           int1 loc_index,                                      // Data index.
                          )
{
  float4 data;

  data.x = node_data[loc_index.value].velocity.x;                               // Getting "x" velocity...
  data.y = node_data[loc_index.value].velocity.y;                               // Getting "y" velocity...
  data.z = node_data[loc_index.value].velocity.z;                               // Getting "z" velocity...
  data.w = node_data[loc_index.value].velocity.w;                               // Getting "w" velocity...

  return data;
};

/// # Node acceleration get function
/// ### Description:
/// Gets the acceleration from node structure.
float4 node::get_acceleration (
                               int1 loc_index,                                  // Data index.
                              )
{
  float4 data;

  data.x = node_data[loc_index.value].acceleration.x;                           // Getting "x" acceleration...
  data.y = node_data[loc_index.value].acceleration.y;                           // Getting "y" acceleration...
  data.z = node_data[loc_index.value].acceleration.z;                           // Getting "z" acceleration...
  data.w = node_data[loc_index.value].acceleration.w;                           // Getting "w" acceleration...

  return data;
};

/// # Node color get function
/// ### Description:
/// Gets the color from node structure.
float4 node::get_color (
                        int1 loc_index,                                         // Data index.
                       )
{
  color4 data;

  data.r = node_data[loc_index.value].color.r;                                  // Getting "r" color...
  data.g = node_data[loc_index.value].color.g;                                  // Getting "g" color...
  data.b = node_data[loc_index.value].color.b;                                  // Getting "b" color...
  data.a = node_data[loc_index.value].color.a;                                  // Getting "a" color...

  return data;
};

/// # Node mass get function
/// ### Description:
/// Gets the mass from node structure.
float4 node::get_mass (
                       int1 loc_index,                                          // Data index.
                      )
{
  float1 data;

  data.value = node_data[loc_index.value].mass.value;                           // Getting mass...

  return data;
};

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// "CONTROL" FUNCTIONS: /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # OpenCL push function:
/// ### Description:
/// Writes to an OpenCL client.
void node::push (
                 queue* loc_queue,                                              // Queue.
                )
{
  cl_int loc_error;                                                             // Local error code.

  baseline->action ("setting \"node\" kernel argument...");                     // Printing message...

  // Setting OpenCL buffer as kernel argument:
  loc_error = clSetKernelArg (
                              loc_kernel->kernel_id,                            // Kernel.
                              LAYOUT_NODE,                                      // Kernel argument index.
                              sizeof(cl_mem),                                   // Kernel argument size.
                              &node_buffer                                      // Kernel argument value.
                             );

  check_error (loc_error);                                                      // Checking returned error code...

  baseline->done ();                                                            // Printing message...

  #ifdef USE_GRAPHICS
    baseline->action ("acquiring \"node\" OpenCL buffer...");                   // Printing message...

    glFinish ();                                                                // Ensuring that all OpenGL routines have completed all operations...

    // Acquiring OpenCL buffer:
    loc_error = clEnqueueAcquireGLObjects (
                                           loc_queue->queue_id,                 // Queue.
                                           1,                                   // # of memory objects.
                                           &node_buffer,                        // Memory object array.
                                           0,                                   // # of events in event list.
                                           NULL,                                // Event list.
                                           NULL                                 // Event.
                                          );

    check_error (loc_error);                                                    // Checking returned error code...

    baseline->done ();                                                          // Printing message...
  #endif

  baseline->action ("writing \"node\" OpenCL buffer...");                       // Printing message...

  // Writing OpenCL buffer:
  loc_error = clEnqueueWriteBuffer (
                                    loc_queue->queue_id,                        // OpenCL queue ID.
                                    node_buffer,                                // Data buffer.
                                    CL_TRUE,                                    // Blocking write flag.
                                    0,                                          // Data buffer offset.
                                    sizeof(node_data)*node_size.value,          // Data buffer size.
                                    node_data,                                  // Data buffer.
                                    0,                                          // Number of events in the list.
                                    NULL,                                       // Event list.
                                    NULL                                        // Event.
                                   );

  check_error (loc_error);

  baseline->done ();                                                            // Printing message...

  #ifdef USE_GRAPHICS
    baseline->action ("releasing \"node\" OpenCL buffer...");                   // Printing message...

    // Releasing openCL buffer:
    loc_error = clEnqueueReleaseGLObjects (
                                           loc_queue->queue_id,                 // Queue.
                                           1,                                   // # of memory objects.
                                           &node_buffer,                        // Memory object array.
                                           0,                                   // # of events in event list.
                                           NULL,                                // Event list.
                                           NULL                                 // Event.
                                          );

    clFinish (loc_queue->queue_id);                                             // Ensuring that all OpenCL routines have completed all operations...

    check_error (loc_error);                                                    // Checking returned error code...

    baseline->done ();                                                          // Printing message...
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
                                   loc_queue->queue_id,                         // OpenCL queue ID.
                                   node_buffer,                                 // Data buffer.
                                   CL_TRUE,                                     // Blocking write flag.
                                   0,                                           // Data buffer offset.
                                   sizeof(node_data)*node_size.value,           // Data buffer size.
                                   node_data,                                   // Data buffer.
                                   0,                                           // Number of events in the list.
                                   NULL,                                        // Event list.
                                   NULL                                         // Event.
                                  );

  check_error (loc_error);
}

/// # OpenCL acquire function:
/// ### Description:
/// Acquires an OpenCL buffer.
void node::acquire (
                    queue* loc_queue,                                           // Queue.
                   )
{
  #ifdef USE_GRAPHICS
    glFinish ();                                                                // Ensuring that all OpenGL routines have completed all operations...

    // Acquiring OpenCL buffer:
    loc_error = clEnqueueAcquireGLObjects (
                                           loc_queue->queue_id,                 // Queue.
                                           1,                                   // # of memory objects.
                                           &node_buffer,                        // Memory object array.
                                           0,                                   // # of events in event list.
                                           NULL,                                // Event list.
                                           NULL                                 // Event.
                                          );

    check_error (loc_error);                                                    // Checking returned error code...
  #endif
}

/// # OpenCL release function:
/// ### Description:
/// Releases an OpenCL buffer.
void node::release (
                    queue* loc_queue,                                           // Queue.
                   )
{
  #ifdef USE_GRAPHICS
    // Releasing openCL buffer:
    loc_error = clEnqueueReleaseGLObjects (
                                           loc_queue->queue_id,                 // Queue.
                                           1,                                   // # of memory objects.
                                           &node_buffer,                        // Memory object array.
                                           0,                                   // # of events in event list.
                                           NULL,                                // Event list.
                                           NULL                                 // Event.
                                          );

    clFinish (loc_queue->queue_id);                                             // Ensuring that all OpenCL routines have completed all operations...

    check_error (loc_error);                                                    // Checking returned error code...
  #endif
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// ERROR FUNCTION: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/// # OpenCL error check function
/// ### Description:
/// Checks for an OpenCL error code and print it to stdout.
void node::check_error (
                        cl_int loc_error                                        // Error code.
                       )
{
  if(loc_error != CL_SUCCESS)                                                   // Checking local error code...
  {
    baseline->error (get_error (loc_error));                                    // Printing error message...
    exit (EXIT_FAILURE);                                                        // Exiting...
  }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DESTRUCTOR: /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
node::~node()
{
  cl_int loc_error;                                                             // Local error.

  baseline->action ("releasing \"node\" object...");                            // Printing message...

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

  baseline->done ();                                                            // Printing message...
}
