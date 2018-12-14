/// @file

#define SIZE_WINDOW_X  800                                                      // Window x-size [px].
#define SIZE_WINDOW_Y  600                                                      // Window y-size [px].
#define WINDOW_NAME    "neutrino 2.0"                                           // Window name.

#define QUEUE_NUM      1

#define KERNEL_NUM     1
#define KERNEL_DIM     1

#define XMIN          -1.0
#define XMAX           1.0
#define YMIN          -1.0
#define YMAX           1.0
#define NODES_X        100
#define NODES_Y        100
#define NODES          NODES_X*NODES_Y                                          // Number of nodes.
#define DX             (XMAX - XMIN)/(float)(NODES_X - 1)
#define DY             (YMAX - YMIN)/(float)(NODES_Y - 1)

#include "neutrino.hpp"
#include "window.hpp"
#include "opencl.hpp"
#include "queue.hpp"
#include "kernel.hpp"

int main()
{
  size_t    i;
  size_t    j;

  neutrino* baseline        = new neutrino();                                   // The Neutrino object.
  window*   gui             = new window();                                     // The gui window object.
  opencl*   cl              = new opencl();                                     // The OpenCL context object.

  queue**   Q               = new queue*[QUEUE_NUM];                            // OpenCL queue.

  size_t**  K_size          = new size_t*[KERNEL_NUM];                          // OpenCL kernel dimensions array...
  kernel**  K               = new kernel*[KERNEL_NUM];                          // OpenCL kernel array...

  point4*   points          = new point4();                                     // Point array.
  color4*   colors          = new color4();                                     // Color array.
  text4*    message         = new text4();                                      // Text message.

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////// INITIALIZING NEUTRINO, OPENGL and OPENCL //////////////////
  ////////////////////////////////////////////////////////////////////////////////
  baseline  ->init(QUEUE_NUM, KERNEL_NUM);                                      // Initializing neutrino...
  gui       ->init(baseline, SIZE_WINDOW_X, SIZE_WINDOW_Y, WINDOW_NAME);        // Initializing window...
  cl        ->init(baseline, gui->glfw_window, GPU);                            // Initializing OpenCL context...

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////// INITIALIZING OPENCL QUEUES /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  for(i = 0; i < QUEUE_NUM; i++)                                                // For each OpenCL queue:
  {
    Q[i]                    = new queue();                                      // OpenCL queue.
    Q[i]    ->init(baseline);                                                   // Initializing OpenCL queue...
  }

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////// INITIALIZING OPENCL KERNELS /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  for(j = 0; j < KERNEL_NUM; j++)                                               // For each OpenCL kernel:
  {
    K_size[j]               = new size_t[KERNEL_DIM];                           // OpenCL kernel dimensions.

    for (i = 0; i < KERNEL_DIM; i++)                                            // Setting all kernel sizes...
    {
      K_size[j][i] = NODES;                                                     // Setting size of each kernel dimension...
    }

    K[j]                    = new kernel();                                     // OpenCL kernel.
    K[j]    ->init(
                    baseline,                                                   // Neutrino baseline.
                    baseline->prefix("Code/kernel/thekernel.cl"),               // Kernel file name.
                    K_size[j],                                                  // Kernel dimensions array.
                    KERNEL_DIM                                                  // Kernel dimension.
                  );
  }

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////// INITIALIZING OPENCL DATA OBJECTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  points    ->init(baseline, NODES);                                            // Initializing points...
  colors    ->init(baseline, NODES);                                            // Initializing colors...
  message   ->init(baseline, "neutrino 2.0!", 0.0, 1.0, 0.0, 1.0);              // Initializing message...

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////// SETTING OPENCL DATA OBJECTS /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  for(j = 0; j < NODES_Y; j++)
  {
    for(i = 0; i < NODES_X; i++)
    {
      points->set_x(j*NODES_Y + i, XMIN + i*DX);
      points->set_y(j*NODES_Y + i, YMIN + j*DY);
      points->set_z(j*NODES_Y + i, 0.0);
      points->set_w(j*NODES_Y + i, 1.0);

      colors->set_r(j*NODES_Y + i, 0.01*(rand() % 100));
      colors->set_g(j*NODES_Y + i, 0.01*(rand() % 100));
      colors->set_b(j*NODES_Y + i, 0.01*(rand() % 100));
      colors->set_a(j*NODES_Y + i, 1.0);
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// SETTING OPENCL KERNEL ARGUMENTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  points    ->set_arg   (K[0], 0);                                              // Setting kernel argument...
  colors    ->set_arg   (K[0], 1);                                              // Setting kernel argument...

  points    ->acquire_gl(Q[0], 0);
  points    ->push      (Q[0], 0);
  points    ->release_gl(Q[0], 0);

  colors    ->acquire_gl(Q[0], 1);
  colors    ->push      (Q[0], 1);
  colors    ->release_gl(Q[0], 1);

  while (!gui->closed())                                                        // Opening window...
  {
    baseline->get_tic();                                                        // Getting "tic" [us]...

    gui     ->clear();                                                          // Clearing window...
    gui     ->poll_events();                                                    // Polling window events...

    points  ->acquire_gl(Q[0], 0);
    colors  ->acquire_gl(Q[0], 1);

    K[0]    ->execute   (Q[0], WAIT);

    points  ->release_gl(Q[0], 0);
    colors  ->release_gl(Q[0], 1);

    gui     ->print(message);                                                   // Printing text...
    gui     ->plot(points, colors, STYLE_POINT);
    gui     ->refresh();                                                        // Refreshing window...

    baseline->get_toc();                                                        // Getting "toc" [us]...
  }

  delete    baseline;
  delete    gui;
  delete    cl;
  delete    message;

  delete    points;
  delete    colors;

  delete[]  Q;

  delete[]  K_size;
  delete[]  K;

  return 0;
}
