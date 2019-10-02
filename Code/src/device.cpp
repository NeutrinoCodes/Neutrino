/// @file

#include "device.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// "device" class ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
device::device()
{

}

std::string device::get_string
(
 cl_device_id   loc_device_id,                                                                      // OpenCL device ID.
 cl_device_info loc_parameter_name                                                                  // Parameter name.
)

{
  cl_int      loc_error;                                                                            // Error code.
  size_t      loc_parameter_size;                                                                   // Parameter size.
  std::string loc_parameter_value;                                                                  // Parameter value.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting parameter size:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               0,                                                                                   // Dummy parameter size: "0" means we ask for the # of parameters.
               NULL,                                                                                // Dummy parameter.
               &loc_parameter_size                                                                  // Returned parameter size.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  char* loc_parameter_buffer = new char[loc_parameter_size];                                        // Text buffer.

  // Getting parameter information:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               loc_parameter_size,                                                                  // Parameter size.
               loc_parameter_buffer,                                                                // Returned parameter value.
               NULL                                                                                 // Returned parameter size (NULL = ignored).
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  loc_parameter_value = loc_parameter_buffer;                                                       // Setting parameter value...

  return (loc_parameter_value);                                                                     // Returning parameter value...
}

cl_uint device::get_cl_uint
(
 cl_device_id   loc_device_id,                                                                      // OpenCL device ID.
 cl_device_info loc_parameter_name                                                                  // Parameter name.
)
{
  cl_int  loc_error;                                                                                // Error code.
  size_t  loc_parameter_size;                                                                       // Parameter size.
  cl_uint loc_parameter_value;                                                                      // Parameter value.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting parameter size:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               0,                                                                                   // Dummy parameter size: "0" means we ask for the # of parameters.
               NULL,                                                                                // Dummy parameter.
               &loc_parameter_size                                                                  // Returned parameter size.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  // Getting parameter information:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               loc_parameter_size,                                                                  // Parameter size.
               &loc_parameter_value,                                                                // Returned parameter value.
               NULL                                                                                 // Returned parameter size (NULL = ignored).
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  return (loc_parameter_value);                                                                     // Returning parameter value...
}

cl_uint device::get_cl_bool
(
 cl_device_id   loc_device_id,                                                                      // OpenCL device ID.
 cl_device_info loc_parameter_name                                                                  // Parameter name.
)
{
  cl_int  loc_error;                                                                                // Error code.
  size_t  loc_parameter_size;                                                                       // Parameter size.
  cl_bool loc_parameter_value;                                                                      // Parameter value.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting parameter size:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               0,                                                                                   // Dummy parameter size: "0" means we ask for the # of parameters.
               NULL,                                                                                // Dummy parameter.
               &loc_parameter_size                                                                  // Returned parameter size.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  // Getting parameter information:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               loc_parameter_size,                                                                  // Parameter size.
               &loc_parameter_value,                                                                // Returned parameter value.
               NULL                                                                                 // Returned parameter size (NULL = ignored).
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  return (loc_parameter_value);                                                                     // Returning parameter value...
}

cl_device_fp_config device::get_cl_device_fp_config
(
 cl_device_id   loc_device_id,                                                                      // OpenCL device ID.
 cl_device_info loc_parameter_name                                                                  // Parameter name.
)
{
  cl_int              loc_error;                                                                    // Error code.
  size_t              loc_parameter_size;                                                           // Parameter size.
  cl_device_fp_config loc_parameter_value;                                                          // Parameter value.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting parameter size:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               0,                                                                                   // Dummy parameter size: "0" means we ask for the # of parameters.
               NULL,                                                                                // Dummy parameter.
               &loc_parameter_size                                                                  // Returned parameter size.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  // Getting parameter information:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               loc_parameter_size,                                                                  // Parameter size.
               &loc_parameter_value,                                                                // Returned parameter value.
               NULL                                                                                 // Returned parameter size (NULL = ignored).
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  return (loc_parameter_value);                                                                     // Returning parameter value...
}

cl_device_exec_capabilities device::get_cl_device_exec_capabilities
(
 cl_device_id   loc_device_id,                                                                      // OpenCL device ID.
 cl_device_info loc_parameter_name                                                                  // Parameter name.
)
{
  cl_int                      loc_error;                                                            // Error code.
  size_t                      loc_parameter_size;                                                   // Parameter size.
  cl_device_exec_capabilities loc_parameter_value;                                                  // Parameter value.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting parameter size:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               0,                                                                                   // Dummy parameter size: "0" means we ask for the # of parameters.
               NULL,                                                                                // Dummy parameter.
               &loc_parameter_size                                                                  // Returned parameter size.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  // Getting parameter information:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               loc_parameter_size,                                                                  // Parameter size.
               &loc_parameter_value,                                                                // Returned parameter value.
               NULL                                                                                 // Returned parameter size (NULL = ignored).
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  return (loc_parameter_value);                                                                     // Returning parameter value...
}

cl_ulong device::get_cl_ulong
(
 cl_device_id   loc_device_id,                                                                      // OpenCL device ID.
 cl_device_info loc_parameter_name                                                                  // Parameter name.
)
{
  cl_int   loc_error;                                                                               // Error code.
  size_t   loc_parameter_size;                                                                      // Parameter size.
  cl_ulong loc_parameter_value;                                                                     // Parameter value.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting parameter size:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               0,                                                                                   // Dummy parameter size: "0" means we ask for the # of parameters.
               NULL,                                                                                // Dummy parameter.
               &loc_parameter_size                                                                  // Returned parameter size.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  // Getting parameter information:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               loc_parameter_size,                                                                  // Parameter size.
               &loc_parameter_value,                                                                // Returned parameter value.
               NULL                                                                                 // Returned parameter size (NULL = ignored).
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  return (loc_parameter_value);                                                                     // Returning parameter value...
}

cl_device_mem_cache_type device::get_cl_device_mem_cache_type
(
 cl_device_id   loc_device_id,                                                                      // OpenCL device ID.
 cl_device_info loc_parameter_name                                                                  // Parameter name.
)
{
  cl_int                   loc_error;                                                               // Error code.
  size_t                   loc_parameter_size;                                                      // Parameter size.
  cl_device_mem_cache_type loc_parameter_value;                                                     // Parameter value.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting parameter size:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               0,                                                                                   // Dummy parameter size: "0" means we ask for the # of parameters.
               NULL,                                                                                // Dummy parameter.
               &loc_parameter_size                                                                  // Returned parameter size.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  // Getting parameter information:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               loc_parameter_size,                                                                  // Parameter size.
               &loc_parameter_value,                                                                // Returned parameter value.
               NULL                                                                                 // Returned parameter size (NULL = ignored).
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  return (loc_parameter_value);                                                                     // Returning parameter value...
}

size_t device::get_size_t
(
 cl_device_id   loc_device_id,                                                                      // OpenCL device ID.
 cl_device_info loc_parameter_name                                                                  // Parameter name.
)
{
  cl_int loc_error;                                                                                 // Error code.
  size_t loc_parameter_size;                                                                        // Parameter size.
  size_t loc_parameter_value;                                                                       // Parameter value.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting parameter size:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               0,                                                                                   // Dummy parameter size: "0" means we ask for the # of parameters.
               NULL,                                                                                // Dummy parameter.
               &loc_parameter_size                                                                  // Returned parameter size.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  // Getting parameter information:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               loc_parameter_size,                                                                  // Parameter size.
               &loc_parameter_value,                                                                // Returned parameter value.
               NULL                                                                                 // Returned parameter size (NULL = ignored).
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  return (loc_parameter_value);                                                                     // Returning parameter value...
}

cl_device_local_mem_type device::get_cl_device_local_mem_type
(
 cl_device_id   loc_device_id,                                                                      // OpenCL device ID.
 cl_device_info loc_parameter_name                                                                  // Parameter name.
)
{
  cl_int                   loc_error;                                                               // Error code.
  size_t                   loc_parameter_size;                                                      // Parameter size.
  cl_device_local_mem_type loc_parameter_value;                                                     // Parameter value.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting parameter size:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               0,                                                                                   // Dummy parameter size: "0" means we ask for the # of parameters.
               NULL,                                                                                // Dummy parameter.
               &loc_parameter_size                                                                  // Returned parameter size.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  // Getting parameter information:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               loc_parameter_size,                                                                  // Parameter size.
               &loc_parameter_value,                                                                // Returned parameter value.
               NULL                                                                                 // Returned parameter size (NULL = ignored).
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  return (loc_parameter_value);                                                                     // Returning parameter value...
}

cl_platform_id device::get_cl_platform_id
(
 cl_device_id   loc_device_id,                                                                      // OpenCL device ID.
 cl_device_info loc_parameter_name                                                                  // Parameter name.
)
{
  cl_int         loc_error;                                                                         // Error code.
  size_t         loc_parameter_size;                                                                // Parameter size.
  cl_platform_id loc_parameter_value;                                                               // Parameter value.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting parameter size:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               0,                                                                                   // Dummy parameter size: "0" means we ask for the # of parameters.
               NULL,                                                                                // Dummy parameter.
               &loc_parameter_size                                                                  // Returned parameter size.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  // Getting parameter information:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               loc_parameter_size,                                                                  // Parameter size.
               &loc_parameter_value,                                                                // Returned parameter value.
               NULL                                                                                 // Returned parameter size (NULL = ignored).
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  return (loc_parameter_value);                                                                     // Returning parameter value...
}

cl_device_type device::get_cl_device_type
(
 cl_device_id   loc_device_id,                                                                      // OpenCL device ID.
 cl_device_info loc_parameter_name                                                                  // Parameter name.
)
{
  cl_int         loc_error;                                                                         // Error code.
  size_t         loc_parameter_size;                                                                // Parameter size.
  cl_device_type loc_parameter_value;                                                               // Parameter value.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting parameter size:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               0,                                                                                   // Dummy parameter size: "0" means we ask for the # of parameters.
               NULL,                                                                                // Dummy parameter.
               &loc_parameter_size                                                                  // Returned parameter size.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  // Getting parameter information:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               loc_parameter_size,                                                                  // Parameter size.
               &loc_parameter_value,                                                                // Returned parameter value.
               NULL                                                                                 // Returned parameter size (NULL = ignored).
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  return (loc_parameter_value);                                                                     // Returning parameter value...
}

cl_command_queue_properties device::get_cl_command_queue_properties
(
 cl_device_id   loc_device_id,                                                                      // OpenCL device ID.
 cl_device_info loc_parameter_name                                                                  // Parameter name.
)
{
  cl_int                      loc_error;                                                            // Error code.
  size_t                      loc_parameter_size;                                                   // Parameter size.
  cl_command_queue_properties loc_parameter_value;                                                  // Parameter value.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Getting parameter size:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               0,                                                                                   // Dummy parameter size: "0" means we ask for the # of parameters.
               NULL,                                                                                // Dummy parameter.
               &loc_parameter_size                                                                  // Returned parameter size.
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  // Getting parameter information:
  loc_error = clGetDeviceInfo
              (
               loc_device_id,                                                                       // Device ID.
               loc_parameter_name,                                                                  // Parameter name.
               loc_parameter_size,                                                                  // Parameter size.
               &loc_parameter_value,                                                                // Returned parameter value.
               NULL                                                                                 // Returned parameter size (NULL = ignored).
              );

  baseline->check_error (loc_error);                                                                // Checking error...

  return (loc_parameter_value);                                                                     // Returning parameter value...
}

void device::init
(
 cl_device_id loc_device_id                                                                         // OpenCL deivce ID.
)
{
  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  address_bits                  = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_ADDRESS_BITS                                           // Parameter of interest [cl_device_info].
                                  );
  available                     = get_cl_bool                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_AVAILABLE                                              // Parameter of interest [cl_device_info].
                                  );
  compiler_available            = get_cl_bool                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_COMPILER_AVAILABLE                                     // Parameter of interest [cl_device_info].
                                  );
  double_fp_config              = get_cl_device_fp_config                                           // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_COMPILER_AVAILABLE                                     // Parameter of interest [cl_device_info].
                                  );
  endian_little                 = get_cl_bool                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_ENDIAN_LITTLE                                          // Parameter of interest [cl_device_info].
                                  );
  error_correction_support      = get_cl_bool                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_ERROR_CORRECTION_SUPPORT                               // Parameter of interest [cl_device_info].
                                  );
  execution_capabilities        = get_cl_device_exec_capabilities                                   // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_EXECUTION_CAPABILITIES                                 // Parameter of interest [cl_device_info].
                                  );
  extensions                    = get_string                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_EXTENSIONS                                             // Parameter of interest [cl_device_info].
                                  );
  global_mem_cache_size         = get_cl_ulong                                                      // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_GLOBAL_MEM_CACHE_SIZE                                  // Parameter of interest [cl_device_info].
                                  );
  global_mem_cache_type         = get_cl_device_mem_cache_type                                      // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_GLOBAL_MEM_CACHE_TYPE                                  // Parameter of interest [cl_device_info].
                                  );
  global_mem_cacheline_size     = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE                              // Parameter of interest [cl_device_info].
                                  );
  global_mem_size               = get_cl_ulong                                                      // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_GLOBAL_MEM_SIZE                                        // Parameter of interest [cl_device_info].
                                  );
  half_fp_config                = get_cl_device_fp_config                                           // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_GLOBAL_MEM_SIZE                                        // Parameter of interest [cl_device_info].
                                  );
  image_support                 = get_cl_bool                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_IMAGE_SUPPORT                                          // Parameter of interest [cl_device_info].
                                  );
  image2D_max_height            = get_size_t                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_IMAGE2D_MAX_HEIGHT                                     // Parameter of interest [cl_device_info].
                                  );
  image2D_max_width             = get_size_t                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_IMAGE2D_MAX_WIDTH                                      // Parameter of interest [cl_device_info].
                                  );
  image3D_max_depth             = get_size_t                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_IMAGE3D_MAX_DEPTH                                      // Parameter of interest [cl_device_info].
                                  );
  image3D_max_height            = get_size_t                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_IMAGE3D_MAX_HEIGHT                                     // Parameter of interest [cl_device_info].
                                  );
  image3D_max_width             = get_size_t                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_IMAGE3D_MAX_WIDTH                                      // Parameter of interest [cl_device_info].
                                  );
  local_mem_size                = get_cl_ulong                                                      // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_LOCAL_MEM_SIZE                                         // Parameter of interest [cl_device_info].
                                  );
  local_mem_type                = get_cl_device_local_mem_type                                      // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_LOCAL_MEM_TYPE                                         // Parameter of interest [cl_device_info].
                                  );
  max_clock_frequency           = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_MAX_CLOCK_FREQUENCY                                    // Parameter of interest [cl_device_info].
                                  );
  max_compute_units             = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_MAX_COMPUTE_UNITS                                      // Parameter of interest [cl_device_info].
                                  );
  max_constant_args             = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_MAX_CONSTANT_ARGS                                      // Parameter of interest [cl_device_info].
                                  );
  max_constant_buffer_size      = get_cl_ulong                                                      // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE                               // Parameter of interest [cl_device_info].
                                  );
  max_mem_alloc_size            = get_cl_ulong                                                      // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_MAX_MEM_ALLOC_SIZE                                     // Parameter of interest [cl_device_info].
                                  );
  max_parameter_size            = get_size_t                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_MAX_PARAMETER_SIZE                                     // Parameter of interest [cl_device_info].
                                  );
  max_read_image_args           = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_MAX_READ_IMAGE_ARGS                                    // Parameter of interest [cl_device_info].
                                  );
  max_samplers                  = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_MAX_SAMPLERS                                           // Parameter of interest [cl_device_info].
                                  );
  max_work_group_size           = get_size_t                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_MAX_WORK_GROUP_SIZE                                    // Parameter of interest [cl_device_info].
                                  );
  max_work_item_dimensions      = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS                               // Parameter of interest [cl_device_info].
                                  );
/*
   max_work_item_sizes           = get_info (// Getting device information...
                                            loc_device_id,// OpenCL device id [cl_device_id].
                                            CL_DEVICE_MAX_WORK_ITEM_SIZES// Parameter of interest [cl_device_info].
                                           );
 */
  max_write_image_args          = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_MAX_WRITE_IMAGE_ARGS                                   // Parameter of interest [cl_device_info].
                                  );
  mem_base_addr_align           = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_MEM_BASE_ADDR_ALIGN                                    // Parameter of interest [cl_device_info].
                                  );
  min_data_type_align_size      = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE                               // Parameter of interest [cl_device_info].
                                  );
  name                          = get_string                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_NAME                                                   // Parameter of interest [cl_device_info].
                                  );
  platform                      = get_cl_platform_id                                                // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_PLATFORM                                               // Parameter of interest [cl_device_info].
                                  );
  preferred_vector_width_char   = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR                            // Parameter of interest [cl_device_info].
                                  );
  preferred_vector_width_short  = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT                           // Parameter of interest [cl_device_info].
                                  );
  preferred_vector_width_int    = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT                             // Parameter of interest [cl_device_info].
                                  );
  preferred_vector_width_long   = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG                            // Parameter of interest [cl_device_info].
                                  );
  preferred_vector_width_float  = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT                           // Parameter of interest [cl_device_info].
                                  );
  preferred_vector_width_double = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE                          // Parameter of interest [cl_device_info].
                                  );

  profile                       = get_string                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_PROFILE                                                // Parameter of interest [cl_device_info].
                                  );
  profiling_timer_resolution    = get_size_t                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_PROFILING_TIMER_RESOLUTION                             // Parameter of interest [cl_device_info].
                                  );
  queue_properties              = get_cl_command_queue_properties                                   // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_QUEUE_PROPERTIES                                       // Parameter of interest [cl_device_info].
                                  );
  single_fp_config              = get_cl_device_fp_config                                           // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_SINGLE_FP_CONFIG                                       // Parameter of interest [cl_device_info].
                                  );
  type                          = get_cl_device_type                                                // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_TYPE                                                   // Parameter of interest [cl_device_info].
                                  );
  vendor                        = get_string                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_VENDOR                                                 // Parameter of interest [cl_device_info].
                                  );
  vendor_id                     = get_cl_uint                                                       // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_VENDOR_ID                                              // Parameter of interest [cl_device_info].
                                  );
  version                       = get_string                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DEVICE_VERSION                                                // Parameter of interest [cl_device_info].
                                  );
  driver_version                = get_string                                                        // Getting device information...
                                  (
                                   loc_device_id,                                                   // OpenCL device id [cl_device_id].
                                   CL_DRIVER_VERSION                                                // Parameter of interest [cl_device_info].
                                  );

  id                            = loc_device_id;                                                    // Initializing device_id...
}

device::~device()
{

}
