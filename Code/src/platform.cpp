#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "PLATFORM" CLASS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
platform::platform()
{

}

// PRIVATE METHODS:
size_t platform::get_info_size(cl_platform_info loc_parameter_name)
{
  cl_int  loc_err;                                                              // Local error code.
  size_t  loc_parameter_size;                                                   // Local parameter size.

  // Getting platform information:
  loc_err = clGetPlatformInfo(platform_id,                                      // Platform id.
                              loc_parameter_name,                               // Local parameter name.
                              0,                                                // Dummy parameter size: "0" means we ask for the # of parameters.
                              NULL,                                             // Dummy parameter.
                              &loc_parameter_size);                             // Returned local parameter size.

  if(loc_err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  return (loc_parameter_size);                                                  // Returning local parameter size...
}

char* platform::get_info_value(cl_platform_info loc_parameter_name, size_t loc_parameter_size)
{
  cl_int  loc_err;                                                              // Local error code.
  char*   loc_parameter_vaue;                                                   // Local parameter value.

  // Getting platform information:
  loc_err = clGetPlatformInfo(platform_id,                                      // Platform id.
                              loc_parameter_name,                               // Parameter name.
                              loc_parameter_size,                               // Parameter size.
                              loc_parameter_value,                              // Returned local parameter value.
                              NULL);                                            // Returned parameter size (NULL = ignored).

  if(loc_err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  return (loc_parameter_value);                                                 // Returning local parameter value...
}

// PUBLIC METHODS:
void platform::init(cl_platform_id loc_platform_id)
{
  info*   profile     = new info(get_info_size(CL_PLATFORM_PROFILE));           // Platform info.
  info*   version     = new info(get_info_size(CL_PLATFORM_VERSION));           // Platform info.
  info*   name        = new info(get_info_size(CL_PLATFORM_NAME));              // Platform info.
  info*   vendor      = new info(get_info_size(CL_PLATFORM_VENDOR));            // Platform info.
  info*   extensions  = new info(get_info_size(CL_PLATFORM_EXTENSIONS));        // Platform info.

  profile->value    = get_info_value(CL_PLATFORM_PROFILE, profile->size);       // Setting info value...
  version->value    = get_info_value(CL_PLATFORM_VERSION, version->size);       // Setting info value...
  name->value       = get_info_value(CL_PLATFORM_NAME, name->size);             // Setting info value...
  vendor->value     = get_info_value(CL_PLATFORM_VENDOR, vendor->size);         // Setting info value...
  extensions->value = get_info_value(CL_PLATFORM_EXTENSIONS, extensions->size); // Setting info value...

  platform_id = loc_platform_id;                                                // Initializing theplatform...
}

platform::~platform()
{
  delete profile;
  delete version;
  delete name;
  delete vendor;
  delete extensions;
}
