/// @file     kernel.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definition of an OpenCL "kernel" class.

#include "kernel.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "kernel" class /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
kernel::kernel()
{
  source    = "";                                                                                   // Initializing kernel source...
  program   = NULL;                                                                                 // Initializing kernel program...
  size_i    = 0;                                                                                    // Initializing kernel size (i-index)...
  size_j    = 0;                                                                                    // Initializing kernel size (j-index)...
  size_k    = 0;                                                                                    // Initializing kernel size (k-index)...
  event     = NULL;                                                                                 // Initializing kernel event...
  kernel_id = NULL;                                                                                 // Initializing kernel id...
}

void kernel::init
(
 neutrino*   loc_baseline,                                                                          // Neutrino baseline.
 std::string loc_kernel_home,                                                                       // Kernel home directory.
 std::string loc_kernel_file_name,                                                                  // OpenCL kernel file name.
 size_t      loc_kernel_size_i,                                                                     // OpenCL kernel size (i-index).
 size_t      loc_kernel_size_j,                                                                     // OpenCL kernel size (j-index).
 size_t      loc_kernel_size_k                                                                      // OpenCL kernel size (k-index).
)
{
  cl_int      loc_error;                                                                            // Error code.
  size_t      loc_log_size;                                                                         // OpenCL JIT compiler log size.
  std::string loc_source;                                                                           // Source file as string.
  char*       loc_source_buffer;                                                                    // Source file temporary char buffer.
  char*       loc_options_buffer;                                                                   // Options temporary char buffer.
  size_t      i;                                                                                    // Index.

  baseline                                     = loc_baseline;                                      // Getting Neutrino baseline...
  size_i                                       = loc_kernel_size_i;                                 // Getting OpenCL kernel size (i-index)...
  size_j                                       = loc_kernel_size_j;                                 // Getting OpenCL kernel size (j-index)...
  size_k                                       = loc_kernel_size_k;                                 // Getting OpenCL kernel size (k-index)...

  kernel_home                                  = loc_kernel_home;                                   // Getting OpenCL kernel home directory...
  kernel_file_name                             = kernel_home + "/" +
                                                 loc_kernel_file_name;                              // Building up vertex file full name...
  compiler_options                             = "-I" + kernel_home;                                // Building up JIT compiler options string...
  loc_options_buffer                           =                                                    // Building temporary char options buffer...
                                                 new char[compiler_options.size () + 1];
  compiler_options.copy (loc_options_buffer, compiler_options.size () + 1);                         // Building options string...
  loc_options_buffer[compiler_options.size ()] = '\0';                                              // Null terminating options string...

  baseline->action ("loading OpenCL kernel source from file...");                                   // Printing message...
  loc_source                                   =
    baseline->load_file (kernel_file_name);                                                         // Loading file...
  source_size                                  = loc_source.size ();                                // Getting source size...
  source                                       = loc_source;
  baseline->done ();                                                                                // Printing message...

  baseline->action ("creating OpenCL program from kernel source...");                               // Printing message...
  loc_source_buffer                            = new char[source_size + 1];                         // Building temporary source char buffer...
  loc_source.copy (loc_source_buffer, source_size + 1);                                             // Building string source buffer...
  loc_source_buffer[source_size]               = '\0';                                              // Null terminateing buffer string...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Creating OpenCL program from its source:
  program                                      = clCreateProgramWithSource
                                                 (
                                                  baseline->context_id,                             // OpenCL context ID.
                                                  1,                                                // Number of program sources.
                                                  (
                                                   const
                                                   char
                                                   *
                                                   *)&loc_source_buffer,                            // Program source.
                                                  &source_size,                                     // Source size.
                                                  &loc_error                                        // Error code.
                                                 );
  baseline->check_error (loc_error);                                                                // Checking error...
  baseline->done ();                                                                                // Printing message...

  delete loc_source_buffer;

  baseline->action ("building OpenCL program...");                                                  // Printing message...

  // Creating device ID list:
  device_id    = new cl_device_id[1];                                                               // OpenCL device ID.
  device_id[0] = baseline->device_id;                                                               // Getting device ID.

  // Building OpenCL program:
  loc_error    = clBuildProgram
                 (
                  program,                                                                          // Program.
                  1,                                                                                // Number of devices.
                  device_id,                                                                        // Device ID.
                  loc_options_buffer,                                                               // Including header files from kernel's directory.
                  NULL,                                                                             // Notification routine.
                  NULL                                                                              // Notification argument.
                 );

  delete loc_options_buffer;

  if(loc_error != CL_SUCCESS)                                                                       // Checking compiled kernel...
  {
    baseline->error (baseline->get_error (loc_error));                                              // Printing message...

    // Getting OpenCL compiler information:
    loc_error = clGetProgramBuildInfo
                (
                 program,                                                                           // Program.
                 device_id[0],                                                                      // Device ID.
                 CL_PROGRAM_BUILD_LOG,                                                              // Build log parameter.
                 0,                                                                                 // Dummy parameter size.
                 NULL,                                                                              // Dummy parameter value.
                 &loc_log_size                                                                      // Size of log.
                );

    baseline->check_error (loc_error);                                                              // Checking error...

    char* loc_log_buffer = new char[loc_log_size + 1]();                                            // Allocating log buffer...

    // Reading OpenCL compiler error log:
    loc_error = clGetProgramBuildInfo
                (
                 program,                                                                           // Program.
                 device_id[0],                                                                      // Device ID.
                 CL_PROGRAM_BUILD_LOG,                                                              // Build log parameter.
                 loc_log_size + 1,                                                                  // Log size.
                 loc_log_buffer,                                                                    // The log.
                 NULL                                                                               // Dummy size parameter.
                );

    baseline->check_error (loc_error);                                                              // Checking error...

    compiler_log = loc_log_buffer;                                                                  // Setting compiler log...
    std::cout << compiler_log << std::endl;                                                         // Printing log...
    delete (loc_log_buffer);                                                                        // Deleting log buffer...
    exit (loc_error);                                                                               // Exiting...
  }

  baseline->done ();                                                                                // Printing message...

  baseline->action ("creating OpenCL kernel object from program...");                               // Printing message...

  // Creating OpenCL kernel:
  kernel_id = clCreateKernel
              (
               program,                                                                             // OpenCL kernel program.
               NU_KERNEL_NAME,                                                                      // Kernel name.
               &loc_error                                                                           // Error code.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  baseline->done ();                                                                                // Printing message...

  // Initializing kernel object:
  baseline->action ("initializing kernel object...");                                               // Printing message...

  for(i = 0; i < baseline->k_num; i++)                                                              // Scanning OpenCL kernel argument array...
  {
    if(baseline->kernel_id[i] == NULL)                                                              // Looking for 1st non-assigned OpenCL kernel ID...
    {
      baseline->kernel_id[i] = kernel_id;                                                           // Assigning value to 1st non-assigned OpenCL kernel ID...
      break;                                                                                        // Exiting loop...
    }
  }

  baseline->done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// setarg "int1" overload ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void kernel::setarg
(
 int1*   loc_data,                                                                                  // int1 data.
 cl_uint loc_layout_index                                                                           // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Creating OpenCL memory buffer:
    loc_data->buffer = clCreateBuffer
                       (
                        baseline->context_id,                                                       // OpenCL context.
                        CL_MEM_READ_WRITE |                                                         // Memory flag.
                        CL_MEM_COPY_HOST_PTR,                                                       // Memory flag.
                        sizeof(cl_long)*loc_data->size,                                             // Data buffer size.
                        loc_data->data,                                                             // Data buffer.
                        &loc_error                                                                  // Error code.
                       );

    baseline->check_error (loc_error);                                                              // Checking returned error code...

    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               (cl_uint)loc_layout_index,                                                           // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  baseline->done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// setarg "int2" overload ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void kernel::setarg
(
 int2*   loc_data,                                                                                  // int2 data.
 cl_uint loc_layout_index                                                                           // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Creating OpenCL memory buffer:
    loc_data->buffer = clCreateBuffer
                       (
                        baseline->context_id,                                                       // OpenCL context.
                        CL_MEM_READ_WRITE |                                                         // Memory flag.
                        CL_MEM_COPY_HOST_PTR,                                                       // Memory flag.
                        sizeof(int2_structure)*loc_data->size,                                      // Data buffer size.
                        loc_data->data,                                                             // Data buffer.
                        &loc_error                                                                  // Error code.
                       );

    baseline->check_error (loc_error);                                                              // Checking returned error code...

    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               (cl_uint)loc_layout_index,                                                           // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  baseline->done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// setarg "int3" overload ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void kernel::setarg
(
 int3*   loc_data,                                                                                  // int3 data.
 cl_uint loc_layout_index                                                                           // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Creating OpenCL memory buffer:
    loc_data->buffer = clCreateBuffer
                       (
                        baseline->context_id,                                                       // OpenCL context.
                        CL_MEM_READ_WRITE |                                                         // Memory flag.
                        CL_MEM_COPY_HOST_PTR,                                                       // Memory flag.
                        sizeof(int3_structure)*loc_data->size,                                      // Data buffer size.
                        loc_data->data,                                                             // Data buffer.
                        &loc_error                                                                  // Error code.
                       );

    baseline->check_error (loc_error);                                                              // Checking returned error code...

    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               (cl_uint)loc_layout_index,                                                           // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  baseline->done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// setarg "int4" overload ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void kernel::setarg
(
 int4*   loc_data,                                                                                  // int4 data.
 cl_uint loc_layout_index                                                                           // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Creating OpenCL memory buffer:
    loc_data->buffer = clCreateBuffer
                       (
                        baseline->context_id,                                                       // OpenCL context.
                        CL_MEM_READ_WRITE |                                                         // Memory flag.
                        CL_MEM_COPY_HOST_PTR,                                                       // Memory flag.
                        sizeof(int4_structure)*loc_data->size,                                      // Data buffer size.
                        loc_data->data,                                                             // Data buffer.
                        &loc_error                                                                  // Error code.
                       );

    baseline->check_error (loc_error);                                                              // Checking returned error code...

    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               (cl_uint)loc_layout_index,                                                           // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  baseline->done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// setarg "float1" overload ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void kernel::setarg
(
 float1* loc_data,                                                                                  // float1 data.
 cl_uint loc_layout_index                                                                           // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Creating OpenCL memory buffer:
    loc_data->buffer = clCreateBuffer
                       (
                        baseline->context_id,                                                       // OpenCL context.
                        CL_MEM_READ_WRITE |                                                         // Memory flag.
                        CL_MEM_COPY_HOST_PTR,                                                       // Memory flag.
                        sizeof(cl_float)*loc_data->size,                                            // Data buffer size.
                        loc_data->data,                                                             // Data buffer.
                        &loc_error                                                                  // Error code.
                       );

    baseline->check_error (loc_error);                                                              // Checking returned error code...

    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               (cl_uint)loc_layout_index,                                                           // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  baseline->done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// setarg "float1G" overload ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void kernel::setarg
(
 float1G* loc_data,                                                                                 // float1G data.
 GLuint   loc_layout_index                                                                          // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(baseline->interop)                                                                             // Checking for interoperability...
  {
    if(!loc_data->ready)
    {
      // Generating VAO...
      glGenVertexArrays
      (
       1,                                                                                           // Number of VAOs to generate.
       &loc_data->vao                                                                               // VAOs array.
      );

      // Binding node VAO...
      glBindVertexArray
      (
       loc_data->vao                                                                                // VAOs array.
      );

      // Generating VBO:
      glGenBuffers
      (
       1,                                                                                           // Number of VBOs to generate.
       &loc_data->vbo                                                                               // VBOs array.
      );

      // Binding VBO:
      glBindBuffer
      (
       GL_ARRAY_BUFFER,                                                                             // VBO target.
       loc_data->vbo                                                                                // VBO to bind.
      );

      // Creating and initializing a buffer object's data store:
      glBufferData
      (
       GL_ARRAY_BUFFER,                                                                             // VBO target.
       sizeof(GLfloat)*loc_data->size,                                                              // VBO size.
       loc_data->data,                                                                              // VBO data.
       GL_DYNAMIC_DRAW                                                                              // VBO usage.
      );

      // Specifying the format for attribute in vertex shader:
      glVertexAttribPointer
      (
       loc_layout_index,                                                                            // VAO index.
       1,                                                                                           // VAO's number of components.
       GL_FLOAT,                                                                                    // Data type.
       GL_FALSE,                                                                                    // Not using normalized numbers.
       0,                                                                                           // Data stride.
       0                                                                                            // Data offset.
      );

      // Enabling attribute in vertex shader:
      glEnableVertexAttribArray
      (
       loc_layout_index                                                                             // VAO index.
      );

      // Binding VBO:
      glBindBuffer
      (
       GL_ARRAY_BUFFER,                                                                             // VBO target.
       loc_data->vbo                                                                                // VBO to bind.
      );

      glFinish ();                                                                                  // Waiting for OpenGL to finish...

      // Creating OpenCL buffer from OpenGL buffer:
      loc_data->buffer = clCreateFromGLBuffer
                         (
                          baseline->context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE,                                                        // Memory flags.
                          loc_data->vbo,                                                            // VBO.
                          &loc_error                                                                // Returned error.
                         );

      loc_data->ready  = true;                                                                      // Setting "ready" flag...
    }

    loc_error = clSetKernelArg
                (
                 kernel_id,                                                                         // Kernel id.
                 loc_layout_index,                                                                  // Layout index.
                 sizeof(cl_mem),                                                                    // Data size.
                 &loc_data->buffer                                                                  // Data value.
                );

    baseline->check_error (loc_error);                                                              // Checking returned error code...

    baseline->done ();                                                                              // Printing message...
  }
  else
  {
    if(!loc_data->ready)
    {
      // Creating OpenCL memory buffer:
      loc_data->buffer = clCreateBuffer
                         (
                          baseline->context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE |                                                       // Memory flag.
                          CL_MEM_COPY_HOST_PTR,                                                     // Memory flag.
                          sizeof(cl_float)*loc_data->size,                                          // Data buffer size.
                          loc_data->data,                                                           // Data buffer.
                          &loc_error                                                                // Error code.
                         );

      baseline->check_error (loc_error);                                                            // Checking returned error code...

      loc_data->ready = true;                                                                       // Setting "ready" flag...
    }

    loc_error = clSetKernelArg
                (
                 kernel_id,                                                                         // Kernel id.
                 (cl_uint)loc_layout_index,                                                         // Layout index.
                 sizeof(cl_mem),                                                                    // Data size.
                 &loc_data->buffer                                                                  // Data value.
                );

    baseline->done ();                                                                              // Printing message...
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// setarg "float2" overload /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void kernel::setarg
(
 float2* loc_data,                                                                                  // float2 data.
 cl_uint loc_layout_index                                                                           // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Creating OpenCL memory buffer:
    loc_data->buffer = clCreateBuffer
                       (
                        baseline->context_id,                                                       // OpenCL context.
                        CL_MEM_READ_WRITE |                                                         // Memory flag.
                        CL_MEM_COPY_HOST_PTR,                                                       // Memory flag.
                        sizeof(float2_structure)*loc_data->size,                                    // Data buffer size.
                        loc_data->data,                                                             // Data buffer.
                        &loc_error                                                                  // Error code.
                       );

    baseline->check_error (loc_error);                                                              // Checking returned error code...

    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               (cl_uint)loc_layout_index,                                                           // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  baseline->done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// setarg "float3" overload /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void kernel::setarg
(
 float3* loc_data,                                                                                  // float3 data.
 cl_uint loc_layout_index                                                                           // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Creating OpenCL memory buffer:
    loc_data->buffer = clCreateBuffer
                       (
                        baseline->context_id,                                                       // OpenCL context.
                        CL_MEM_READ_WRITE |                                                         // Memory flag.
                        CL_MEM_COPY_HOST_PTR,                                                       // Memory flag.
                        sizeof(float3_structure)*loc_data->size,                                    // Data buffer size.
                        loc_data->data,                                                             // Data buffer.
                        &loc_error                                                                  // Error code.
                       );

    baseline->check_error (loc_error);                                                              // Checking returned error code...

    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               (cl_uint)loc_layout_index,                                                           // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  baseline->done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// setarg "float4" overload /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void kernel::setarg
(
 float4* loc_data,                                                                                  // float4 data.
 cl_uint loc_layout_index                                                                           // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Creating OpenCL memory buffer:
    loc_data->buffer = clCreateBuffer
                       (
                        baseline->context_id,                                                       // OpenCL context.
                        CL_MEM_READ_WRITE |                                                         // Memory flag.
                        CL_MEM_COPY_HOST_PTR,                                                       // Memory flag.
                        sizeof(float4_structure)*loc_data->size,                                    // Data buffer size.
                        loc_data->data,                                                             // Data buffer.
                        &loc_error                                                                  // Error code.
                       );

    baseline->check_error (loc_error);                                                              // Checking returned error code...

    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               (cl_uint)loc_layout_index,                                                           // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  baseline->done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// setarg "float4G" overload /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void kernel::setarg
(
 float4G* loc_data,                                                                                 // float4G data.
 GLuint   loc_layout_index                                                                          // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(baseline->interop)                                                                             // Checking for interoperability...
  {
    if(!loc_data->ready)
    {
      // Generating VAO...
      glGenVertexArrays
      (
       1,                                                                                           // Number of VAOs to generate.
       &loc_data->vao                                                                               // VAOs array.
      );

      // Binding node VAO...
      glBindVertexArray
      (
       loc_data->vao                                                                                // VAOs array.
      );

      // Generating VBO:
      glGenBuffers
      (
       1,                                                                                           // Number of VBOs to generate.
       &loc_data->vbo                                                                               // VBOs array.
      );

      // Binding VBO:
      glBindBuffer
      (
       GL_ARRAY_BUFFER,                                                                             // VBO target.
       loc_data->vbo                                                                                // VBO to bind.
      );

      // Creating and initializing a buffer object's data store:
      glBufferData
      (
       GL_ARRAY_BUFFER,                                                                             // VBO target.
       sizeof(float4G_structure)*loc_data->size,                                                    // VBO size.
       loc_data->data,                                                                              // VBO data.
       GL_DYNAMIC_DRAW                                                                              // VBO usage.
      );

      // Specifying the format for attribute in vertex shader:
      glVertexAttribPointer
      (
       loc_layout_index,                                                                            // VAO index.
       4,                                                                                           // VAO's number of components.
       GL_FLOAT,                                                                                    // Data type.
       GL_FALSE,                                                                                    // Not using normalized numbers.
       0,                                                                                           // Data stride.
       0                                                                                            // Data offset.
      );

      // Enabling attribute in vertex shader:
      glEnableVertexAttribArray
      (
       loc_layout_index                                                                             // VAO index.
      );

      // Binding VBO:
      glBindBuffer
      (
       GL_ARRAY_BUFFER,                                                                             // VBO target.
       loc_data->vbo                                                                                // VBO to bind.
      );

      glFinish ();                                                                                  // Waiting for OpenGL to finish...

      // Creating OpenCL buffer from OpenGL buffer:
      loc_data->buffer = clCreateFromGLBuffer
                         (
                          baseline->context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE,                                                        // Memory flags.
                          loc_data->vbo,                                                            // VBO.
                          &loc_error                                                                // Returned error.
                         );

      loc_data->ready  = true;                                                                      // Setting "ready" flag...
    }

    loc_error = clSetKernelArg
                (
                 kernel_id,                                                                         // Kernel id.
                 loc_layout_index,                                                                  // Layout index.
                 sizeof(cl_mem),                                                                    // Data size.
                 &loc_data->buffer                                                                  // Data value.
                );

    baseline->check_error (loc_error);                                                              // Checking returned error code...

    baseline->done ();                                                                              // Printing message...
  }
  else
  {
    if(!loc_data->ready)
    {
      // Generating VAO...
      glGenVertexArrays
      (
       1,                                                                                           // Number of VAOs to generate.
       &loc_data->vao                                                                               // VAOs array.
      );

      // Binding node VAO...
      glBindVertexArray
      (
       loc_data->vao                                                                                // VAOs array.
      );

      // Generating VBO:
      glGenBuffers
      (
       1,                                                                                           // Number of VBOs to generate.
       &loc_data->vbo                                                                               // VBOs array.
      );

      // Binding VBO:
      glBindBuffer
      (
       GL_ARRAY_BUFFER,                                                                             // VBO target.
       loc_data->vbo                                                                                // VBO to bind.
      );

      // Creating and initializing a buffer object's data store:
      glBufferData
      (
       GL_ARRAY_BUFFER,                                                                             // VBO target.
       sizeof(float4G_structure)*loc_data->size,                                                    // VBO size.
       loc_data->data,                                                                              // VBO data.
       GL_DYNAMIC_DRAW                                                                              // VBO usage.
      );

      // Specifying the format for attribute in vertex shader:
      glVertexAttribPointer
      (
       loc_layout_index,                                                                            // VAO index.
       4,                                                                                           // VAO's number of components.
       GL_FLOAT,                                                                                    // Data type.
       GL_FALSE,                                                                                    // Not using normalized numbers.
       0,                                                                                           // Data stride.
       0                                                                                            // Data offset.
      );

      // Enabling attribute in vertex shader:
      glEnableVertexAttribArray
      (
       loc_layout_index                                                                             // VAO index.
      );

      // Binding VBO:
      glBindBuffer
      (
       GL_ARRAY_BUFFER,                                                                             // VBO target.
       loc_data->vbo                                                                                // VBO to bind.
      );

      glFinish ();                                                                                  // Waiting for OpenGL to finish...

      // Creating OpenCL memory buffer:
      loc_data->buffer = clCreateBuffer
                         (
                          baseline->context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE |                                                       // Memory flag.
                          CL_MEM_COPY_HOST_PTR,                                                     // Memory flag.
                          sizeof(float4_structure)*loc_data->size,                                  // Data buffer size.
                          loc_data->data,                                                           // Data buffer.
                          &loc_error                                                                // Error code.
                         );

      baseline->check_error (loc_error);                                                            // Checking returned error code...

      loc_data->ready = true;                                                                       // Setting "ready" flag...
    }

    loc_error = clSetKernelArg
                (
                 kernel_id,                                                                         // Kernel id.
                 (cl_uint)loc_layout_index,                                                         // Layout index.
                 sizeof(cl_mem),                                                                    // Data size.
                 &loc_data->buffer                                                                  // Data value.
                );

    baseline->check_error (loc_error);                                                              // Checking returned error code...

    baseline->done ();                                                                              // Printing message...
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// DESTRUCTOR ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
kernel::~kernel()
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  baseline->action ("releasing OpenCL kernel...");                                                  // Printing message...
  loc_error = clReleaseKernel (kernel_id);                                                          // Releasing OpenCL kernel...
  baseline->check_error (loc_error);                                                                // Checking error code...
  baseline->done ();                                                                                // Printing message...

  baseline->action ("releasing OpenCL kernel event...");                                            // Printing message...
  loc_error = clReleaseEvent (event);                                                               // Releasing OpenCL event...
  baseline->check_error (loc_error);                                                                // Checking error code...
  baseline->done ();                                                                                // Printing message...

  baseline->action ("releasing OpenCL program...");                                                 // Printing message...
  loc_error = clReleaseProgram (program);                                                           // Releasing OpenCL program...
  baseline->check_error (loc_error);                                                                // Checking error code...
  baseline->done ();                                                                                // Printing message...

  baseline->action ("releasing device ID array...");                                                // Printing message...
  delete[] device_id;                                                                               // Deleting device ID array...
  baseline->done ();                                                                                // Printing message...
}
