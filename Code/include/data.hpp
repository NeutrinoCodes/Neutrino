#ifndef data_hpp
#define data_hpp

#include "neutrino.hpp"
#include "opengl.hpp"
#include "opencl.hpp"
#include "kernel.hpp"
#include "queue.hpp"

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// DATA STRUCTURES ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct
{
  #ifdef USE_OPENGL
    GLfloat x;                                                                  // "x" coordinate.
    GLfloat y;                                                                  // "y" coordinate.
    GLfloat z;                                                                  // "z" coordinate.
    GLfloat w;                                                                  // "w" coordinate.
  #else
    cl_float x;                                                                 // "x" coordinate.
    cl_float y;                                                                 // "y" coordinate.
    cl_float z;                                                                 // "z" coordinate.
    cl_float w;                                                                 // "w" coordinate.
  #endif
} float4;
#pragma pack(pop)

#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct
{
  float4 position;                                                              // Node position.
  float4 position_buffer;                                                       // Node position buffer.
  float4 velocity;                                                              // Node velocity.
  float4 velocity_buffer;                                                       // Node velocity buffer.
  float4 acceleration;                                                          // Node acceleration.
  float4 acceleration_buffer;                                                   // Node acceleration buffer.
  float4 mass;                                                                  // Node mass.
} node;
#pragma pack(pop)

#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct
{
  cl_long up;                                                                   // "UP" neighbour index.
  cl_long down;                                                                 // "DOWN" neighbour index.
  cl_long left;                                                                 // "LEFT" neighbour index.
  cl_long right;                                                                // "RIGHT" neighbour index.
} neighbour;
#pragma pack(pop)

#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct
{
  float4 stiffness;                                                             // Link stifness.
  float4 damping;                                                               // Link damping.
} link;
#pragma pack(pop)

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// POINT CLASS ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class point4
{
private:
  neutrino*  baseline;                                                          // Neutrino baseline.
  size_t*    position;                                                          // Position of kernel argument in each kernel.
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
  GLfloat*   data;                                                              // Wrapped data.

  GLsizeiptr size;                                                              // Data size.
  cl_mem     buffer;                                                            // OpenGL data memory buffer.
  GLuint     vao;                                                               // OpenGL data VAO.
  GLuint     vbo;                                                               // OpenGL data VBO.

  point4();
  // Initialization:
  void    init (
                neutrino*  loc_baseline,                                        // Neutrino baseline.
                GLsizeiptr loc_data_size,                                       // Data number.
                GLuint     loc_vao_index                                        // VAO index.
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

  ~point4();
};

#endif
