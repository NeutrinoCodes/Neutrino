#include "context.hpp"
//#include "opengl.hpp"
//#include "opencl.hpp"

void create_opengl_context()
{
  init_glfw();
  init_hints();
  create_window();
  init_glew();
}

void create_opencl_context()
{

  for (cl_uint i = 0; i < get_platforms(); i++)
  {
    get_platform_info(i, CL_PLATFORM_NAME);
    get_platform_info(i, CL_PLATFORM_PROFILE);
    get_platform_info(i, CL_PLATFORM_VERSION);
    get_platform_info(i, CL_PLATFORM_VENDOR);
    get_platform_info(i, CL_PLATFORM_EXTENSIONS);

    for (cl_uint j = 0; j < get_devices(i); j++)
    {
      get_device_info(j, CL_DEVICE_NAME);
      get_device_info(j, CL_DEVICE_VERSION);
      get_device_info(j, CL_DRIVER_VERSION);
      get_device_info(j, CL_DEVICE_OPENCL_C_VERSION);
      //get_device_info(j, CL_DEVICE_MAX_COMPUTE_UNITS);
    }

  }

  get_context_properties();
  create_context();
}

void destroy_opengl_context()
{
  glfwDestroyWindow(window);
	glfwTerminate();
}

void destroy_opencl_context()
{
  free(devices);
  free(platforms);
}
