#include "context.hpp"

void init_opengl_context()
{
  init_window();                                                                // Initializing window...
  init_shaders();                                                               // Initializing shaders...
  init_screen();                                                                // Initializing screen...
  init_text();                                                                  // Initializing text library (FreeType_2)...
}

void init_opencl_context()
{
  cl_uint i;                                                                    // Platform #.
  cl_uint j;                                                                    // Device #.
  cl_int  err;                                                                  // Error code.

  num_platforms = get_platforms();                                              // Getting number of existing platforms...

  for (i = 0; i < num_platforms; i++)
  {
    printf("Action: getting OpenCL platform info for platform #%d... \n", i);

    get_platform_info(i, CL_PLATFORM_NAME);                                     // Getting platform information...
    get_platform_info(i, CL_PLATFORM_PROFILE);                                  // Getting platform information...
    get_platform_info(i, CL_PLATFORM_VERSION);                                  // Getting platform information...
    get_platform_info(i, CL_PLATFORM_VENDOR);                                   // Getting platform information...
    get_platform_info(i, CL_PLATFORM_EXTENSIONS);                               // Getting platform information...

    printf("        DONE!\n");

    num_devices = get_devices(i);                                               // Gettign number of existing device on a platform...

    for (j = 0; j < num_devices; j++)
    {
      printf("Action: getting OpenCL device info for device #%d... \n", j);

      get_device_info(j, CL_DEVICE_NAME);                                       // Getting device information...
      get_device_info(j, CL_DEVICE_VERSION);                                    // Getting device information...
      get_device_info(j, CL_DRIVER_VERSION);                                    // Getting device information...
      get_device_info(j, CL_DEVICE_OPENCL_C_VERSION);                           // Getting device information...
      get_device_info(j, CL_DEVICE_MAX_COMPUTE_UNITS);                          // Getting device information...

      printf("        DONE!\n");
    }

  }

  // Setting OpenCL context properties:

  #ifdef __APPLE__
    printf("Found APPLE system!\n");

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
    printf("Found LINUX system!\n");

    cl_context_properties properties[] =
    {
      CL_GL_CONTEXT_KHR, (cl_context_properties)glfwGetGLXContext(window),
      CL_GLX_DISPLAY_KHR, (cl_context_properties)glfwGetX11Display(),
      CL_CONTEXT_PLATFORM, (cl_context_properties)platforms[0],
      0
    };
  #endif

  #ifdef __WINDOWS__
    printf("Found WINDOWS system!\n");

    cl_context_properties properties[] =
    {
      CL_GL_CONTEXT_KHR, (cl_context_properties)glfwGetWGLContext(window),
      CL_WGL_HDC_KHR, (cl_context_properties)GetDC(glfwGetWin32Window(window)),
      CL_CONTEXT_PLATFORM, (cl_context_properties)platforms[0],
      0
    };
  #endif

  printf("Action: creating OpenCL context for GPU... ");

  context = clCreateContextFromType(properties,                                 // Creating OpenCL context...
                                    CL_DEVICE_TYPE_GPU,
                                    NULL,
                                    NULL,
                                    &err);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");
}

void destroy_opengl_context()
{
  glfwDestroyWindow(window);                                                    // Destroying window...
	glfwTerminate();                                                              // Terminating GLFW...
}

void destroy_opencl_context()
{
  finish_queue();                                                               // Finishing OpenCL queue...
  release_kernel();                                                             // Releasing OpenCL kernel...
  release_queue();                                                              // Releasing OpenCL queue...
  release_program();                                                            // Releasing OpenCL program...
  release_context();                                                            // Releasgin OpenCL context...
  free(devices);                                                                // Freeing OpenCL devices...
  free(platforms);                                                              // Freeing OpenCL platforms...
}
