#ifndef baseline_hpp
#define baseline_hpp

#include "neutrino.hpp"

// OPENGL:
#define USE_GRAPHICS                                                            // Define it in order to use OpenGL-OpenCL interoperability graphics.
#define SIZE_WINDOW_X 800                                                       // Window x-size [px].
#define SIZE_WINDOW_Y 600                                                       // Window y-size [px].
#define WINDOW_NAME   "neutrino 2.0"                                            // Window name.

// OPENCL:
#define QUEUE_NUM     1                                                         // Number of OpenCL queues [#].
#define KERNEL_NUM    1                                                         // Number of OpenCL kernels [#].
#define KERNEL_DIM    1                                                         // Dimension of OpenCL kernels [#].

// MESH:
#define XMIN          -1.0                                                      // XMIN spatial boundary [m].
#define XMAX          1.0                                                       // XMAX spatial boundary [m].
#define YMIN          -1.0                                                      // YMIN spatial boundary [m].
#define YMAX          1.0                                                       // YMAX spatial boundary [m].
#define NODES_X       100                                                       // Number of nodes in "X" direction [#].
#define NODES_Y       100                                                       // Number of nodes in "Y" direction [#].
#define NODES         NODES_X* NODES_Y                                          // Total number of nodes [#].
#define DX            (float)((XMAX - XMIN)/(NODES_X - 1))                      // DX mesh spatial size [m].
#define DY            (float)((YMAX - YMIN)/(NODES_Y - 1))                      // DY mesh spatial size [m].

// CELL:
#define NEIGHBOURS    4                                                         // Number of neighbour nodes [#].
#define UP            0                                                         // Up neighbour designator [#].
#define DOWN          1                                                         // Down neighbour designator [#].
#define LEFT          2                                                         // Left neighbour designator [#].
#define RIGHT         3                                                         // Right neighbour designator [#].

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// INT1 STRUCTURE: ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct int1
{
  #ifdef USE_GRAPHICS
    GLsizeiptr value;                                                           // Value.
  #else
    size_t value;                                                               // Value.
  #endif
} int1;
#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FLOAT1 STRUCTURE: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct float1
{
  #ifdef USE_GRAPHICS
    GLfloat value;                                                              // Value.
  #else
    cl_float value;                                                             // Value.
  #endif
} float1;
#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FLOAT4 STRUCTURE: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct float4
{
  #ifdef USE_GRAPHICS
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

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// COLOR4 STRUCTURE: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct color4
{
  #ifdef USE_GRAPHICS
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

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// NODE STRUCTURE: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#define ARGUMENT_NODE        0                                                  // Kernel argument index.

// OPENGL LAYOUTS (must be a progressive number across all data structures):
#define LAYOUT_NODE_POSITION 0
#define LAYOUT_NODE_COLOR    1

#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct node_structure
{
  // Physical variables:
  float4 position;                                                              // Node position.
  float4 velocity;                                                              // Node velocity.
  float4 acceleration;                                                          // Node acceleration.

  // Numeric buffer variables:
  float4 position_buffer;                                                       // Node position buffer.
  float4 velocity_buffer;                                                       // Node velocity buffer.
  float4 acceleration_buffer;                                                   // Node acceleration buffer.

  // Color:
  color4 color;                                                                 // Node color.

  // Mass:
  float1 mass;                                                                  // Node mass.
} node_structure;
#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// LINK STRUCTURE: ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#define ARGUMENT_LINK                  1                                        // Kernel argument index.

// OPENGL LAYOUTS:
#define LAYOUT_LINK_NEIGHBOUR_POSITION 2
#define LAYOUT_LINK_NEIGHBOUR_COLOR    3

#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct bond_structure
{
  // Neighbour indexes:
  int1 index[NEIGHBOURS];                                                       // Neighbour index.

  // Neighbour positions:
  float4 position[NEIGHBOURS];                                                  // Neighbour position.

  // Neighbour colors:
  color4 color[NEIGHBOURS];                                                     // Neighbour color.

  // Link properties:
  float1 stiffness[NEIGHBOURS];                                                 // Link stiffness.
  float1 damping[NEIGHBOURS];                                                   // Link internal damping.
} bond_structure;
#pragma pack(pop)
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// FUNCTIONS: //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void        init_int1 (
                       int1 loc_data
                      );
void        init_float1 (
                         float1 data
                        );
void        init_float4 (
                         float4 data
                        );
void        init_color4 (
                         color4 data
                        );
const char* get_error (
                       cl_int loc_error                                         // Local error code.
                      );
#endif
