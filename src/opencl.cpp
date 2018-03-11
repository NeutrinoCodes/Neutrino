#include "opencl.hpp"

char*                   value;
cl_platform_id*         platforms;
cl_device_id*           devices;
cl_context_properties*  properties;
cl_context              context;
cl_command_queue*       queue;
cl_program*             program;
cl_kernel*              kernel;

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

void create_queue(cl_device_id device_id, cl_context context, cl_command_queue* queue)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: Creating OpenCL command queue...\n");                                                                       ///< Printing action message...
    *queue = clCreateCommandQueue(context, device_id, 0, &err);                                                                 ///< Creating command queue...

    if (!(*queue))
    {
        fprintf(stderr, "Error: Failed to create command queue!\n");                                                          ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void create_program(cl_context context, const char* source_code, cl_program* program)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: Creating OpenCL program...\n");                                                                             ///< Printing action message...
    *program = clCreateProgramWithSource(context, 1, (const char **) &source_code, NULL, &err);                                 ///< Creating program from source...

    if (!(*program))                                                                                                            ///< Checking program...
    {
        fprintf(stderr, "Error: Failed to create compute program!\n");                                                          ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }
    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void build_program(cl_device_id device_id, cl_program program, const char* options)
{
    int err;                                                                                                                    ///< Error code [#].
    size_t log_size;                                                                                                            ///< Info buffer size [#].
    char* log;                                                                                                                  ///< Info buffer.

    printf("Action: Building OpenCL program...\n");                                                                             ///< Printing action message...
    err = clBuildProgram(program, 0, NULL, options, NULL, NULL);                                                                ///< Building the program...

    if (err != CL_SUCCESS)                                                                                                      ///< Checking program...
    {
        fprintf(stderr, "Error: Failed to build program executable!\n");                                                        ///< Printing error message...

        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);                                    ///< Getting build info (log size)...
        log = (char*) calloc(log_size + 1, sizeof(char));                                                                         ///< Allocating buffer for build log...

        if (!log)                                                                                                               ///< Checking for buffer allocation...
        {
            fprintf(stderr, "Error: unable to allocate buffer memory for program build log!\n");                                ///< Printing error message...
            exit(EXIT_FAILURE);                                                                                                 ///< Exiting the application...
        }
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size + 1, log, NULL);                               ///< Getting build info (log data)...
        printf("%s\n", log);                                                                                                    ///< Printing build info...
        free(log);                                                                                                              ///< Freeing log buffer...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void create_kernel(cl_program program, const char* source_name, cl_kernel* kernel)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: Creating OpenCL kernel...\n");                                                                              ///< Printing action message...
    *kernel = clCreateKernel(program, source_name, &err);                                                                       ///< Creating kernel...

    if (err != CL_SUCCESS)                                                                                                      ///< Checking kernel...
    {
        fprintf(stderr, "Error: Failed to create OpenCL kernel!\n");                                                            ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void create_buffer_from_VBO(cl_context context, GLuint vbo, cl_mem_flags memflags, cl_mem* memory)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: Creating openCL buffer from openGL VBO...\n");                                                              ///< Printing action message...
    *memory = clCreateFromGLBuffer(context, memflags, vbo, &err);                                                               ///< Creating memory buffer...

    if (err != CL_SUCCESS)                                                                                                      ///< Checking memory buffer...
    {
        fprintf(stderr, "Error: Failed to allocate device memory! %d\n", err);                                                  ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void get_kernel_workgroup_size(cl_kernel kernel, cl_device_id device_id, size_t* local)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: getting maximum kernel workgroup size...\n");                                                               ///< Printing action message...
    err = clGetKernelWorkGroupInfo(kernel, device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(*local), local, NULL);                  ///< Getting max kernel workgroup size...

    if (err != CL_SUCCESS)                                                                                                      ///< Checking error...
    {
        fprintf(stderr, "Error: Failed to retrieve kernel work group info! %d\n", err);                                         ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void execute_kernel(cl_command_queue queue, cl_kernel kernel, cl_uint dimensions, size_t* global, size_t* local)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: executing kernel...\n");                                                                                    ///< Printing action message...
    err = clEnqueueNDRangeKernel(queue, kernel, dimensions, NULL, global, local, 0, NULL, NULL);                                ///< Executing kernel...

    if (err != CL_SUCCESS)                                                                                                      ///< Checking error...
    {
        fprintf(stderr, "Error: Failed to execute kernel! %d\n", err);                                                          ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void acquire_GLObjects(cl_command_queue queue, int num_buffers, cl_mem* CL_memory_buffer)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: acquiring OpenCL memory objects...\n");                                                                     ///< Printing action message...
    err = clEnqueueAcquireGLObjects(queue, num_buffers, CL_memory_buffer, 0, NULL, NULL);                                       ///< Acquiring OpenCL memory objects...

    if (err != CL_SUCCESS)                                                                                                      ///< Checking error...
    {
        fprintf(stderr, "Error: Couldn't acquire the GL objects! %d\n", err);                                                   ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void enqueue_task(cl_command_queue queue, cl_kernel kernel, cl_event* kernel_event)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: enqueueing OpenCL task...\n");                                                                              ///< Printing action message...
    err = clEnqueueTask(queue, kernel, 0, NULL, kernel_event);                                                                  ///< Enqueueing OpenCL task...

    if (err != CL_SUCCESS)                                                                                                      ///< Checking error...
    {
        fprintf(stderr, "Error: Couldn't enqueue the kernel! %d\n", err);                                                       ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void wait_for_events(cl_event* kernel_event)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: waiting for OpenCL events...\n");                                                                           ///< Printing action message...
    err = clWaitForEvents(1, kernel_event);                                                                                     ///< Waiting for OpenCL events...

    if (err != CL_SUCCESS)                                                                                                      ///< Checking error...
    {
        fprintf(stderr, "Error: Couldn't wait for the OpenCL event! %d\n", err);                                                ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void release_GLObjects(cl_command_queue queue, int num_buffers, cl_mem* CL_memory_buffer)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: releasing enqueued OpenCL objects...\n");                                                                   ///< Printing action message...
    err = clEnqueueReleaseGLObjects(queue, num_buffers, CL_memory_buffer, 0, NULL, NULL);                                       ///< Releasing OpenCL objects...

    if (err != CL_SUCCESS)                                                                                                      ///< Checking error...
    {
        fprintf(stderr, "Error: Couldn't release OpenCL objects! %d\n", err);                                                   ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void finish_queue(cl_command_queue queue)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: waiting for OpenCL command sequence end...\n");                                                             ///< Printing action message...
    err = clFinish(queue);                                                                                                      ///< Waiting for OpenCL commands to have completed...

    if (err != CL_SUCCESS)                                                                                                      ///< Checking error...
    {
        fprintf(stderr, "Error: Couldn't wait for OpenCL command sequnce end! %d\n", err);                                      ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void release_event(cl_event kernel_event)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: decrementing the OpenCL event reference count...\n");                                                       ///< Printing action message...
    err = clReleaseEvent(kernel_event);                                                                                         ///< Decrementing the event reference count...

    if (err != CL_SUCCESS)                                                                                                      ///< Checking error...
    {
        fprintf(stderr, "Error: Couldn't decrement the OpenCL event reference count! %d\n", err);                               ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void release_mem_object(cl_mem CL_memory_buffer)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: decrementing the OpenCL memory object reference count...\n");                                               ///< Printing action message...

    err = clReleaseMemObject(CL_memory_buffer);                                                                                 ///< Decrementing the memory object reference count...

    if (err != CL_SUCCESS)                                                                                                      ///< Checking error...
    {
        fprintf(stderr, "Error: Couldn't decrement the OpenCL memory object reference count! %d\n", err);                       ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void release_kernel(cl_kernel kernel)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: releasing the OpenCL command queue...\n");                                                      ///< Printing action message...
    err = clReleaseKernel(kernel);                                                                                                    ///< Releasing kernel...

    if (err != CL_SUCCESS)                                                                                                      ///< Checking error...
    {
        fprintf(stderr, "Error: Couldn't release kernel! %d\n", err);                                                           ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void release_queue(cl_command_queue queue)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: releasing the OpenCL command queue...\n");                                                                  ///< Printing action message...
    err = clReleaseCommandQueue(queue);

    if (err != CL_SUCCESS)                                                                                                      ///< Checking error...
    {
        fprintf(stderr, "Error: Couldn't release OpenCL command queue! %d\n", err);                                             ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void release_program(cl_program program)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: releasing the OpenCL program...\n");                                                                        ///< Printing action message...

    err = clReleaseProgram(program);

    if (err != CL_SUCCESS)                                                                                                      ///< Checking error...
    {
        fprintf(stderr, "Error: Couldn't release OpenCL program! %d\n", err);                                                   ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}

void release_context(cl_context context)
{
    int err;                                                                                                                    ///< Error code [#].

    printf("Action: releasing the OpenCL context...\n");                                                                        ///< Printing action message...

    err = clReleaseContext(context);

    if (err != CL_SUCCESS)                                                                                                      ///< Checking error...
    {
        fprintf(stderr, "Error: Couldn't release OpenCL context! %d\n", err);                                                   ///< Printing error message...
        exit(err);                                                                                                              ///< Exiting the application...
    }

    printf("DONE!\n\n");                                                                                                        ///< Printing DONE! message...
}
