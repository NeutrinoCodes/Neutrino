/// @file     data_classes.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definitions of classes used for data storage.

#include "data_classes.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "nu_int" class //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
nu_int::nu_int(
               std::vector<nu_data*> loc_nu_data,                                                   // Neutrino common base data class.
               size_t                loc_layout                                                     // Kernel argument layout index.
              )
{
  size_t i;                                                                                         // Data vector current index.

  i                      = loc_nu_data.size ();                                                     // Getting data vector current index...
  loc_nu_data.push_back (this);
  loc_nu_data[i]->type   = NU_INT;                                                                  // Setting Neutrino data type...
  loc_nu_data[i]->layout = loc_layout;                                                              // Setting kernel argument layout index...
  ready                  = false;                                                                   // Resetting "ready" flag...
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
////////////////////////////////////////// "nu_int2" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_int2::nu_int2(
                 std::vector<nu_data*> loc_nu_data,                                                 // Neutrino common base data class.
                 size_t                loc_layout                                                   // Kernel argument layout index.
                )
{
  size_t i;                                                                                         // Data vector current index.

  i                      = loc_nu_data.size ();                                                     // Getting data vector current index...
  loc_nu_data.push_back (this);
  loc_nu_data[i]->type   = NU_INT2;                                                                 // Setting Neutrino data type...
  loc_nu_data[i]->layout = loc_layout;                                                              // Setting kernel argument layout index...
  ready                  = false;                                                                   // Resetting "ready" flag...
}

nu_int2::~nu_int2()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// "nu_int3" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_int3::nu_int3(
                 std::vector<nu_data*> loc_nu_data,                                                 // Neutrino common base data class.
                 size_t                loc_layout                                                   // Kernel argument layout index.
                )
{
  size_t i;                                                                                         // Data vector current index.

  i                      = loc_nu_data.size ();                                                     // Getting data vector current index...
  loc_nu_data.push_back (this);
  loc_nu_data[i]->type   = NU_INT3;                                                                 // Setting Neutrino data type...
  loc_nu_data[i]->layout = loc_layout;                                                              // Setting kernel argument layout index...
  ready                  = false;                                                                   // Resetting "ready" flag...
}

nu_int3::~nu_int3()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// "nu_int4" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_int4::nu_int4(
                 std::vector<nu_data*> loc_nu_data,                                                 // Neutrino common base data class.
                 size_t                loc_layout                                                   // Kernel argument layout index.
                )
{
  size_t i;                                                                                         // Data vector current index.

  i                      = loc_nu_data.size ();                                                     // Getting data vector current index...
  loc_nu_data.push_back (this);
  loc_nu_data[i]->type   = NU_INT4;                                                                 // Setting Neutrino data type...
  loc_nu_data[i]->layout = loc_layout;                                                              // Setting kernel argument layout index...
  ready                  = false;                                                                   // Resetting "ready" flag...
}

nu_int4::~nu_int4()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// "nu_float" class /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_float::nu_float(
                   std::vector<nu_data*> loc_nu_data,                                               // Neutrino common base data class.
                   size_t                loc_layout                                                 // Kernel argument layout index.
                  )
{
  size_t i;                                                                                         // Data vector current index.

  i                      = loc_nu_data.size ();                                                     // Getting data vector current index...
  loc_nu_data.push_back (this);
  loc_nu_data[i]->type   = NU_FLOAT;                                                                // Setting Neutrino data type...
  loc_nu_data[i]->layout = loc_layout;                                                              // Setting kernel argument layout index...
  ready                  = false;                                                                   // Resetting "ready" flag...
}

nu_float::~nu_float()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "nu_float2" class ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_float2::nu_float2(
                     std::vector<nu_data*> loc_nu_data,                                             // Neutrino common base data class.
                     size_t                loc_layout                                               // Kernel argument layout index.
                    )
{
  size_t i;                                                                                         // Data vector current index.

  i                      = loc_nu_data.size ();                                                     // Getting data vector current index...
  loc_nu_data.push_back (this);
  loc_nu_data[i]->type   = NU_FLOAT2;                                                               // Setting Neutrino data type...
  loc_nu_data[i]->layout = loc_layout;                                                              // Setting kernel argument layout index...
  ready                  = false;                                                                   // Resetting "ready" flag...
}

nu_float2::~nu_float2()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "nu_float3" class ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_float3::nu_float3(
                     std::vector<nu_data*> loc_nu_data,                                             // Neutrino common base data class.
                     size_t                loc_layout                                               // Kernel argument layout index.
                    )
{
  size_t i;                                                                                         // Data vector current index.

  i                      = loc_nu_data.size ();                                                     // Getting data vector current index...
  loc_nu_data.push_back (this);
  loc_nu_data[i]->type   = NU_FLOAT3;                                                               // Setting Neutrino data type...
  loc_nu_data[i]->layout = loc_layout;                                                              // Setting kernel argument layout index...
  ready                  = false;                                                                   // Resetting "ready" flag...
}

nu_float3::~nu_float3()
{
  // Doing nothing!
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// "nu_float4" class //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
nu_float4::nu_float4(
                     std::vector<nu_data*> loc_nu_data,                                             // Neutrino common base data class.
                     size_t                loc_layout                                               // Kernel argument layout index.
                    )
{
  size_t i;                                                                                         // Data vector current index.

  i                      = loc_nu_data.size ();                                                     // Getting data vector current index...
  loc_nu_data.push_back (this);
  loc_nu_data[i]->type   = NU_FLOAT4;                                                               // Setting Neutrino data type...
  loc_nu_data[i]->layout = loc_layout;                                                              // Setting kernel argument layout index...
  ready                  = false;                                                                   // Resetting "ready" flag...
  std::cout << "sono qui" << std::endl;
}

nu_float4::~nu_float4()
{
  // Doing nothing!
}
