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
    /* EZOR 18NOV2020 to be modified according to std::vector data.
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
     */
  }

  else
  {
    throw(errno);                                                                                   // Throwing error in case of a reading problem...
  }
}

nu_int::~nu_int()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "nu_int2" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_int2::nu_int2()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

nu_int2::~nu_int2()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "nu_int3" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_int3::nu_int3()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

nu_int3::~nu_int3()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "nu_int4" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_int4::nu_int4()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

nu_int4::~nu_int4()
{
  // Doing nothing!
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

nu_float2::~nu_float2()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// "nu_float3" class ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_float3::nu_float3()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

nu_float3::~nu_float3()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// "nu_float4" class //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_float4::nu_float4()
{
  ready = false;                                                                                    // Resetting "ready" flag...
}

nu_float4::~nu_float4()
{
  // Doing nothing!
}
