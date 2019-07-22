#include "datatypes.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "float1" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
float1::float1()
{
  ready = false;                                                                // Resetting "ready" flag...
}

void float1::init (
                   size_t loc_size                                              // Data size.
                  )
{
  data = new cl_float[loc_size];
  size = loc_size;

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
  ready = false;                                                                // Resetting "ready" flag...
}

void int1::init (
                 size_t loc_size                                                // Data size.
                )
{
  data = new cl_long[loc_size];
  size = loc_size;
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
  ready = false;                                                                // Resetting "ready" flag...
}

void float4::init (
                   size_t loc_size                                              // Data size.
                  )
{
  data = new float4_structure[loc_size];
  size = loc_size;
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
  ready = false;                                                                // Resetting "ready" flag...
}

void int4::init (
                 size_t loc_size                                                // Data size.
                )
{
  data = new int4_structure[loc_size];
  size = loc_size;
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
  ready = false;                                                                // Resetting "ready" flag...
}

void float1G::init (
                    GLsizeiptr loc_size                                         // Data size.
                   )
{
  data = new GLfloat[loc_size];
  size = loc_size;
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
  ready = false;                                                                // Resetting "ready" flag...
}

void float4G::init (
                    GLsizeiptr loc_size                                         // Data size.
                   )
{
  data = new float4G_structure[loc_size];
  size = loc_size;
}

float4G::~float4G()
{
  delete[] data;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// "info" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
info::info(
           size_t loc_size
          )
{
  value = new char[loc_size];
  size  = loc_size;
}

info::~info()
{
  delete[] value;
}
