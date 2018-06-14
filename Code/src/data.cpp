#include "data.hpp"

float4::float4(int num_data)
{
  x = new GLfloat[num_data];
  y = new GLfloat[num_data];
  z = new GLfloat[num_data];
  w = new GLfloat[num_data];
  size = num_data;
  vao = 0;
  vbo = 0;
  buffer = NULL;

  data = new GLfloat[4*num_data];

  for (i = 0; i < num_data; i++)
  {
<<<<<<< HEAD
    data[4*i + 0] = x[i] = 0;
    data[4*i + 1] = y[i] = 0;
    data[4*i + 2] = z[i] = 0;
    data[4*i + 3] = w[i] = 1.0;
=======
    data[4*i + 0] = x[i] = 0.0f;
    data[4*i + 1] = y[i] = 0.0f;
    data[4*i + 2] = z[i] = 0.0f;
    data[4*i + 3] = w[i] = 1.0f;
>>>>>>> ad470deaf9a0e71eaeba6e7cc85820a9723bc772
  }
}

float4::~float4()
{
  release_mem_object(buffer);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &vao);
}

int4::int4(int num_data)
{
  x = new GLint[num_data];
  y = new GLint[num_data];
  z = new GLint[num_data];
  w = new GLint[num_data];
  size = num_data;
  vao = 0;
  vbo = 0;
  buffer = NULL;

  data = new GLint[4*num_data];

  for (i = 0; i < num_data; i++)
  {
<<<<<<< HEAD
    data[4*i + 0] = x[i] = 0;
    data[4*i + 1] = y[i] = 0;
    data[4*i + 2] = z[i] = 0;
    data[4*i + 3] = w[i] = 1.0;
=======
    data[4*i + 0] = x[i] = 0.0f;
    data[4*i + 1] = y[i] = 0.0f;
    data[4*i + 2] = z[i] = 0.0f;
    data[4*i + 3] = w[i] = 1.0f;
>>>>>>> ad470deaf9a0e71eaeba6e7cc85820a9723bc772
  }
}

int4::~int4()
{
  release_mem_object(buffer);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &vao);
}

point4::point4(int num_data)
{
  x = new GLfloat[num_data];
  y = new GLfloat[num_data];
  z = new GLfloat[num_data];
  w = new GLfloat[num_data];
  size = num_data;
  vao = 0;
  vbo = 0;
  buffer = NULL;

  data = new GLfloat[4*num_data];

  for (i = 0; i < num_data; i++)
  {
<<<<<<< HEAD
    data[4*i + 0] = x[i] = 0;
    data[4*i + 1] = y[i] = 0;
    data[4*i + 2] = z[i] = 0;
    data[4*i + 3] = w[i] = 1.0;
=======
    data[4*i + 0] = x[i] = 0.0f;
    data[4*i + 1] = y[i] = 0.0f;
    data[4*i + 2] = z[i] = 0.0f;
    data[4*i + 3] = w[i] = 1.0f;
>>>>>>> ad470deaf9a0e71eaeba6e7cc85820a9723bc772
  }
}

point4::~point4()
{
  release_mem_object(buffer);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &vao);
}

color4::color4(int num_data)
{
  r = new GLfloat[num_data];
  g = new GLfloat[num_data];
  b = new GLfloat[num_data];
  a = new GLfloat[num_data];
  size = num_data;
  vao = 0;
  vbo = 0;
  buffer = NULL;

  data = new GLfloat[4*num_data];

  for (i = 0; i < num_data; i++)
  {
<<<<<<< HEAD
    data[4*i + 0] = r[i] = 0;
    data[4*i + 1] = g[i] = 0;
    data[4*i + 2] = b[i] = 0;
    data[4*i + 3] = a[i] = 1.0;
=======
    data[4*i + 0] = r[i] = 0.0f;
    data[4*i + 1] = g[i] = 0.0f;
    data[4*i + 2] = b[i] = 0.0f;
    data[4*i + 3] = a[i] = 1.0f;
>>>>>>> ad470deaf9a0e71eaeba6e7cc85820a9723bc772
  }
}

color4::~color4()
{
  release_mem_object(buffer);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &vao);
}
