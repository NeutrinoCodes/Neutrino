/// @file

// OPENGL:
#define USE_GRAPHICS                                                            // Define it in order to use OpenGL-OpenCL interoperability graphics.
#define SIZE_WINDOW_X 800                                                       // Window x-size [px].
#define SIZE_WINDOW_Y 600                                                       // Window y-size [px].
#define WINDOW_NAME   "neutrino 2.0"                                            // Window name.
#define VERTEX_FILE   "/Code/shader/voxel_vertex.vert"                          // OpenGL vertex shader.
#define GEOMETRY_FILE "/Code/shader/voxel_geometry.geom"                        // OpenGL geometry shader.
#define FRAGMENT_FILE "/Code/shader/voxel_fragment.frag"                        // OpenGL fragment shader.

// OPENCL:
#define KERNEL_DIM    1                                                         // Dimension of OpenCL kernels [#].
#define KERNEL_FILE   "Code/kernel/sine_kernel.cl"                              // OpenCL kernel.

// MESH:
#define XMIN          -1.0                                                      // XMIN spatial boundary [m].
#define XMAX          +1.0                                                      // XMAX spatial boundary [m].
#define YMIN          -1.0                                                      // YMIN spatial boundary [m].
#define YMAX          +1.0                                                      // YMAX spatial boundary [m].
#define NODES_X       100                                                       // Number of nodes in "X" direction [#].
#define NODES_Y       100                                                       // Number of nodes in "Y" direction [#].
#define NODES         NODES_X* NODES_Y                                          // Total number of nodes [#].
#define DX            (float)((XMAX - XMIN)/(NODES_X - 1))                      // DX mesh spatial size [m].
#define DY            (float)((YMAX - YMIN)/(NODES_Y - 1))                      // DY mesh spatial size [m].

// INCLUDES:
#include "opengl.hpp"
#include "opencl.hpp"

int main ()
{
  neutrino* bas = new neutrino ();                                              // Neutrino baseline.
  opengl*   gui = new opengl ();                                                // OpenGL context.
  opencl*   ctx = new opencl ();                                                // OpenCL context.
  shader*   S   = new shader ();                                                // OpenGL shader program.
  point*    P   = new point ();                                                 // OpenGL point.
  color*    C   = new color ();                                                 // OpenGL color.
  queue*    Q   = new queue ();                                                 // OpenCL queue.
  kernel*   K   = new kernel ();                                                // OpenCL kernel array.

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// INITIALIZATION ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  bas->init (QUEUE_NUM, KERNEL_NUM);                                            // Initializing Neutrino...
  gui->init (bas, SIZE_WINDOW_X, SIZE_WINDOW_Y, WINDOW_NAME);                   // Initializing OpenGL context...
  ctx->init (bas, gui->glfw_window, GPU);                                       // Initializing OpenCL context...
  S->init ();                                                                   // Initializing OpenGL shader...
  P->init (NODES);                                                              // Initializing OpenGL point array...
  C->init (NODES);                                                              // Initializing OpenGL color array...
  Q->init (bas);                                                                // Initializing OpenCL queue...
  K->init (
           bas,                                                                 // Neutrino baseline.
           bas->prefix (KERNEL_FILE),                                           // Kernel file name.
           NODES,                                                               // Kernel dimensions array.
           KERNEL_DIM                                                           // Kernel dimension.
          );

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// SETTING POINTS DATA /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  for(j = 0; j < NODES_Y; j++)
  {
    for(i = 0; i < NODES_X; i++)
    {
      // Setting point coordinates:
      P[j*NODES_X + i].x = i*DX + XMIN;
      P[j*NODES_X + i].y = j*DY + YMIN;
      P[j*NODES_X + i].z = 0.0;
      P[j*NODES_X + i].w = 1.0;

      // Setting point colors:
      C[j*NODES_X + i].r = 0.01*(rand () % 100);
      C[j*NODES_X + i].g = 0.01*(rand () % 100);
      C[j*NODES_X + i].b = 0.01*(rand () % 100);
      C[j*NODES_X + i].a = 1.0;
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// SETTING OPENCL KERNEL ARGUMENTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  K->setarg (P, 0);
  Q->write (P, 0);

  K->setarg (C, 1);
  Q->write (C, 1);

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// SETTING OPENGL SHADER ARGUMENTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  S->setarg (P, 0, "voxel_center");
  S->setarg (C, 1, "voxel_color");
  S->build ();

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// APPLICATION LOOP //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  while(!gui->closed ())                                                        // Opening window...
  {
    bas->get_tic ();                                                            // Getting "tic" [us]...

    gui->clear ();                                                              // Clearing window...
    gui->poll_events ();                                                        // Polling window events...

    Q->acquire (P, 0);
    ctx->execute (K, Q, WAIT);
    Q->release (P, 0);

    gui->plot (
               cell_node,
               cell_link,
               PARTICLE_NUM,
               STYLE_SHADED
              );

    gui->refresh ();                                                            // Refreshing window...

    bas->get_toc ();                                                            // Getting "toc" [us]...
  }

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// CLEANUP //////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  delete bas;
  delete gui;
  delete ctx;
  delete S;
  delete P;
  delete C;
  delete Q;
  delete K;

  return 0;
}
