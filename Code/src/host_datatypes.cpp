#include "host_datatypes.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "FLOAT4" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
float4::float4()
{
// Doing nothing.
}

void float4::init (
                   size_t loc_size                                              // Data size.
                  )
{
  float4_structure* data = new float4_structure[loc_size];
  size = loc_size;
}

float4::~float4()
{
  delete[] data;
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "INT4" CLASS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int4::int4()
{
// Doing nothing.
}

void int4::init (
                 size_t loc_size                                                // Data size.
                )
{
  int4_structure* data = new int4_structure[loc_size];
  size = loc_size;
}

int4::~int4()
{
  delete[] data;
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "POINT" CLASS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
point::point()
{
// Doing nothing.
}

void point::init (
                  GLsizeiptr loc_size                                           // Data size.
                 )
{
  point_structure* data = new point_structure[loc_size];
  size = loc_size;
}

point::~point()
{
  delete[] data;
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "COLOR" CLASS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
color::color()
{
// Doing nothing.
}

void color::init (
                  GLsizeiptr loc_size                                           // Data size.
                 )
{
  color_structure* data = new color_structure[loc_size];
  size = loc_size;
}

color::~color()
{
  delete[] data;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// "INFO" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
info::info(
           size_t loc_size
          )
{
  size  = loc_size;
  value = new char[loc_size];
}

info::~info()
{
  delete[] value;
}
