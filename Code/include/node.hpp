#ifndef node_hpp
#define node_hpp

#include "neutrino.hpp"
#include "opengl.hpp"
#include "opencl.hpp"
#include "kernel.hpp"
#include "queue.hpp"
#include "data.hpp"

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// NODE CLASS /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class node
{
private:
  neutrino*    baseline;                                                        // Neutrino baseline.
  // OpenCL error get function:
  const char* get_error (
                         cl_int loc_error                                       // Error code.
                        );
  // OpenCL error check function:
  void        check_error (
                           cl_int loc_error                                     // Error code.
                          );

  cl_context   opencl_context;                                                  // OpenCL context.

public:
  node*        node_data;                                                       // Node data structure.
  cl_mem       node_buffer;                                                     // OpenCL NODE data memory buffer.

    #ifdef USE_GRAPHICS
    GLuint     node_vao;                                                        // Node VAO.
    GLuint     node_vbo;                                                        // Node VBO.
    GLsizeiptr node_size;                                                       // Data size.
    #else
    size_t     node_size;                                                       // Data size.
    #endif

  node();
  // Initialization:
  void    init (
                neutrino*  loc_baseline,                                        // Neutrino baseline.
                GLsizeiptr loc_node_size,                                       // Data number.
               );
  ////////////////////////////////////////////////////////////////////////////
  /////////////////////////// HOST "SET" FUNCTIONS:  /////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  // Kernel set function:
  void    set_arg (
                   kernel* loc_kernel,                                          // OpenCL kernel.
                   cl_uint loc_kernel_arg                                       // OpenCL kernel argument #.
                  );
  // "x" set function:
  void    set_x (
                 GLsizeiptr loc_index,                                          // Data index.
                 GLfloat    loc_value                                           // Data value.
                );
  // "y" set function:
  void    set_y (
                 GLsizeiptr loc_index,                                          // Data index.
                 GLfloat    loc_value                                           // Data value.
                );
  // "z" set function:
  void    set_z (
                 GLsizeiptr loc_index,                                          // Data index.
                 GLfloat    loc_value                                           // Data value.
                );
  // "w" set function:
  void    set_w (
                 GLsizeiptr loc_index,                                          // Data index.
                 GLfloat    loc_value                                           // Data value.
                );
  ////////////////////////////////////////////////////////////////////////////
  /////////////////////////// HOST "GET" FUNCTIONS:  /////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  // Kernel get function:
  size_t  get_arg (
                   kernel* loc_kernel                                           // OpenCL kernel.
                  );
  // "x" get function:
  GLfloat get_x (
                 GLsizeiptr loc_index                                           // Data index.
                );
  // "y" get function:
  GLfloat get_y (
                 GLsizeiptr loc_index                                           // Data index.
                );
  // "z" get function:
  GLfloat get_z (
                 GLsizeiptr loc_index                                           // Data index.
                );
  // "w" get function:
  GLfloat get_w (
                 GLsizeiptr loc_index                                           // Data index.
                );
  ////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// CLIENT FUNCTIONS:  ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  // OpenCL write buffer function:
  void    push (
                queue*  loc_queue,                                              // OpenCL queue.
                cl_uint loc_kernel_arg                                          // OpenCL kernel argument index.
               );
  // OpenCL read buffer function:
  void    pull (
                queue*  loc_queue,                                              // OpenCL queue.
                cl_uint loc_kernel_arg                                          // OpenCL kernel argument index.
               );
  // OpenCL acquire buffer function:
  void    acquire_gl (
                      queue*  loc_queue,                                        // Queue.
                      cl_uint loc_kernel_arg                                    // Kernel argument index.
                     );
  // OpenCL release buffer function:
  void    release_gl (
                      queue*  loc_queue,                                        // Queue.
                      cl_uint loc_kernel_arg                                    // Kernel argument index.
                     );

  ~node();
};

#endif
