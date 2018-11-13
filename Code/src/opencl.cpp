/// @file

#include "opencl.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "OPENCL" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
opencl::opencl()
{
  existing_platform = NULL;                                                     // Initializing platforms IDs array...
  platforms_number = 0;                                                         // Initializing # of platforms...
  devices_number = 0;                                                           // Initializing # of devices...
  properties = NULL;                                                            // Initializing platforms' properties...
  context_id = NULL;                                                            // Initializing platforms' context...
  device_type = DEFAULT;                                                        // Initializing device type...
}

// PRIVATE METHODS:
const char* opencl::get_error(cl_int loc_error)
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

cl_uint opencl::get_num_platforms()
{
  cl_int loc_err;                                                               // Local error code.
  cl_uint loc_platforms_number;                                                 // Local # of platforms.

  printf("Action: getting number of OpenCL platforms... ");

  // Getting number of existing OpenCL platforms:
  loc_err = clGetPlatformIDs(0,                                                 // Dummy # of platforms ("0" means we are asking for the # of platfomrs).
                            NULL,                                               // Dummy platfomrs id.
                            &loc_platforms_number);                             // Returned local # of existing platforms.

  if(loc_err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  printf("\n        Found %d platform(s)!\n", loc_platforms_number);
  printf("        DONE!\n");

  return loc_platforms_number;                                                  // Returning local # of existing platforms...
}

cl_uint opencl::get_platforms()
{
  cl_int          loc_err;                                                      // Local error code.
  cl_platform_id* loc_platform_id;                                              // Local platform ID array.
  cl_uint         loc_platforms_number;                                         // Local # of existing platfomrs.
  int             i;                                                            // Index.

  loc_platforms_number = get_num_platforms();                                   // Getting # of existing platfomrs...
  loc_platform_id = (cl_platform_id*) malloc(sizeof(cl_platform_id) * loc_platforms_number);     // Allocating platform array...

  // Getting OpenCL platform IDs:
  loc_err = clGetPlatformIDs(loc_platforms_number,                              // Local # of existing platforms.
                             loc_platform_id,                                   // Local platform IDs array.
                             NULL);                                             // Dummy # of platfomrs.

  if(loc_err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  *existing_platform = new platform[loc_platforms_number];                      // Local platform object array.

  for(i = 0; i < loc_platforms_number; i++)
  {
    existing_platform[i]->init(loc_platform_id[i]);                             // Initializing platform objects...
  }

  printf("\n        Found %d platform(s)!\n", loc_platforms_number);
  printf("        DONE!\n");

  return(loc_platforms_number);
}

cl_uint opencl::get_num_devices(cl_uint loc_platform_index)
{
  cl_int          loc_err;                                                      // Local error code.
  cl_uint         loc_devices_number;                                           // Local # of devices.

  printf("Action: getting number of OpenCL devices... ");

  loc_err = clGetDeviceIDs(existing_platform[loc_platform_index]->platform_id,  // Getting number of existing OpenCL GPU devices...
                           device_type,                                         // Device type.
                           0,                                                   // Dummy # of devices ("0" means we are asking for the # of devices).
                           NULL,                                                // Dummy device.
                           &loc_devices_number);                                // Returned local # of existing devices.

  if(loc_err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  printf("\n        Found %d device(s)!\n", loc_devices_number);
  printf("        DONE!\n");

  return(loc_devices_number);                                                   // Returning local number of existing OpenCL GPU devices...
}

cl_uint opencl::get_devices(cl_uint loc_platform_index)
{
  cl_int          loc_err;
  cl_uint         loc_devices_number;
  cl_device_id*   loc_device_id;
  int             i;

  loc_devices_number = get_num_devices(loc_platform_index);                     // Getting # of existing devices...
  loc_device_id = (cl_device_id*) malloc(sizeof(cl_device_id) * loc_devices_number);           // Allocating device array...

  // Getting OpenCL device IDs...
  loc_err = clGetDeviceIDs(existing_platform[loc_platform_index]->platform_id,  // Platform...
                           device_type,                                         // Device type.
                           loc_devices_number,                                  // Local # of devices.
                           loc_device_id,                                       // Local device_id array.
                           NULL);                                               // Dummy # of existing devices.

  if(loc_err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  *existing_device = new device[loc_devices_number];

  for(i = 0; i < loc_devices_number; i++)
  {
    existing_device[i]->init(loc_device_id[i]);                                 // Initializing existing devices...
  }

  printf("\n        Found %d device(s)!\n", loc_devices_number);
  printf("        DONE!\n");

  return(loc_devices_number);
}

// PUBLIC METHODS:
void opencl::init(neutrino* loc_neutrino, GLFWwindow* loc_glfw_window, compute_device_type loc_device_type)
{
  cl_int        loc_err;                                                        // Local error code.
  cl_uint       loc_platform_index;                                             // Local platform index.
  cl_uint       loc_device_index;                                               // Local device index.
  cl_device_id* loc_existing_device_id;                                         // Local existing device_id array.
  int           i;                                                              // Index.

  printf("Action: finding OpenCL platforms...\n");

  switch(loc_device_type)                                                       // Setting device type...
  {
    case CPU:
      device_type = CL_DEVICE_TYPE_CPU;
    break;

    case GPU:
      device_type = CL_DEVICE_TYPE_GPU;
    break;

    case ACCELERATOR:
      device_type = CL_DEVICE_TYPE_ACCELERATOR;
    break;

    case DEFAULT:
      device_type = CL_DEVICE_TYPE_DEFAULT;
    break;

    case ALL:
      device_type = CL_DEVICE_TYPE_ALL;
    break;

    default:
      device_type = CL_DEVICE_TYPE_DEFAULT;
    break;
  }

  platforms_number = get_platforms();                                           // Getting number of existing platforms [#]...

  for(loc_platform_index = 0; loc_platform_index < platforms_number; loc_platform_index++)
  {
    printf("        PLATFORM #%d:\n", loc_platform_index + 1);
    printf("        --> profile: %s\n", existing_platform[loc_platform_index]->profile->value);
    printf("        --> version: %s\n", existing_platform[loc_platform_index]->version->value);
    printf("        --> name:    %s\n", existing_platform[loc_platform_index]->name->value);
    printf("        --> vendor:  %s\n", existing_platform[loc_platform_index]->vendor->value);
    printf("\n");
  }

  printf("DONE!\n");

  if(platforms_number > 1)
  {
    printf("Action: please choose a platform [1...%d", loc_platform_index);
    choosen_platform = loc_neutrino->query_numeric(" + enter]: ", 1, platforms_number) - 1;
  }

  else
  {
    choosen_platform = 0;
  }

  printf("DONE!\n");

  printf("Action: finding OpenCL GPU devices...\n");

  devices_number = get_devices(choosen_platform);                               // Getting # of existing GPU devices on choosen platform [#]...

  for(loc_device_index = 0; loc_device_index < devices_number; loc_device_index++)
  {
    printf("        DEVICE #%d:\n", loc_device_index);
    printf("        --> device name: %s\n", existing_device[loc_device_index]->device_name->value);
    printf("        --> device platform: %s\n", existing_device[loc_device_index]->device_platform->value);
    printf("\n");
  }

  printf("DONE!\n");

  if(devices_number > 1)
  {
    printf("Action: please choose a device [1...%d", loc_device_index);
    choosen_device = loc_neutrino->query_numeric(" + enter]: ", 1, devices_number) - 1;
  }

  else
  {
    choosen_device = 0;
  }

  printf("DONE!\n");

  printf("Action: identifying operative system... ");

  #ifdef __APPLE__                                                              // Checking for APPLE system...
    printf("found APPLE!\n");                                                   // Printing message...

    CGLContextObj     kCGLContext     = CGLGetCurrentContext();                 // Setting APPLE OpenCL context properties...
    CGLShareGroupObj  kCGLShareGroup  = CGLGetShareGroup(kCGLContext);          // Setting APPLE OpenCL context properties...
    cl_context_properties properties[] =                                        // Setting APPLE OpenCL context properties...
    {
      CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
      (cl_context_properties) kCGLShareGroup,
      0
    };
  #endif

  #ifdef __linux__                                                              // Checking for LINUX system...
    printf("found LINUX!\n");                                                   // Printing message...

    cl_context_properties properties[] =                                        // Setting LINUX OpenCL context properties...
    {
      CL_GL_CONTEXT_KHR, (cl_context_properties)glfwGetGLXContext(loc_glfw_window),
      CL_GLX_DISPLAY_KHR, (cl_context_properties)glfwGetX11Display(),
      CL_CONTEXT_PLATFORM, (cl_context_properties)existing_platform[choosen_platform],
      0
    };
  #endif

  #ifdef __WINDOWS__                                                            // Checking for WINDOWS system...
    printf("found WINDOWS!\n");                                                 // Printing message...

    cl_context_properties properties[] =                                        // Setting WINDOWS OpenCL context properties...
    {
      CL_GL_CONTEXT_KHR, (cl_context_properties)glfwGetWGLContext(loc_glfw_window),
      CL_WGL_HDC_KHR, (cl_context_properties)GetDC(glfwGetWin32Window(loc_glfw_window)),
      CL_CONTEXT_PLATFORM, (cl_context_properties)existing_platform[choosen_platform],
      0
    };
  #endif

  printf("Action: creating OpenCL context... ");                                // Printing message...

  // Creating OpenCL context:
  /*
  loc_existing_device_id = (cl_device_id*) malloc(devices_number);

  for(i = 0; i < devices_number; i++)
  {
    loc_existing_device_id[i] = existing_device[i]->device_id;                  // Initializing existing devices...
  }
  */

  // EZOR: 02NOV2018. For the moment we create a context made of only 1 device (choosen device).
  loc_existing_device_id = (cl_device_id*) malloc(1);
  loc_existing_device_id[0] = existing_device[choosen_device]->device_id;

  context_id = clCreateContext(properties,                                      // Context properties.
                               1,                                               // # of devices on choosen platform.
                               loc_existing_device_id,                          // Local list of existing devices on choosen platform.
                               NULL,                                            // Context error report callback function.
                               NULL,                                            // Context error report callback function argument.
                               &loc_err);                                       // Local error code.

  if(loc_err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  free(loc_existing_device_id);                                                 // Freeing local existing device ids...

  printf("DONE!\n");                                                            // Printing message...
}

opencl::~opencl()
{
  cl_int loc_err;                                                               // Local error code.

  printf("Action: releasing    OpenCL context... ");

  loc_err = clReleaseContext(context_id);                                       // Releasing OpenCL context...

  if(loc_err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(loc_err));
    exit(loc_err);
  }

  printf("DONE!\n");
}





/*
  switch (name_param)
  {
    case CL_PLATFORM_PROFILE:
      printf("        CL_PLATFORM_PROFILE = %s\n", value);
    break;

    case CL_PLATFORM_VERSION:
      printf("        CL_PLATFORM_VERSION = %s\n", value);
    break;

    case CL_PLATFORM_NAME:
      printf("        CL_PLATFORM_NAME = %s\n", value);
    break;

    case CL_PLATFORM_VENDOR:
      printf("        CL_PLATFORM_VENDOR = %s\n", value);
    break;

    case CL_PLATFORM_EXTENSIONS:
      printf("        CL_PLATFORM_EXTENSIONS = %s\n", value);
  }

*/




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
