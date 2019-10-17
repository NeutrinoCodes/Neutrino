/// @file     data_classes.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definitions of classes used for data storage.

#include "data_classes.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int1" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
int1::int1()
{
  ready = false;                                                                                    /// Resetting "ready" flag...
}

void int1::init (
                 size_t loc_size                                                                    /// Data size.
                )
{
  size_t i;                                                                                         /// Index.

  data = new cl_long[loc_size];                                                                     /// "1 x size" data storage [cl_long].
  size = loc_size;                                                                                  /// Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i] = 0;                                                                                    /// Resetting data...
  }
}

int1::~int1()
{
  delete[] data;                                                                                    /// Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int2" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
int2::int2()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void int2::init (
                 size_t loc_size                                                                    // Data size.
                )
{
  size_t i;                                                                                         // Index.

  data = new int2_structure[loc_size];                                                              // "2 x size" data storage [cl_long].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i].x = 0;                                                                                  // Resetting data...
    data[i].y = 0;                                                                                  // Resetting data...
  }
}

int2::~int2()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int3" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
int3::int3()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void int3::init (
                 size_t loc_size                                                                    // Data size.
                )
{
  size_t i;                                                                                         // Index.

  data = new int3_structure[loc_size];                                                              // "3 x size" data storage [cl_long].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i].x = 0;                                                                                  // Resetting data...
    data[i].y = 0;                                                                                  // Resetting data...
    data[i].z = 0;                                                                                  // Resetting data...
  }
}

int3::~int3()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int4" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
int4::int4()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void int4::init
(
 size_t loc_size                                                                                    // Data size.
)
{
  size_t i;                                                                                         // Index.

  data = new int4_structure[loc_size];                                                              // "4 x size" data storage [cl_long].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i].x = 0;                                                                                  // Resetting data...
    data[i].y = 0;                                                                                  // Resetting data...
    data[i].z = 0;                                                                                  // Resetting data...
    data[i].w = 0;                                                                                  // Resetting data...
  }
}

int4::~int4()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "float1" class /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
float1::float1()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void float1::init
(
 size_t loc_size                                                                                    // Data size.
)
{
  size_t i;                                                                                         // Index.

  data = new cl_float[loc_size];                                                                    // "1 x size" data storage [cl_float].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i] = 0.0f;                                                                                 // Resetting data...
  }
}

float1::~float1()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "float1G" class ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
float1G::float1G()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void float1G::init
(
 GLsizeiptr loc_size                                                                                // Data size.
)
{
  GLsizeiptr i;                                                                                     // Index.

  data = new GLfloat[loc_size];                                                                     // "1 x size" data storage [GLfloat].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i] = 0.0f;                                                                                 // Resetting data...
  }
}

float1G::~float1G()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// "float2" class ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
float2::float2()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void float2::init
(
 size_t loc_size                                                                                    // Data size.
)
{
  size_t i;                                                                                         // Index.

  data = new float2_structure[loc_size];                                                            // "2 x size" data storage [cl_float].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i].x = 0.0f;                                                                               // Resetting data...
    data[i].y = 0.0f;                                                                               // Resetting data...
  }
}

float2::~float2()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// "float3" class ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
float3::float3()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void float3::init
(
 size_t loc_size                                                                                    // Data size.
)
{
  size_t i;                                                                                         // Index.

  data = new float3_structure[loc_size];                                                            // "3 x size" data storage [cl_float].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i].x = 0.0f;                                                                               // Resetting data...
    data[i].y = 0.0f;                                                                               // Resetting data...
    data[i].z = 0.0f;                                                                               // Resetting data...
  }
}

float3::~float3()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// "float4" class //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
float4::float4()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void float4::init
(
 size_t loc_size                                                                                    // Data size.
)
{
  size_t i;                                                                                         // Index.

  data = new float4_structure[loc_size];                                                            // "4 x size" data storage [cl_float].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i].x = 0.0f;                                                                               // Resetting data...
    data[i].y = 0.0f;                                                                               // Resetting data...
    data[i].z = 0.0f;                                                                               // Resetting data...
    data[i].w = 0.0f;                                                                               // Resetting data...
  }
}

float4::~float4()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// "float4G" class /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
float4G::float4G()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void float4G::init
(
 GLsizeiptr loc_size                                                                                // Data size.
)
{
  GLsizeiptr i;                                                                                     // Index.

  data = new float4G_structure[loc_size];                                                           // "4 x size" data storage [GLfloat].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i].x = 0.0f;                                                                               // Resetting data...
    data[i].y = 0.0f;                                                                               // Resetting data...
    data[i].z = 0.0f;                                                                               // Resetting data...
    data[i].w = 0.0f;                                                                               // Resetting data...
  }
}

float4G::~float4G()
{
  delete[] data;                                                                                    // Deleting data storage...
}
