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

void push_float4_data(data_float4 &data)
{
  int err;
  unsigned int i;
  float* unfolded_data;

  unfolded_data = new float[data.size];

  kernel_arg++;

  for (i = 0; i < data.size; i++)
  {
    unfolded_data[4*i]     = data.x[i];
    unfolded_data[4*i + 1] = data.y[i];
    unfolded_data[4*i + 2] = data.z[i];
    unfolded_data[4*i + 3] = data.w[i];
  }

  printf("pippo\n");
  glGenVertexArrays(1, &data.vao);
  printf("pippo\n");
  glBindVertexArray(data.vao);
  glGenBuffers(1, &data.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, data.vbo);
  glBufferData(GL_ARRAY_BUFFER, 4*data.size*sizeof(GLfloat), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data.buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data.vbo, &err);
  if(err < 0)
  {
    fprintf(stderr, "Couldn’t create a buffer object from the VBO");
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(cl_mem), &data.buffer);

  if(err < 0)
  {
    fprintf(stderr, "Couldn’t set a kernel argument");
    exit(EXIT_FAILURE);
  };
}

void push_float4_size(data_float4 &data)
{
  int err;
  unsigned int i;
  float* unfolded_data;

  unfolded_data = new float[data.size];

  kernel_arg++;

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
  glBufferData(GL_ARRAY_BUFFER, 4*data.size*sizeof(GLfloat), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data.buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data.vbo, &err);
  if(err < 0)
  {
    fprintf(stderr, "Couldn’t create a buffer object from the VBO");
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(unsigned int), &data.size);

  if(err < 0)
  {
    fprintf(stderr, "Couldn’t set a kernel argument");
    exit(EXIT_FAILURE);
  };
}

void push_float_data(data_float &data)
{
  int err;
  unsigned int i;
  float* unfolded_data;

  unfolded_data = new float[data.size];

  kernel_arg++;

  for (i = 0; i < data.size; i++)
  {
    unfolded_data[i] = data.x[i];
  }

  glGenVertexArrays(1, &data.vao);
  glBindVertexArray(data.vao);
  glGenBuffers(1, &data.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, data.vbo);
  glBufferData(GL_ARRAY_BUFFER, data.size*sizeof(GLfloat), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data.buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data.vbo, &err);
  if(err < 0)
  {
    fprintf(stderr, "Couldn’t create a buffer object from the VBO");
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(cl_mem), &data.buffer);

  if(err < 0)
  {
    fprintf(stderr, "Couldn’t set a kernel argument");
    exit(EXIT_FAILURE);
  };
}

void push_float_size(data_float &data)
{
  int err;
  unsigned int i;
  float* unfolded_data;

  unfolded_data = new float[data.size];

  kernel_arg++;

  for (i = 0; i < data.size; i++)
  {
    unfolded_data[i] = data.x[i];
  }

  glGenVertexArrays(1, &data.vao);
  glBindVertexArray(data.vao);
  glGenBuffers(1, &data.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, data.vbo);
  glBufferData(GL_ARRAY_BUFFER, data.size*sizeof(GLfloat), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data.buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data.vbo, &err);
  if(err < 0)
  {
    fprintf(stderr, "Couldn’t create a buffer object from the VBO");
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(unsigned int), &data.size);

  if(err < 0)
  {
    fprintf(stderr, "Couldn’t set a kernel argument");
    exit(EXIT_FAILURE);
  };
}

void push_int4_data(data_int4 &data)
{
  int err;
  unsigned int i;
  int* unfolded_data;

  unfolded_data = new int[data.size];

  kernel_arg++;

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
  glBufferData(GL_ARRAY_BUFFER, 4*data.size*sizeof(GLint), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data.buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data.vbo, &err);
  if(err < 0)
  {
    fprintf(stderr, "Couldn’t create a buffer object from the VBO");
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(cl_mem), &data.buffer);

  if(err < 0)
  {
    fprintf(stderr, "Couldn’t set a kernel argument");
    exit(EXIT_FAILURE);
  };
}

void push_int4_size(data_int4 &data)
{
  int err;
  unsigned int i;
  int* unfolded_data;

  unfolded_data = new int[data.size];

  kernel_arg++;

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
  glBufferData(GL_ARRAY_BUFFER, 4*data.size*sizeof(GLint), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data.buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data.vbo, &err);
  if(err < 0)
  {
    fprintf(stderr, "Couldn’t create a buffer object from the VBO");
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(unsigned int), &data.size);

  if(err < 0)
  {
    fprintf(stderr, "Couldn’t set a kernel argument");
    exit(EXIT_FAILURE);
  };
}

void push_int_data(data_int &data)
{
  int err;
  unsigned int i;
  int* unfolded_data;

  unfolded_data = new int[data.size];

  kernel_arg++;

  for (i = 0; i < data.size; i++)
  {
    unfolded_data[i] = data.x[i];
  }

  glGenVertexArrays(1, &data.vao);
  glBindVertexArray(data.vao);
  glGenBuffers(1, &data.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, data.vbo);
  glBufferData(GL_ARRAY_BUFFER, data.size*sizeof(GLint), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data.buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data.vbo, &err);
  if(err < 0)
  {
    fprintf(stderr, "Couldn’t create a buffer object from the VBO");
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &data.buffer);

  if(err < 0)
  {
    fprintf(stderr, "Couldn’t set a kernel argument");
    exit(EXIT_FAILURE);
  };
}

void push_int_size(data_int &data)
{
  int err;
  unsigned int i;
  int* unfolded_data;

  unfolded_data = new int[data.size];

  kernel_arg++;

  for (i = 0; i < data.size; i++)
  {
    unfolded_data[i] = data.x[i];
  }

  glGenVertexArrays(1, &data.vao);
  glBindVertexArray(data.vao);
  glGenBuffers(1, &data.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, data.vbo);
  glBufferData(GL_ARRAY_BUFFER, data.size*sizeof(GLint), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data.buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data.vbo, &err);
  if(err < 0)
  {
    fprintf(stderr, "Couldn’t create a buffer object from the VBO");
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(unsigned int), &data.size);

  if(err < 0)
  {
    fprintf(stderr, "Couldn’t set a kernel argument");
    exit(EXIT_FAILURE);
  };
}
