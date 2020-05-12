/// @file     platform.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definition of an OpenCL "platform" class.

#include "platform.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// "platform" class ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
platform::platform()
{

}

size_t platform::get_info_size
(
 cl_platform_id   loc_platform_id,                                                                  // OpenCL platform ID.
 cl_platform_info loc_parameter_name                                                                // Parameter name.
)
{
  cl_int loc_error;                                                                                 // Error code.
  size_t loc_parameter_size;                                                                        // Parameter size.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting platform information:
  loc_error = clGetPlatformInfo
              (
               loc_platform_id,                                                                     // Platform id.
               loc_parameter_name,                                                                  // Parameter name.
               0,                                                                                   // "0" = we ask for the number of parameters.
               NULL,                                                                                // Dummy parameter.
               &loc_parameter_size                                                                  // Returned parameter size.
              );

  baseline->check_error (loc_error);

  return (loc_parameter_size);                                                                      // Returning local parameter size...
}

std::string platform::get_info_value
(
 cl_platform_id   loc_platform_id,                                                                  // OpenCL platform ID.
 cl_platform_info loc_parameter_name,                                                               // Paramenter name.
 size_t           loc_parameter_size                                                                // Parameter size.
)
{
  cl_int      loc_error;                                                                            // Error code.
  std::string loc_parameter;
  char*       loc_parameter_buffer = new char[loc_parameter_size]();                                // Parameter value.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting platform information:
  loc_error = clGetPlatformInfo
              (
               loc_platform_id,                                                                     // Platform id.
               loc_parameter_name,                                                                  // Parameter name.
               loc_parameter_size,                                                                  // Parameter size.
               loc_parameter_buffer,                                                                // Returned parameter value.
               NULL                                                                                 // Returned parameter size (NULL = ignored).
              );

  baseline->check_error (loc_error);

  loc_parameter = std::string (loc_parameter_buffer);

  return (loc_parameter);                                                                           // Returning local parameter value...
}

void platform::init
(
 cl_platform_id loc_platform_id                                                                     // Platform ID.
)
{
  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Profile info:
  profile = get_info_value
            (
             loc_platform_id,
             CL_PLATFORM_PROFILE,
             get_info_size
             (
              loc_platform_id,
              CL_PLATFORM_PROFILE
             )
            );

  // Version info:
  version = get_info_value
            (
             loc_platform_id,
             CL_PLATFORM_VERSION,
             get_info_size
             (
              loc_platform_id,
              CL_PLATFORM_VERSION
             )
            );

  // Name info:
  name = get_info_value
         (
          loc_platform_id,
          CL_PLATFORM_NAME,
          get_info_size
          (
           loc_platform_id,
           CL_PLATFORM_NAME
          )
         );

  // Vendor info:
  vendor = get_info_value
           (
            loc_platform_id,
            CL_PLATFORM_VENDOR,
            get_info_size
            (
             loc_platform_id,
             CL_PLATFORM_VENDOR
            )
           );

  // Vendor info:
  extensions = get_info_value
               (
                loc_platform_id,
                CL_PLATFORM_EXTENSIONS,
                get_info_size
                (
                 loc_platform_id,
                 CL_PLATFORM_EXTENSIONS
                )
               );

  id = loc_platform_id;                                                                             // Initializing platform id...
}

platform::~platform()
{

}
