/// @file

#define USE_OPENGL    true                                                      // Set to "true" to use OpenGL-OpenCL interop.

#define SIZE_WINDOW_X 800                                                       // Window x-size [px].
#define SIZE_WINDOW_Y 600                                                       // Window y-size [px].
#define WINDOW_NAME   "neutrino 2.0"                                            // Window name.

#define QUEUE_NUM     1

#define KERNEL_NUM    1
#define KERNEL_DIM    1

#define XMIN          -1.0
#define XMAX          1.0
#define YMIN          -1.0
#define YMAX          1.0
#define NODES_X       100
#define NODES_Y       100
#define NODES         NODES_X* NODES_Y                                          // Number of nodes.
#define DX            (float)((XMAX - XMIN)/(NODES_X - 1))
#define DY            (float)((YMAX - YMIN)/(NODES_Y - 1))

#include "neutrino.hpp"
#include "window.hpp"
#include "opencl.hpp"
#include "queue.hpp"
#include "kernel.hpp"
#include "index.hpp"

int main ()
{
  size_t        i;
  size_t        j;

  neutrino*     baseline   = new neutrino ();                                   // The Neutrino object.

  #if USE_OPENGL
    window*     gui        = new window ();                                     // The gui window object.
    text4*      message    = new text4 ();                                      // Text message.
    memory_orb* controller = new memory_orb ();
  #endif

  opencl*       cl         = new opencl ();                                     // The OpenCL context object.

  queue**       Q          = new queue*[QUEUE_NUM];                             // OpenCL queue.

  size_t**      K_size     = new size_t*[KERNEL_NUM];                           // OpenCL kernel dimensions array...
  kernel**      K          = new kernel*[KERNEL_NUM];                           // OpenCL kernel array...

  point4*       points     = new point4 ();                                     // Point array.
  color4*       colors     = new color4 ();                                     // Color array.

  node_index*   index_PR   = new node_index ();                                 // Right particle.
  node_index*   index_PU   = new node_index ();                                 // Up particle.
  node_index*   index_PL   = new node_index ();                                 // Left particle.
  node_index*   index_PD   = new node_index ();                                 // Down particle.

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////// INITIALIZING NEUTRINO, OPENGL and OPENCL //////////////////
  ////////////////////////////////////////////////////////////////////////////////
  baseline  -> init (QUEUE_NUM, KERNEL_NUM, USE_OPENGL);                        // Initializing neutrino...
  #if USE_OPENGL
    gui       -> init (baseline, SIZE_WINDOW_X, SIZE_WINDOW_Y, WINDOW_NAME);    // Initializing window...
    cl        -> init (baseline, gui -> glfw_window, GPU);                      // Initializing OpenCL context with CL-GL interop...
  #else
    cl        -> init (baseline, NULL, GPU);                                    // Initializing OpenCL context without CL-GL interop...
  #endif

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////// INITIALIZING OPENCL QUEUES /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  for(i = 0; i < QUEUE_NUM; i++)                                                // For each OpenCL queue:
  {
    Q[i] = new queue ();                                                        // OpenCL queue.
    Q[i]    -> init (baseline);                                                 // Initializing OpenCL queue...
  }

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////// INITIALIZING OPENCL KERNELS /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  for(j = 0; j < KERNEL_NUM; j++)                                               // For each OpenCL kernel:
  {
    K_size[j] = new size_t[KERNEL_DIM];                                         // OpenCL kernel dimensions.

    for(i = 0; i < KERNEL_DIM; i++)                                             // Setting all kernel sizes...
    {
      K_size[j][i] = NODES;                                                     // Setting size of each kernel dimension...
    }

    K[j]      = new kernel ();                                                  // OpenCL kernel.
    K[j]    -> init (
                     baseline,                                                  // Neutrino baseline.
                     baseline -> prefix ("Code/kernel/thekernel.cl"),           // Kernel file name.
                     K_size[j],                                                 // Kernel dimensions array.
                     KERNEL_DIM                                                 // Kernel dimension.
                    );
  }

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////// INITIALIZING OPENCL DATA OBJECTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // Mesh nodes:
  points    -> init (baseline, NODES);                                          // Initializing points...

  // Mesh neighbourhood connectivity:
  index_PR -> init (baseline, NODES, 2);                                        // Right neighbours indexes...
  index_PU -> init (baseline, NODES, 3);                                        // Up neighbours indexes...
  index_PL -> init (baseline, NODES, 4);                                        // Left neighbours indexes...
  index_PD -> init (baseline, NODES, 5);                                        // Down neighbours indexes...

  // Mesh nodes colors:
  colors    -> init (baseline, NODES);                                          // Initializing colors...

  #if USE_OPENGL
    message   -> init (baseline, "neutrino 2.0!", 0.0, 1.0, 0.0, 1.0);          // Initializing message...
    controller -> init (baseline);
  #endif

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////// SETTING OPENCL DATA OBJECTS /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  for(j = 0; j < NODES_Y; j++)
  {
    for(i = 0; i < NODES_X; i++)
    {
      points -> set_x (j*NODES_X + i, XMIN + i*DX);
      points -> set_y (j*NODES_X + i, YMIN + j*DY);
      points -> set_z (j*NODES_X + i, 0.0);
      points -> set_w (j*NODES_X + i, 1.0);

      if((i != 0) && (i != (NODES_X - 1)) && (j != 0) && (j != (NODES_Y - 1)))  // When on bulk:
      {
        index_PR -> set_x (i + NODES_X*j, (i + 1) + NODES_X*j);
        index_PU -> set_x (i + NODES_X*j, i + NODES_X*(j + 1));
        index_PL -> set_x (i + NODES_X*j, (i - 1) + NODES_X*j);
        index_PD -> set_x (i + NODES_X*j, i + NODES_X*(j - 1));
      }

      if((i == 0) && (j != 0) && (j != (NODES_Y - 1)))                          // When on left border (excluding extremes):
      {
        index_PR -> set_x (i + NODES_X*j, (i + 1) + NODES_X*j);
        index_PU -> set_x (i + NODES_X*j, i + NODES_X*(j + 1));
        index_PL -> set_x (i + NODES_X*j, i + NODES_X*j);
        index_PD -> set_x (i + NODES_X*j, i + NODES_X*(j - 1));
      }

      if((i == (NODES_X - 1)) && (j != 0) && (j != (NODES_Y - 1)))              // When on right border (excluding extremes):
      {
        index_PR -> set_x (i + NODES_X*j, i + NODES_X*j);
        index_PU -> set_x (i + NODES_X*j, i + NODES_X*(j + 1));
        index_PL -> set_x (i + NODES_X*j, (i - 1) + NODES_X*j);
        index_PD -> set_x (i + NODES_X*j, i + NODES_X*(j - 1));
      }

      if((j == 0) && (i != 0) && (i != (NODES_X - 1)))                          // When on bottom border (excluding extremes):
      {
        index_PR -> set_x (i + NODES_X*j, (i + 1) + NODES_X*j);
        index_PU -> set_x (i + NODES_X*j, i + NODES_X*(j + 1));
        index_PL -> set_x (i + NODES_X*j, (i - 1) + NODES_X*j);
        index_PD -> set_x (i + NODES_X*j, i + NODES_X*j);
      }

      if((j == (NODES_Y - 1)) && (i != 0) && (i != (NODES_X - 1)))              // When on high border (excluding extremes):
      {
        index_PR -> set_x (i + NODES_X*j, (i + 1) + NODES_X*j);
        index_PU -> set_x (i + NODES_X*j, i + NODES_X*j);
        index_PL -> set_x (i + NODES_X*j, (i - 1) + NODES_X*j);
        index_PD -> set_x (i + NODES_X*j, i + NODES_X*(j - 1));
      }

      if((i == 0) && (j == 0))                                                  // When on bottom left corner:
      {
        index_PR -> set_x (i + NODES_X*j, (i + 1) + NODES_X*j);
        index_PU -> set_x (i + NODES_X*j, i + NODES_X*(j + 1));
        index_PL -> set_x (i + NODES_X*j, i + NODES_X*j);
        index_PD -> set_x (i + NODES_X*j, i + NODES_X*j);
      }

      if((i == (NODES_X - 1)) && (j == 0))                                      // When on bottom right corner:
      {
        index_PR -> set_x (i + NODES_X*j, i + NODES_X*j);
        index_PU -> set_x (i + NODES_X*j, i + NODES_X*(j + 1));
        index_PL -> set_x (i + NODES_X*j, (i - 1) + NODES_X*j);
        index_PD -> set_x (i + NODES_X*j, i + NODES_X*j);
      }

      if((i == 0) && (j == (NODES_Y - 1)))                                      // When on top left corner:
      {
        index_PR -> set_x (i + NODES_X*j, (i + 1) + NODES_X*j);
        index_PU -> set_x (i + NODES_X*j, i + NODES_X*j);
        index_PL -> set_x (i + NODES_X*j, i + NODES_X*j);
        index_PD -> set_x (i + NODES_X*j, i + NODES_X*(j - 1));
      }

      if((i == (NODES_X - 1)) && (j == (NODES_Y - 1)))                          // When on top right corner:
      {
        index_PR -> set_x (i + NODES_X*j, i + NODES_X*j);
        index_PU -> set_x (i + NODES_X*j, i + NODES_X*j);
        index_PL -> set_x (i + NODES_X*j, (i - 1) + NODES_X*j);
        index_PD -> set_x (i + NODES_X*j, i + NODES_X*(j - 1));
      }

      colors -> set_r (j*NODES_X + i, 0.01*(rand () % 100));
      colors -> set_g (j*NODES_X + i, 0.01*(rand () % 100));
      colors -> set_b (j*NODES_X + i, 0.01*(rand () % 100));
      colors -> set_a (j*NODES_X + i, 1.0);
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// SETTING OPENCL KERNEL ARGUMENTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  points    -> set_arg (K[0], 0);                                               // Setting kernel argument...
  colors    -> set_arg (K[0], 1);                                               // Setting kernel argument...

  #if USE_OPENGL
    points    -> acquire_gl (Q[0], 0);
  #endif

  points    -> push (Q[0], 0);

  #if USE_OPENGL
    points    -> release_gl (Q[0], 0);
  #endif

  #if USE_OPENGL
    colors    -> acquire_gl (Q[0], 1);
  #endif

  colors    -> push (Q[0], 1);

  #if USE_OPENGL
    colors    -> release_gl (Q[0], 1);
  #endif

  #if USE_OPENGL

    while(!gui -> closed ())                                                    // Opening window...
    {
      baseline -> get_tic ();                                                   // Getting "tic" [us]...

      gui     -> clear ();                                                      // Clearing window...
      gui     -> poll_events ();                                                // Polling window events...

      points  -> acquire_gl (Q[0], 0);
      colors  -> acquire_gl (Q[0], 1);

      K[0]    -> execute (Q[0], WAIT);

      points  -> release_gl (Q[0], 0);
      colors  -> release_gl (Q[0], 1);

      //gui     -> print (message);                                               // Printing text...
      gui     -> plot (points, colors, STYLE_WIREFRAME);
      //gui     -> cockpit_AI (controller);
      gui     -> refresh ();                                                    // Refreshing window...
      /*
         printf (
              "r = %f, p = %f, y = %f, q0 = %f, q1 = %f, q2 = %f, q3 = %f\n",
              gui -> roll,
              gui -> pitch,
              gui -> yaw,
              gui -> q[0],
              gui -> q[1],
              gui -> q[2],
              gui -> q[3]
             );
       */

      baseline -> get_toc ();                                                   // Getting "toc" [us]...
    }

  #else
    baseline -> get_tic ();

    K[0]    -> execute (Q[0], WAIT);

    baseline -> get_toc ();

    points -> pull (Q[0], 0);

    i = 100;
    float x = points -> get_x (i);
    float y = points -> get_y (i);
    float z = 0.1*sin (10*x) + 0.1*cos (10*y);
    printf ("x = %f, y = %f\n", x, y);
    printf ("Reference result: z = %f\n", z);
    printf ("Result from OpenCL kernel: z = %f\n", points -> get_z (i));
  #endif

  delete    baseline;
  #if USE_OPENGL
    delete    gui;
    delete    message;
    delete    controller;
  #endif
  delete    cl;

  delete    points;
  delete    colors;

  delete[]  Q;

  delete[]  K_size;
  delete[]  K;

  return 0;
}
