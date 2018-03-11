#include "opencl.hpp"

char*                   value;
cl_platform_id*         platforms;
cl_device_id*           devices;
cl_context_properties*  properties;
cl_context              context;

cl_uint get_platforms()
{
  cl_uint num_platforms;

  clGetPlatformIDs(0, NULL, &num_platforms);
  platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * num_platforms);
  clGetPlatformIDs(num_platforms, platforms, NULL);

  return num_platforms;
}

void get_platform_info(cl_uint index_platform, cl_platform_info name_param)
{
  size_t  size_value;

  clGetPlatformInfo(platforms[index_platform], name_param, 0, NULL, &size_value);
  value = (char*) malloc(size_value);
  clGetPlatformInfo(platforms[index_platform], name_param, size_value, value, NULL);


  free(value);
}

cl_uint get_devices(cl_uint index_platform)
{
  cl_uint num_devices;

  clGetDeviceIDs(platforms[index_platform], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
  devices = (cl_device_id*) malloc(sizeof(cl_device_id) * num_devices);
  clGetDeviceIDs(platforms[index_platform], CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);

  return num_devices;
}

void get_device_info(cl_uint index_device, cl_device_info name_param)
{
  size_t  size_value;

  clGetDeviceInfo(devices[index_device], name_param, 0, NULL, &size_value);
  value = (char*) malloc(size_value);
  clGetDeviceInfo(devices[index_device], name_param, size_value, value, NULL);

  switch (name_param)
  {
    case CL_DEVICE_ADDRESS_BITS:                    printf("CL_DEVICE_ADDRESS_BITS = %s\n", value); break;
    case CL_DEVICE_AVAILABLE:                       printf("CL_DEVICE_AVAILABLE = %s\n", value); break;
    case CL_DEVICE_COMPILER_AVAILABLE:              printf("CL_DEVICE_COMPILER_AVAILABLE = %s\n", value); break;
    case CL_DEVICE_ENDIAN_LITTLE:                   printf("CL_DEVICE_ENDIAN_LITTLE = %s\n", value); break;
    case CL_DEVICE_ERROR_CORRECTION_SUPPORT:        printf("CL_DEVICE_ERROR_CORRECTION_SUPPORT = %s\n", value); break;
    case CL_DEVICE_EXECUTION_CAPABILITIES:          printf("CL_DEVICE_EXECUTION_CAPABILITIES = %s\n", value); break;
    case CL_DEVICE_EXTENSIONS:                      printf("CL_DEVICE_EXTENSIONS = %s\n", value); break;
    case CL_DEVICE_GLOBAL_MEM_CACHE_SIZE:           printf("CL_DEVICE_GLOBAL_MEM_CACHE_SIZE = %s\n", value); break;
    case CL_DEVICE_GLOBAL_MEM_CACHE_TYPE:           printf("CL_DEVICE_GLOBAL_MEM_CACHE_TYPE = %s\n", value); break;
    case CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE:       printf("CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE = %s\n", value); break;
    case CL_DEVICE_GLOBAL_MEM_SIZE:                 printf("CL_DEVICE_GLOBAL_MEM_SIZE = %s\n", value); break;
    case CL_DEVICE_IMAGE_SUPPORT:                   printf("CL_DEVICE_IMAGE_SUPPORT = %s\n", value); break;
    case CL_DEVICE_IMAGE2D_MAX_HEIGHT:              printf("CL_DEVICE_IMAGE2D_MAX_HEIGHT = %s\n", value); break;
    case CL_DEVICE_IMAGE2D_MAX_WIDTH:               printf("CL_DEVICE_IMAGE2D_MAX_WIDTH = %s\n", value); break;
    case CL_DEVICE_IMAGE3D_MAX_DEPTH:               printf("CL_DEVICE_IMAGE3D_MAX_DEPTH = %s\n", value); break;
    case CL_DEVICE_IMAGE3D_MAX_HEIGHT:              printf("CL_DEVICE_IMAGE3D_MAX_HEIGHT = %s\n", value); break;
    case CL_DEVICE_IMAGE3D_MAX_WIDTH:               printf("CL_DEVICE_IMAGE3D_MAX_WIDTH = %s\n", value); break;
    case CL_DEVICE_LOCAL_MEM_SIZE:                  printf("CL_DEVICE_LOCAL_MEM_SIZE = %s\n", value); break;
    case CL_DEVICE_LOCAL_MEM_TYPE:                  printf("CL_DEVICE_LOCAL_MEM_TYPE = %s\n", value); break;
    case CL_DEVICE_MAX_CLOCK_FREQUENCY:             printf("CL_DEVICE_MAX_CLOCK_FREQUENCY = %s\n", value); break;
    case CL_DEVICE_MAX_COMPUTE_UNITS:               printf("CL_DEVICE_MAX_COMPUTE_UNITS = %s\n", value); break;
    case CL_DEVICE_MAX_CONSTANT_ARGS:               printf("CL_DEVICE_MAX_CONSTANT_ARGS = %s\n", value); break;
    case CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE:        printf("CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE = %s\n", value); break;
    case CL_DEVICE_MAX_MEM_ALLOC_SIZE:              printf("CL_DEVICE_MAX_MEM_ALLOC_SIZE = %s\n", value); break;
    case CL_DEVICE_MAX_PARAMETER_SIZE:              printf("CL_DEVICE_MAX_PARAMETER_SIZE = %s\n", value); break;
    case CL_DEVICE_MAX_READ_IMAGE_ARGS:             printf("CL_DEVICE_MAX_READ_IMAGE_ARGS = %s\n", value); break;
    case CL_DEVICE_MAX_SAMPLERS:                    printf("CL_DEVICE_MAX_SAMPLERS = %s\n", value); break;
    case CL_DEVICE_MAX_WORK_GROUP_SIZE:             printf("CL_DEVICE_MAX_WORK_GROUP_SIZE = %s\n", value); break;
    case CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:        printf("CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS = %s\n", value); break;
    case CL_DEVICE_MAX_WORK_ITEM_SIZES:             printf("CL_DEVICE_MAX_WORK_ITEM_SIZES = %s\n", value); break;
    case CL_DEVICE_MAX_WRITE_IMAGE_ARGS:            printf("CL_DEVICE_MAX_WRITE_IMAGE_ARGS = %s\n", value); break;
    case CL_DEVICE_MEM_BASE_ADDR_ALIGN:             printf("CL_DEVICE_MEM_BASE_ADDR_ALIGN = %s\n", value); break;
    case CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE:        printf("CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE = %s\n", value); break;
    case CL_DEVICE_NAME:                            printf("CL_DEVICE_NAME = %s\n", value); break;
    case CL_DEVICE_PLATFORM:                        printf("CL_DEVICE_PLATFORM = %s\n", value); break;
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR:     printf("CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR = %s\n", value); break;
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE:   printf("CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE = %s\n", value); break;
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT:    printf("CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT = %s\n", value); break;
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT:      printf("CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT = %s\n", value); break;
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG:     printf("CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG = %s\n", value); break;
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT:    printf("CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT = %s\n", value); break;
    case CL_DEVICE_PROFILE:                         printf("CL_DEVICE_PROFILE = %s\n", value); break;
    case CL_DEVICE_PROFILING_TIMER_RESOLUTION:      printf("CL_DEVICE_PROFILING_TIMER_RESOLUTION = %s\n", value); break;
    case CL_DEVICE_QUEUE_PROPERTIES:                printf("CL_DEVICE_QUEUE_PROPERTIES = %s\n", value); break;
    case CL_DEVICE_SINGLE_FP_CONFIG:                printf("CL_DEVICE_SINGLE_FP_CONFIG = %s\n", value); break;
    case CL_DEVICE_TYPE:                            printf("CL_DEVICE_TYPE = %s\n", value); break;
    case CL_DEVICE_VENDOR_ID:                       printf("CL_DEVICE_VENDOR_ID = %s\n", value); break;
    case CL_DEVICE_VENDOR:                          printf("CL_DEVICE_VENDOR = %s\n", value); break;
    case CL_DEVICE_VERSION:                         printf("CL_DEVICE_VERSION = %s\n", value); break;
    case CL_DRIVER_VERSION:                         printf("CL_DRIVER_VERSION = %s\n", value);
  }

  free(value);
}

void get_context_properties()
{
  #ifdef __APPLE__
    CGLContextObj     kCGLContext     = CGLGetCurrentContext();
    CGLShareGroupObj  kCGLShareGroup  = CGLGetShareGroup(kCGLContext);
    cl_context_properties properties[] =
    {
        CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
        (cl_context_properties) kCGLShareGroup,
        0
    };
  #endif

  #ifdef __linux__
  	cl_context_properties properties[] =
  	{
      CL_GL_CONTEXT_KHR, (cl_context_properties)glfwGetGLXContext(window),
      CL_GLX_DISPLAY_KHR, (cl_context_properties)glfwGetX11Display(),
      CL_CONTEXT_PLATFORM, (cl_context_properties)platforms[0],
      0
  	};
	#endif

	#ifdef __WINDOWS__
  	cl_context_properties properties[] =
  	{
  		CL_GL_CONTEXT_KHR, (cl_context_properties)glfwGetWGLContext(window),
  		CL_WGL_HDC_KHR, (cl_context_properties)GetDC(glfwGetWin32Window(window)),
  		CL_CONTEXT_PLATFORM, (cl_context_properties)platforms[0],
  		0
  	};
	#endif
}

void create_context()
{
  int err;

  context = clCreateContextFromType(properties, CL_DEVICE_TYPE_GPU, NULL, NULL, &err);
  
  if (!(context))
  {
    fprintf(stderr, "Error: failed to create OpenCL-GL shared context!\n");
    exit(err);
  }
}
