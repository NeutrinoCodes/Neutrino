#ifndef data_hpp
#define data_hpp

#include "neutrino.hpp"
#include "opengl.hpp"
#include "opencl.hpp"
#include "kernel.hpp"
#include "queue.hpp"

#define NUM_VECTOR_COMPONENTS 4                                                 // # of components in data structure.
#define NUM_NEIGHBOURS        4                                                 // # of neighbour nodes.

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// INT1 STRUCTURE: ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct
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
typedef struct
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
typedef struct
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
typedef struct
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
#define NODE 1                                                                  // Kernel argument index.
#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct
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
#define LINK 2                                                                  // Kernel argument index.
#pragma pack(push, 1)                                                           // Telling the C++ compiler to use tight packing...
typedef struct
{
  // Neighbour indexe:
  int1 index;                                                                   // Neighbour index.

  // Neighbour color:
  color4 color;                                                                 // Neighbour color.

  // Link properties:
  float1 stiffness;                                                             // Link stiffness.
  float1 damping;                                                               // Link internal damping.
} link_structure;
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
