#include "device.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "DEVICE" CLASS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
device::device()
{

}

/// # Device get information value function
/// ### Description:
/// Gets the value of a device information.
string device::get_info (
                         cl_device_id   loc_device_id,                          // OpenCL device ID.
                         cl_device_info loc_parameter_name,                     // Parameter name.
                        )
{
  cl_int loc_error;                                                             // Error code.
  size_t loc_parameter_size;                                                    // Parameter size.
  string loc_parameter_value;                                                   // Parameter value.

  // Getting parameter size:
  loc_error            = clGetDeviceInfo (
                                          loc_device_id,                        // Device ID.
                                          loc_parameter_name,                   // Parameter name.
                                          0,                                    // Dummy parameter size: "0" means we ask for the # of parameters.
                                          NULL,                                 // Dummy parameter.
                                          &loc_parameter_size                   // Returned parameter size.
                                         );

  baseline->check_error (loc_error);                                            // Checking error...

  loc_parameter_buffer = new char[loc_parameter_size];                          // Text buffer.

  // Getting parameter information:
  loc_error            = clGetDeviceInfo (
                                          loc_device_id,                        // Device ID.
                                          loc_parameter_name,                   // Parameter name.
                                          loc_parameter_size,                   // Parameter size.
                                          loc_parameter_buffer,                 // Returned parameter value.
                                          NULL                                  // Returned parameter size (NULL = ignored).
                                         );

  baseline->check_error (loc_error);                                            // Checking error...

  loc_parameter_value  = loc_parameter_buffer;                                  // Setting parameter value...

  return (loc_parameter_value);                                                 // Returning parameter value...
}

/// # Initialization function
/// ### Description:
/// Gets all the device information.
void device::init (
                   cl_device_id loc_device_id                                   // OpenCL deivce ID.
                  )
{
  size_t info_size;

  // Device name info:
  name    = get_info (
                      loc_device_id,
                      CL_DEVICE_NAME
                     );

  // Device platform info:
  profile = get_info (
                      loc_device_id,
                      CL_DEVICE_PROFILE
                     );

  /*
     case CL_DEVICE_ADDRESS_BITS:
     printf("        CL_DEVICE_ADDRESS_BITS = %s\n", value);
     break;

     case CL_DEVICE_AVAILABLE:
     printf("        CL_DEVICE_AVAILABLE = %s\n", value);
     break;

     case CL_DEVICE_COMPILER_AVAILABLE:
     printf("        CL_DEVICE_COMPILER_AVAILABLE = %s\n", value);
     break;

     case CL_DEVICE_ENDIAN_LITTLE:
     printf("        CL_DEVICE_ENDIAN_LITTLE = %s\n", value);
     break;

     case CL_DEVICE_ERROR_CORRECTION_SUPPORT:
     printf("        CL_DEVICE_ERROR_CORRECTION_SUPPORT = %s\n", value);
     break;

     case CL_DEVICE_EXECUTION_CAPABILITIES:
     printf("        CL_DEVICE_EXECUTION_CAPABILITIES = %s\n", value);
     break;

     case CL_DEVICE_EXTENSIONS:
     printf("        CL_DEVICE_EXTENSIONS = %s\n", value);
     break;

     case CL_DEVICE_GLOBAL_MEM_CACHE_SIZE:
     printf("        CL_DEVICE_GLOBAL_MEM_CACHE_SIZE = %s\n", value);
     break;

     case CL_DEVICE_GLOBAL_MEM_CACHE_TYPE:
     printf("        CL_DEVICE_GLOBAL_MEM_CACHE_TYPE = %s\n", value);
     break;

     case CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE:
     printf("        CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE = %s\n", value);
     break;

     case CL_DEVICE_GLOBAL_MEM_SIZE:
     printf("        CL_DEVICE_GLOBAL_MEM_SIZE = %s\n", value);
     break;

     case CL_DEVICE_IMAGE_SUPPORT:
     printf("        CL_DEVICE_IMAGE_SUPPORT = %s\n", value);
     break;

     case CL_DEVICE_IMAGE2D_MAX_HEIGHT:
     printf("        CL_DEVICE_IMAGE2D_MAX_HEIGHT = %s\n", value);
     break;

     case CL_DEVICE_IMAGE2D_MAX_WIDTH:
     printf("        CL_DEVICE_IMAGE2D_MAX_WIDTH = %s\n", value);
     break;

     case CL_DEVICE_IMAGE3D_MAX_DEPTH:
     printf("        CL_DEVICE_IMAGE3D_MAX_DEPTH = %s\n", value);
     break;

     case CL_DEVICE_IMAGE3D_MAX_HEIGHT:
     printf("        CL_DEVICE_IMAGE3D_MAX_HEIGHT = %s\n", value);
     break;

     case CL_DEVICE_IMAGE3D_MAX_WIDTH:
     printf("        CL_DEVICE_IMAGE3D_MAX_WIDTH = %s\n", value);
     break;

     case CL_DEVICE_LOCAL_MEM_SIZE:
     printf("        CL_DEVICE_LOCAL_MEM_SIZE = %s\n", value);
     break;

     case CL_DEVICE_LOCAL_MEM_TYPE:
     printf("        CL_DEVICE_LOCAL_MEM_TYPE = %s\n", value);
     break;

     case CL_DEVICE_MAX_CLOCK_FREQUENCY:
     printf("        CL_DEVICE_MAX_CLOCK_FREQUENCY = %s\n", value);
     break;

     case CL_DEVICE_MAX_COMPUTE_UNITS:
     printf("        CL_DEVICE_MAX_COMPUTE_UNITS = %d\n", (int)*value);
     break;

     case CL_DEVICE_MAX_CONSTANT_ARGS:
     printf("        CL_DEVICE_MAX_CONSTANT_ARGS = %s\n", value);
     break;

     case CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE:
     printf("        CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE = %s\n", value);
     break;

     case CL_DEVICE_MAX_MEM_ALLOC_SIZE:
     printf("        CL_DEVICE_MAX_MEM_ALLOC_SIZE = %s\n", value);
     break;

     case CL_DEVICE_MAX_PARAMETER_SIZE:
     printf("        CL_DEVICE_MAX_PARAMETER_SIZE = %s\n", value);
     break;

     case CL_DEVICE_MAX_READ_IMAGE_ARGS:
     printf("        CL_DEVICE_MAX_READ_IMAGE_ARGS = %s\n", value);
     break;

     case CL_DEVICE_MAX_SAMPLERS:
     printf("        CL_DEVICE_MAX_SAMPLERS = %s\n", value);
     break;

     case CL_DEVICE_MAX_WORK_GROUP_SIZE:
     printf("        CL_DEVICE_MAX_WORK_GROUP_SIZE = %s\n", value);
     break;

     case CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:
     printf("        CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS = %s\n", value);
     break;

     case CL_DEVICE_MAX_WORK_ITEM_SIZES:
     printf("        CL_DEVICE_MAX_WORK_ITEM_SIZES = %s\n", value);
     break;

     case CL_DEVICE_MAX_WRITE_IMAGE_ARGS:
     printf("        CL_DEVICE_MAX_WRITE_IMAGE_ARGS = %s\n", value);
     break;

     case CL_DEVICE_MEM_BASE_ADDR_ALIGN:
     printf("        CL_DEVICE_MEM_BASE_ADDR_ALIGN = %s\n", value);
     break;

     case CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE:
     printf("        CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE = %s\n", value);
     break;

     case CL_DEVICE_NAME:
     printf("        CL_DEVICE_NAME = %s\n", value);
     break;

     case CL_DEVICE_PLATFORM:
     printf("        CL_DEVICE_PLATFORM = %s\n", value);
     break;

     case CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR:
     printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR = %s\n", value);
     break;

     case CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE:
     printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE = %s\n", value);
     break;

     case CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT:
     printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT = %s\n", value);
     break;

     case CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT:
     printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT = %s\n", value);
     break;

     case CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG:
     printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG = %s\n", value);
     break;

     case CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT:
     printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT = %s\n", value);
     break;

     case CL_DEVICE_PROFILE:
     printf("        CL_DEVICE_PROFILE = %s\n", value);
     break;

     case CL_DEVICE_PROFILING_TIMER_RESOLUTION:
     printf("        CL_DEVICE_PROFILING_TIMER_RESOLUTION = %s\n", value);
     break;

     case CL_DEVICE_QUEUE_PROPERTIES:
     printf("        CL_DEVICE_QUEUE_PROPERTIES = %s\n", value);
     break;

     case CL_DEVICE_SINGLE_FP_CONFIG:
     printf("        CL_DEVICE_SINGLE_FP_CONFIG = %s\n", value);
     break;

     case CL_DEVICE_TYPE:
     printf("        CL_DEVICE_TYPE = %s\n", value);
     break;

     case CL_DEVICE_VENDOR_ID:
     printf("        CL_DEVICE_VENDOR_ID = %s\n", value);
     break;

     case CL_DEVICE_VENDOR:
     printf("        CL_DEVICE_VENDOR = %s\n", value);
     break;

     case CL_DEVICE_VERSION:
     printf("        CL_DEVICE_VERSION = %s\n", value);
     break;

     case CL_DRIVER_VERSION:
     printf("        CL_DRIVER_VERSION = %s\n", value);
     }
   */

  id      = loc_device_id;                                                      // Initializing device_id...
}

device::~device()
{

}
