/// @file     data_classes.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definitions of classes used for data storage.

#include "data_classes.hpp"

std::vector<nu::data*> nu::data::container;                                                         // Neutrino data array.

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// "int" class //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
nu::int1::int1(
               size_t loc_layout                                                                    // Kernel argument layout index.
              )
{
  size_t i;                                                                                         // Data vector current index.

  i                              = nu::data::container.size ();                                     // Getting data vector current index...
  nu::data::container.push_back (this);
  nu::data::container[i]->type   = NU_INT;                                                          // Setting Neutrino data type...
  nu::data::container[i]->layout = loc_layout;                                                      // Setting kernel argument layout index...
  ready                          = false;                                                           // Resetting "ready" flag...
}

void nu::int1::read
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
        container[i] = loc_data;                                                                         // Setting data...
       }

       else
       {
        container[i] = 0;                                                                                // Resetting data...
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

nu::int1::~int1()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int2" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu::int2::int2 (
                size_t loc_layout                                                                   // Kernel argument layout index.
               )
{
  size_t i;                                                                                         // Data vector current index.

  i                              = nu::data::container.size ();                                     // Getting data vector current index...
  nu::data::container.push_back (this);
  nu::data::container[i]->type   = NU_INT2;                                                         // Setting Neutrino data type...
  nu::data::container[i]->layout = loc_layout;                                                      // Setting kernel argument layout index...
  ready                          = false;                                                           // Resetting "ready" flag...
}

nu::int2::~int2 ()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int3" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu::int3::int3 (
                size_t loc_layout                                                                   // Kernel argument layout index.
               )
{
  size_t i;                                                                                         // Data vector current index.

  i                              = nu::data::container.size ();                                     // Getting data vector current index...
  nu::data::container.push_back (this);
  nu::data::container[i]->type   = NU_INT3;                                                         // Setting Neutrino data type...
  nu::data::container[i]->layout = loc_layout;                                                      // Setting kernel argument layout index...
  ready                          = false;                                                           // Resetting "ready" flag...
}

nu::int3::~int3 ()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "int4" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu::int4::int4 (
                size_t loc_layout                                                                   // Kernel argument layout index.
               )
{
  size_t i;                                                                                         // Data vector current index.

  i                              = nu::data::container.size ();                                     // Getting data vector current index...
  nu::data::container.push_back (this);
  nu::data::container[i]->type   = NU_INT4;                                                         // Setting Neutrino data type...
  nu::data::container[i]->layout = loc_layout;                                                      // Setting kernel argument layout index...
  ready                          = false;                                                           // Resetting "ready" flag...
}

nu::int4::~int4 ()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "float1" class /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu::float1::float1 (
                    size_t loc_layout                                                               // Kernel argument layout index.
                   )
{
  size_t i;                                                                                         // Data vector current index.

  i                              = nu::data::container.size ();                                     // Getting data vector current index...
  nu::data::container.push_back (this);
  nu::data::container[i]->type   = NU_FLOAT;                                                        // Setting Neutrino data type...
  nu::data::container[i]->layout = loc_layout;                                                      // Setting kernel argument layout index...
  ready                          = false;                                                           // Resetting "ready" flag...
}

nu::float1::~float1 ()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// "float2" class ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu::float2::float2 (
                    size_t loc_layout                                                               // Kernel argument layout index.
                   )
{
  size_t i;                                                                                         // Data vector current index.

  i                              = nu::data::container.size ();                                     // Getting data vector current index...
  nu::data::container.push_back (this);
  nu::data::container[i]->type   = NU_FLOAT2;                                                       // Setting Neutrino data type...
  nu::data::container[i]->layout = loc_layout;                                                      // Setting kernel argument layout index...
  ready                          = false;                                                           // Resetting "ready" flag...
}

nu::float2::~float2 ()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// "float3" class ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu::float3::float3 (
                    size_t loc_layout                                                               // Kernel argument layout index.
                   )
{
  size_t i;                                                                                         // Data vector current index.

  i                              = nu::data::container.size ();                                     // Getting data vector current index...
  nu::data::container.push_back (this);
  nu::data::container[i]->type   = NU_FLOAT3;                                                       // Setting Neutrino data type...
  nu::data::container[i]->layout = loc_layout;                                                      // Setting kernel argument layout index...
  ready                          = false;                                                           // Resetting "ready" flag...
}

nu::float3::~float3 ()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// "float4" class //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu::float4::float4 (
                    size_t loc_layout                                                               // Kernel argument layout index.
                   )
{
  size_t i;                                                                                         // Data vector current index.

  i                              = nu::data::container.size ();                                     // Getting data vector current index...
  nu::data::container.push_back (this);
  nu::data::container[i]->type   = NU_FLOAT4;                                                       // Setting Neutrino data type...
  nu::data::container[i]->layout = loc_layout;                                                      // Setting kernel argument layout index...
  ready                          = false;                                                           // Resetting "ready" flag...
}

nu::float4::~float4 ()
{
  // Doing nothing!
}
