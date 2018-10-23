/// @file

#include "opencl.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// "get_error" FUNCTION //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
const char* get_error(cl_int error)
{
  switch(error)
  {
    // run-time and JIT compiler errors
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

    // compile-time errors
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

    // extension errors
    case  -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case  -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case  -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case  -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case  -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case  -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";

    default: return "Unknown OpenCL error";
  }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// "INFO" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
info::info(size_t value_size)
{
  size = value_size;                                                            // Setting value array size...
  value = (char*) malloc(value_size);                                           // Allocating value array...
}

info::~info()
{
  free(value);                                                                   // Freeing value array...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "PLATFORM" CLASS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
platform::platform()
{

}

// PRIVATE METHODS:
size_t platform::get_info_size(cl_platform_info parameter_name)
{
  cl_int  err;                                                                  // Error code.
  size_t  parameter_size;                                                       // Parameter size.

  // Getting platform information:
  err = clGetPlatformInfo(theplatform,                                          // Platform id.
                          parameter_name,                                       // Parameter name.
                          0,                                                    // Dummy parameter size: "0" means we ask for the # of parameters.
                          NULL,                                                 // Dummy parameter.
                          &parameter_size);                                     // Returned parameter size.

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  return (parameter_size);                                                      // Returning parameter size...
}

char* platform::get_info_value(cl_platform_info parameter_name, size_t parameter_size)
{
  cl_int  err;                                                                  // Error code.
  char*   parameter;                                                            // Parameter.

  // Getting platform information:
  err = clGetPlatformInfo(theplatform,                                          // Platform id.
                          parameter_name,                                       // Parameter name.
                          parameter_size,                                       // Parameter size.
                          parameter,                                            // Parameter.
                          NULL);                                                // Returned parameter size (NULL = ignored).

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  return (parameter);                                                           // Returning parameter...
}

// PUBLIC METHODS:
void platform::init(cl_platform_id pl_id)
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

  theplatform = pl_id;                                                          // Initializing theplatform...
}

platform::~platform()
{
  delete profile;
  delete version;
  delete name;
  delete vendor;
  delete extensions;
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "DEVICE" CLASS ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
device::device()
{

}

// PRIVATE METHODS:
size_t device::get_info_size(cl_device_info parameter_name)
{
  cl_int  err;                                                                  // Error code.
  size_t  parameter_size;                                                       // Parameter size.

  // Getting device information:
  err = clGetDeviceInfo(thedevice,                                              // Device id.
                        parameter_name,                                         // Parameter name.
                        0,                                                      // Dummy parameter size: "0" means we ask for the # of parameters.
                        NULL,                                                   // Dummy parameter.
                        &parameter_size);                                       // Returned parameter size.

  if(err != CL_SUCCESS)
  {
    printf("Error:  %s\n", get_error(err));
    exit(err);
  }

  return (parameter_size);
}

char* device::get_info_value(cl_device_info parameter_name, size_t parameter_size)
{
  cl_int  err;                                                                  // Error code.
  char*   parameter;                                                            // Parameter.

  // Getting platform information:
  err = clGetDeviceInfo(thedevice,                                              // Device id.
                        parameter_name,                                         // Parameter name.
                        parameter_size,                                         // Parameter size.
                        parameter,                                              // Parameter.
                        NULL);                                                  // Returned parameter size (NULL = ignored).

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  return (parameter);                                                           // Returning parameter...
}

// PUBLIC METHODS:
void device::init(cl_device_id dev_id)
{
  info*   device_name               = new info(get_info_size(CL_DEVICE_NAME));
  info*   device_platform           = new info(get_info_size(CL_DEVICE_PLATFORM));

  device_name->value                = get_info_value(CL_DEVICE_NAME, device_name->size);
  device_platform->value            = get_info_value(CL_DEVICE_PLATFORM, device_platform->size);

  thedevice = dev_id;                                                           // Initializing thedevice...
}

device::~device()
{
  delete device_name;
  delete device_platform;
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "OPENCL" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
opencl::opencl()
{
  existing_platform = NULL;                                                     // Initializing platforms IDs array...
  num_platforms = 0;                                                            // Initializing # of platforms...
  num_devices = 0;                                                              // Initializing # of devices...
  properties = NULL;                                                            // Initializing platforms properties...
  thecontext = NULL;                                                            // Initializing platforms context...
  thedevice_type = DEFAULT;                                                     // Initializing device type...
}

// PRIVATE METHODS:
cl_uint opencl::get_num_platforms()
{
  cl_int err;                                                                   // Error code.
  cl_uint num_pl;                                                               // # of platforms.

  printf("Action: getting number of OpenCL platforms... ");

  // Getting number of existing OpenCL platforms:
  err = clGetPlatformIDs(0,                                                     // Dummy # of platforms ("0" means we are asking for the # of platfomrs).
                         NULL,                                                  // Dummy platfomrs id.
                         &num_pl);                                              // Returned # of existing platfomrs.

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("\n        Found %d platform(s)!\n", num_platforms);
  printf("        DONE!\n");

  return num_pl;                                                                // Returning # of existing platforms...
}

cl_uint opencl::get_platforms()
{
  cl_int          err;                                                          // Error code.
  cl_platform_id* pl_id;                                                        // Platform ID array.
  cl_uint         num_pl;                                                       // # of existing platfomrs.
  int             i;                                                            // Index.

  num_pl = get_num_platforms();                                                 // Getting # of existing platfomrs...
  pl_id = (cl_platform_id*) malloc(sizeof(cl_platform_id) * num_pl);            // Allocating platform array...

  // Getting OpenCL platform IDs:
  err = clGetPlatformIDs(num_pl,                                                // # of existing platforms.
                         pl_id,                                                 // Platform IDs array.
                         NULL);                                                 // Dummy # of platfomrs.

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  *existing_platform = new platform[num_pl];                                    // Platform object array.

  for(i = 0; i < num_pl; i++)
  {
    existing_platform[i]->init(pl_id[i]);                                       // Initializing platform objects...
  }

  printf("\n        Found %d platform(s)!\n", num_pl);
  printf("        DONE!\n");

  return(num_pl);
}

cl_uint opencl::get_num_devices(cl_uint pl_index)
{
  cl_int          err;                                                          // Error code.
  cl_uint         num_devices;                                                  // # of devices.

  printf("Action: getting number of OpenCL devices... ");

  err = clGetDeviceIDs(existing_platform[pl_index]->theplatform,                // Getting number of existing OpenCL GPU devices...
                       thedevice_type,                                          // Device type.
                       0,                                                       // Dummy # of devices ("0" means we are asking for the # of devices).
                       NULL,                                                    // Dummy device.
                       &num_devices);                                           // Returned # of existing devices.

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("\n        Found %d device(s)!\n", num_devices);
  printf("        DONE!\n");

  return(num_devices);                                                          // Returning number of existing OpenCL GPU devices...
}

cl_device_id* opencl::get_devices(cl_uint pl_index)
{
  cl_int          err;
  cl_uint         num_devices;
  cl_device_id*   dev_id;
  int             i;

  num_devices = get_num_devices(pl_index);                                      // Getting # of existing devices...
  dev_id = (cl_device_id*) malloc(sizeof(cl_device_id) * num_devices);          // Allocating device array...

  // Getting OpenCL device IDs...
  err = clGetDeviceIDs(existing_platform[pl_index]->theplatform,                // Platform...
                       thedevice_type,                                          // Device type.
                       num_devices,                                             // # of devices.
                       dev_id,                                                  // Device array.
                       NULL);                                                   // Dummy # of existing devices.

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  *existing_device = new device[num_devices];

  for(i = 0; i < num_devices; i++)
  {
    existing_device[i]->init(dev_id[i]);                                        // Initializing existing devices...
  }

  printf("\n        Found %d device(s)!\n", num_devices);
  printf("        DONE!\n");

  return(dev_id);
}

// PUBLIC METHODS:
void opencl::init(GLFWwindow* thewindow, device_type dev_type)
{
  cl_uint pl_index;                                                             // Platform index.
  cl_uint dev_index;                                                            // Device index.
  cl_int  err;                                                                  // Error code.

  printf("Action: finding OpenCL platforms...\n");

  switch (dev_type)                                                             // Setting device type...
  {
    case CPU:
      thedevice_type = CL_DEVICE_TYPE_CPU;
    break;

    case GPU:
      thedevice_type = CL_DEVICE_TYPE_GPU;
    break;

    case ACCELERATOR:
      thedevice_type = CL_DEVICE_TYPE_ACCELERATOR;
    break;

    case DEFAULT:
      thedevice_type = CL_DEVICE_TYPE_DEFAULT;
    break;

    case ALL:
      thedevice_type = CL_DEVICE_TYPE_ALL;
    break;

    default:
      thedevice_type = CL_DEVICE_TYPE_DEFAULT;
    break;
  }

  num_platforms = get_platforms();                                              // Getting number of existing platforms [#]...

  for (pl_index = 0; pl_index < num_platforms; pl_index++)
  {
    printf("        PLATFORM #%d:\n", pl_index + 1);
    printf("        --> profile: %s\n", existing_platform[pl_index]->profile->value);
    printf("        --> version: %s\n", existing_platform[pl_index]->version->value);
    printf("        --> name:    %s\n", existing_platform[pl_index]->name->value);
    printf("        --> vendor:  %s\n", existing_platform[pl_index]->vendor->value);
    printf("\n");
  }

  printf("DONE!\n");

  if (num_platforms > 1)
  {
    printf("Action: please choose a platform [1...%d", pl_index);
    choosen_platform = query_numeric(" + enter]: ", 1, num_platforms) - 1;
  }

  else
  {
    choosen_platform = 0;
  }

  printf("DONE!\n");

  printf("Action: finding OpenCL GPU devices...\n");

  num_devices = get_devices(choosen_platform);                                  // Getting # of existing GPU devices on choosen platform [#]...

  for (dev_index = 0; dev_index < num_devices; dev_index++)
  {
    printf("        DEVICE #%d:\n", dev_index);
    printf("        --> device name: %s\n", existing_device[dev_index]->device_name->value);
    printf("        --> device platform: %s\n", existing_device[dev_index]->device_platform->value);
    printf("\n");
  }

  window = thewindow;

  #ifdef __APPLE__                                                              // Checking for APPLE system...
    printf("Found APPLE system!\n");                                            // Printing message...

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
    printf("Found LINUX system!\n");                                            // Printing message...

    cl_context_properties properties[] =                                        // Setting LINUX OpenCL context properties...
    {
      CL_GL_CONTEXT_KHR, (cl_context_properties)glfwGetGLXContext(window),
      CL_GLX_DISPLAY_KHR, (cl_context_properties)glfwGetX11Display(),
      CL_CONTEXT_PLATFORM, (cl_context_properties)existing_platform[choosen_platform],
      0
    };
  #endif

  #ifdef __WINDOWS__                                                            // Checking for WINDOWS system...
    printf("Found WINDOWS system!\n");                                          // Printing message...

    cl_context_properties properties[] =                                        // Setting WINDOWS OpenCL context properties...
    {
      CL_GL_CONTEXT_KHR, (cl_context_properties)glfwGetWGLContext(window),
      CL_WGL_HDC_KHR, (cl_context_properties)GetDC(glfwGetWin32Window(window)),
      CL_CONTEXT_PLATFORM, (cl_context_properties)existing_platform[choosen_platform],
      0
    };
  #endif

  printf("Action: creating OpenCL context... ");                                // Printing message...

  // Creating OpenCL context:
  thecontext = clCreateContext(properties,                                      // Context properties.
                              1,                                                // # of devices on choosen platform.
                              existing_device,                                  // List of existing devices on choosen platform.
                              NULL,                                             // Context error report callback function.
                              NULL,                                             // Context error report callback function argument.
                              &err);                                            // Error code.

  if(err != CL_SUCCESS)                                                         // Checking for error...
  {
    printf("\nError:  %s\n", get_error(err));                                   // Printing message...
    exit(err);                                                                  // Exiting...
  }

  printf("DONE!\n");                                                            // Printing message...
}

opencl::~opencl()
{
  cl_int err;

  printf("Action: releasing OpenCL context... ");

  err = clReleaseContext(thecontext);                                           // Releasing OpenCL context...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  free(device);                                                                 // Freeing OpenCL devices...
  free(platform);                                                               // Freeing OpenCL platforms...

  printf("DONE!\n");
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// "QUEUE" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
queue::queue(cl_context thecontext, cl_uint dev_index)
{
  device_index = dev_index;                                                     // Initializing device index...
  thequeue = NULL;                                                              // Initializing thequeue...
  context = thecontext;                                                         // Initializing context...
}

void queue::init()
{
  cl_int  err;                                                                  // Error code.

  printf("Action: creating OpenCL command queue... ");

  // Creating OpenCL queue:
  thequeue = clCreateCommandQueue(context,                                      // OpenCL context.
                                  existing_device[device_index]->thedevice,     // Device id.
                                  0,                                            // Queue properties (con be used for enabling profiling).
                                  &err);                                        // Error code.

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

queue::~queue()
{
  cl_int  err;                                                                  // Error code.

  printf("Action: releasing the OpenCL command queue... ");

  err = clReleaseCommandQueue(thequeue);                                        // Releasing OpenCL queue...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "KERNEL" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
kernel::kernel(cl_context thecontext)
{
  kernel_source       = NULL;
  program             = NULL;
  size                = 0;
  dimension           = 0;
  event               = NULL;
  thekernel           = NULL;
  context             = thecontext;                                             // Initializing context...
}

void kernel::init(char* neutrino_path, char* kernel_file_name, size_t kernel_size, cl_uint kernel_dimension)
{
  cl_int    err;                                                                // Error code.
  size_t    kernel_source_size;                                                 // Kernel source size [characters].

  file_name = kernel_filename;
  size      = kernel_size;
  dimension = kernel_dimension;

  printf("Action: loading OpenCL kernel source from file... ");

  load_file(neutrino_path, file_name, &source, &source_size);

  printf("Action: creating OpenCL program from kernel source... ");

  // Creating OpenCL program from its source:
  program = clCreateProgramWithSource(context,
                                      1,
                                      (const char**)&source,
                                      &source_size,
                                      &err);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  free(source);                                                                 // Freeing OpenCL kernel buffer...
  printf("DONE!\n");

  printf("Action: building OpenCL program... ");

  // Building OpenCL program:
  err = clBuildProgram(program,
                       1,
                       device,
                       "",
                       NULL,
                       NULL);

  if (err != CL_SUCCESS)                                                        // Checking compiled kernel...
  {
    printf("\nError:  %s\n", get_error(err));

    // Getting OpenCL compiler information:
    err = clGetProgramBuildInfo(program,
                                device[0],
                                CL_PROGRAM_BUILD_LOG,
                                0,
                                NULL,
                                &log_size);

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }

    log = (char*) calloc(log_size + 1, sizeof(char));                           // Allocating log buffer...

    if (!log)
    {
      printf("\nError:  unable to allocate buffer memory log!\n");
      exit(EXIT_FAILURE);
    }

    // Reading OpenCL compiler error log:
    err = clGetProgramBuildInfo(program,
                                device[0],
                                CL_PROGRAM_BUILD_LOG,
                                log_size + 1,
                                log,
                                NULL);

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }

    printf("%s\n", log);                                                        // Displaying log...
    free(log);                                                                  // Freeing log...
    exit(err);                                                                  // Exiting...
  }

  printf("DONE!\n");

  printf("Action: creating OpenCL kernel object from program... ");

  // Creating OpenCL kernel:
  thekernel = clCreateKernel(program,
                             KERNEL_NAME,
                             &err);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

void kernel::execute(queue* q, kernel_event k_ev)
{
  err = clEnqueueNDRangeKernel(q->thequeue,                                     // Enqueueing OpenCL kernel (as a single task)...
                               thekernel,
                               dimension,
                               NULL,
                               &size,
                               NULL,
                               0,
                               NULL,
                               &event);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  switch(k_ev)
  {
    case WAIT:
      err = clWaitForEvents(1, &event);                                         // Waiting for kernel execution to be completed (host blocking)...

      if(err != CL_SUCCESS)
      {
        printf("\nError:  %s\n", get_error(err));
        exit(err);
      }
    break;

    case DONT_WAIT:
                                                                                // Doing nothing!
    break;

    default:
      err = clWaitForEvents(1, &event);                                         // Waiting for kernel execution to be completed (host blocking)...

      if(err != CL_SUCCESS)
      {
        printf("\nError:  %s\n", get_error(err));
        exit(err);
      }
    break;
  }


}

kernel::~kernel()
{
  printf("Action: releasing OpenCL kernel... ");

  err = clReleaseKernel(thekernel);                                             // Releasing OpenCL kernel...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");

  printf("Action: releasing OpenCL kernel event... ");
  err = clReleaseEvent(event);                                                  // Releasing OpenCL event...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");

  printf("Action: releasing OpenCL program... ");

  err = clReleaseProgram(program);                                              // Releasing OpenCL program...

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
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
