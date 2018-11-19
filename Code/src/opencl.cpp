/// @file

#include "opencl.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "OPENCL" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
opencl::opencl()
{
  opencl_platform = NULL;                                                       // Initializing platforms IDs array...
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

// OpenCL error check function:
void opencl::check_error          (
                                    cl_int loc_error                            // Error code.
                                  )
{
  if(loc_error != CL_SUCCESS)                                                   // Checking local error code...
  {
    printf("\nError:  %s\n", get_error(loc_error));                             // Printing error message...
    exit(EXIT_FAILURE);                                                         // Exiting...
  }
}

cl_uint opencl::get_platforms_number()
{
  cl_int  loc_error;                                                            // Error code.
  cl_uint loc_platforms_number;                                                 // # of platforms.

  printf("Action: getting number of OpenCL platforms... ");                     // Printing message...

  // Getting number of existing OpenCL platforms:
  loc_error = clGetPlatformIDs(
                                0,                                              // Dummy # of platforms ("0" means we are asking for the # of platfomrs).
                                NULL,                                           // Dummy platfomrs id.
                                &loc_platforms_number                           // Returned local # of existing platforms.
                              );

  check_error(loc_error);                                                       // Checking returned error code...

  printf("\n        Found %d platform(s)!\n", loc_platforms_number);
  printf("        DONE!\n");

  return loc_platforms_number;                                                  // Returning # of existing platforms...
}

cl_platform_id opencl::get_platform_id(cl_uint loc_platform_index)
{
  cl_int          loc_error;                                                    // Error code.
  cl_platform_id* loc_platform_id;                                              // Platform IDs array.
  cl_platform_id  loc_selected_platform_id;

  printf("Action: getting OpenCL platform ID... ");                             // Printing message...

  loc_platform_id = new cl_platform_id[platforms_number];                       // Allocating platform array...

  // Getting OpenCL platform IDs:
  loc_error = clGetPlatformIDs(
                                platforms_number,                               // # of existing platforms.
                                loc_platform_id,                                // Platform IDs array.
                                NULL                                            // Dummy # of platforms.
                              );

  check_error(loc_error);                                                       // Checking returned error code...

  loc_selected_platform_id = loc_platform_id[loc_platform_index];               // Setting id of selected platform...
  delete loc_platform_id;                                                       // Deleting platform IDs array...

  printf("        DONE!\n");                                                    // Printing message...

  return(loc_selected_platform_id);                                             // Returning selected platform ID...
}

cl_uint opencl::get_devices_number()
{
  cl_int          loc_error;                                                    // Error code.
  cl_uint         loc_devices_number;                                           // # of devices.

  printf("Action: getting number of OpenCL devices... ");

  // Getting number of existing OpenCL devices:
  loc_error = clGetDeviceIDs  (
                                opencl_platform->id,                            // Platform ID.
                                device_type,                                    // Device type.
                                0,                                              // Dummy # of devices ("0" means we are asking for the # of devices).
                                NULL,                                           // Dummy device.
                                &loc_devices_number                             // Returned local # of existing devices.
                              );

  check_error(loc_error);                                                       // Checking returned error code...

  printf("\n        Found %d device(s)!\n", loc_devices_number);
  printf("        DONE!\n");

  return(loc_devices_number);                                                   // Returning # of existing devices...
}

cl_device_id opencl::get_device_id(cl_uint loc_device_index)
{
  cl_int          loc_error;
  cl_device_id*   loc_device_id;
  cl_device_id    loc_selected_device_id;

  printf("Action: getting OpenCL device ID... ");                               // Printing message...

  devices_number = get_devices_number();                                        // Getting # of existing devices...
  loc_device_id = new cl_device_id[devices_number];                             // Allocating platform array...

  // Getting OpenCL device IDs:
  loc_error = clGetDeviceIDs  (
                                opencl_platform->id,                            // Platform ID.
                                device_type,                                    // Device type.
                                platforms_number,                               // # of existing platforms.
                                loc_device_id,                                  // Device IDs array.
                                NULL                                            // Dummy # of platforms.
                              );

  check_error(loc_error);                                                       // Checking returned error code...

  loc_selected_device_id = loc_device_id[loc_device_index];                     // Setting ID of selected device...
  delete loc_device_id;                                                         // Deleting device IDs array...

  printf("        DONE!\n");                                                    // Printing message...

  return(loc_selected_device_id);                                               // Returning selected device ID...
}

// PUBLIC METHODS:
void opencl::init(neutrino* loc_neutrino, GLFWwindow* loc_glfw_window, compute_device_type loc_device_type)
{
  cl_int            loc_error;                                                  // Error code.
  cl_platform_id    loc_platform_id;                                            // Platform ID.
  cl_device_id      loc_device_id;                                              // Device ID.
  cl_int            i;                                                          // Index.

  device_type_text  = new char[SIZE_TEXT_MAX];                                  // Device type text [string].

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////// SETTING TARGET DEVICE TYPE //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  printf("Action: setting target device type = ");                              // Printing message...

  switch(loc_device_type)                                                       // Selecting device type...
  {
    case CPU:
      device_type = CL_DEVICE_TYPE_CPU;                                         // Setting device type = CPU...
      device_type_text = (char*) "CPU";                                         // Printing message...
    break;

    case GPU:
      device_type = CL_DEVICE_TYPE_GPU;                                         // Setting device type = GPU...
      device_type_text = (char*) "GPU";                                         // Printing message...
    break;

    case ACCELERATOR:
      device_type = CL_DEVICE_TYPE_ACCELERATOR;                                 // Setting device type = ACCELERATOR...
      device_type_text = (char*) "ACCELERATOR";                                 // Printing message...
    break;

    case DEFAULT:
      device_type = CL_DEVICE_TYPE_DEFAULT;                                     // Setting device type = DEFAULT...
      device_type_text = (char*) "DEFAULT";                                     // Printing message...
    break;

    case ALL:
      device_type = CL_DEVICE_TYPE_ALL;                                         // Setting device type = ALL...
      device_type_text = (char*) "ALL";                                         // Printing message...
    break;

    default:
      device_type = CL_DEVICE_TYPE_DEFAULT;                                     // Setting device type = DEFAULT...
      device_type_text = (char*) "DEFAULT";                                     // Printing message...
    break;
  }

  printf("%s...", device_type_text);                                            // Printing message...

  printf("   DONE!\n");                                                         // Printing message...

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////// SETTING OPENCL PLATFORM ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  printf("Action: finding OpenCL platforms...\n");                              // Printing message...

  platforms_number = get_platforms_number();                                    // Getting # of existing platforms [#]...

  for(i = 0; i < platforms_number; i++)                                         // Checking all platforms:
  {
    loc_platform_id = get_platform_id(i);                                       // Getting platform ID...
    opencl_platform = new platform(loc_platform_id);                            // Initializing platform...
    printf("        PLATFORM #%d:\n", i + 1);                                   // Printing message...
    printf("        --> profile: %s\n", opencl_platform->profile->value);       // Printing message...
    printf("        --> version: %s\n", opencl_platform->version->value);       // Printing message...
    printf("        --> name:    %s\n", opencl_platform->name->value);          // Printing message...
    printf("        --> vendor:  %s\n", opencl_platform->vendor->value);        // Printing message...
    printf("\n");

    delete opencl_platform;                                                     // Deleting platform...
  }

  printf("DONE!\n");                                                            // Printing message...

  if(platforms_number > 1)                                                      // Asking to select a platform, in case many have been found...
  {
    printf("Action: please select a platform [1...%d", platforms_number);       // Formulating query...
    selected_platform = (
                          loc_neutrino->query_numeric (
                                                        " + enter]: ",          // Query text.
                                                        1,                      // Minimum numeric choice in query answer.
                                                        platforms_number        // Maximum numeric choice in query answer.
                                                      )
                        ) - 1;                                                  // Setting selected platform index [0...platforms_number - 1]...
  }

  else
  {
    selected_platform = 0;                                                      // Setting 1st platform, in case it is the only found one...
  }

  loc_platform_id = get_platform_id(selected_platform);                         // Getting selected platform ID...
  opencl_platform = new platform(loc_platform_id);                              // Initializing platform...

  printf("DONE!\n");

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// SETTING OPENCL DEVICE ////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  printf("Action: finding OpenCL %s devices...\n", device_type_text);           // Printing message...

  devices_number = get_devices_number();                                        // Getting # of existing GPU devices on selected platform [#]...

  for(i = 0; i < devices_number; i++)                                           // Checking all devices:
  {
    loc_device_id = get_device_id(i);                                           // Getting device ID...
    opencl_device = new device(loc_device_id);                                  // Initializing platform...

    printf("        DEVICE #%d:\n", i);                                         // Printing message...
    printf("        --> device name:     %s\n", opencl_device->name->value);    // Printing message...
    printf("        --> device platform: %s\n", opencl_device->profile->value); // Printing message...
    printf("\n");                                                               // Printing message...

    delete opencl_device;                                                       // Deleting device...
  }

  printf("DONE!\n");                                                            // Printing message...

  if(devices_number > 1)                                                        // Asking to select a platform, in case many have been found...
  {
    printf("Action: please select a device [1...%d", devices_number);           // Formulating query...
    selected_device = (
                        loc_neutrino->query_numeric (
                                                      " + enter]: ",            // Query text.
                                                      1,                        // Minimum numeric choice in query answer.
                                                      devices_number            // Maximum numeric choice in query answer.
                                                    )
                      ) - 1;                                                    // Setting selected device index [0...platforms_number - 1]...
  }

  else
  {
    selected_device = 0;                                                        // Setting 1st device, in case it is the only found one...
  }

  loc_device_id = get_device_id(selected_device);                               // Getting selected device ID...
  opencl_device = new device(loc_device_id);                                    // Initializing device...

  printf("DONE!\n");                                                            // Printing message...

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// IDENTIFYING OS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  printf("Action: identifying operating system... ");                           // Printing message...

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
      CL_CONTEXT_PLATFORM, (cl_context_properties)opencl_platform,
      0
    };
  #endif

  #ifdef __WINDOWS__                                                            // Checking for WINDOWS system...
    printf("found WINDOWS!\n");                                                 // Printing message...

    cl_context_properties properties[] =                                        // Setting WINDOWS OpenCL context properties...
    {
      CL_GL_CONTEXT_KHR, (cl_context_properties)glfwGetWGLContext(loc_glfw_window),
      CL_WGL_HDC_KHR, (cl_context_properties)GetDC(glfwGetWin32Window(loc_glfw_window)),
      CL_CONTEXT_PLATFORM, (cl_context_properties)opencl_platform,
      0
    };
  #endif

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////// CREATING OPENCL CONTEXT ///////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  printf("Action: creating OpenCL context... ");                                // Printing message...

  context_id = clCreateContext  (
                                  properties,                                   // Context properties.
                                  1,                                            // # of devices on selected platform.
                                  &opencl_device->id,                           // Pointer to the selecet devices on selected platform.
                                  NULL,                                         // Context error report callback function.
                                  NULL,                                         // Context error report callback function argument.
                                  &loc_error                                    // Error code.
                                );

  check_error(loc_error);                                                       // Checking returned error code...

  printf("DONE!\n");                                                            // Printing message...
}

opencl::~opencl()
{
  cl_int loc_error;                                                             // Error code.

  printf("Action: releasing    OpenCL context... ");

  delete opencl_platform;
  delete opencl_device;
  delete device_type_text;
  loc_error = clReleaseContext(context_id);                                     // Releasing OpenCL context...

  check_error(loc_error);                                                       // Checking returned error code...

  printf("DONE!\n");
}
