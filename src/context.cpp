#include "context.hpp"

void create_opengl_context()
{
  init_glfw();
  init_hints();
  create_window();
  init_glew();
  init_shaders();
}

void create_opencl_context()
{
  num_platforms = get_platforms();

  for (cl_uint i = 0; i < num_platforms; i++)
  {
    printf("Action: getting OpenCL platform info... \n");
    get_platform_info(i, CL_PLATFORM_NAME);
    get_platform_info(i, CL_PLATFORM_PROFILE);
    get_platform_info(i, CL_PLATFORM_VERSION);
    get_platform_info(i, CL_PLATFORM_VENDOR);
    get_platform_info(i, CL_PLATFORM_EXTENSIONS);
    printf("        DONE!\n");

    num_devices = get_devices(i);

    for (cl_uint j = 0; j < num_devices; j++)
    {
      printf("Action: getting OpenCL device info... \n");
      get_device_info(j, CL_DEVICE_NAME);
      get_device_info(j, CL_DEVICE_VERSION);
      get_device_info(j, CL_DRIVER_VERSION);
      //get_device_info(j, CL_DEVICE_OPENCL_C_VERSION);
      //get_device_info(j, CL_DEVICE_MAX_COMPUTE_UNITS);
      printf("        DONE!\n");
    }

  }

  set_interop();
  create_context();
  create_program();
  build_program();
  create_queue();
  create_kernel();
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
