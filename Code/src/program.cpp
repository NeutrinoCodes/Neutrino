#include "program.hpp"

#define NUM_POINTS      10000
#define X_MIN           -1.0f
#define Y_MIN           -1.0f
#define SIZE_X          100
#define SIZE_Y          100
#define DX              0.02f
#define DY              0.02f

point4* points = new point4(NUM_POINTS);
color4* colors = new color4(NUM_POINTS);
float tick;

void setup()
{
  size_global = points->size;
  dim_kernel = 1;
  int i;
  int j;
  float x;
  float y;

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// Preparing arrays... /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  y = Y_MIN;

  for (j = 0; j < SIZE_Y; j++)
  {
    x = X_MIN;

    for (i = 0; i < SIZE_X; i++)
    {
      points->x[i + SIZE_X*j]= x;                                               // Setting "x" initial positions...
      points->y[i + SIZE_X*j]= y;                                               // Setting "y" initial positions...
      points->z[i + SIZE_X*j] = 0.0f;                                           // Setting "z" initial positions...
      points->w[i + SIZE_X*j] = 1.0f;                                           // Setting "w" initial positions...
      x += DX;
    }
    y += DY;
  }

  for (i = 0; i < colors->size; i++)
  {
    colors->r[i] = glm::linearRand(0.0f, 1.0f);                                 // Setting "x" initial colors...
    colors->g[i] = glm::linearRand(0.0f, 1.0f);                                 // Setting "y" initial colors...
    colors->b[i] = glm::linearRand(0.0f, 1.0f);                                 // Setting "z" initial colors...
    colors->a[i] = 1.0f;                                                        // Setting "w" initial colors...
  }

  tick = 0.0f;                                                                  // Setting initial time tick...

  set_point4(points, 0);                                                        // Setting kernel argument #0...
  set_color4(colors, 1);                                                        // Setting kernel argument #1...
  set_int(&points->size, 2);                                                    // Setting kernel argument #2...
  set_float(&tick, 3);                                                          // Setting kernel argument #3...
  set_kernel();
}

void loop()
{
  push_point4(&points->buffer, 0);
  push_color4(&colors->buffer, 1);
  push_int(&points->size, 2);
  push_float(&tick, 3);
  push_kernel();

  pop_point4(&points->buffer, 0);
  pop_color4(&colors->buffer, 1);
  pop_int(&points->size, 2);
  pop_float(&tick, 3);
  pop_kernel();

  tick += 0.1f;

  plot(points, colors);
  //overlay("pippo", 5, 1.0, 1.0, 1.0, glm::vec3(1.0, 1.0, 1.0));
}

void terminate()
{
  delete points;
  delete colors;
  printf("All done!\n");
}
