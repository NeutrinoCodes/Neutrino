#include "program.hpp"

// These files are relative to the build/mac or build/linux directory:
#define VERTEX_FILE     "../../shader/vertex.txt"
#define FRAGMENT_FILE   "../../shader/fragment.txt"
#define KERNEL_FILE     "../../kernel/thekernel.txt"

#define NUM_POINTS      900
#define X_MIN           -1.0f
#define Y_MIN           -1.0f
#define SIZE_X          30
#define SIZE_Y          30
#define DX              0.066f
#define DY              0.066f

data_float4 points(NUM_POINTS);
data_float4 colors(NUM_POINTS);
float tick;

void load()
{
  load_vertex(VERTEX_FILE);
  load_fragment(FRAGMENT_FILE);
  load_kernel(KERNEL_FILE);
}

void setup()
{
  size_global = points.size;
  dim_kernel = 1;
  int i;
  unsigned int j;
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
      points.x[i + SIZE_X*j]= x;                                                // Setting "x" initial positions...
      points.y[i + SIZE_X*j]= y;                                                // Setting "y" initial positions...
      points.z[i + SIZE_X*j] = 0.0f;                                            // Setting "z" initial positions...
      points.w[i + SIZE_X*j] = 1.0f;                                            // Setting "w" initial positions...
      x += DX;
    }
    y += DY;
  }

  for (i = 0; i < colors.size; i++)
  {
    colors.x[i] = glm::linearRand(0.0f, 1.0f);                                  // Setting "x" initial colors...
    colors.y[i] = glm::linearRand(0.0f, 1.0f);                                  // Setting "y" initial colors...
    colors.z[i] = glm::linearRand(0.0f, 1.0f);                                  // Setting "z" initial colors...
    colors.w[i] = 1.0f;                                                         // Setting "w" initial colors...
  }

  tick = 0.0f;                                                                  // Setting initial time tick...

  set_points(&points, 0);                                                       // Setting kernel argument #0...
  set_colors(&colors, 1);                                                       // Setting kernel argument #1...
  set_int(&points.size, 2);                                                     // Setting kernel argument #2...
  set_float(&tick, 3);                                                          // Setting kernel argument #3...
}

void loop()
{
  push_points(&points.buffer);
  push_colors(&colors.buffer);
  push_int(&points.size, 2);
  push_float(&tick, 3);
  push_kernel();
  pop_points(&points.buffer);
  pop_colors(&colors.buffer);
  pop_kernel();
  init_screen();

  tick += 0.1f;

  plot_points(&points, &colors);
}

void terminate()
{
  printf("All done!\n");
}
