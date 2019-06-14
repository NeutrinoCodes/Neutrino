/// @file

#ifndef kernel_hpp
#define kernel_hpp

#include "neutrino.hpp"
#include "queue.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "KERNEL" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class kernel
{
private:
  neutrino*     baseline;                                                       // Neutrino baseline.
  cl_device_id* device_id;                                                      // Device ID array.
  // OpenCL error get function:
  const char* get_error (
                         cl_int loc_error                                       // Error code.
                        );
  // OpenCL error check function:
  void        check_error (
                           cl_int loc_error                                     // Error code.
                          );

public:
  cl_kernel  kernel_id;                                                         // Kernel id.
  char*      file_name;                                                         // Kernel file name.
  char*      source;                                                            // Kernel source.
  size_t     source_size;                                                       // Kernel source size [characters].
  cl_program program;                                                           // Kernel program.
  size_t*    size;                                                              // Kernel size(s) [size_t x dimension array].
  cl_uint    dimension;                                                         // Kernel dimension.
  cl_event   event;                                                             // Kernel event.
  char*      log_value;                                                         // OpenCL compiler log value array.
  size_t     log_size;                                                          // OpenCL compiler log size array.

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// CONSTRUCTOR ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  kernel();
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////// INIT ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void init (
             neutrino* loc_baseline,                                            // Neutrino baseline.
             char*     loc_kernel_filename,                                     // OpenCL kernel file name.
             size_t*   loc_kernel_size,                                         // OpenCL kernel size.
             cl_uint   loc_kernel_dimension                                     // OpenCL kernel dimension.
            );

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// SETARG ///////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  template <typename T> void setarg (
                                     T loc_data                                 // Data object.
                                    )
  {
    // Creating OpenCL memory buffer:
    loc_data.buffer = clCreateBuffer (
                                      opencl_context,                           // OpenCL context.
                                      CL_MEM_READ_WRITE |
                                      CL_MEM_COPY_HOST_PTR,                     // Memory flags.
                                      sizeof(loc_data.data)*loc_data.size,      // Data buffer size.
                                      loc_data.data_type,                       // Data buffer.
                                      &loc_error                                // Error code.
                                     );

    check_error (loc_error);                                                    // Checking returned error code...
  };

  template <> void setarg <point*>(
                                   point* loc_data                              // Data object.
                                  )
  {
    // Generating VAO...
    glGenVertexArrays (
                       1,                                                       // # of VAOs to generate.
                       &loc_data.vao                                            // VAOs array.
                      );
    glBindVertexArray (loc_data.vao);                                           // Binding node VAO...

    // Generating VBO:
    glGenBuffers (
                  1,                                                            // # of VBOs to generate.
                  &loc_data.vbo                                                 // VBOs array.
                 );

    // Binding VBO:
    glBindBuffer (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  loc_data.vbo                                                  // VBO to bind.
                 );

    // Creating and initializing a buffer object's data store:
    glBufferData (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  sizeof(loc_data.data)*loc_data.size,                          // VBO size.
                  loc_data.data,                                                // VBO data.
                  GL_DYNAMIC_DRAW                                               // VBO usage.
                 );

    // Specifying the format for attribute in vertex shader:
    glVertexAttribPointer (
                           LAYOUT_NODE,                                         // VAO index.
                           sizeof(loc_data.data),                               // VAO's # of components.
                           GL_FLOAT,                                            // Data type.
                           GL_FALSE,                                            // Not using normalized numbers.
                           0,                                                   // Data stride.
                           0                                                    // Data offset.
                          );

    // Enabling attribute in vertex shader:
    glEnableVertexAttribArray (
                               LAYOUT_NODE;                                     // VAO index.
                              );

    // Binding VBO:
    glBindBuffer (
                  GL_ARRAY_BUFFER,                                              // VBO target.
                  loc_data.vbo                                                  // VBO to bind.
                 );

    // Creating OpenCL buffer from OpenGL buffer:
    loc_data.buffer = clCreateFromGLBuffer (
                                            opencl_context,                     // OpenCL context.
                                            CL_MEM_READ_WRITE,                  // Memory flags.
                                            loc_data.vbo,                       // VBO.
                                            &loc_error                          // Returned error.
                                           );

    check_error (loc_error);                                                    // Checking returned error code...
  };
  // EZOR: to be put as a method of the opencl class.
  // Kernel execution:
  void execute (
                queue*      loc_queue,                                          // OpenCL queue.
                kernel_mode loc_kernel_mode                                     // OpenCL kernel mode.
               );



  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// DESTRUCTOR /////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~kernel();
};

#endif
