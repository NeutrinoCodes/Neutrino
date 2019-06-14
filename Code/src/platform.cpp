#include "platform.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "PLATFORM" CLASS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
platform::platform()
{
  profile    = NULL;
  version    = NULL;
  name       = NULL;
  vendor     = NULL;
  extensions = NULL;
}

size_t platform::get_info_size (
                                cl_platform_id   loc_platform_id,               // OpenCL platform ID.
                                cl_platform_info loc_parameter_name             // Parameter name.
                               )
{
  cl_int loc_error;                                                             // Error code.
  size_t loc_parameter_size;                                                    // Parameter size.

  // Getting platform information:
  loc_error = clGetPlatformInfo (
                                 loc_platform_id,                               // Platform id.
                                 loc_parameter_name,                            // Parameter name.
                                 0,                                             // Dummy parameter size: "0" means we ask for the # of parameters.
                                 NULL,                                          // Dummy parameter.
                                 &loc_parameter_size                            // Returned parameter size.
                                );

  baseline->check_error (loc_error);

  return (loc_parameter_size);                                                  // Returning local parameter size...
}

char* platform::get_info_value (
                                cl_platform_id   loc_platform_id,               // OpenCL platform ID.
                                cl_platform_info loc_parameter_name,            // Paramenter name.
                                size_t           loc_parameter_size             // Parameter size.
                               )
{
  cl_int loc_error;                                                             // Error code.
  parameter_value = new char[loc_parameter_size];                               // Parameter value.

  // Getting platform information:
  loc_error       = clGetPlatformInfo (
                                       loc_platform_id,                         // Platform id.
                                       loc_parameter_name,                      // Parameter name.
                                       loc_parameter_size,                      // Parameter size.
                                       parameter_value,                         // Returned parameter value.
                                       NULL                                     // Returned parameter size (NULL = ignored).
                                      );

  baseline->check_error (loc_error);

  return (parameter_value);                                                     // Returning local parameter value...
}

/// # Initialisation function
/// ### Description:
/// Gets platform information.
void platform::init (
                     cl_platform_id loc_platform_id                             // Platform ID.
                    )
{
  // Profile info:
  profile           = new info (
                                get_info_size (
                                               loc_platform_id,
                                               CL_PLATFORM_PROFILE
                                              )
                               );

  profile->value    = get_info_value (
                                      loc_platform_id,
                                      CL_PLATFORM_PROFILE,
                                      profile->size
                                     );

  // Version info:
  version           = new info (
                                get_info_size (
                                               loc_platform_id,
                                               CL_PLATFORM_VERSION
                                              )
                               );

  version->value    = get_info_value (
                                      loc_platform_id,
                                      CL_PLATFORM_VERSION,
                                      version->size
                                     );

  // Name info:
  name              = new info (
                                get_info_size (
                                               loc_platform_id,
                                               CL_PLATFORM_NAME
                                              )
                               );

  name->value       = get_info_value (
                                      loc_platform_id,
                                      CL_PLATFORM_NAME,
                                      name->size
                                     );

  // Vendor info:
  vendor            = new info (
                                get_info_size (
                                               loc_platform_id,
                                               CL_PLATFORM_VENDOR
                                              )
                               );

  vendor->value     = get_info_value (
                                      loc_platform_id,
                                      CL_PLATFORM_VENDOR,
                                      vendor->size
                                     );

  // Vendor info:
  extensions        = new info (
                                get_info_size (
                                               loc_platform_id,
                                               CL_PLATFORM_EXTENSIONS
                                              )
                               );

  extensions->value = get_info_value (
                                      loc_platform_id,
                                      CL_PLATFORM_EXTENSIONS,
                                      extensions->size
                                     );

  id                = loc_platform_id;                                          // Initializing platform id...
}

platform::~platform()
{
  delete profile;
  delete version;
  delete name;
  delete vendor;
  delete extensions;
  delete parameter_value;
}
