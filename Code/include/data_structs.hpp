/// @file     data_structs.hpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Declarations of structures used for data storage.

#ifndef data_structs_hpp
#define data_structs_hpp

#include "neutrino.hpp"

#pragma pack(push, 1)                                                                               // Packing data in 1 column...
/// @brief    **2D vector of "cl_long" data.**
/// @details  This structure is used as data storage in the "int2" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
typedef struct _int2_structure
{
  cl_long x;                                                                                        ///< "x" coordinate.
  cl_long y;                                                                                        ///< "y" coordinate.
} int2_structure;
#pragma pack(pop)                                                                                   // End of packing.

/// @brief    **3D vector of "cl_long" data.**
/// @details  This structure is used as data storage in the "int3" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _int3_structure
{
  cl_long x;                                                                                        // "x" coordinate.
  cl_long y;                                                                                        // "y" coordinate.
  cl_long z;                                                                                        // "z" coordinate.
} int3_structure;
#pragma pack(pop)

/// @brief    **4D vector of "cl_long" data.**
/// @details  This structure is used as data storage in the "int4" class. It is tightly packed to be
/// compatible with the OpenCL requirement of having a contiguous data arrangement without padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _int4_structure
{
  cl_long x;                                                                                        // "x" coordinate.
  cl_long y;                                                                                        // "y" coordinate.
  cl_long z;                                                                                        // "z" coordinate.
  cl_long w;                                                                                        // "w" coordinate.
} int4_structure;
#pragma pack(pop)

/// @brief    **2D vector of "cl_float" data.**
/// @details  This structure is used as data storage in the "float2" class. It is tightly packed to
/// be compatible with the OpenCL requirement of having a contiguous data arrangement without
/// padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _float2_structure
{
  cl_float x;                                                                                       // "x" coordinate.
  cl_float y;                                                                                       // "y" coordinate.
} float2_structure;
#pragma pack(pop)

/// @brief    **3D vector of "cl_float" data.**
/// @details  This structure is used as data storage in the "float3" class. It is tightly packed to
/// be compatible with the OpenCL requirement of having a contiguous data arrangement without
/// padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _float3_structure
{
  cl_float x;                                                                                       // "x" coordinate.
  cl_float y;                                                                                       // "y" coordinate.
  cl_float z;                                                                                       // "z" coordinate.
} float3_structure;
#pragma pack(pop)

/// @brief    **4D vector of cl_float data.**
/// @details  This structure is used as data storage in the "float4" class. It is tightly packed to
/// be compatible with the OpenCL requirement of having a contiguous data arrangement without
/// padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _float4_structure
{
  cl_float x;                                                                                       // "x" coordinate.
  cl_float y;                                                                                       // "y" coordinate.
  cl_float z;                                                                                       // "z" coordinate.
  cl_float w;                                                                                       // "w" coordinate.
} float4_structure;
#pragma pack(pop)

/// @brief    **4D vector of "GLfloat" data.**
/// @details  This structure is used as data storage in the "float4G" class. It is tightly packed to
/// be compatible with the OpenCL requirement of having a contiguous data arrangement without
/// padding.
#pragma pack(push, 1)                                                                               // Packing data in 1 column...
typedef struct _float4G_structure
{
  GLfloat x;                                                                                        /// "x" coordinate.
  GLfloat y;                                                                                        /// "y" coordinate.
  GLfloat z;                                                                                        /// "z" coordinate.
  GLfloat w;                                                                                        /// "w" coordinate.
} float4G_structure;
#pragma pack(pop)

#endif
