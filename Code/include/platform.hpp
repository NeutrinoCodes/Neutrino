/// @file

#ifndef platform_hpp
#define platform_hpp

  #include "neutrino.hpp"
  #include "datatypes.hpp"

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// "PLATFORM" CLASS /////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class platform
{
private:
  neutrino* baseline;                                                           // Neutrino baseline.
  char*     parameter_value;                                                    // Parameter value.
  // Gets size information:
  size_t get_info_size (
                        cl_platform_id   loc_platform_id,                       // Platform ID.
                        cl_platform_info loc_parameter_name                     // Paramenter name.
                       );
  // Gets size information:
  char*  get_info_value (
                         cl_platform_id   loc_platform_id,                      // Platform ID.
                         cl_platform_info loc_parameter_name,                   // Paramenter name.
                         size_t           loc_parameter_size                    // Parameter size.
                        );

public:
  cl_platform_id id;                                                            // OpenCL platform id.
  info*          profile;                                                       // Platform parameter.
  info*          version;                                                       // Platform parameter.
  info*          name;                                                          // Platform parameter.
  info*          vendor;                                                        // Platform parameter.
  info*          extensions;                                                    // Platform parameter.

  platform  ();
  void init (
             cl_platform_id loc_platform_id                                     // Platform ID.
            );

  ~platform ();
};

#endif
