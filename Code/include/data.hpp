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
// float4:
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

// color4:
#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct
{
  #ifdef USE_OPENGL
    GLfloat r;                                                                  // "x" coordinate.
    GLfloat g;                                                                  // "y" coordinate.
    GLfloat b;                                                                  // "z" coordinate.
    GLfloat a;                                                                  // "w" coordinate.
  #else
    cl_float r;                                                                 // "x" coordinate.
    cl_float g;                                                                 // "y" coordinate.
    cl_float b;                                                                 // "z" coordinate.
    cl_float a;                                                                 // "w" coordinate.
  #endif
} color4;
#pragma pack(pop)

// int1:
#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct
{
  cl_long index;                                                                // Integer index.
} int1;
#pragma pack(pop)

// NODE:
#define NODE 1
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

// NEIGHBOUR:
#define NEIGHBOUR 2
#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct
{
  int1 up;                                                                      // "UP" neighbour index.
  int1 down;                                                                    // "DOWN" neighbour index.
  int1 left;                                                                    // "LEFT" neighbour index.
  int1 right;                                                                   // "RIGHT" neighbour index.
} neighbour;
#pragma pack(pop)

// LINK:
#define LINK  3
#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct
{
  float4 stiffness;                                                             // Link stifness.
  float4 damping;                                                               // Link damping.
} link;
#pragma pack(pop)

// COLOR:
#define COLOR 4
#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct
{
  color4 node;                                                                  // "NODE" color.
  color4 up;                                                                    // "UP" color.
  color4 down;                                                                  // "DOWN" color.
  color4 left;                                                                  // "LEFT" color.
  color4 right;                                                                 // "RIGHT" color.
} color;
#pragma pack(pop)
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// PARTICLE CLASS ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void init_float4 (
                  float4 data
                 );
void init_color4 (
                  color4 data
                 );

template<typename T>
void cl_create_from_gl_buffer (
                               GLuint     loc_vao,
                               GLuint     loc_vbo,
                               GLuint     loc_data_type,
                               T          loc_data,
                               GLsizeiptr loc_data_size,
                               cl_context loc_opencl_context,
                               cl_mem     loc_buffer
                              )
{
  // Generating VAO...
  glGenVertexArrays (
                     1,                                                         // # of VAOs to generate.
                     &loc_vao                                                   // VAOs array.
                    );
  glBindVertexArray (loc_vao);                                                  // Binding node VAO...

  // Generating VBO:
  glGenBuffers (
                1,                                                              // # of VBOs to generate.
                &loc_vbo                                                        // VBOs array.
               );

  // Binding VBO:
  glBindBuffer (
                GL_ARRAY_BUFFER,                                                // VBO target.
                loc_vbo                                                         // VBO to bind.
               );

  // Creating and initializing a buffer object's data store:
  glBufferData (
                GL_ARRAY_BUFFER,                                                // VBO target.
                (GLsizeiptr)(sizeof(loc_data)*(loc_data_size)),                 // VBO size.
                loc_data,                                                       // VBO data.
                GL_DYNAMIC_DRAW                                                 // VBO usage.
               );

  // Enabling attribute in vertex shader:
  glEnableVertexAttribArray (
                             NODE;                                              // VAO index.
                            );

  // Binding VBO:
  glBindBuffer (
                GL_ARRAY_BUFFER,                                                // VBO target.
                loc_vbo                                                         // VBO to bind.
               );

  // Specifying the format for attribute in vertex shader:
  glVertexAttribPointer (
                         loc_data_type,                                         // VAO index.
                         sizeof(loc_data),                                      // VAO's # of components.
                         GL_FLOAT,                                              // Data type.
                         GL_FALSE,                                              // Not using normalized numbers.
                         0,                                                     // Data stride.
                         0                                                      // Data offset.
                        );

  // Creating OpenCL buffer from OpenGL buffer:
  loc_buffer = clCreateFromGLBuffer (
                                     loc_opencl_context,                        // OpenCL context.
                                     CL_MEM_READ_WRITE,                         // Memory flags.
                                     loc_vbo,                                   // VBO.
                                     &loc_error                                 // Returned error.
                                    );
}

class particle
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
  #ifdef USE_GRAPHICS
    // OpenGL/CL shared data:
    GLfloat* data;                                                              // Data.

    // OpenGL VAOs:
    GLuint   node_vao;                                                          // Node VAO.
    GLuint   neighbour_vao;                                                     // Neighbour VAO.
    GLuint   link_vao;                                                          // Link VAO.
    GLuint   color_vao;                                                         // Color VAO.

    // OpenGL VBOs:
    GLuint   node_vbo;                                                          // Node VBO.
    GLuint   neighbour_vbo;                                                     // Neighbour VBO.
    GLuint   link_vbo;                                                          // Link VBO.
    GLuint   color_vbo;                                                         // Color VBO.
  #else
    // OpenCL data:
    cl_float* data;                                                             // Data.
  #endif

  GLsizeiptr size;                                                              // Data size.
  cl_mem     buffer;                                                            // OpenCL data memory buffer.



  particle ();
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

  ~particle();
};

#endif
