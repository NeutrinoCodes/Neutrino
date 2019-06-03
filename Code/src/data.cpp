#include "data.hpp"

void init_float4 (
                  float4 loc_data
                 )
{
  loc_data . x = 0.0;
  loc_data . y = 0.0;
  loc_data . z = 0.0;
  loc_data . w = 1.0;
}

void init_color4 (
                  color4 loc_data
                 )
{
  loc_data . r = 0.0;
  loc_data . g = 0.0;
  loc_data . b = 0.0;
  loc_data . a = 1.0;
}

point4::point4()
{

}

/// # OpenCL error get function
/// ### Description:
/// Translates an OpenCL numeric error code into a human-readable string.
const char* point4::get_error (
                               cl_int loc_error                                 // Local error code.
                              )
{
  switch(loc_error)
  {
    // Run-time and JIT compiler errors:
    case      0: return "CL_SUCCESS";
    case     -1: return "CL_DEVICE_NOT_FOUND";
    case     -2: return "CL_DEVICE_NOT_AVAILABLE";
    case     -3: return "CL_COMPILER_NOT_AVAILABLE";
    case     -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case     -5: return "CL_OUT_OF_RESOURCES";
    case     -6: return "CL_OUT_OF_HOST_MEMORY";
    case     -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case     -8: return "CL_MEM_COPY_OVERLAP";
    case     -9: return "CL_IMAGE_FORMAT_MISMATCH";
    case    -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case    -11: return "CL_BUILD_PROGRAM_FAILURE";
    case    -12: return "CL_MAP_FAILURE";
    case    -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
    case    -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
    case    -15: return "CL_COMPILE_PROGRAM_FAILURE";
    case    -16: return "CL_LINKER_NOT_AVAILABLE";
    case    -17: return "CL_LINK_PROGRAM_FAILURE";
    case    -18: return "CL_DEVICE_PARTITION_FAILED";
    case    -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

    // Compile-time errors:
    case    -30: return "CL_INVALID_VALUE";
    case    -31: return "CL_INVALID_DEVICE_TYPE";
    case    -32: return "CL_INVALID_PLATFORM";
    case    -33: return "CL_INVALID_DEVICE";
    case    -34: return "CL_INVALID_CONTEXT";
    case    -35: return "CL_INVALID_QUEUE_PROPERTIES";
    case    -36: return "CL_INVALID_COMMAND_QUEUE";
    case    -37: return "CL_INVALID_HOST_PTR";
    case    -38: return "CL_INVALID_MEM_OBJECT";
    case    -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case    -40: return "CL_INVALID_IMAGE_SIZE";
    case    -41: return "CL_INVALID_SAMPLER";
    case    -42: return "CL_INVALID_BINARY";
    case    -43: return "CL_INVALID_BUILD_OPTIONS";
    case    -44: return "CL_INVALID_PROGRAM";
    case    -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
    case    -46: return "CL_INVALID_KERNEL_NAME";
    case    -47: return "CL_INVALID_KERNEL_DEFINITION";
    case    -48: return "CL_INVALID_KERNEL";
    case    -49: return "CL_INVALID_ARG_INDEX";
    case    -50: return "CL_INVALID_ARG_VALUE";
    case    -51: return "CL_INVALID_ARG_SIZE";
    case    -52: return "CL_INVALID_KERNEL_ARGS";
    case    -53: return "CL_INVALID_WORK_DIMENSION";
    case    -54: return "CL_INVALID_WORK_GROUP_SIZE";
    case    -55: return "CL_INVALID_WORK_ITEM_SIZE";
    case    -56: return "CL_INVALID_GLOBAL_OFFSET";
    case    -57: return "CL_INVALID_EVENT_WAIT_LIST";
    case    -58: return "CL_INVALID_EVENT";
    case    -59: return "CL_INVALID_OPERATION";
    case    -60: return "CL_INVALID_GL_OBJECT";
    case    -61: return "CL_INVALID_BUFFER_SIZE";
    case    -62: return "CL_INVALID_MIP_LEVEL";
    case    -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
    case    -64: return "CL_INVALID_PROPERTY";
    case    -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
    case    -66: return "CL_INVALID_COMPILER_OPTIONS";
    case    -67: return "CL_INVALID_LINKER_OPTIONS";
    case    -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

    // Extension errors:
    case  -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case  -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case  -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case  -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case  -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case  -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";

    default: return "Unknown OpenCL error";
  }
}

/// # OpenCL error check function
/// ### Description:
/// Checks for an OpenCL error code and print it to stdout.
void point4::check_error (
                          cl_int loc_error                                      // Error code.
                         )
{
  if(loc_error != CL_SUCCESS)                                                   // Checking local error code...
  {
    baseline -> error (get_error (loc_error));                                  // Printing error message...
    exit (EXIT_FAILURE);                                                        // Exiting...
  }
}

/// # Initialization function
/// ### Description:
/// Prepares a contiguous (unfolded) array to be used as data buffer
/// allocated on the client memory space. Creates an OpenCL buffer
/// (interoperability buffer) from the OpenGL buffer, in case the
/// use_cl_gl_interop` flag is set to `true`.
/// Creates an OpenCL buffer (not shared with OpenGL), in case the
/// use_cl_gl_interop` flag is set to `false`.
void point4::init (
                   neutrino*  loc_baseline,                                     // Neutrino baseline.
                   GLsizeiptr loc_data_size                                     // Data array size.
                  )
{
  cl_int     loc_error;                                                         // Error code.
  GLsizeiptr i;                                                                 // Index.

  baseline       = loc_baseline;                                                // Getting Neutrino baseline...
  position       = new size_t[baseline -> k_num];                               // Initializing kernel argument position array...

  baseline -> action ("initializing \"point4\" object...");                     // Printing message...

  data_size      = loc_data_size;                                               // Array size.
  buffer         = NULL;                                                        // OpenCL data buffer.
  opencl_context = baseline -> context_id;                                      // Getting OpenCL context...

  // DATA ARRAYS:
  node_data      = new node[data_size];                                         // Node data array.
  neighbour_data = new neighbour[data_size];                                    // Neighbour data array.
  link_data      = new link[data_size];                                         // Link data array.
  color_data     = new color[data_size];                                        // Color data array.

  for(i = 0; i < data_size; i++)                                                // Filling data arrays with default values...
  {
    // POSITIONS:
    init_float4 (node_data . position);                                         // Initializing "position"...
    init_float4 (node_data . position_buffer);                                  // Initializing "position_buffer"...

    // VELOCITIES:
    init_float4 (node_data . velocity);                                         // Initializing "velocity"...
    init_float4 (node_data . velocity_buffer);                                  // Initializing "velocity_buffer"...

    // ACCELERATIONS:
    init_float4 (node_data . acceleration);                                     // Initializing "acceleration"...
    init_float4 (node_data . acceleration_buffer);                              // Initializing "acceleration_buffer"...

    // NEIGHBOURS:
    neighbour_data . up    = i;                                                 // Initializing "up" neighbour index...
    neighbour_data . down  = i;                                                 // Initializing "down" neighbour index...
    neighbour_data . left  = i;                                                 // Initializing "left" neighbour index...
    neighbour_data . right = i;                                                 // Initializing "right" neighbour index...

    // LINKS:
    link_data . stiffness  = 0.0;                                               // Initializing link stiffness tensor...
    link_data . damping    = 0.0;                                               // Initializing link damping tensor...

    // COLORS:
    init_color4 (color_data . node);                                            // Initializing node color...
    init_color4 (color_data . up);                                              // Initializing "up" neighbour color...
    init_color4 (color_data . down);                                            // Initializing "down" neighbour color...
    init_color4 (color_data . left);                                            // Initializing "left" neighbour color...
    init_color4 (color_data . right);                                           // Initializing "right" neighbour color...
  }

  #ifdef USE_GRAPHICS
    // OpenGL VAOs:
    node_vao      = 0;                                                          // Node data VAO.
    neighbour_vao = 0;                                                          // Neighbour data VAO.
    link_vao      = 0;                                                          // Link data VAO.
    color_vao     = 0;                                                          // Color data VAO.

    // OpenGL VBOs:
    node_vbo      = 0;                                                          // Node data VBO.
    neighbour_vbo = 0;                                                          // Neighbour data VBO.
    link_vbo      = 0;                                                          // Link data VBO.
    color_vbo     = 0;                                                          // Color data VBO.

    // Creating OpenCL buffer from OpenGL buffer for NODE structure:
    cl_create_from_gl_buffer<node> (
                                    node_vao,
                                    node_vbo,
                                    NODE,
                                    node_data,
                                    data_size,
                                    opencl_context,
                                    node_buffer
                                   );

    // Creating OpenCL buffer from OpenGL buffer for NEIGHBOUR structure:
    cl_create_from_gl_buffer<neighbour> (
                                         neighbour,
                                         neighbour,
                                         NEIGHBOUR,
                                         neighbour,
                                         data_size,
                                         opencl_context,
                                         neighbour_buffer
                                        );

    // Creating OpenCL buffer from OpenGL buffer for LINK structure:
    cl_create_from_gl_buffer<link> (
                                    link,
                                    link,
                                    LINK,
                                    link,
                                    data_size,
                                    opencl_context,
                                    link_buffer
                                   );

    // Creating OpenCL buffer from OpenGL buffer for COLOR structure:
    cl_create_from_gl_buffer<color> (
                                     color,
                                     color,
                                     COLOR,
                                     color,
                                     data_size,
                                     opencl_context,
                                     color_buffer
                                    );
  #else
    // Creating OpenCL buffer for NODE structure:
    cl_create_buffer<node> (
                            node_data,
                            data_size,
                            opencl_context,
                            node_buffer
                           );

    // Creating OpenCL buffer for NEIGHBOUR structure:
    cl_create_buffer<node> (
                            neighbour_data,
                            data_size,
                            opencl_context,
                            neighbour_buffer
                           );

    // Creating OpenCL buffer for LINK structure:
    cl_create_buffer<node> (
                            link_data,
                            data_size,
                            opencl_context,
                            link_buffer
                           );

    // Creating OpenCL buffer for COLOR structure:
    cl_create_buffer<node> (
                            color_data,
                            data_size,
                            opencl_context,
                            color_buffer
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
void point4::set_arg (
                      kernel* loc_kernel,                                       // OpenCL kernel.
                      cl_uint loc_kernel_arg                                    // OpenCL kernel argument #.
                     )
{
  cl_int loc_error;                                                             // Error code.
  size_t kernel_index;
  size_t i;

  baseline -> action ("setting \"point4\" kernel argument...");                 // Printing message...

  // Getting kernel index:
  for(i = 0; i < baseline -> k_num; i++)                                        // Scanning OpenCL kernel id array...
  {
    if(baseline -> kernel_id[i] == loc_kernel -> kernel_id)                     // Finding current kernel id...
    {
      kernel_index = i;                                                         // Setting kernel index...
    }
  }

  position[kernel_index] = loc_kernel_arg;                                      // Setting kernel argument position in current kernel...

  // Setting OpenCL buffer as kernel argument:
  loc_error              = clSetKernelArg (
                                           loc_kernel -> kernel_id,             // Kernel.
                                           loc_kernel_arg,                      // Kernel argument index.
                                           sizeof(cl_mem),                      // Kernel argument size.
                                           &buffer                              // Kernel argument value.
                                          );

  check_error (loc_error);                                                      // Checking returned error code...

  baseline -> done ();                                                          // Printing message...
}

/// # "x" set function
/// ### Description:
/// Sets the "x" point data value in point data array.
void point4::set_x (
                    GLsizeiptr loc_index,                                       // Data index.
                    GLfloat    loc_value                                        // Data value.
                   )
{
  data[4*loc_index + 0] = loc_value;                                            // Setting data value...
}

/// # "y" set function
/// ### Description:
/// Sets the "y" point data value in point data array.
void point4::set_y (
                    GLsizeiptr loc_index,                                       // Data index.
                    GLfloat    loc_value                                        // Data value.
                   )
{
  data[4*loc_index + 1] = loc_value;                                            // Setting data value...
}

/// # "z" set function
/// ### Description:
/// Sets the "z" point data value in point data array.
void point4::set_z (
                    GLsizeiptr loc_index,                                       // Data index.
                    GLfloat    loc_value                                        // Data value.
                   )
{
  data[4*loc_index + 2] = loc_value;                                            // Setting data value...
}

/// # "w" set function
/// ### Description:
/// Sets the "w" point data value in point data array.
void point4::set_w (
                    GLsizeiptr loc_index,                                       // Data index.
                    GLfloat    loc_value                                        // Data value.
                   )
{
  data[4*loc_index + 3] = loc_value;                                            // Setting data value...
}

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
/// # OpenCL write buffer function
/// ### Description:
/// Enqueues commands to write to a buffer object from host memory.
void point4::push (
                   queue*  loc_queue,                                           // Queue.
                   cl_uint loc_kernel_arg                                       // Kernel argument index.
                  )
{
  cl_int loc_error;                                                             // Local error code.

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
}

/// # OpenCL read buffer function:
/// ### Description:
/// Enqueues commands to read from a buffer object to host memory.
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

/// # OpenCL acquire buffer function
/// ### Description:
/// Acquires OpenCL memory objects that have been created from OpenGL objects.
void point4::acquire_gl (
                         queue*  loc_queue,                                     // Queue.
                         cl_uint loc_kernel_arg                                 // Kernel argument index.
                        )
{
  cl_int loc_error;                                                             // Local error code.

  glFinish ();                                                                  // Ensuring that all OpenGL routines have completed all operations...

  // Passing buffer to OpenCL kernel:
  loc_error = clEnqueueAcquireGLObjects (
                                         loc_queue -> queue_id,                 // Queue.
                                         1,                                     // # of memory objects.
                                         &buffer,                               // Memory object array.
                                         0,                                     // # of events in event list.
                                         NULL,                                  // Event list.
                                         NULL                                   // Event.
                                        );

  check_error (loc_error);                                                      // Checking returned error code...
}

/// # OpenCL release buffer function:
/// ### Description:
/// Releases OpenCL memory objects that have been created from OpenGL objects.
void point4::release_gl (
                         queue*  loc_queue,                                     // Queue.
                         cl_uint loc_kernel_arg                                 // Kernel argument index.
                        )
{
  cl_int loc_error;                                                             // Local error code.

  // Releasing buffer from OpenCL kernel:
  loc_error = clEnqueueReleaseGLObjects (
                                         loc_queue -> queue_id,                 // Queue.
                                         1,                                     // # of memory objects.
                                         &buffer,                               // Memory object array.
                                         0,                                     // # of events in event list.
                                         NULL,                                  // Event list.
                                         NULL                                   // Event.
                                        );

  clFinish (loc_queue -> queue_id);                                             // Ensuring that all OpenCL routines have completed all operations...

  check_error (loc_error);                                                      // Checking returned error code...
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
