#include "interop.hpp"

void set_interop()
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

void set_kernel_argument(data_float4 &data)
{
  int err;
  unsigned int i;
  float* unfolded_data;

  unfolded_data = new float[data.size];

  for (i = 0; i < data.size; i++)
  {
    unfolded_data[4*i]     = data.x[i];
    unfolded_data[4*i + 1] = data.y[i];
    unfolded_data[4*i + 2] = data.z[i];
    unfolded_data[4*i + 3] = data.w[i];
  }

  glGenVertexArrays(1, &data.vao);
  glBindVertexArray(data.vao);
  glGenBuffers(1, &data.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, data.vbo);
  glBufferData(GL_ARRAY_BUFFER, 4*data.size, unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data.buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data.vbo, &err);
  if(err < 0)
  {
    perror("Couldn’t create a buffer object from the VBO");
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &data.buffer);

  if(err < 0)
  {
    printf("Couldn’t set a kernel argument");
    exit(EXIT_FAILURE);
  };
}
