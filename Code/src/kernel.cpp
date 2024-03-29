/// @file     kernel.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definition of an OpenCL "kernel" class.

#include "kernel.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// "kernel" class ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu::kernel::kernel ()
{
  program          = NULL;                                                                          // Initializing kernel program...
  size_i           = 0;                                                                             // Initializing kernel size (i-index)...
  size_j           = 0;                                                                             // Initializing kernel size (j-index)...
  size_k           = 0;                                                                             // Initializing kernel size (k-index)...
  event            = NULL;                                                                          // Initializing kernel event...
  kernel_id        = NULL;                                                                          // Initializing kernel id...

  neutrino::action ("initializing OpenCL kernel object...");                                        // Printing message...
  compiler_options = "";                                                                            // Setting no options...
  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// addsource /////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::kernel::addsource (
                            std::string loc_kernel_file_name                                        // OpenCL kernel file name.
                           )
{
  std::string loc_kernel_source;

  neutrino::action ("loading OpenCL kernel source from file...");                                   // Printing message...
  loc_kernel_source  = neutrino::read_file (loc_kernel_file_name);                                  // Loading kernel source...
  loc_kernel_source += '\n';                                                                        // Appending \n...
  kernel_source.push_back (loc_kernel_source);                                                      // Adding kernel source...
  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// build ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::kernel::build (
                        size_t loc_kernel_size_i,                                                   // OpenCL kernel size (i-index).
                        size_t loc_kernel_size_j,                                                   // OpenCL kernel size (j-index).
                        size_t loc_kernel_size_k                                                    // OpenCL kernel size (k-index).
                       )
{
  cl_int  loc_error;                                                                                // Error code.
  char*   loc_options;                                                                              // Options temporary char buffer.
  char**  loc_kernel_source;                                                                        // Source file temporary char buffer.
  size_t* loc_kernel_source_size;                                                                   // Source file as string.
  size_t  loc_log_size;                                                                             // OpenCL JIT compiler log size.
  GLuint  i;                                                                                        // Index.
  size_i                                = loc_kernel_size_i;                                        // Getting OpenCL kernel size (i-index)...
  size_j                                = loc_kernel_size_j;                                        // Getting OpenCL kernel size (j-index)...
  size_k                                = loc_kernel_size_k;                                        // Getting OpenCL kernel size (k-index)...

  loc_options                           = new char[compiler_options.size () + 1]();                 // Building temporary options char buffer...
  loc_options[compiler_options.size ()] = '\0';                                                     // Null terminating options string...
  compiler_options.copy (loc_options, compiler_options.size ());                                    // Building options string...
  loc_kernel_source_size                = new size_t[kernel_source.size ()]();                      // Building temporary kernel source char buffer size...
  loc_kernel_source                     = new char*[kernel_source.size ()]();                       // Building temporary kernel source char buffer...

  neutrino::action ("linking OpenCL kernel sources...");                                            // Printing message...

  for(i = 0; i < kernel_source.size (); i++)
  {
    loc_kernel_source_size[i] = kernel_source[i].size ();                                           // Getting source size...
    loc_kernel_source[i]      = new char[loc_kernel_source_size[i]]();                              // Building temporary source char buffer...
    kernel_source[i].copy (loc_kernel_source[i], kernel_source[i].size ());                         // Building string source buffer...
  }

  neutrino::done ();                                                                                // Printing message...

  neutrino::action ("creating OpenCL program from kernel sources...");                              // Printing message...
  program = clCreateProgramWithSource
            (
             neutrino::context_id,                                                                  // OpenCL context ID.
             (cl_uint)kernel_source.size (),                                                        // Number of program sources.
             (const char**)loc_kernel_source,                                                       // Program source.
             loc_kernel_source_size,                                                                // Source size.
             &loc_error                                                                             // Error code.
            );
  neutrino::check_error (loc_error);                                                                // Checking error...
  neutrino::done ();                                                                                // Printing message...

  delete[] loc_kernel_source;                                                                       // Deleting buffer...
  delete loc_kernel_source_size;                                                                    // Deleting buffer...

  neutrino::action ("building OpenCL program...");                                                  // Printing message...

  // Creating device ID list:
  device_id    = new cl_device_id[1];                                                               // OpenCL device ID.
  device_id[0] = neutrino::device_id;                                                               // Getting device ID.

  // Building OpenCL program:
  loc_error    = clBuildProgram
                 (
                  program,                                                                          // Program.
                  1,                                                                                // Number of devices.
                  device_id,                                                                        // Device ID.
                  loc_options,                                                                      // Including header files from kernel's directory.
                  NULL,                                                                             // Notification routine.
                  NULL                                                                              // Notification argument.
                 );

  delete loc_options;

  if(loc_error != CL_SUCCESS)                                                                       // Checking compiled kernel...
  {
    neutrino::error (neutrino::get_error (loc_error));                                              // Printing message...

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

    char* loc_log_buffer = new char[loc_log_size + 1]();                                            // Allocating log buffer...

    // Reading OpenCL compiler error log:
    loc_error    = clGetProgramBuildInfo
                   (
                    program,                                                                        // Program.
                    device_id[0],                                                                   // Device ID.
                    CL_PROGRAM_BUILD_LOG,                                                           // Build log parameter.
                    loc_log_size + 1,                                                               // Log size.
                    loc_log_buffer,                                                                 // The log.
                    NULL                                                                            // Dummy size parameter.
                   );

    compiler_log = loc_log_buffer;                                                                  // Setting compiler log...
    std::cout << "" << std::endl;                                                                   // Printing message...
    std::cout << "See error log:" << std::endl;                                                     // Printing message...
    std::cout << "" << std::endl;                                                                   // Printing message...
    std::cout << compiler_log << std::endl;                                                         // Printing log...
    delete[] (loc_log_buffer);                                                                      // Deleting log buffer...
    exit (loc_error);                                                                               // Exiting...
  }

  neutrino::done ();                                                                                // Printing message...

  neutrino::action ("generating OpenCL kernel ID...");                                              // Printing message...

  // Creating OpenCL kernel:
  kernel_id = clCreateKernel
              (
               program,                                                                             // OpenCL kernel program.
               NU_KERNEL_NAME,                                                                      // Kernel name.
               &loc_error                                                                           // Error code.
              );

  neutrino::check_error (loc_error);                                                                // Checking error...

  neutrino::done ();                                                                                // Printing message...

  // Pushing kernel object:
  neutrino::action ("pushing OpenCL kernel ID...");                                                 // Printing message...
  neutrino::kernel_id.push_back (kernel_id);                                                        // Pushing kernel object...
  neutrino::done ();                                                                                // Printing message...

  // Setting kernel arguments:
  for(i = 0; i < neutrino::container.size (); i++)
  {
    switch(container[i]->type)
    {
      case NU_INT:
        ((nu::int1*)neutrino::container[i])->name    = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::int1*)neutrino::container[i], i);
        break;

      case NU_INT2:
        ((nu::int2*)neutrino::container[i])->name    = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::int2*)neutrino::container[i], i);
        break;

      case NU_INT3:
        ((nu::int3*)neutrino::container[i])->name    = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::int3*)neutrino::container[i], i);
        break;

      case NU_INT4:
        ((nu::int4*)neutrino::container[i])->name    = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::int4*)neutrino::container[i], i);
        break;

      case NU_FLOAT:
        ((nu::float1*)neutrino::container[i])->name  = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::float1*)neutrino::container[i], i);
        break;

      case NU_FLOAT2:
        ((nu::float2*)neutrino::container[i])->name  = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::float2*)neutrino::container[i], i);
        break;

      case NU_FLOAT3:
        ((nu::float3*)neutrino::container[i])->name  = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::float3*)neutrino::container[i], i);
        break;

      case NU_FLOAT4:
        ((nu::float4*)neutrino::container[i])->name  = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::float4*)neutrino::container[i], i);
        break;

      case NU_FLOAT16:
        ((nu::float16*)neutrino::container[i])->name = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::float16*)neutrino::container[i], i);
        break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// setarg "nu::int1" overload ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::kernel::setarg
(
 nu::int1* loc_data,                                                                                // nu::int1 data.
 cl_uint   loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  neutrino::action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Generating VAO...
    glGenVertexArrays
    (
     1,                                                                                             // Number of VAOs to generate.
     &loc_data->vao                                                                                 // VAOs array.
    );

    // Binding node VAO...
    glBindVertexArray
    (
     loc_data->vao                                                                                  // VAOs array.
    );

    // Generating SSBO:
    glGenBuffers
    (
     1,                                                                                             // Number of SSBOs to generate.
     &loc_data->ssbo                                                                                // SSBOs array.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    // Creating and initializing a buffer object's data store:
    glBufferData
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     sizeof(GL_INT)*loc_data->data.size (),                                                         // SSBO size.
     loc_data->data.data (),                                                                        // SSBO data.
     GL_DYNAMIC_DRAW                                                                                // SSBO usage.
    );

    // Binding buffer object to an indexed buffer target:
    glBindBufferBase (
                      GL_SHADER_STORAGE_BUFFER,                                                     // SSBO target.
                      loc_layout_index,                                                             // SSBO index.
                      loc_data->ssbo                                                                // SSBO buffer.
                     );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer
    (
     loc_layout_index,                                                                              // VAO index.
     1,                                                                                             // VAO's number of components.
     GL_FLOAT,                                                                                      // Data type.
     GL_FALSE,                                                                                      // Not using normalized numbers.
     0,                                                                                             // Data stride.
     0                                                                                              // Data offset.
    );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray
    (
     loc_layout_index                                                                               // VAO index.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    glFinish ();                                                                                    // Waiting for OpenGL to finish...

    if(neutrino::interop)                                                                           // Checking for interoperability...
    {
      // Creating OpenCL buffer from OpenGL buffer:
      loc_data->buffer = clCreateFromGLBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE,                                                        // Memory flags.
                          loc_data->ssbo,                                                           // VBO.
                          &loc_error                                                                // Returned error.
                         );
    }

    else
    {
      // Creating OpenCL memory buffer:
      loc_data->buffer = clCreateBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE |                                                       // Memory flag.
                          CL_MEM_COPY_HOST_PTR,                                                     // Memory flag.
                          sizeof(GL_INT)*loc_data->data.size (),                                    // Data buffer size.
                          loc_data->data.data (),                                                   // Data buffer.
                          &loc_error                                                                // Error code.
                         );
    }

    neutrino::check_error (loc_error);                                                              // Checking returned error code...
    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               loc_layout_index,                                                                    // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  neutrino::check_error (loc_error);                                                                // Checking returned error code...
  clFinish (neutrino::queue_id);                                                                    // Waiting for OpenCL to finish...
  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// setarg "nu::int2" overload ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::kernel::setarg
(
 nu::int2* loc_data,                                                                                // nu::int2 data.
 cl_uint   loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  neutrino::action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Generating VAO...
    glGenVertexArrays
    (
     1,                                                                                             // Number of VAOs to generate.
     &loc_data->vao                                                                                 // VAOs array.
    );

    // Binding node VAO...
    glBindVertexArray
    (
     loc_data->vao                                                                                  // VAOs array.
    );

    // Generating SSBO:
    glGenBuffers
    (
     1,                                                                                             // Number of SSBOs to generate.
     &loc_data->ssbo                                                                                // SSBOs array.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    // Creating and initializing a buffer object's data store:
    glBufferData
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     sizeof(nu_int2_structure)*loc_data->data.size (),                                              // SSBO size.
     loc_data->data.data (),                                                                        // SSBO data.
     GL_DYNAMIC_DRAW                                                                                // SSBO usage.
    );

    // Binding buffer object to an indexed buffer target:
    glBindBufferBase (
                      GL_SHADER_STORAGE_BUFFER,                                                     // SSBO target.
                      loc_layout_index,                                                             // SSBO index.
                      loc_data->ssbo                                                                // SSBO buffer.
                     );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer
    (
     loc_layout_index,                                                                              // VAO index.
     1,                                                                                             // VAO's number of components.
     GL_FLOAT,                                                                                      // Data type.
     GL_FALSE,                                                                                      // Not using normalized numbers.
     0,                                                                                             // Data stride.
     0                                                                                              // Data offset.
    );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray
    (
     loc_layout_index                                                                               // VAO index.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    glFinish ();                                                                                    // Waiting for OpenGL to finish...

    if(neutrino::interop)                                                                           // Checking for interoperability...
    {
      // Creating OpenCL buffer from OpenGL buffer:
      loc_data->buffer = clCreateFromGLBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE,                                                        // Memory flags.
                          loc_data->ssbo,                                                           // VBO.
                          &loc_error                                                                // Returned error.
                         );
    }

    else
    {
      // Creating OpenCL memory buffer:
      loc_data->buffer = clCreateBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE |                                                       // Memory flag.
                          CL_MEM_COPY_HOST_PTR,                                                     // Memory flag.
                          sizeof(nu_int2_structure)*loc_data->data.size (),                         // Data buffer size.
                          loc_data->data.data (),                                                   // Data buffer.
                          &loc_error                                                                // Error code.
                         );
    }

    neutrino::check_error (loc_error);                                                              // Checking returned error code...
    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               loc_layout_index,                                                                    // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  neutrino::check_error (loc_error);                                                                // Checking returned error code...
  clFinish (neutrino::queue_id);                                                                    // Waiting for OpenCL to finish...
  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// setarg "nu::int3" overload ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::kernel::setarg
(
 nu::int3* loc_data,                                                                                // nu::int3 data.
 cl_uint   loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  neutrino::action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Generating VAO...
    glGenVertexArrays
    (
     1,                                                                                             // Number of VAOs to generate.
     &loc_data->vao                                                                                 // VAOs array.
    );

    // Binding node VAO...
    glBindVertexArray
    (
     loc_data->vao                                                                                  // VAOs array.
    );

    // Generating SSBO:
    glGenBuffers
    (
     1,                                                                                             // Number of SSBOs to generate.
     &loc_data->ssbo                                                                                // SSBOs array.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    // Creating and initializing a buffer object's data store:
    glBufferData
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     sizeof(nu_int3_structure)*loc_data->data.size (),                                              // SSBO size.
     loc_data->data.data (),                                                                        // SSBO data.
     GL_DYNAMIC_DRAW                                                                                // SSBO usage.
    );

    // Binding buffer object to an indexed buffer target:
    glBindBufferBase (
                      GL_SHADER_STORAGE_BUFFER,                                                     // SSBO target.
                      loc_layout_index,                                                             // SSBO index.
                      loc_data->ssbo                                                                // SSBO buffer.
                     );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer
    (
     loc_layout_index,                                                                              // VAO index.
     1,                                                                                             // VAO's number of components.
     GL_FLOAT,                                                                                      // Data type.
     GL_FALSE,                                                                                      // Not using normalized numbers.
     0,                                                                                             // Data stride.
     0                                                                                              // Data offset.
    );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray
    (
     loc_layout_index                                                                               // VAO index.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    glFinish ();                                                                                    // Waiting for OpenGL to finish...

    if(neutrino::interop)                                                                           // Checking for interoperability...
    {
      // Creating OpenCL buffer from OpenGL buffer:
      loc_data->buffer = clCreateFromGLBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE,                                                        // Memory flags.
                          loc_data->ssbo,                                                           // VBO.
                          &loc_error                                                                // Returned error.
                         );
    }

    else
    {
      // Creating OpenCL memory buffer:
      loc_data->buffer = clCreateBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE |                                                       // Memory flag.
                          CL_MEM_COPY_HOST_PTR,                                                     // Memory flag.
                          sizeof(nu_int3_structure)*loc_data->data.size (),                         // Data buffer size.
                          loc_data->data.data (),                                                   // Data buffer.
                          &loc_error                                                                // Error code.
                         );
    }

    neutrino::check_error (loc_error);                                                              // Checking returned error code...
    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               loc_layout_index,                                                                    // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  neutrino::check_error (loc_error);                                                                // Checking returned error code...
  clFinish (neutrino::queue_id);                                                                    // Waiting for OpenCL to finish...
  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// setarg "nu::int4" overload ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::kernel::setarg
(
 nu::int4* loc_data,                                                                                // nu::int4 data.
 cl_uint   loc_layout_index                                                                         // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  neutrino::action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Generating VAO...
    glGenVertexArrays
    (
     1,                                                                                             // Number of VAOs to generate.
     &loc_data->vao                                                                                 // VAOs array.
    );

    // Binding node VAO...
    glBindVertexArray
    (
     loc_data->vao                                                                                  // VAOs array.
    );

    // Generating SSBO:
    glGenBuffers
    (
     1,                                                                                             // Number of SSBOs to generate.
     &loc_data->ssbo                                                                                // SSBOs array.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    // Creating and initializing a buffer object's data store:
    glBufferData
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     sizeof(nu_int4_structure)*loc_data->data.size (),                                              // SSBO size.
     loc_data->data.data (),                                                                        // SSBO data.
     GL_DYNAMIC_DRAW                                                                                // SSBO usage.
    );

    // Binding buffer object to an indexed buffer target:
    glBindBufferBase (
                      GL_SHADER_STORAGE_BUFFER,                                                     // SSBO target.
                      loc_layout_index,                                                             // SSBO index.
                      loc_data->ssbo                                                                // SSBO buffer.
                     );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer
    (
     loc_layout_index,                                                                              // VAO index.
     1,                                                                                             // VAO's number of components.
     GL_FLOAT,                                                                                      // Data type.
     GL_FALSE,                                                                                      // Not using normalized numbers.
     0,                                                                                             // Data stride.
     0                                                                                              // Data offset.
    );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray
    (
     loc_layout_index                                                                               // VAO index.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    glFinish ();                                                                                    // Waiting for OpenGL to finish...

    if(neutrino::interop)                                                                           // Checking for interoperability...
    {
      // Creating OpenCL buffer from OpenGL buffer:
      loc_data->buffer = clCreateFromGLBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE,                                                        // Memory flags.
                          loc_data->ssbo,                                                           // VBO.
                          &loc_error                                                                // Returned error.
                         );
    }

    else
    {
      // Creating OpenCL memory buffer:
      loc_data->buffer = clCreateBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE |                                                       // Memory flag.
                          CL_MEM_COPY_HOST_PTR,                                                     // Memory flag.
                          sizeof(nu_int4_structure)*loc_data->data.size (),                         // Data buffer size.
                          loc_data->data.data (),                                                   // Data buffer.
                          &loc_error                                                                // Error code.
                         );
    }

    neutrino::check_error (loc_error);                                                              // Checking returned error code...
    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               loc_layout_index,                                                                    // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  neutrino::check_error (loc_error);                                                                // Checking returned error code...
  clFinish (neutrino::queue_id);                                                                    // Waiting for OpenCL to finish...
  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// setarg "nu::float1" overload ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::kernel::setarg
(
 nu::float1* loc_data,                                                                              // nu::float1 data.
 GLuint      loc_layout_index                                                                       // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  neutrino::action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Generating VAO...
    glGenVertexArrays
    (
     1,                                                                                             // Number of VAOs to generate.
     &loc_data->vao                                                                                 // VAOs array.
    );

    // Binding node VAO...
    glBindVertexArray
    (
     loc_data->vao                                                                                  // VAOs array.
    );

    // Generating SSBO:
    glGenBuffers
    (
     1,                                                                                             // Number of SSBOs to generate.
     &loc_data->ssbo                                                                                // SSBOs array.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    // Creating and initializing a buffer object's data store:
    glBufferData
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     sizeof(GL_FLOAT)*loc_data->data.size (),                                                       // SSBO size.
     loc_data->data.data (),                                                                        // SSBO data.
     GL_DYNAMIC_DRAW                                                                                // SSBO usage.
    );

    // Binding buffer object to an indexed buffer target:
    glBindBufferBase (
                      GL_SHADER_STORAGE_BUFFER,                                                     // SSBO target.
                      loc_layout_index,                                                             // SSBO index.
                      loc_data->ssbo                                                                // SSBO buffer.
                     );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer
    (
     loc_layout_index,                                                                              // VAO index.
     1,                                                                                             // VAO's number of components.
     GL_FLOAT,                                                                                      // Data type.
     GL_FALSE,                                                                                      // Not using normalized numbers.
     0,                                                                                             // Data stride.
     0                                                                                              // Data offset.
    );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray
    (
     loc_layout_index                                                                               // VAO index.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    glFinish ();                                                                                    // Waiting for OpenGL to finish...

    if(neutrino::interop)                                                                           // Checking for interoperability...
    {
      // Creating OpenCL buffer from OpenGL buffer:
      loc_data->buffer = clCreateFromGLBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE,                                                        // Memory flags.
                          loc_data->ssbo,                                                           // VBO.
                          &loc_error                                                                // Returned error.
                         );
    }

    else
    {
      // Creating OpenCL memory buffer:
      loc_data->buffer = clCreateBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE |                                                       // Memory flag.
                          CL_MEM_COPY_HOST_PTR,                                                     // Memory flag.
                          sizeof(GL_FLOAT)*loc_data->data.size (),                                  // Data buffer size.
                          loc_data->data.data (),                                                   // Data buffer.
                          &loc_error                                                                // Error code.
                         );
    }

    neutrino::check_error (loc_error);                                                              // Checking returned error code...
    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               loc_layout_index,                                                                    // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  neutrino::check_error (loc_error);                                                                // Checking returned error code...
  clFinish (neutrino::queue_id);                                                                    // Waiting for OpenCL to finish...
  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// setarg "nu::float2" overload /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::kernel::setarg
(
 nu::float2* loc_data,                                                                              // nu::float2 data.
 cl_uint     loc_layout_index                                                                       // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  neutrino::action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Generating VAO...
    glGenVertexArrays
    (
     1,                                                                                             // Number of VAOs to generate.
     &loc_data->vao                                                                                 // VAOs array.
    );

    // Binding node VAO...
    glBindVertexArray
    (
     loc_data->vao                                                                                  // VAOs array.
    );

    // Generating SSBO:
    glGenBuffers
    (
     1,                                                                                             // Number of SSBOs to generate.
     &loc_data->ssbo                                                                                // SSBOs array.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    // Creating and initializing a buffer object's data store:
    glBufferData
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     sizeof(nu_float2_structure)*loc_data->data.size (),                                            // SSBO size.
     loc_data->data.data (),                                                                        // SSBO data.
     GL_DYNAMIC_DRAW                                                                                // SSBO usage.
    );

    // Binding buffer object to an indexed buffer target:
    glBindBufferBase (
                      GL_SHADER_STORAGE_BUFFER,                                                     // SSBO target.
                      loc_layout_index,                                                             // SSBO index.
                      loc_data->ssbo                                                                // SSBO buffer.
                     );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer
    (
     loc_layout_index,                                                                              // VAO index.
     1,                                                                                             // VAO's number of components.
     GL_FLOAT,                                                                                      // Data type.
     GL_FALSE,                                                                                      // Not using normalized numbers.
     0,                                                                                             // Data stride.
     0                                                                                              // Data offset.
    );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray
    (
     loc_layout_index                                                                               // VAO index.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    glFinish ();                                                                                    // Waiting for OpenGL to finish...

    if(neutrino::interop)                                                                           // Checking for interoperability...
    {
      // Creating OpenCL buffer from OpenGL buffer:
      loc_data->buffer = clCreateFromGLBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE,                                                        // Memory flags.
                          loc_data->ssbo,                                                           // VBO.
                          &loc_error                                                                // Returned error.
                         );
    }

    else
    {
      // Creating OpenCL memory buffer:
      loc_data->buffer = clCreateBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE |                                                       // Memory flag.
                          CL_MEM_COPY_HOST_PTR,                                                     // Memory flag.
                          sizeof(nu_float2_structure)*loc_data->data.size (),                       // Data buffer size.
                          loc_data->data.data (),                                                   // Data buffer.
                          &loc_error                                                                // Error code.
                         );
    }

    neutrino::check_error (loc_error);                                                              // Checking returned error code...
    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               loc_layout_index,                                                                    // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  neutrino::check_error (loc_error);                                                                // Checking returned error code...
  clFinish (neutrino::queue_id);                                                                    // Waiting for OpenCL to finish...
  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// setarg "nu::float3" overload ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::kernel::setarg
(
 nu::float3* loc_data,                                                                              // nu::float3 data.
 cl_uint     loc_layout_index                                                                       // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  neutrino::action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Generating VAO...
    glGenVertexArrays
    (
     1,                                                                                             // Number of VAOs to generate.
     &loc_data->vao                                                                                 // VAOs array.
    );

    // Binding node VAO...
    glBindVertexArray
    (
     loc_data->vao                                                                                  // VAOs array.
    );

    // Generating SSBO:
    glGenBuffers
    (
     1,                                                                                             // Number of SSBOs to generate.
     &loc_data->ssbo                                                                                // SSBOs array.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    // Creating and initializing a buffer object's data store:
    glBufferData
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     sizeof(nu_float3_structure)*loc_data->data.size (),                                            // SSBO size.
     loc_data->data.data (),                                                                        // SSBO data.
     GL_DYNAMIC_DRAW                                                                                // SSBO usage.
    );

    // Binding buffer object to an indexed buffer target:
    glBindBufferBase (
                      GL_SHADER_STORAGE_BUFFER,                                                     // SSBO target.
                      loc_layout_index,                                                             // SSBO index.
                      loc_data->ssbo                                                                // SSBO buffer.
                     );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer
    (
     loc_layout_index,                                                                              // VAO index.
     1,                                                                                             // VAO's number of components.
     GL_FLOAT,                                                                                      // Data type.
     GL_FALSE,                                                                                      // Not using normalized numbers.
     0,                                                                                             // Data stride.
     0                                                                                              // Data offset.
    );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray
    (
     loc_layout_index                                                                               // VAO index.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    glFinish ();                                                                                    // Waiting for OpenGL to finish...

    if(neutrino::interop)                                                                           // Checking for interoperability...
    {
      // Creating OpenCL buffer from OpenGL buffer:
      loc_data->buffer = clCreateFromGLBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE,                                                        // Memory flags.
                          loc_data->ssbo,                                                           // VBO.
                          &loc_error                                                                // Returned error.
                         );
    }

    else
    {
      // Creating OpenCL memory buffer:
      loc_data->buffer = clCreateBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE |                                                       // Memory flag.
                          CL_MEM_COPY_HOST_PTR,                                                     // Memory flag.
                          sizeof(nu_float3_structure)*loc_data->data.size (),                       // Data buffer size.
                          loc_data->data.data (),                                                   // Data buffer.
                          &loc_error                                                                // Error code.
                         );
    }

    neutrino::check_error (loc_error);                                                              // Checking returned error code...
    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               loc_layout_index,                                                                    // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  neutrino::check_error (loc_error);                                                                // Checking returned error code...
  clFinish (neutrino::queue_id);                                                                    // Waiting for OpenCL to finish...
  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// setarg "nu::float4" overload ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::kernel::setarg
(
 nu::float4* loc_data,                                                                              // nu::float4 data.
 cl_uint     loc_layout_index                                                                       // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  neutrino::action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Generating VAO...
    glGenVertexArrays
    (
     1,                                                                                             // Number of VAOs to generate.
     &loc_data->vao                                                                                 // VAOs array.
    );

    // Binding node VAO...
    glBindVertexArray
    (
     loc_data->vao                                                                                  // VAOs array.
    );

    // Generating SSBO:
    glGenBuffers
    (
     1,                                                                                             // Number of SSBOs to generate.
     &loc_data->ssbo                                                                                // SSBOs array.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    // Creating and initializing a buffer object's data store:
    glBufferData
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     sizeof(nu_float4_structure)*loc_data->data.size (),                                            // SSBO size.
     loc_data->data.data (),                                                                        // SSBO data.
     GL_DYNAMIC_DRAW                                                                                // SSBO usage.
    );

    // Binding buffer object to an indexed buffer target:
    glBindBufferBase (
                      GL_SHADER_STORAGE_BUFFER,                                                     // SSBO target.
                      loc_layout_index,                                                             // SSBO index.
                      loc_data->ssbo                                                                // SSBO buffer.
                     );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer
    (
     loc_layout_index,                                                                              // VAO index.
     1,                                                                                             // VAO's number of components.
     GL_FLOAT,                                                                                      // Data type.
     GL_FALSE,                                                                                      // Not using normalized numbers.
     0,                                                                                             // Data stride.
     0                                                                                              // Data offset.
    );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray
    (
     loc_layout_index                                                                               // VAO index.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    glFinish ();                                                                                    // Waiting for OpenGL to finish...

    if(neutrino::interop)                                                                           // Checking for interoperability...
    {
      // Creating OpenCL buffer from OpenGL buffer:
      loc_data->buffer = clCreateFromGLBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE,                                                        // Memory flags.
                          loc_data->ssbo,                                                           // VBO.
                          &loc_error                                                                // Returned error.
                         );
    }

    else
    {
      // Creating OpenCL memory buffer:
      loc_data->buffer = clCreateBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE |                                                       // Memory flag.
                          CL_MEM_COPY_HOST_PTR,                                                     // Memory flag.
                          sizeof(nu_float4_structure)*loc_data->data.size (),                       // Data buffer size.
                          loc_data->data.data (),                                                   // Data buffer.
                          &loc_error                                                                // Error code.
                         );
    }

    neutrino::check_error (loc_error);                                                              // Checking returned error code...
    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               loc_layout_index,                                                                    // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  neutrino::check_error (loc_error);                                                                // Checking returned error code...
  clFinish (neutrino::queue_id);                                                                    // Waiting for OpenCL to finish...
  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// setarg "nu::float16" overload //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::kernel::setarg
(
 nu::float16* loc_data,                                                                             // nu::float16 data.
 cl_uint      loc_layout_index                                                                      // Layout index.
)
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  neutrino::action ("setting kernel argument...");                                                  // Printing message...

  loc_data->layout = loc_layout_index;                                                              // Setting layout index.

  if(!loc_data->ready)
  {
    // Generating VAO...
    glGenVertexArrays
    (
     1,                                                                                             // Number of VAOs to generate.
     &loc_data->vao                                                                                 // VAOs array.
    );

    // Binding node VAO...
    glBindVertexArray
    (
     loc_data->vao                                                                                  // VAOs array.
    );

    // Generating SSBO:
    glGenBuffers
    (
     1,                                                                                             // Number of SSBOs to generate.
     &loc_data->ssbo                                                                                // SSBOs array.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    // Creating and initializing a buffer object's data store:
    glBufferData
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     sizeof(nu_float16_structure)*loc_data->data.size (),                                           // SSBO size.
     loc_data->data.data (),                                                                        // SSBO data.
     GL_DYNAMIC_DRAW                                                                                // SSBO usage.
    );

    // Binding buffer object to an indexed buffer target:
    glBindBufferBase (
                      GL_SHADER_STORAGE_BUFFER,                                                     // SSBO target.
                      loc_layout_index,                                                             // SSBO index.
                      loc_data->ssbo                                                                // SSBO buffer.
                     );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer
    (
     loc_layout_index,                                                                              // VAO index.
     1,                                                                                             // VAO's number of components.
     GL_FLOAT,                                                                                      // Data type.
     GL_FALSE,                                                                                      // Not using normalized numbers.
     0,                                                                                             // Data stride.
     0                                                                                              // Data offset.
    );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray
    (
     loc_layout_index                                                                               // VAO index.
    );

    // Binding SSBO:
    glBindBuffer
    (
     GL_SHADER_STORAGE_BUFFER,                                                                      // SSBO target.
     loc_data->ssbo                                                                                 // SSBO to bind.
    );

    glFinish ();                                                                                    // Waiting for OpenGL to finish...

    if(neutrino::interop)                                                                           // Checking for interoperability...
    {
      // Creating OpenCL buffer from OpenGL buffer:
      loc_data->buffer = clCreateFromGLBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE,                                                        // Memory flags.
                          loc_data->ssbo,                                                           // VBO.
                          &loc_error                                                                // Returned error.
                         );
    }

    else
    {
      // Creating OpenCL memory buffer:
      loc_data->buffer = clCreateBuffer
                         (
                          neutrino::context_id,                                                     // OpenCL context.
                          CL_MEM_READ_WRITE |                                                       // Memory flag.
                          CL_MEM_COPY_HOST_PTR,                                                     // Memory flag.
                          sizeof(nu_float16_structure)*loc_data->data.size (),                      // Data buffer size.
                          loc_data->data.data (),                                                   // Data buffer.
                          &loc_error                                                                // Error code.
                         );
    }

    neutrino::check_error (loc_error);                                                              // Checking returned error code...
    loc_data->ready = true;                                                                         // Setting "ready" flag...
  }

  loc_error = clSetKernelArg
              (
               kernel_id,                                                                           // Kernel id.
               loc_layout_index,                                                                    // Layout index.
               sizeof(cl_mem),                                                                      // Data size.
               &loc_data->buffer                                                                    // Data value.
              );

  neutrino::check_error (loc_error);                                                                // Checking returned error code...
  clFinish (neutrino::queue_id);                                                                    // Waiting for OpenCL to finish...
  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// DESTRUCTOR ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu::kernel::~kernel ()
{
  cl_int loc_error;                                                                                 // Error code.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  neutrino::action ("releasing OpenCL kernel...");                                                  // Printing message...
  loc_error = clReleaseKernel (kernel_id);                                                          // Releasing OpenCL kernel...
  neutrino::check_error (loc_error);                                                                // Checking error code...
  neutrino::done ();                                                                                // Printing message...

  neutrino::action ("releasing OpenCL kernel event...");                                            // Printing message...
  loc_error = clReleaseEvent (event);                                                               // Releasing OpenCL event...
  neutrino::check_error (loc_error);                                                                // Checking error code...
  neutrino::done ();                                                                                // Printing message...

  neutrino::action ("releasing OpenCL program...");                                                 // Printing message...
  loc_error = clReleaseProgram (program);                                                           // Releasing OpenCL program...
  neutrino::check_error (loc_error);                                                                // Checking error code...
  neutrino::done ();                                                                                // Printing message...

  neutrino::action ("releasing device ID array...");                                                // Printing message...
  delete[] device_id;                                                                               // Deleting device ID array...
  neutrino::done ();                                                                                // Printing message...
}
