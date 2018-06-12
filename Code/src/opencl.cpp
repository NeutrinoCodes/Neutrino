#include "opencl.hpp"

char*                   value;
cl_platform_id*         platforms;
unsigned int            num_platforms;
cl_device_id*           devices;
unsigned int            num_devices;
cl_context_properties*  properties;
cl_context              context;
cl_command_queue        queue;
cl_kernel               kernel;
char*                   kernel_source;
size_t                  size_kernel;
cl_program              kernel_program;
size_t                  size_global;
cl_uint                 dim_kernel;
cl_event                kernel_event;

const char* get_error(cl_int error)
{
  switch(error)
  {
    // run-time and JIT compiler errors
    case 0: return "CL_SUCCESS";
    case -1: return "CL_DEVICE_NOT_FOUND";
    case -2: return "CL_DEVICE_NOT_AVAILABLE";
    case -3: return "CL_COMPILER_NOT_AVAILABLE";
    case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case -5: return "CL_OUT_OF_RESOURCES";
    case -6: return "CL_OUT_OF_HOST_MEMORY";
    case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case -8: return "CL_MEM_COPY_OVERLAP";
    case -9: return "CL_IMAGE_FORMAT_MISMATCH";
    case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case -11: return "CL_BUILD_PROGRAM_FAILURE";
    case -12: return "CL_MAP_FAILURE";
    case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
    case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
    case -15: return "CL_COMPILE_PROGRAM_FAILURE";
    case -16: return "CL_LINKER_NOT_AVAILABLE";
    case -17: return "CL_LINK_PROGRAM_FAILURE";
    case -18: return "CL_DEVICE_PARTITION_FAILED";
    case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

    // compile-time errors
    case -30: return "CL_INVALID_VALUE";
    case -31: return "CL_INVALID_DEVICE_TYPE";
    case -32: return "CL_INVALID_PLATFORM";
    case -33: return "CL_INVALID_DEVICE";
    case -34: return "CL_INVALID_CONTEXT";
    case -35: return "CL_INVALID_QUEUE_PROPERTIES";
    case -36: return "CL_INVALID_COMMAND_QUEUE";
    case -37: return "CL_INVALID_HOST_PTR";
    case -38: return "CL_INVALID_MEM_OBJECT";
    case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case -40: return "CL_INVALID_IMAGE_SIZE";
    case -41: return "CL_INVALID_SAMPLER";
    case -42: return "CL_INVALID_BINARY";
    case -43: return "CL_INVALID_BUILD_OPTIONS";
    case -44: return "CL_INVALID_PROGRAM";
    case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
    case -46: return "CL_INVALID_KERNEL_NAME";
    case -47: return "CL_INVALID_KERNEL_DEFINITION";
    case -48: return "CL_INVALID_KERNEL";
    case -49: return "CL_INVALID_ARG_INDEX";
    case -50: return "CL_INVALID_ARG_VALUE";
    case -51: return "CL_INVALID_ARG_SIZE";
    case -52: return "CL_INVALID_KERNEL_ARGS";
    case -53: return "CL_INVALID_WORK_DIMENSION";
    case -54: return "CL_INVALID_WORK_GROUP_SIZE";
    case -55: return "CL_INVALID_WORK_ITEM_SIZE";
    case -56: return "CL_INVALID_GLOBAL_OFFSET";
    case -57: return "CL_INVALID_EVENT_WAIT_LIST";
    case -58: return "CL_INVALID_EVENT";
    case -59: return "CL_INVALID_OPERATION";
    case -60: return "CL_INVALID_GL_OBJECT";
    case -61: return "CL_INVALID_BUFFER_SIZE";
    case -62: return "CL_INVALID_MIP_LEVEL";
    case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
    case -64: return "CL_INVALID_PROPERTY";
    case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
    case -66: return "CL_INVALID_COMPILER_OPTIONS";
    case -67: return "CL_INVALID_LINKER_OPTIONS";
    case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

    // extension errors
    case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
    default: return "Unknown OpenCL error";
  }
}

cl_uint get_platforms()
{
  cl_int err;
  cl_uint num_platforms;

  printf("Action: getting OpenCL platforms... ");

  err = clGetPlatformIDs(0, NULL, &num_platforms);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * num_platforms);

  err = clGetPlatformIDs(num_platforms, platforms, NULL);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("\n        Found %d platform(s)!\n", num_platforms);
  printf("        DONE!\n");

  return num_platforms;
}

void get_platform_info(cl_uint index_platform, cl_platform_info name_param)
{
  cl_int err;
  size_t  size_value;

  err = clGetPlatformInfo(platforms[index_platform], name_param, 0, NULL, &size_value);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  value = (char*) malloc(size_value);

  err = clGetPlatformInfo(platforms[index_platform], name_param, size_value, value, NULL);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  switch (name_param)
  {
    case CL_PLATFORM_PROFILE:                       printf("        CL_PLATFORM_PROFILE = %s\n", value); break;
    case CL_PLATFORM_VERSION:                       printf("        CL_PLATFORM_VERSION = %s\n", value); break;
    case CL_PLATFORM_NAME:                          printf("        CL_PLATFORM_NAME = %s\n", value); break;
    case CL_PLATFORM_VENDOR:                        printf("        CL_PLATFORM_VENDOR = %s\n", value); break;
    case CL_PLATFORM_EXTENSIONS:                    printf("        CL_PLATFORM_EXTENSIONS = %s\n", value);
  }

  free(value);
}

cl_uint get_devices(cl_uint index_platform)
{
  cl_int err;
  cl_uint num_devices;

  printf("Action: getting OpenCL devices... ");

  err = clGetDeviceIDs(platforms[index_platform], CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  devices = (cl_device_id*) malloc(sizeof(cl_device_id) * num_devices);
  err = clGetDeviceIDs(platforms[index_platform], CL_DEVICE_TYPE_GPU, num_devices, devices, NULL);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("\n        Found %d device(s)!\n", num_devices);
  printf("        DONE!\n");

  return num_devices;
}

void get_device_info(cl_uint index_device, cl_device_info name_param)
{
  cl_int err;
  size_t  size_value;

  err = clGetDeviceInfo(devices[index_device], name_param, 0, NULL, &size_value);

  if(err != CL_SUCCESS)
  {
    printf("Error:  %s\n", get_error(err));
    exit(err);
  }

  value = (char*) malloc(size_value);
  err = clGetDeviceInfo(devices[index_device], name_param, size_value, value, NULL);

  if(err != CL_SUCCESS)
  {
    printf("Error:  %s\n", get_error(err));
    exit(err);
  }

  switch (name_param)
  {
    case CL_DEVICE_ADDRESS_BITS:                    printf("        CL_DEVICE_ADDRESS_BITS = %s\n", value); break;
    case CL_DEVICE_AVAILABLE:                       printf("        CL_DEVICE_AVAILABLE = %s\n", value); break;
    case CL_DEVICE_COMPILER_AVAILABLE:              printf("        CL_DEVICE_COMPILER_AVAILABLE = %s\n", value); break;
    case CL_DEVICE_ENDIAN_LITTLE:                   printf("        CL_DEVICE_ENDIAN_LITTLE = %s\n", value); break;
    case CL_DEVICE_ERROR_CORRECTION_SUPPORT:        printf("        CL_DEVICE_ERROR_CORRECTION_SUPPORT = %s\n", value); break;
    case CL_DEVICE_EXECUTION_CAPABILITIES:          printf("        CL_DEVICE_EXECUTION_CAPABILITIES = %s\n", value); break;
    case CL_DEVICE_EXTENSIONS:                      printf("        CL_DEVICE_EXTENSIONS = %s\n", value); break;
    case CL_DEVICE_GLOBAL_MEM_CACHE_SIZE:           printf("        CL_DEVICE_GLOBAL_MEM_CACHE_SIZE = %s\n", value); break;
    case CL_DEVICE_GLOBAL_MEM_CACHE_TYPE:           printf("        CL_DEVICE_GLOBAL_MEM_CACHE_TYPE = %s\n", value); break;
    case CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE:       printf("        CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE = %s\n", value); break;
    case CL_DEVICE_GLOBAL_MEM_SIZE:                 printf("        CL_DEVICE_GLOBAL_MEM_SIZE = %s\n", value); break;
    case CL_DEVICE_IMAGE_SUPPORT:                   printf("        CL_DEVICE_IMAGE_SUPPORT = %s\n", value); break;
    case CL_DEVICE_IMAGE2D_MAX_HEIGHT:              printf("        CL_DEVICE_IMAGE2D_MAX_HEIGHT = %s\n", value); break;
    case CL_DEVICE_IMAGE2D_MAX_WIDTH:               printf("        CL_DEVICE_IMAGE2D_MAX_WIDTH = %s\n", value); break;
    case CL_DEVICE_IMAGE3D_MAX_DEPTH:               printf("        CL_DEVICE_IMAGE3D_MAX_DEPTH = %s\n", value); break;
    case CL_DEVICE_IMAGE3D_MAX_HEIGHT:              printf("        CL_DEVICE_IMAGE3D_MAX_HEIGHT = %s\n", value); break;
    case CL_DEVICE_IMAGE3D_MAX_WIDTH:               printf("        CL_DEVICE_IMAGE3D_MAX_WIDTH = %s\n", value); break;
    case CL_DEVICE_LOCAL_MEM_SIZE:                  printf("        CL_DEVICE_LOCAL_MEM_SIZE = %s\n", value); break;
    case CL_DEVICE_LOCAL_MEM_TYPE:                  printf("        CL_DEVICE_LOCAL_MEM_TYPE = %s\n", value); break;
    case CL_DEVICE_MAX_CLOCK_FREQUENCY:             printf("        CL_DEVICE_MAX_CLOCK_FREQUENCY = %s\n", value); break;
    case CL_DEVICE_MAX_COMPUTE_UNITS:               printf("        CL_DEVICE_MAX_COMPUTE_UNITS = %d\n", (int)*value); break;
    case CL_DEVICE_MAX_CONSTANT_ARGS:               printf("        CL_DEVICE_MAX_CONSTANT_ARGS = %s\n", value); break;
    case CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE:        printf("        CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE = %s\n", value); break;
    case CL_DEVICE_MAX_MEM_ALLOC_SIZE:              printf("        CL_DEVICE_MAX_MEM_ALLOC_SIZE = %s\n", value); break;
    case CL_DEVICE_MAX_PARAMETER_SIZE:              printf("        CL_DEVICE_MAX_PARAMETER_SIZE = %s\n", value); break;
    case CL_DEVICE_MAX_READ_IMAGE_ARGS:             printf("        CL_DEVICE_MAX_READ_IMAGE_ARGS = %s\n", value); break;
    case CL_DEVICE_MAX_SAMPLERS:                    printf("        CL_DEVICE_MAX_SAMPLERS = %s\n", value); break;
    case CL_DEVICE_MAX_WORK_GROUP_SIZE:             printf("        CL_DEVICE_MAX_WORK_GROUP_SIZE = %s\n", value); break;
    case CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:        printf("        CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS = %s\n", value); break;
    case CL_DEVICE_MAX_WORK_ITEM_SIZES:             printf("        CL_DEVICE_MAX_WORK_ITEM_SIZES = %s\n", value); break;
    case CL_DEVICE_MAX_WRITE_IMAGE_ARGS:            printf("        CL_DEVICE_MAX_WRITE_IMAGE_ARGS = %s\n", value); break;
    case CL_DEVICE_MEM_BASE_ADDR_ALIGN:             printf("        CL_DEVICE_MEM_BASE_ADDR_ALIGN = %s\n", value); break;
    case CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE:        printf("        CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE = %s\n", value); break;
    case CL_DEVICE_NAME:                            printf("        CL_DEVICE_NAME = %s\n", value); break;
    case CL_DEVICE_PLATFORM:                        printf("        CL_DEVICE_PLATFORM = %s\n", value); break;
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR:     printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR = %s\n", value); break;
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE:   printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE = %s\n", value); break;
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT:    printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT = %s\n", value); break;
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT:      printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT = %s\n", value); break;
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG:     printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG = %s\n", value); break;
    case CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT:    printf("        CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT = %s\n", value); break;
    case CL_DEVICE_PROFILE:                         printf("        CL_DEVICE_PROFILE = %s\n", value); break;
    case CL_DEVICE_PROFILING_TIMER_RESOLUTION:      printf("        CL_DEVICE_PROFILING_TIMER_RESOLUTION = %s\n", value); break;
    case CL_DEVICE_QUEUE_PROPERTIES:                printf("        CL_DEVICE_QUEUE_PROPERTIES = %s\n", value); break;
    case CL_DEVICE_SINGLE_FP_CONFIG:                printf("        CL_DEVICE_SINGLE_FP_CONFIG = %s\n", value); break;
    case CL_DEVICE_TYPE:                            printf("        CL_DEVICE_TYPE = %s\n", value); break;
    case CL_DEVICE_VENDOR_ID:                       printf("        CL_DEVICE_VENDOR_ID = %s\n", value); break;
    case CL_DEVICE_VENDOR:                          printf("        CL_DEVICE_VENDOR = %s\n", value); break;
    case CL_DEVICE_VERSION:                         printf("        CL_DEVICE_VERSION = %s\n", value); break;
    case CL_DRIVER_VERSION:                         printf("        CL_DRIVER_VERSION = %s\n", value);
  }

  free(value);
}

void load_kernel(const char* filename_kernel)
{
  FILE* handle;

  printf("Action: loading OpenCL kernel from file... ");

  handle = fopen(filename_kernel, "rb");

  if(handle == NULL)
  {
    printf("\nError:  could not find the file!");
    exit(1);
  }
  fseek(handle, 0, SEEK_END);
  size_kernel = (size_t)ftell(handle);
  rewind(handle);
  kernel_source = (char*)malloc(size_kernel + 1);
  if (!kernel_source)
  {
    printf("\nError:  unable to allocate buffer memory!\n");
    exit(EXIT_FAILURE);
  }

  fread(kernel_source, sizeof(char), size_kernel, handle);
  kernel_source[size_kernel] = '\0';
  fclose(handle);

  printf("DONE!\n");
}

void init_opencl_kernel()
{
  cl_int err;
  size_t log_size;
  char* log;

  printf("Action: initializing OpenCL kernel... ");
  kernel_program = clCreateProgramWithSource(context, 1, (const char **) &kernel_source, &size_kernel, &err);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  free(kernel_source);

  err = clBuildProgram(kernel_program, 1, devices, "", NULL, NULL);

  if (err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));

    clGetProgramBuildInfo(kernel_program, devices[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
    log = (char*) calloc(log_size + 1, sizeof(char));

    if (!log)
    {
      printf("\nError:  unable to allocate buffer memory for program build log!\n");
      exit(EXIT_FAILURE);
    }

    clGetProgramBuildInfo(kernel_program, devices[0], CL_PROGRAM_BUILD_LOG, log_size + 1, log, NULL);

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }

    printf("%s\n", log);
    free(log);
    exit(err);
  }

  queue = clCreateCommandQueue(context, devices[0], 0, &err);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  kernel = clCreateKernel(kernel_program, KERNEL_NAME, &err);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

void get_kernel_workgroup_size(cl_kernel kernel, cl_device_id device_id, size_t* local)
{
    cl_int err;

    printf("Action: getting maximum kernel workgroup size... ");
    err = clGetKernelWorkGroupInfo(kernel, device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(*local), local, NULL);

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }

    printf("DONE!\n");
}

void execute_kernel()
{
  cl_int err;

  err = clEnqueueNDRangeKernel(queue, kernel, dim_kernel, NULL, &size_global, NULL, 0, NULL, &kernel_event);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

}

void push_point4(cl_mem* CL_memory_buffer)
{
  cl_int err;

  //printf("Action: acquiring OpenCL memory objects... ");
  err = clEnqueueAcquireGLObjects(queue, 1, CL_memory_buffer, 0, NULL, NULL);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  //printf("DONE!\n");
}

void push_color4(cl_mem* CL_memory_buffer)
{
  cl_int err;

  //printf("Action: acquiring OpenCL memory objects... ");
  err = clEnqueueAcquireGLObjects(queue, 1, CL_memory_buffer, 0, NULL, NULL);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  //printf("DONE!\n");
}

void enqueue_task()
{
    cl_int err;

    //printf("Action: enqueueing OpenCL task... ");
    err = clEnqueueTask(queue, kernel, 0, NULL, &kernel_event);

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }

    //printf("DONE!\n");
}

void wait_for_event()
{
    cl_int err;

    //printf("Action: waiting for OpenCL events... ");
    err = clWaitForEvents(1, &kernel_event);

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }

    //printf("DONE!\n");
}

void pop_point4(cl_mem* CL_memory_buffer)
{
  cl_int err;

  //printf("Action: releasing enqueued OpenCL objects... ");
  err = clEnqueueReleaseGLObjects(queue, 1, CL_memory_buffer, 0, NULL, NULL);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  //printf("DONE!\n");
}

void pop_color4(cl_mem* CL_memory_buffer)
{
  cl_int err;

  //printf("Action: releasing enqueued OpenCL objects... ");
  err = clEnqueueReleaseGLObjects(queue, 1, CL_memory_buffer, 0, NULL, NULL);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  //printf("DONE!\n");
}

void finish_queue()
{
  cl_int err;

  //printf("Action: waiting for OpenCL command sequence end... ");
  err = clFinish(queue);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  //printf("DONE!\n");
}

void release_event()
{
    cl_int err;

    //printf("Action: decrementing the OpenCL event reference count... ");
    err = clReleaseEvent(kernel_event);

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }

    //printf("DONE!\n");
}

void release_mem_object(cl_mem CL_memory_buffer)
{
  cl_int err;

  printf("Action: decrementing the OpenCL memory object reference count... ");

  if(CL_memory_buffer != NULL)
  {
    err = clReleaseMemObject(CL_memory_buffer);

    if(err != CL_SUCCESS)
    {
      printf("\nError:  %s\n", get_error(err));
      exit(err);
    }
  }

  printf("DONE!\n");
}

void release_kernel()
{
  cl_int err;

  printf("Action: releasing the OpenCL command queue... ");
  err = clReleaseKernel(kernel);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

void release_queue()
{
  cl_int err;

  printf("Action: releasing the OpenCL command queue... ");
  err = clReleaseCommandQueue(queue);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

void release_program()
{
  cl_int err;

  printf("Action: releasing the OpenCL program... ");

  err = clReleaseProgram(kernel_program);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

void release_context()
{
  cl_int err;

  printf("Action: releasing the OpenCL context... ");

  err = clReleaseContext(context);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

void push_kernel()
{
  execute_kernel();
}

void pop_kernel()
{
  finish_queue();
}
