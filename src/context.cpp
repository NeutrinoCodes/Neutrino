#include "context.hpp"

void create_opengl_context()
{
  init_glfw();
  init_hints();
  create_window();
  init_glew();
  init_shaders();
  init_screen();
}

void create_opencl_context()
{
  cl_uint i;
  cl_uint j;

  num_platforms = get_platforms();

  for (i = 0; i < num_platforms; i++)
  {
    printf("Action: getting OpenCL platform info for platform #%d... \n", i);
    get_platform_info(i, CL_PLATFORM_NAME);
    get_platform_info(i, CL_PLATFORM_PROFILE);
    get_platform_info(i, CL_PLATFORM_VERSION);
    get_platform_info(i, CL_PLATFORM_VENDOR);
    get_platform_info(i, CL_PLATFORM_EXTENSIONS);
    printf("        DONE!\n");

    num_devices = get_devices(i);

    for (j = 0; j < num_devices; j++)
    {
      printf("Action: getting OpenCL device info for device #%d... \n", j);
      get_device_info(j, CL_DEVICE_NAME);
      get_device_info(j, CL_DEVICE_VERSION);
      get_device_info(j, CL_DRIVER_VERSION);
      get_device_info(j, CL_DEVICE_OPENCL_C_VERSION);
      get_device_info(j, CL_DEVICE_MAX_COMPUTE_UNITS);
      printf("        DONE!\n");
    }

  }

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

  cl_int err;

  printf("Action: creating OpenCL context for GPU... ");
  context = clCreateContextFromType(properties, CL_DEVICE_TYPE_GPU, NULL, NULL, &err);

  if(err != CL_SUCCESS)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(err);
  }

  printf("DONE!\n");

}

void destroy_opengl_context()
{
  glfwDestroyWindow(window);
	glfwTerminate();
}

void destroy_opencl_context()
{
  finish_queue();
  release_kernel();
  release_queue();
  release_program();
  release_context();
  free(devices);
  free(platforms);
}
