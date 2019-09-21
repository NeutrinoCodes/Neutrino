/// @file

#include "datatypes.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "float1" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
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

  data = new cl_float[loc_size];
  size = loc_size;

  for(i = 0; i < loc_size; i++)
  {
    data[i] = 0.0f;                                                                                 // Resetting data...
  }
}

float1::~float1()
{
  delete[] data;
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "int1" CLASS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int1::int1()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void int1::init (
                 size_t loc_size                                                                    // Data size.
                )
{
  size_t i;                                                                                         // Index.

  data = new cl_long[loc_size];
  size = loc_size;

  for(i = 0; i < loc_size; i++)
  {
    data[i] = 0;                                                                                    // Resetting data...
  }
}

int1::~int1()
{
  delete[] data;
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "float4" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
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

  data = new float4_structure[loc_size];
  size = loc_size;

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
  delete[] data;
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "int4" CLASS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
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

  data = new int4_structure[loc_size];
  size = loc_size;

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
  delete[] data;
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "float1G" CLASS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
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

  data = new GLfloat[loc_size];
  size = loc_size;

  for(i = 0; i < loc_size; i++)
  {
    data[i] = 0.0f;                                                                                 // Resetting data...
  }
}

float1G::~float1G()
{
  delete[] data;
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "float4G" CLASS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
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

  data = new float4G_structure[loc_size];
  size = loc_size;

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
  delete[] data;
}
