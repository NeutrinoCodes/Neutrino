/// @file

// GRAPHICS:
#define USE_GRAPHICS                                                            // Define it in order to use OpenGL-OpenCL interoperability graphics.

// WINDOW:
#define SIZE_WINDOW_X  800                                                      // Window x-size [px].
#define SIZE_WINDOW_Y  600                                                      // Window y-size [px].
#define WINDOW_NAME    "neutrino 2.0"                                           // Window name.

// OPENCL QUEUES:
#define QUEUE_NUM      1                                                        // Number of OpenCL queues [#].

// OPENCL KERNELS:
#define KERNEL_NUM     1                                                        // Number of OpenCL kernels [#].
#define KERNEL_DIM     1                                                        // Dimension of OpenCL kernels [#].

// MESH:
#define XMIN           -1.0                                                     // XMIN spatial boundary [m].
#define XMAX           1.0                                                      // XMAX spatial boundary [m].
#define YMIN           -1.0                                                     // YMIN spatial boundary [m].
#define YMAX           1.0                                                      // YMAX spatial boundary [m].
#define NODES_X        100                                                      // Number of nodes in "X" direction [#].
#define NODES_Y        100                                                      // Number of nodes in "Y" direction [#].
#define NODES          NODES_X* NODES_Y                                         // Total number of nodes [#].
#define DX             (float)((XMAX - XMIN)/(NODES_X - 1))                     // DX mesh spatial size [m].
#define DY             (float)((YMAX - YMIN)/(NODES_Y - 1))                     // DY mesh spatial size [m].

// CELL:
#define NUM_NEIGHBOURS 4                                                        // Number of neighbour nodes [#].
#define PARTICLE_NUM   5                                                        // Total number of particles in computational molecule [#].
#define PC             0                                                        // Central particle designator [#].
#define PR             1                                                        // Right particle designator [#].
#define PU             2                                                        // Up particle designator [#].
#define PL             3                                                        // Left particle designator [#].
#define PD             4                                                        // Down particle designator [#].

#include "neutrino.hpp"
#include "opengl.hpp"
#include "opencl.hpp"
#include "queue.hpp"
#include "kernel.hpp"
#include "node.hpp"
#include "link.hpp"

int main ()
{
  size_t        i;
  size_t        j;

  neutrino*     baseline   = new neutrino ();                                   // The Neutrino object.

  #if USE_GRAPHICS
    window*     gui        = new window ();                                     // The gui window object.
    text4*      message    = new text4 ();                                      // Text message.
    memory_orb* controller = new memory_orb ();
  #endif

  opencl*       cl         = new opencl ();                                     // The OpenCL context object.
  queue**       Q          = new queue*[QUEUE_NUM];                             // OpenCL queue.
  size_t**      K_size     = new size_t*[KERNEL_NUM];                           // OpenCL kernel dimensions array...
  kernel**      K          = new kernel*[KERNEL_NUM];                           // OpenCL kernel array...

  color4*       color      = new color4 ();                                     // Color array.
  point4**      point      = new point4*[PARTICLE_NUM];                         // Point array.
  int1**        index      = new int1*[PARTICLE_NUM];                           // Index array.
  int           vao_index;                                                      // VAO index.

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
  vao_index = 0;                                                                // Setting VAO index...
  color -> init (baseline, NODES, vao_index);                                   // Initializing PC colors...

  for(i = 0; i < PARTICLE_NUM; i++)                                             // For each particle in computational molecule:
  {
    vao_index = i + 1;                                                          // Setting VAO index...

    // Position arrays:
    point[i]  = new point4 ();                                                  // Instatiating point array...
    point[i] -> init (baseline, NODES, vao_index);                              // Initializing point array...

    // Mesh neighbourhood connectivity:
    index[i]  = new int1 ();                                                    // Instantiating index array...
    index[i] -> init (baseline, NODES);                                         // Initializing index array...
  }

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
      color -> set_r (j*NODES_X + i, 0.01*(rand () % 100));                     // Setting RED color channel...
      color -> set_g (j*NODES_X + i, 0.01*(rand () % 100));                     // Setting GREEN color channel...
      color -> set_b (j*NODES_X + i, 0.01*(rand () % 100));                     // Setting BLUE color channel...
      color -> set_a (j*NODES_X + i, 1.0);                                      // Setting ALPHA color channel...

      index[PC] -> set_x (j*NODES_X + i, j*NODES_X + i);                        // Setting index of PC (trivial case, not used)...

      point[PC] -> set_x (j*NODES_X + i, i*DX + XMIN);
      point[PC] -> set_y (j*NODES_X + i, j*DY + YMIN);
      point[PC] -> set_z (j*NODES_X + i, 0.0);
      point[PC] -> set_w (j*NODES_X + i, 1.0);

      if((i != 0) && (i != (NODES_X - 1)) && (j != 0) && (j != (NODES_Y - 1)))  // When on bulk:
      {
        index[PR] -> set_x (j*NODES_X + i, NODES_X*j + (i + 1));
        index[PU] -> set_x (j*NODES_X + i, NODES_X*(j + 1) + i);
        index[PL] -> set_x (j*NODES_X + i, NODES_X*j + (i - 1));
        index[PD] -> set_x (j*NODES_X + i, NODES_X*(j - 1) + i);
      }

      if((i == 0) && (j != 0) && (j != (NODES_Y - 1)))                          // When on left border (excluding extremes):
      {
        index[PR] -> set_x (j*NODES_X + i, NODES_X*j + (i + 1));
        index[PU] -> set_x (j*NODES_X + i, NODES_X*(j + 1) + i);
        index[PL] -> set_x (j*NODES_X + i, NODES_X*j + i);
        index[PD] -> set_x (j*NODES_X + i, NODES_X*(j - 1) + i);
      }

      if((i == (NODES_X - 1)) && (j != 0) && (j != (NODES_Y - 1)))              // When on right border (excluding extremes):
      {
        index[PR] -> set_x (j*NODES_X + i, NODES_X*j + i);
        index[PU] -> set_x (j*NODES_X + i, NODES_X*(j + 1) + i);
        index[PL] -> set_x (j*NODES_X + i, NODES_X*j + (i - 1));
        index[PD] -> set_x (j*NODES_X + i, NODES_X*(j - 1) + i);
      }

      if((j == 0) && (i != 0) && (i != (NODES_X - 1)))                          // When on bottom border (excluding extremes):
      {
        index[PR] -> set_x (j*NODES_X + i, NODES_X*j + (i + 1));
        index[PU] -> set_x (j*NODES_X + i, NODES_X*(j + 1) + i);
        index[PL] -> set_x (j*NODES_X + i, NODES_X*j + (i - 1));
        index[PD] -> set_x (j*NODES_X + i, NODES_X*j + i);
      }

      if((j == (NODES_Y - 1)) && (i != 0) && (i != (NODES_X - 1)))              // When on high border (excluding extremes):
      {
        index[PR] -> set_x (j*NODES_X + i, NODES_X*j + (i + 1));
        index[PU] -> set_x (j*NODES_X + i, NODES_X*j + i);
        index[PL] -> set_x (j*NODES_X + i, NODES_X*j + (i - 1));
        index[PD] -> set_x (j*NODES_X + i, NODES_X*(j - 1) + i);
      }

      if((i == 0) && (j == 0))                                                  // When on bottom left corner:
      {
        index[PR] -> set_x (j*NODES_X + i, NODES_X*j + (i + 1));
        index[PU] -> set_x (j*NODES_X + i, NODES_X*(j + 1) + i);
        index[PL] -> set_x (j*NODES_X + i, NODES_X*j + i);
        index[PD] -> set_x (j*NODES_X + i, NODES_X*j + i);
      }

      if((i == (NODES_X - 1)) && (j == 0))                                      // When on bottom right corner:
      {
        index[PR] -> set_x (j*NODES_X + i, NODES_X*j + i);
        index[PU] -> set_x (j*NODES_X + i, NODES_X*(j + 1) + i);
        index[PL] -> set_x (j*NODES_X + i, NODES_X*j + (i - 1));
        index[PD] -> set_x (j*NODES_X + i, NODES_X*j + i);
      }

      if((i == 0) && (j == (NODES_Y - 1)))                                      // When on top left corner:
      {
        index[PR] -> set_x (j*NODES_X + i, NODES_X*j + (i + 1));
        index[PU] -> set_x (j*NODES_X + i, NODES_X*j + i);
        index[PL] -> set_x (j*NODES_X + i, NODES_X*j + i);
        index[PD] -> set_x (j*NODES_X + i, NODES_X*(j - 1) + i);
      }

      if((i == (NODES_X - 1)) && (j == (NODES_Y - 1)))                          // When on top right corner:
      {
        index[PR] -> set_x (j*NODES_X + i, NODES_X*j + i);
        index[PU] -> set_x (j*NODES_X + i, NODES_X*j + i);
        index[PL] -> set_x (j*NODES_X + i, NODES_X*j + (i - 1));
        index[PD] -> set_x (j*NODES_X + i, NODES_X*(j - 1) + i);
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// SETTING OPENCL KERNEL ARGUMENTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  color           -> set_arg (K[0], 0);                                         // Setting kernel argument...
  point[PC]       -> set_arg (K[0], 1);                                         // Setting kernel argument...
  point[PR]       -> set_arg (K[0], 2);                                         // Setting kernel argument...
  point[PU]       -> set_arg (K[0], 3);                                         // Setting kernel argument...
  point[PL]       -> set_arg (K[0], 4);                                         // Setting kernel argument...
  point[PD]       -> set_arg (K[0], 5);                                         // Setting kernel argument...
  index[PR]       -> set_arg (K[0], 6);                                         // Setting kernel argument...
  index[PU]       -> set_arg (K[0], 7);                                         // Setting kernel argument...
  index[PL]       -> set_arg (K[0], 8);                                         // Setting kernel argument...
  index[PD]       -> set_arg (K[0], 9);                                         // Setting kernel argument...

  #if USE_OPENGL
    color         -> acquire_gl (Q[0], 0);
    point[PC]     -> acquire_gl (Q[0], 1);
    point[PR]     -> acquire_gl (Q[0], 2);
    point[PU]     -> acquire_gl (Q[0], 3);
    point[PL]     -> acquire_gl (Q[0], 4);
    point[PD]     -> acquire_gl (Q[0], 5);
  #endif

  color           -> push (Q[0], 0);
  point[PC]       -> push (Q[0], 1);
  point[PR]       -> push (Q[0], 2);
  point[PU]       -> push (Q[0], 3);
  point[PL]       -> push (Q[0], 4);
  point[PD]       -> push (Q[0], 5);
  index[PR]       -> push (Q[0], 6);
  index[PU]       -> push (Q[0], 7);
  index[PL]       -> push (Q[0], 8);
  index[PD]       -> push (Q[0], 9);

  #if USE_OPENGL
    color         -> release_gl (Q[0], 0);
    point[PC]     -> release_gl (Q[0], 1);
    point[PR]     -> release_gl (Q[0], 2);
    point[PU]     -> release_gl (Q[0], 3);
    point[PL]     -> release_gl (Q[0], 4);
    point[PD]     -> release_gl (Q[0], 5);
  #endif

  #if USE_OPENGL

    while(!gui -> closed ())                                                    // Opening window...
    {
      baseline    -> get_tic ();                                                // Getting "tic" [us]...

      gui         -> clear ();                                                  // Clearing window...
      gui         -> poll_events ();                                            // Polling window events...

      color       -> acquire_gl (Q[0], 0);
      point[PC]   -> acquire_gl (Q[0], 1);
      point[PR]   -> acquire_gl (Q[0], 2);
      point[PU]   -> acquire_gl (Q[0], 3);
      point[PL]   -> acquire_gl (Q[0], 4);
      point[PD]   -> acquire_gl (Q[0], 5);

      K[0]        -> execute (Q[0], WAIT);

      color       -> release_gl (Q[0], 0);
      point[PC]   -> release_gl (Q[0], 1);
      point[PR]   -> release_gl (Q[0], 2);
      point[PU]   -> release_gl (Q[0], 3);
      point[PL]   -> release_gl (Q[0], 4);
      point[PD]   -> release_gl (Q[0], 5);

      //gui     -> print (message);                                             // Printing text...
      gui         -> plot (
                           color,
                           point,
                           PARTICLE_NUM,
                           STYLE_SHADED
                          );
      //gui     -> cockpit_AI (controller);
      gui         -> refresh ();                                                // Refreshing window...
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

  #endif

  delete    baseline;

  #if USE_OPENGL
    delete    gui;
    delete    message;
    delete    controller;
  #endif

  delete    cl;

  delete    color;
  delete[]  point;

  delete[]  index;

  delete[]  Q;

  delete[]  K_size;
  delete[]  K;

  return 0;
}
