#include "device.hpp"

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "DEVICE" CLASS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
device::device()
{

}

/// # OpenCL error get function
/// ### Description:
/// Translates an OpenCL numeric error code into a human-readable string.
const char* device::get_error (
                               cl_int loc_error
                              )
{
  switch(loc_error)
  {
    // Run-time and JIT compiler errors:
    case      0: return "CL_SUCCESS";
    case     -1: return "CL_DEVICE_NOT_FOUND";
    case     -2: return "CL_DEVICE_NOT_AVAILABLE";
    case     -3: return "CL_COMPILER_NOT_AVAILABLE";
    case     -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case     -5: return "CL_OUT_OF_RESOURCES";
    case     -6: return "CL_OUT_OF_HOST_MEMORY";
    case     -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case     -8: return "CL_MEM_COPY_OVERLAP";
    case     -9: return "CL_IMAGE_FORMAT_MISMATCH";
    case    -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case    -11: return "CL_BUILD_PROGRAM_FAILURE";
    case    -12: return "CL_MAP_FAILURE";
    case    -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
    case    -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
    case    -15: return "CL_COMPILE_PROGRAM_FAILURE";
    case    -16: return "CL_LINKER_NOT_AVAILABLE";
    case    -17: return "CL_LINK_PROGRAM_FAILURE";
    case    -18: return "CL_DEVICE_PARTITION_FAILED";
    case    -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

    // Compile-time errors:
    case    -30: return "CL_INVALID_VALUE";
    case    -31: return "CL_INVALID_DEVICE_TYPE";
    case    -32: return "CL_INVALID_PLATFORM";
    case    -33: return "CL_INVALID_DEVICE";
    case    -34: return "CL_INVALID_CONTEXT";
    case    -35: return "CL_INVALID_QUEUE_PROPERTIES";
    case    -36: return "CL_INVALID_COMMAND_QUEUE";
    case    -37: return "CL_INVALID_HOST_PTR";
    case    -38: return "CL_INVALID_MEM_OBJECT";
    case    -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case    -40: return "CL_INVALID_IMAGE_SIZE";
    case    -41: return "CL_INVALID_SAMPLER";
    case    -42: return "CL_INVALID_BINARY";
    case    -43: return "CL_INVALID_BUILD_OPTIONS";
    case    -44: return "CL_INVALID_PROGRAM";
    case    -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
    case    -46: return "CL_INVALID_KERNEL_NAME";
    case    -47: return "CL_INVALID_KERNEL_DEFINITION";
    case    -48: return "CL_INVALID_KERNEL";
    case    -49: return "CL_INVALID_ARG_INDEX";
    case    -50: return "CL_INVALID_ARG_VALUE";
    case    -51: return "CL_INVALID_ARG_SIZE";
    case    -52: return "CL_INVALID_KERNEL_ARGS";
    case    -53: return "CL_INVALID_WORK_DIMENSION";
    case    -54: return "CL_INVALID_WORK_GROUP_SIZE";
    case    -55: return "CL_INVALID_WORK_ITEM_SIZE";
    case    -56: return "CL_INVALID_GLOBAL_OFFSET";
    case    -57: return "CL_INVALID_EVENT_WAIT_LIST";
    case    -58: return "CL_INVALID_EVENT";
    case    -59: return "CL_INVALID_OPERATION";
    case    -60: return "CL_INVALID_GL_OBJECT";
    case    -61: return "CL_INVALID_BUFFER_SIZE";
    case    -62: return "CL_INVALID_MIP_LEVEL";
    case    -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
    case    -64: return "CL_INVALID_PROPERTY";
    case    -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
    case    -66: return "CL_INVALID_COMPILER_OPTIONS";
    case    -67: return "CL_INVALID_LINKER_OPTIONS";
    case    -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

    // Extension errors:
    case  -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case  -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case  -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case  -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case  -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case  -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";

    default: return "Unknown OpenCL error";
  }
}

/// # OpenCL error check function
/// ### Description:
/// Checks for an OpenCL error code and print it to stdout.
void device::check_error (
                          cl_int loc_error                                      // Error code.
                         )
{
  if(loc_error != CL_SUCCESS)                                                   // Checking local error code...
  {
    baseline -> error (get_error (loc_error));                                  // Printing error message...
    exit (EXIT_FAILURE);                                                        // Exiting...
  }
}

/// # Device get information size function
/// ### Description:
/// Gets the size of a device information.
size_t device::get_info_size (
                              cl_device_id   loc_device_id,                     // OpenCL device ID.
                              cl_device_info loc_parameter_name                 // Device parameter.
                             )
{
  cl_int loc_error;                                                             // Error code.
  size_t loc_parameter_size;                                                    // Parameter size.

  // Getting platform information:
  loc_error = clGetDeviceInfo (
                               loc_device_id,                                   // Device ID.
                               loc_parameter_name,                              // Parameter name.
                               0,                                               // Dummy parameter size: "0" means we ask for the # of parameters.
                               NULL,                                            // Dummy parameter.
                               &loc_parameter_size                              // Returned parameter size.
                              );

  check_error (loc_error);

  return (loc_parameter_size);                                                  // Returning parameter size...
}

/// # Device get information value function
/// ### Description:
/// Gets the value of a device information.
char* device::get_info_value (
                              cl_device_id   loc_device_id,                     // OpenCL device ID.
                              cl_device_info loc_parameter_name,                // Parameter name.
                              size_t         loc_parameter_size                 // Parameter size.
                             )
{
  cl_int loc_error;                                                             // Error code.
  parameter_value = new char[loc_parameter_size];                               // Parameter value.

  // Getting platform information:
  loc_error       = clGetDeviceInfo (
                                     loc_device_id,                             // Device ID.
                                     loc_parameter_name,                        // Parameter name.
                                     loc_parameter_size,                        // Parameter size.
                                     parameter_value,                           // Returned parameter value.
                                     NULL                                       // Returned parameter size (NULL = ignored).
                                    );

  check_error (loc_error);

  return (parameter_value);                                                     // Returning parameter value...
}

/// # Initialization function
/// ### Description:
/// Gets all the device information.
void device::init (
                   cl_device_id loc_device_id                                   // OpenCL deivce ID.
                  )
{
  // Device name info:
  name             = new info (
                               get_info_size (
                                              loc_device_id,
                                              CL_DEVICE_NAME
                                             )
                              );

  name -> value    = get_info_value (
                                     loc_device_id,
                                     CL_DEVICE_NAME,
                                     name -> size
                                    );

  // Device platform info:
  profile          = new info (
                               get_info_size (
                                              loc_device_id,
                                              CL_DEVICE_PROFILE
                                             )
                              );

  profile -> value = get_info_value (
                                     loc_device_id,
                                     CL_DEVICE_PROFILE,
                                     profile -> size
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

  id               = loc_device_id;                                             // Initializing device_id...
}

device::~device()
{
  delete name;
  delete profile;
  delete parameter_value;
}
