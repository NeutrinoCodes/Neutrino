#ifndef node_hpp
#define node_hpp

#include "neutrino.hpp"
#include "opengl.hpp"
#include "opencl.hpp"
#include "kernel.hpp"
#include "queue.hpp"
#include "data.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// NODE CLASS ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
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

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// CONSTRUCTOR: ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  node();
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// INIT FUNCTION: ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void   init (
               neutrino*  loc_baseline,                                         // Neutrino baseline.
               GLsizeiptr loc_node_size,                                        // Data number.
              );
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// "SET" FUNCTIONS: //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void   set_position (
                       GLsizeiptr loc_index,                                    // Data index.
                       float4     loc_value                                     // Data value.
                      );
  void   set_velocity (
                       GLsizeiptr loc_index,                                    // Data index.
                       float4     loc_value                                     // Data value.
                      );
  void   set_acceleration (
                           GLsizeiptr loc_index,                                // Data index.
                           float4     loc_value                                 // Data value.
                          );
  void   set_color (
                    GLsizeiptr loc_index,                                       // Data index.
                    color4     loc_value                                        // Data value.
                   );
  void   set_mass (
                   GLsizeiptr loc_index,                                        // Data index.
                   float1     loc_value                                         // Data value.
                  );
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// "GET" FUNCTIONS: //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  float4 get_position (
                       GLsizeiptr loc_index,                                    // Data index.
                      );
  float4 get_velocity (
                       GLsizeiptr loc_index,                                    // Data index.
                      );
  float4 get_acceleration (
                           GLsizeiptr loc_index,                                // Data index.
                          );
  color4 get_color (
                    GLsizeiptr loc_index,                                       // Data index.
                   );
  float1 get_mass (
                   GLsizeiptr loc_index,                                        // Data index.
                  );
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// CONTROL FUNCTIONS:  ////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void   push (
               queue* loc_queue,                                                // Queue.
              );
  void   pull (
               queue* loc_queue,                                                // OpenCL queue.
              );
  void   acquire (
                  queue* loc_queue,                                             // Queue.
                 );
  void   release (
                  queue* loc_queue,                                             // Queue.
                 );
  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// DESTRUCTOR: ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~node();
};

#endif
