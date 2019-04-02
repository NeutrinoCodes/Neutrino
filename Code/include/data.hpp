/// @file

#ifndef data_hpp
#define data_hpp

#include "neutrino.hpp"
#include "kernel.hpp"
#include "queue.hpp"

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "POINT4" CLASS ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class data
{
private:
  neutrino*  baseline;                                                          // Neutrino baseline.
  size_t*    position;                                                          // Position of kernel argument in each kernel.
  data_type  variant;                                                           // Data type.
  // OpenCL error get function:
  const char* get_error (
                         cl_int loc_error                                       // Error code.
                        );
  // OpenCL error check function:
  void        check_error (
                           cl_int loc_error                                     // Error code.
                          );

  cl_context opencl_context;                                                    // OpenCL context.

public:
  GLfloat* data;                                                                // Wrapped data.

  GLsizeiptr size;                                                              // Data size.
  cl_mem     buffer;                                                            // OpenGL data memory buffer.
  GLuint     vao;                                                               // OpenGL data VAO.
  GLuint     vbo;                                                               // OpenGL data VBO.
  // Initialization:
  void     init (
                 neutrino*  loc_baseline,                                       // Neutrino baseline.
                 GLsizeiptr loc_data_size                                       // Data number.
                );
  ////////////////////////////////////////////////////////////////////////////
  /////////////////////////// HOST "SET" FUNCTIONS:  /////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  // Kernel set function:
  void     set_arg (
                    kernel* loc_kernel,                                         // OpenCL kernel.
                    cl_uint loc_kernel_arg                                      // OpenCL kernel argument #.
                   );
  // "data" set functions:
  void     set_data (
                     GLsizeiptr loc_index,                                      // Data index.
                     cl_long    loc_value                                       // Data value.
                    );
  void     set_data (
                     GLsizeiptr loc_index,                                      // Data index.
                     cl_float   loc_value                                       // Data value.
                    );
  // "x" set functions:
  void     set_x (
                  GLsizeiptr loc_index,                                         // Data index.
                  cl_long    loc_value                                          // Data value.
                 );
  void     set_x (
                  GLsizeiptr loc_index,                                         // Data index.
                  cl_float   loc_value                                          // Data value.
                 );
  void     set_x (
                  GLsizeiptr loc_index,                                         // Data index.
                  GLfloat    loc_value                                          // Data value.
                 );
  // "y" set functions:
  void     set_y (
                  GLsizeiptr loc_index,                                         // Data index.
                  cl_long    loc_value                                          // Data value.
                 );
  void     set_y (
                  GLsizeiptr loc_index,                                         // Data index.
                  cl_float   loc_value                                          // Data value.
                 );
  void     set_y (
                  GLsizeiptr loc_index,                                         // Data index.
                  GLfloat    loc_value                                          // Data value.
                 );
  // "z" set function:
  void     set_z (
                  GLsizeiptr loc_index,                                         // Data index.
                  cl_long    loc_value                                          // Data value.
                 );
  void     set_z (
                  GLsizeiptr loc_index,                                         // Data index.
                  cl_float   loc_value                                          // Data value.
                 );
  void     set_z (
                  GLsizeiptr loc_index,                                         // Data index.
                  GLfloat    loc_value                                          // Data value.
                 );
  // "w" set function:
  void     set_w (
                  GLsizeiptr loc_index,                                         // Data index.
                  cl_long    loc_value                                          // Data value.
                 );
  void     set_w (
                  GLsizeiptr loc_index,                                         // Data index.
                  cl_float   loc_value                                          // Data value.
                 );
  void     set_w (
                  GLsizeiptr loc_index,                                         // Data index.
                  GLfloat    loc_value                                          // Data value.
                 );
  ////////////////////////////////////////////////////////////////////////////
  /////////////////////////// HOST "GET" FUNCTIONS:  /////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  // Kernel get function:
  size_t   get_arg (
                    kernel* loc_kernel                                          // OpenCL kernel.
                   );
  // "data" get functions:
  cl_long  get_data (
                     GLsizeiptr loc_index                                       // Data index.
                    );
  cl_float get_data (
                     GLsizeiptr loc_index                                       // Data index.
                    );
  // "x" get functions:
  cl_long  get_x (
                  GLsizeiptr loc_index                                          // Data index.
                 );
  cl_float get_x (
                  GLsizeiptr loc_index                                          // Data index.
                 );
  GLfloat  get_x (
                  GLsizeiptr loc_index                                          // Data index.
                 );
  // "y" get functions:
  cl_long  get_y (
                  GLsizeiptr loc_index                                          // Data index.
                 );
  cl_float get_y (
                  GLsizeiptr loc_index                                          // Data index.
                 );
  GLfloat  get_y (
                  GLsizeiptr loc_index                                          // Data index.
                 );
  // "z" get functions:
  cl_long  get_z (
                  GLsizeiptr loc_index                                          // Data index.
                 );
  cl_float get_z (
                  GLsizeiptr loc_index                                          // Data index.
                 );
  GLfloat  get_z (
                  GLsizeiptr loc_index                                          // Data index.
                 );
  // "w" get functions:
  cl_long  get_w (
                  GLsizeiptr loc_index                                          // Data index.
                 );
  cl_float get_w (
                  GLsizeiptr loc_index                                          // Data index.
                 );
  GLfloat  get_w (
                  GLsizeiptr loc_index                                          // Data index.
                 );
  ////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// CLIENT FUNCTIONS:  ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  // OpenCL write buffer function:
  void     push (
                 queue*  loc_queue,                                             // OpenCL queue.
                 cl_uint loc_kernel_arg                                         // OpenCL kernel argument index.
                );
  // OpenCL read buffer function:
  void     pull (
                 queue*  loc_queue,                                             // OpenCL queue.
                 cl_uint loc_kernel_arg                                         // OpenCL kernel argument index.
                );
  // OpenCL acquire buffer function:
  void     acquire_gl (
                       queue*  loc_queue,                                       // Queue.
                       cl_uint loc_kernel_arg                                   // Kernel argument index.
                      );
  // OpenCL release buffer function:
  void     release_gl (
                       queue*  loc_queue,                                       // Queue.
                       cl_uint loc_kernel_arg                                   // Kernel argument index.
                      );

  ~data();
};

#endif
