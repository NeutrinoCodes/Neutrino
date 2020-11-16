/// @file     data_classes.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definitions of classes used for data storage.

#include "data_classes.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "nu_int" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
nu_int::nu_int()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void nu_int::init (
                   GLsizeiptr loc_size                                                              // Data size.
                  )
{
  GLsizeiptr i;                                                                                     // Index.

  data = new GLint[loc_size];                                                                       // "1 x size" data storage [GLint].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i] = 0;                                                                                    // Resetting data...
  }
}

void nu_int::read
(
 std::string loc_file_directory,                                                                    // File directory.
 std::string loc_file_name                                                                          // File name.
)
{
  size_t      i;                                                                                    // Data index.
  GLint       loc_data;                                                                             // File data.
  std::string loc_full_name;                                                                        // Full file name.

  #ifdef __linux__
    loc_full_name = loc_file_directory +                                                            // Data directory.
                    std::string ("/") +                                                             // Slash.
                    loc_file_name;                                                                  // Data file name.
  #endif

  #ifdef __APPLE__
    loc_full_name = loc_file_directory +                                                            // Data directory.
                    std::string ("/") +                                                             // Slash.
                    loc_file_name;                                                                  // Data file name.
  #endif

  #ifdef WIN32
    loc_full_name = loc_file_directory +                                                            // Data directory.
                    std::string ("\\") +                                                            // Backslash.
                    loc_file_name;                                                                  // Data file name.
  #endif

  std::ifstream loc_file (loc_full_name);                                                           // File.

  if(loc_file)                                                                                      // Checking file...
  {
    for(i = 0; i < size; i++)
    {
      if(loc_file >> loc_data)
      {
        data[i] = loc_data;                                                                         // Setting data...
      }

      else
      {
        data[i] = 0;                                                                                // Resetting data...
      }
    }

    loc_file.close ();                                                                              // Closing file...
  }

  else
  {
    throw(errno);                                                                                   // Throwing error in case of a reading problem...
  }
}

nu_int::~nu_int()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "nu_int2" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_int2::nu_int2()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void nu_int2::init (
                    GLsizeiptr loc_size                                                             // Data size.
                   )
{
  GLsizeiptr i;                                                                                     // Index.

  data = new nu_int2_structure[loc_size];                                                           // "2 x size" data storage [cl_long].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i].x = 0;                                                                                  // Resetting data...
    data[i].y = 0;                                                                                  // Resetting data...
  }
}

nu_int2::~nu_int2()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "nu_int3" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_int3::nu_int3()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void nu_int3::init (
                    GLsizeiptr loc_size                                                             // Data size.
                   )
{
  GLsizeiptr i;                                                                                     // Index.

  data = new nu_int3_structure[loc_size];                                                           // "3 x size" data storage [cl_long].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i].x = 0;                                                                                  // Resetting data...
    data[i].y = 0;                                                                                  // Resetting data...
    data[i].z = 0;                                                                                  // Resetting data...
  }
}

nu_int3::~nu_int3()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "nu_int4" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_int4::nu_int4()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void nu_int4::init
(
 GLsizeiptr loc_size                                                                                // Data size.
)
{
  GLsizeiptr i;                                                                                     // Index.

  data = new nu_int4_structure[loc_size];                                                           // "4 x size" data storage [cl_long].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i].x = 0;                                                                                  // Resetting data...
    data[i].y = 0;                                                                                  // Resetting data...
    data[i].z = 0;                                                                                  // Resetting data...
    data[i].w = 0;                                                                                  // Resetting data...
  }
}

nu_int4::~nu_int4()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "nu_float" class /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_float::nu_float()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

nu_float::~nu_float()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// "nu_float2" class ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_float2::nu_float2()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void nu_float2::init
(
 GLsizeiptr loc_size                                                                                // Data size.
)
{
  GLsizeiptr i;                                                                                     // Index.

  data = new nu_float2_structure[loc_size];                                                         // "2 x size" data storage [GLfloat].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i].x = 0.0f;                                                                               // Resetting data...
    data[i].y = 0.0f;                                                                               // Resetting data...
  }
}

nu_float2::~nu_float2()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// "nu_float3" class ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_float3::nu_float3()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void nu_float3::init
(
 GLsizeiptr loc_size                                                                                // Data size.
)
{
  GLsizeiptr i;                                                                                     // Index.

  data = new nu_float3_structure[loc_size];                                                         // "3 x size" data storage [GLfloat].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i].x = 0.0f;                                                                               // Resetting data...
    data[i].y = 0.0f;                                                                               // Resetting data...
    data[i].z = 0.0f;                                                                               // Resetting data...
  }
}

nu_float3::~nu_float3()
{
  delete[] data;                                                                                    // Deleting data storage...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// "nu_float4" class //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_float4::nu_float4()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

void nu_float4::init
(
 GLsizeiptr loc_size                                                                                // Data size.
)
{
  GLsizeiptr i;                                                                                     // Index.

  data = new nu_float4_structure[loc_size];                                                         // "4 x size" data storage [GLfloat].
  size = loc_size;                                                                                  // Data size [#].

  for(i = 0; i < loc_size; i++)
  {
    data[i].x = 0.0f;                                                                               // Resetting data...
    data[i].y = 0.0f;                                                                               // Resetting data...
    data[i].z = 0.0f;                                                                               // Resetting data...
    data[i].w = 1.0f;                                                                               // Setting data...
  }
}

nu_float4::~nu_float4()
{
  delete[] data;                                                                                    // Deleting data storage...
}
