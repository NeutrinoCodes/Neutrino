#include "kernel.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "KERNEL" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
kernel::kernel()
{
  source    = NULL;                                                             // Initializing kernel source...
  program   = NULL;                                                             // Initializing kernel program...
  size_i    = 0;                                                                // Initializing kernel size (i-index)...
  size_j    = 0;                                                                // Initializing kernel size (j-index)...
  size_k    = 0;                                                                // Initializing kernel size (k-index)...
  event     = NULL;                                                             // Initializing kernel event...
  kernel_id = NULL;                                                             // Initializing kernel id...
}

/// # Initialization function
/// ### Description:
/// Creates the OpenCL program from its source. Creates the device ID list.
/// Builds the OpenCL program. Creates the OpenCL kernel.
void kernel::init (
                   neutrino*   loc_baseline,                                    // Neutrino baseline.
                   const char* loc_kernel_home,                                 // Kernel hoem directory.
                   const char* loc_kernel_file_name,                            // OpenCL kernel file name.
                   size_t      loc_kernel_size_i,                               // OpenCL kernel size (i-index).
                   size_t      loc_kernel_size_j,                               // OpenCL kernel size (j-index).
                   size_t      loc_kernel_size_k                                // OpenCL kernel size (k-index).
                  )
{
  cl_int loc_error;                                                             // Error code.
  size_t loc_kernel_source_size;                                                // Kernel source size [characters].
  size_t i;                                                                     // Index.

  baseline = loc_baseline;                                                      // Getting Neutrino baseline...
  size_i   = loc_kernel_size_i;                                                 // Getting OpenCL kernel size (i-index)...
  size_j   = loc_kernel_size_j;                                                 // Getting OpenCL kernel size (j-index)...
  size_k   = loc_kernel_size_k;                                                 // Getting OpenCL kernel size (k-index)...

  strncpy (kernel_home, loc_kernel_home, MAX_PATH_SIZE);                        // Getting OpenCL kernel hoem directory...

  // Building up vertex file full name:
  snprintf (
            kernel_file_name,                                                   // Destination string.
            MAX_PATH_SIZE,                                                      // Size of destination string.
            "%s/%s",                                                            // Compiled string.
            kernel_home,                                                        // Shader home directory.
            loc_kernel_file_name                                                // Vertex shader file name.
           );

  // Building up JIT compiler options string:
  snprintf (
            compiler_options,                                                   // Destination string.
            MAX_PATH_SIZE,                                                      // Size of destination string.
            "%s %s",                                                            // Compiled string.
            "-I",                                                               // "Include" option.
            kernel_home                                                         // Kernel home directory.
           );

  baseline->action ("loading OpenCL kernel source from file...");               // Printing message...

  baseline->load_file (kernel_file_name, &source, &source_size);                // Loading file...

  baseline->done ();                                                            // Printing message...

  baseline->action ("creating OpenCL program from kernel source...");           // Printing message...

  // Creating OpenCL program from its source:
  program = clCreateProgramWithSource (
                                       baseline->context_id,                    // OpenCL context ID.
                                       1,                                       // # of program sources.
                                       (const char**)&source,                   // Program source.
                                       &source_size,                            // Source size.
                                       &loc_error                               // Error code.
                                      );

  baseline->check_error (loc_error);                                            // Checking error.

  baseline->free_file (source);                                                 // Freeing OpenCL kernel buffer...

  baseline->done ();                                                            // Printing message...

  baseline->action ("building OpenCL program...");                              // Printing message...

  // Creating device ID list:
  device_id    = new cl_device_id[1];                                           // OpenCL device ID.
  device_id[0] = baseline->device_id;                                           // Getting device ID.

  // Building OpenCL program:
  loc_error    = clBuildProgram (
                                 program,                                       // Program.
                                 1,                                             // # of devices.
                                 device_id,                                     // Device ID.
                                 compiler_options,                              // Including header files from kernel's directory.
                                 NULL,                                          // Notification routine.
                                 NULL                                           // Notification argument.
                                );

  if(loc_error != CL_SUCCESS)                                                   // Checking compiled kernel...
  {
    baseline->error (baseline->get_error (loc_error));                          // Printing message...

    // Getting OpenCL compiler information:
    loc_error = clGetProgramBuildInfo (
                                       program,
                                       device_id[0],
                                       CL_PROGRAM_BUILD_LOG,
                                       0,
                                       NULL,
                                       &log_size
                                      );

    baseline->check_error (loc_error);

    log_value = (char*) calloc (log_size + 1, sizeof(char));                    // Allocating log buffer...

    if(!log_value)
    {
      baseline->error ("unable to allocate buffer memory log!");                // Printing message...
      exit (EXIT_FAILURE);                                                      // Exiting...
    }

    // Reading OpenCL compiler error log:
    loc_error = clGetProgramBuildInfo (
                                       program,
                                       device_id[0],
                                       CL_PROGRAM_BUILD_LOG,
                                       log_size + 1,
                                       log_value,
                                       NULL
                                      );

    baseline->check_error (loc_error);                                          // Checking error...

    printf ("%s\n", log_value);                                                 // Displaying log...
    free (log_value);                                                           // Freeing log...
    exit (loc_error);                                                           // Exiting...
  }

  baseline->done ();                                                            // Printing message...

  baseline->action ("creating OpenCL kernel object from program...");           // Printing message...

  // Creating OpenCL kernel:
  kernel_id = clCreateKernel (
                              program,                                          // OpenCL kernel program.
                              KERNEL_NAME,                                      // Kernel name.
                              &loc_error                                        // Error code.
                             );

  baseline->check_error (loc_error);                                            // Checking error...

  baseline->done ();                                                            // Printing message...

  // Initializing kernel object:
  baseline->action ("initializing \"kernel\" object...");

  for(i = 0; i < baseline->k_num; i++)                                          // Scanning OpenCL kernel argument array...
  {
    if(baseline->kernel_id[i] == NULL)                                          // Looking for 1st non-assigned OpenCL kernel ID...
    {
      baseline->kernel_id[i] = kernel_id;                                       // Assigning value to 1st non-assigned OpenCL kernel ID...
      break;                                                                    // Exiting loop...
    }
  }

  baseline->done ();                                                            // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////// SETARG "float4" overload ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void kernel::setarg (
                     float4* loc_data,                                          // Float4 object.
                     cl_uint loc_layout_index                                   // Layout index.
                    )
{
  cl_int loc_error;                                                             // Error code.

  baseline->action ("setting kernel argument...");                              // Printing message...
  // Creating OpenCL memory buffer:
  loc_data->buffer = clCreateBuffer (
                                     baseline->context_id,                      // OpenCL context.
                                     CL_MEM_READ_WRITE |
                                     CL_MEM_COPY_HOST_PTR,                      // Memory flags.
                                     sizeof(loc_data->data)*loc_data->size,     // Data buffer size.
                                     loc_data->data,                            // Data buffer.
                                     &loc_error                                 // Error code.
                                    );

  baseline->check_error (loc_error);                                            // Checking returned error code...

  loc_error = clSetKernelArg (
                              kernel_id,                                        // Kernel id.
                              (cl_uint)loc_layout_index,                        // Layout index.
                              sizeof(cl_mem),                                   // Data size.
                              &loc_data->buffer                                 // Data value.
                             );

  baseline->done ();                                                            // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// SETARG "int4" overload ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void kernel::setarg (
                     int4*   loc_data,                                          // Int4 object.
                     cl_uint loc_layout_index                                   // Layout index.
                    )
{
  cl_int loc_error;                                                             // Error code.

  baseline->action ("setting kernel argument...");                              // Printing message...
  // Creating OpenCL memory buffer:
  loc_data->buffer = clCreateBuffer (
                                     baseline->context_id,                      // OpenCL context.
                                     CL_MEM_READ_WRITE |
                                     CL_MEM_COPY_HOST_PTR,                      // Memory flags.
                                     sizeof(loc_data->data)*loc_data->size,     // Data buffer size.
                                     loc_data->data,                            // Data buffer.
                                     &loc_error                                 // Error code.
                                    );

  baseline->check_error (loc_error);                                            // Checking returned error code...

  loc_error = clSetKernelArg (
                              kernel_id,                                        // Kernel id.
                              (cl_uint)loc_layout_index,                        // Layout index.
                              sizeof(cl_mem),                                   // Data size.
                              &loc_data->buffer                                 // Data value.
                             );

  baseline->done ();                                                            // Printing message...
}
//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// SETARG "point" overload ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void kernel::setarg (
                     point* loc_data,                                           // Data object.
                     GLuint loc_layout_index                                    // Layout index.
                    )
{
  cl_int loc_error;                                                             // Error code.

  baseline->action ("setting kernel argument...");                              // Printing message...

  loc_data->layout = loc_layout_index;                                          // Setting layout index.

  // Generating VAO...
  glGenVertexArrays (
                     1,                                                         // # of VAOs to generate.
                     &loc_data->vao                                             // VAOs array.
                    );
  glBindVertexArray (loc_data->vao);                                            // Binding node VAO...

  // Generating VBO:
  glGenBuffers (
                1,                                                              // # of VBOs to generate.
                &loc_data->vbo                                                  // VBOs array.
               );

  // Binding VBO:
  glBindBuffer (
                GL_ARRAY_BUFFER,                                                // VBO target.
                loc_data->vbo                                                   // VBO to bind.
               );

  // Creating and initializing a buffer object's data store:
  glBufferData (
                GL_ARRAY_BUFFER,                                                // VBO target.
                sizeof(loc_data->data)*loc_data->size,                          // VBO size.
                loc_data->data,                                                 // VBO data.
                GL_DYNAMIC_DRAW                                                 // VBO usage.
               );

  // Specifying the format for attribute in vertex shader:
  glVertexAttribPointer (
                         loc_layout_index,                                      // VAO index.
                         sizeof(loc_data->data),                                // VAO's # of components.
                         GL_FLOAT,                                              // Data type.
                         GL_FALSE,                                              // Not using normalized numbers.
                         0,                                                     // Data stride.
                         0                                                      // Data offset.
                        );

  // Enabling attribute in vertex shader:
  glEnableVertexAttribArray (
                             loc_layout_index                                   // VAO index.
                            );

  // Binding VBO:
  glBindBuffer (
                GL_ARRAY_BUFFER,                                                // VBO target.
                loc_data->vbo                                                   // VBO to bind.
               );

  // Creating OpenCL buffer from OpenGL buffer:
  loc_data->buffer = clCreateFromGLBuffer (
                                           baseline->context_id,                // OpenCL context.
                                           CL_MEM_READ_WRITE,                   // Memory flags.
                                           loc_data->vbo,                       // VBO.
                                           &loc_error                           // Returned error.
                                          );

  loc_error        = clSetKernelArg (
                                     kernel_id,                                 // Kernel id.
                                     loc_layout_index,                          // Layout index.
                                     sizeof(cl_mem),                            // Data size.
                                     &loc_data->buffer                          // Data value.
                                    );

  baseline->check_error (loc_error);                                            // Checking returned error code...

  baseline->done ();                                                            // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// SETARG "color" overload ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void kernel::setarg (
                     color* loc_data,                                           // Data object.
                     GLuint loc_layout_index                                    // Layout index.
                    )
{
  cl_int loc_error;                                                             // Error code.

  baseline->action ("setting kernel argument...");                              // Printing message...

  loc_data->layout = loc_layout_index;                                          // Setting layout index.

  // Generating VAO...
  glGenVertexArrays (
                     1,                                                         // # of VAOs to generate.
                     &loc_data->vao                                             // VAOs array.
                    );
  glBindVertexArray (loc_data->vao);                                            // Binding node VAO...

  // Generating VBO:
  glGenBuffers (
                1,                                                              // # of VBOs to generate.
                &loc_data->vbo                                                  // VBOs array.
               );

  // Binding VBO:
  glBindBuffer (
                GL_ARRAY_BUFFER,                                                // VBO target.
                loc_data->vbo                                                   // VBO to bind.
               );

  // Creating and initializing a buffer object's data store:
  glBufferData (
                GL_ARRAY_BUFFER,                                                // VBO target.
                sizeof(loc_data->data)*loc_data->size,                          // VBO size.
                loc_data->data,                                                 // VBO data.
                GL_DYNAMIC_DRAW                                                 // VBO usage.
               );

  // Specifying the format for attribute in vertex shader:
  glVertexAttribPointer (
                         loc_layout_index,                                      // VAO index.
                         sizeof(loc_data->data),                                // VAO's # of components.
                         GL_FLOAT,                                              // Data type.
                         GL_FALSE,                                              // Not using normalized numbers.
                         0,                                                     // Data stride.
                         0                                                      // Data offset.
                        );

  // Enabling attribute in vertex shader:
  glEnableVertexAttribArray (
                             loc_layout_index                                   // VAO index.
                            );

  // Binding VBO:
  glBindBuffer (
                GL_ARRAY_BUFFER,                                                // VBO target.
                loc_data->vbo                                                   // VBO to bind.
               );

  // Creating OpenCL buffer from OpenGL buffer:
  loc_data->buffer = clCreateFromGLBuffer (
                                           baseline->context_id,                // OpenCL context.
                                           CL_MEM_READ_WRITE,                   // Memory flags.
                                           loc_data->vbo,                       // VBO.
                                           &loc_error                           // Returned error.
                                          );

  loc_error        = clSetKernelArg (
                                     kernel_id,                                 // Kernel id.
                                     loc_layout_index,                          // Layout index.
                                     sizeof(cl_mem),                            // Data size.
                                     &loc_data->buffer                          // Data value.
                                    );

  baseline->check_error (loc_error);                                            // Checking returned error code...

  baseline->done ();                                                            // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// DESTRUCTOR ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
kernel::~kernel()
{
  cl_int loc_error;                                                             // Error code.

  baseline->action ("releasing OpenCL kernel...");                              // Printing message...
  loc_error = clReleaseKernel (kernel_id);                                      // Releasing OpenCL kernel...
  baseline->check_error (loc_error);                                            // Checking error code...
  baseline->done ();                                                            // Printing message...

  baseline->action ("releasing OpenCL kernel event...");                        // Printing message...
  loc_error = clReleaseEvent (event);                                           // Releasing OpenCL event...
  baseline->check_error (loc_error);                                            // Checking error code...
  baseline->done ();                                                            // Printing message...

  baseline->action ("releasing OpenCL program...");                             // Printing message...
  loc_error = clReleaseProgram (program);                                       // Releasing OpenCL program...
  baseline->check_error (loc_error);                                            // Checking error code...
  baseline->done ();                                                            // Printing message...

  baseline->action ("releasing device ID array...");                            // Printing message...
  delete[] device_id;                                                           // Deleting device ID array...
  baseline->done ();                                                            // Printing message...
}
