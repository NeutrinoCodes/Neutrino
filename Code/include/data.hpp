#ifndef data_hpp
#define data_hpp

#include "neutrino.hpp"

#define OFFSETOF(s, f) ((size_t)((char*)&((s*)0)->f - (char*)0))                // "s" = structure, "f" = field

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
typedef struct link_structure
{
  // Neighbour indexes:
  int1 index[4];                                                                // Neighbour index.

  // Neighbour positions:
  float4 position[4];                                                           // Neighbour position.

  // Neighbour colors:
  color4 color[4];                                                              // Neighbour color.

  // Link properties:
  float1 stiffness[4];                                                          // Link stiffness.
  float1 damping[4];                                                            // Link internal damping.
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
