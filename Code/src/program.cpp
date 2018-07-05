#include "program.hpp"

#define NUM_POINTS      10000
#define X_MIN           -1.0f
#define Y_MIN           -1.0f
#define SIZE_X          100
#define SIZE_Y          100
#define DX              0.02f
#define DY              0.02f

point4* points =    new point4(NUM_POINTS);
color4* colors =    new color4(NUM_POINTS);

point4* points_1 =    new point4(8);
color4* colors_1 =    new color4(8);

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

  points_1->x[0] = 1.10f;
  points_1->y[0] = 2.50f;
  points_1->z[0] = 0.0f;
  points_1->w[0] = 1.0f;

  points_1->x[1] = 0.40f;
  points_1->y[1] = -0.70f;
  points_1->z[1] = 0.0f;
  points_1->w[1] = 1.0f;

  points_1->x[2] = 1.70f;
  points_1->y[2] = 2.50f;
  points_1->z[2] = 0.0f;
  points_1->w[2] = 1.0f;

  points_1->x[3] = 1.00f;
  points_1->y[3] = -0.70f;
  points_1->z[3] = 0.0f;
  points_1->w[3] = 1.0f;

  points_1->x[4] = 0.40f;
  points_1->y[4] = 1.20f;
  points_1->z[4] = 0.0f;
  points_1->w[4] = 1.0f;

  points_1->x[5] = 1.80f;
  points_1->y[5] = 1.20f;
  points_1->z[5] = 0.0f;
  points_1->w[5] = 1.0f;

  points_1->x[6] = 0.30f;
  points_1->y[6] = 0.60f;
  points_1->z[6] = 0.0f;
  points_1->w[6] = 1.0f;

  points_1->x[7] = 1.70f;
  points_1->y[7] = 0.60f;
  points_1->z[7] = 0.0f;
  points_1->w[7] = 1.0f;

  colors_1->r[0] = 1.0f;
  colors_1->g[0] = 0.0f;
  colors_1->b[0] = 0.0f;
  colors_1->a[0] = 1.0f;

  colors_1->r[1] = 1.0f;
  colors_1->g[1] = 0.0f;
  colors_1->b[1] = 0.0f;
  colors_1->a[1] = 1.0f;

  colors_1->r[2] = 0.0f;
  colors_1->g[2] = 0.0f;
  colors_1->b[2] = 1.0f;
  colors_1->a[2] = 1.0f;

  colors_1->r[3] = 0.0f;
  colors_1->g[3] = 0.0f;
  colors_1->b[3] = 1.0f;
  colors_1->a[3] = 1.0f;

  colors_1->r[4] = 1.0f;
  colors_1->g[4] = 0.0f;
  colors_1->b[4] = 0.0f;
  colors_1->a[4] = 1.0f;

  colors_1->r[5] = 1.0f;
  colors_1->g[5] = 0.0f;
  colors_1->b[5] = 0.0f;
  colors_1->a[5] = 1.0f;

  colors_1->r[6] = 0.0f;
  colors_1->g[6] = 0.0f;
  colors_1->b[6] = 1.0f;
  colors_1->a[6] = 1.0f;

  colors_1->r[7] = 0.0f;
  colors_1->g[7] = 0.0f;
  colors_1->b[7] = 1.0f;
  colors_1->a[7] = 1.0f;

  tick = 0.0f;                                                                  // Setting initial time tick...

  init_point4(points_1);
  init_color4(colors_1);

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
  overlay(points_1, colors_1);
}

void terminate()
{
  delete points;
  delete colors;
  printf("All done!\n");
}
