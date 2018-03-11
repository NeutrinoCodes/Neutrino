#include "context.hpp"

void create_opengl_context()
{
  init_glfw();
  init_hints();
  create_window();
  init_glew();
  init_shaders(VERTEX_FILE, FRAGMENT_FILE);
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
  read_file(KERNEL_FILE, &kernel_size, &kernel_source);
  create_program(context, kernel_source, &kernel_program);
  free_file(kernel_source);
  build_program(devices[0], kernel_program, KERNEL_OPTIONS);
  create_queue(devices[0], context, &queue);
  create_kernel(kernel_program, KERNEL_NAME, &kernel);
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
