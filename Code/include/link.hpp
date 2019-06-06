#ifndef link_hpp
#define link_hpp

#include "neutrino.hpp"
#include "opengl.hpp"
#include "opencl.hpp"
#include "kernel.hpp"
#include "queue.hpp"
#include "data.hpp"

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// LINK CLASS /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class link
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
  link*        link_data;                                                       // Link data structure.
  cl_mem       link_buffer;                                                     // OpenCL link data memory buffer.

    #ifdef USE_GRAPHICS
    GLuint     link_vao;                                                        // Node VAO.
    GLuint     link_vbo;                                                        // Node VBO.
    GLsizeiptr link_size;                                                       // Data size.
    #else
    size_t     link_size;                                                       // Data size.
    #endif

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// CONSTRUCTOR: ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  link();
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// INIT FUNCTION: ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void   init (
               neutrino*  loc_baseline,                                         // Neutrino baseline.
               GLsizeiptr loc_link_size,                                        // Data number.
              );
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// "SET" FUNCTIONS: //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void   set_neighbour_index (
                              GLsizeiptr loc_index,                             // Data index.
                              GLsizeiptr loc_value[4]                           // Data value.
                             );
  void   set_stiffness (
                        GLsizeiptr loc_index,                                   // Data index.
                        float1     loc_value                                    // Data value.
                       );
  void   set_damping (
                      GLsizeiptr loc_index,                                     // Data index.
                      float1     loc_value                                      // Data value.
                     );
  //////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "GET" FUNCTIONS: ///////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////
  float4 get_neighbour_index (
                              GLsizeiptr loc_index,                             // Data index.
                             );
  float1 get_stiffness (
                        GLsizeiptr loc_index,                                   // Data index.
                       );
  float1 get_damping (
                      GLsizeiptr loc_index,                                     // Data index.
                     );
  ////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// CLIENT FUNCTIONS:  ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  // OpenCL write buffer function:
  void   push (
               queue*  loc_queue,                                               // OpenCL queue.
               cl_uint loc_kernel_arg                                           // OpenCL kernel argument index.
              );
  // OpenCL read buffer function:
  void   pull (
               queue*  loc_queue,                                               // OpenCL queue.
               cl_uint loc_kernel_arg                                           // OpenCL kernel argument index.
              );
  // OpenCL acquire buffer function:
  void   acquire_gl (
                     queue*  loc_queue,                                         // Queue.
                     cl_uint loc_kernel_arg                                     // Kernel argument index.
                    );
  // OpenCL release buffer function:
  void   release_gl (
                     queue*  loc_queue,                                         // Queue.
                     cl_uint loc_kernel_arg                                     // Kernel argument index.
                    );

  ~link();
};

#endif
