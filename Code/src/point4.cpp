#include "point4.hpp"

point4::point4()
{

}

// OpenCL error get function:
const char* point4::get_error     (
                                    cl_int loc_error                            // Local error code.
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

// OpenCL error check function:
void point4::check_error        (
                                  cl_int loc_error                              // Error code.
                                )
{
  if(loc_error != CL_SUCCESS)                                                   // Checking local error code...
  {
    printf("\nError:  %s\n", get_error(loc_error));                             // Printing error message...
    exit(EXIT_FAILURE);                                                         // Exiting...
  }
}

void point4::init               (
                                  neutrino* loc_baseline,                       // Neutrino baseline.
                                  int         loc_data_number                   // Data number.
                                )
{
  cl_int loc_error;                                                             // Error code.
  int i;                                                                        // Index.

  // Printing action message:
  baseline->action      (
                          "initializing \"point4\" object...",
                          MAX_MESSAGE_SIZE
                        );

  x = new GLfloat[loc_data_number];                                             // "x" data array.
  y = new GLfloat[loc_data_number];                                             // "y" data array.
  z = new GLfloat[loc_data_number];                                             // "z" data array.
  w = new GLfloat[loc_data_number];                                             // "w" data array.

  size = loc_data_number;                                                       // Array size (the same for all of them).
  vao = 0;                                                                      // OpenGL data VAO.
  vbo = 0;                                                                      // OpenGL data VBO.
  buffer = NULL;                                                                // OpenCL data buffer.
  opencl_context = loc_baseline->context_id;                                    // Getting OpenCL context...

  for (i = 0; i < loc_data_number; i++)                                         // Filling arrays with default data...
  {
    x[i] = 0.0f;                                                                // Setting "x" data...
    y[i] = 0.0f;                                                                // Setting "y" data...
    z[i] = 0.0f;                                                                // Setting "z" data...
    w[i] = 1.0f;                                                                // Setting "w" data...
  }

  data = new GLfloat[4*size];                                                   // Creating array for unfolded data...

  for (i = 0; i < size; i++)                                                    // Filling unfolded data array...
  {
    data[4*i + 0] = x[i];                                                       // Filling "x"...
    data[4*i + 1] = y[i];                                                       // Filling "y"...
    data[4*i + 2] = z[i];                                                       // Filling "z"...
    data[4*i + 3] = w[i];                                                       // Filling "w"...
  }

  // Generating VAO:
  glGenVertexArrays             (
                                  1,                                            // # of VAOs to generate.
                                  &vao                                          // VAOs array.
                                );

  // Binding VAO:
  glBindVertexArray             (
                                  vao                                           // VAO to bind.
                                );

  // Generating VBO:
  glGenBuffers                  (
                                  1,                                            // # of VBOs to generate.
                                  &vbo                                          // VBOs array.
                                );

  // Binding VBO:
  glBindBuffer                  (
                                  GL_ARRAY_BUFFER,                              // VBO target.
                                  vbo                                           // VBO to bind.
                                );

  // Creating and initializing a buffer object's data store:
  glBufferData                  (
                                  GL_ARRAY_BUFFER,                              // VBO target.
                                  4*sizeof(GLfloat)*(size),                     // VBO size.
                                  data,                                         // VBO data.
                                  GL_DYNAMIC_DRAW                               // VBO usage.
                                );

  // Enabling "layout = 0" attribute in vertex shader:
  glEnableVertexAttribArray     (
                                  LAYOUT_0                                      // VAO index.
                                );

  // Binding VBO:
  glBindBuffer                  (
                                  GL_ARRAY_BUFFER,                              // VBO target.
                                  vbo                                           // VBO to bind.
                                );

  // Specifying the format for "layout = 0" attribute in vertex shader:
  glVertexAttribPointer         (
                                  LAYOUT_0,                                     // VAO index.
                                  4,                                            // VAO's # of components.
                                  GL_FLOAT,                                     // Data type.
                                  GL_FALSE,                                     // Not using normalized numbers.
                                  0,                                            // Data stride.
                                  0                                             // Data offset.
                                );

  // Creating OpenCL buffer from OpenGL buffer:
  buffer = clCreateFromGLBuffer (
                                  opencl_context,                               // OpenCL context.
                                  CL_MEM_READ_WRITE,                            // Memory flags.
                                  vbo,                                          // VBO.
                                  &loc_error                                    // Returned error.
                                );

  delete[] data;                                                                // Deleting array for unfolded data...

  check_error(loc_error);                                                       // Checking returned error code...

  baseline->done();                                                            // Printing message...
}

void point4::set                (
                                  kernel* loc_kernel,
                                  int     loc_kernel_arg
                                )
{
  cl_int loc_error;                                                             // Error.

  // Setting buffer as OpenCL kernel argument:
  loc_error = clSetKernelArg      (
                                    loc_kernel->kernel_id,                      // Kernel.
                                    loc_kernel_arg,                             // Kernel argument index.
                                    sizeof(cl_mem),                             // Kernel argument size.
                                    &buffer                                     // Kernel argument value.
                                  );

  check_error(loc_error);                                                       // Checking returned error code...
}

// Push kernel argument:
void point4::push               (
                                  queue*  loc_queue,                            // Queue.
                                  kernel* loc_kernel,                           // Kernel.
                                  int     loc_kernel_arg                        // Kernel argument index.
                                )
{
  cl_int  loc_error;                                                            // Local error code.

  // Passing "points" to OpenCL kernel:
  loc_error = clEnqueueAcquireGLObjects (
                                          loc_queue->queue_id,                  // Queue.
                                          1,                                    // # of memory objects.
                                          &buffer,                              // Memory object array.
                                          0,                                    // # of events in event list.
                                          NULL,                                 // Event list.
                                          NULL                                  // Event.
                                        );

  check_error(loc_error);                                                       // Checking returned error code...
}

// Pop kernel argument:
void point4::pop                (
                                  queue*  loc_queue,                            // Queue.
                                  kernel* loc_kernel,                           // Kernel.
                                  int     loc_kernel_arg                        // Kernel argument index.
                                )
{
  cl_int  loc_error;                                                            // Local error code.

  // Releasing "points" from OpenCL kernel:
  loc_error = clEnqueueReleaseGLObjects (
                                          loc_queue->queue_id,                  // Queue.
                                          1,                                    // # of memory objects.
                                          &buffer,                              // Memory object array.
                                          0,                                    // # of events in event list.
                                          NULL,                                 // Event list.
                                          NULL                                  // Event.
                                        );

  check_error(loc_error);                                                       // Checking returned error code...
}

point4::~point4()
{
  cl_int loc_error;                                                             // Local error.

  // Printing action message:
  baseline->action      (
                          "releasing \"float1\" object...",
                          MAX_MESSAGE_SIZE
                        );

  if(buffer != NULL)
  {
    loc_error = clReleaseMemObject(buffer);                                     // Releasing OpenCL buffer object...

    check_error(loc_error);
  }

  glDeleteBuffers(1, &vbo);                                                     // Releasing OpenGL VBO...
  glDeleteBuffers(1, &vao);                                                     // Releasing OpenGL VAO...

  delete[] x;                                                                   // Releasing "x" data...
  delete[] y;                                                                   // Releasing "y" data...
  delete[] z;                                                                   // Releasing "z" data...
  delete[] w;                                                                   // Releasing "w" data...

  baseline->done();
}
