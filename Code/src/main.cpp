/// @file

// MESH:
 #define XMIN        -1.0                                                       // XMIN spatial boundary [m].
 #define XMAX        +1.0                                                       // XMAX spatial boundary [m].
 #define YMIN        -1.0                                                       // YMIN spatial boundary [m].
 #define YMAX        +1.0                                                       // YMAX spatial boundary [m].
 #define NODES_X     10                                                         // Number of nodes in "X" direction [#].
 #define NODES_Y     10                                                         // Number of nodes in "Y" direction [#].
 #define NODES       100                                                        // To be fixed: (NODES_X)*(NODES_Y)                           // Total number of nodes [#].
 #define DX          (float)((XMAX - XMIN)/(NODES_X - 1))                       // DX mesh spatial size [m].
 #define DY          (float)((YMAX - YMIN)/(NODES_Y - 1))                       // DY mesh spatial size [m].

// OPENGL:
 #define INTEROP     true                                                       // "true" = use OpenGL-OpenCL interoperability.
 #define GUI_SIZE_X  800                                                        // Window x-size [px].
 #define GUI_SIZE_Y  600                                                        // Window y-size [px].
 #define GUI_NAME    "neutrino 3.0"                                             // Window name.
#define SHADER_HOME \
  "/run/media/ezor/LINUX/BookhouseBoys/ezor/Neutrino/Code/shader"
//#define SHADER_HOME \
//  "/Users/Erik/Documents/PROJECTS/BookhouseBoys/ezor/Neutrino/Code/shader"
 #define SHADER_VERT "voxel_vertex.vert"                                        // OpenGL vertex shader.
 #define SHADER_GEOM "voxel_geometry.geom"                                      // OpenGL geometry shader.
 #define SHADER_FRAG "voxel_fragment.frag"                                      // OpenGL fragment shader.

// OPENCL:
 #define QUEUE_NUM   1                                                          // # of OpenCL queues [#].
 #define KERNEL_NUM  1                                                          // # of OpenCL kernel [#].
 #define KERNEL_SX   NODES                                                      // Dimension of OpenCL kernel (i-index).
 #define KERNEL_SY   0                                                          // Dimension of OpenCL kernel (j-index).
 #define KERNEL_SZ   0                                                          // Dimension of OpenCL kernel (k-index).
#define KERNEL_HOME \
  "/run/media/ezor/LINUX/BookhouseBoys/ezor/Neutrino/Code/kernel"               // OpenCL kernel header files directory.
//#define KERNEL_HOME \
//  "/Users/Erik/Documents/PROJECTS/BookhouseBoys/ezor/Neutrino/Code/kernel"
 #define KERNEL_FILE "sine_kernel.cl"                                           // OpenCL kernel.

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
  size_t    i;                                                                  // "x" direction index.
  size_t    j;                                                                  // "y" direction index.

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// INITIALIZATION ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  bas->init (QUEUE_NUM, KERNEL_NUM, INTEROP);                                   // Initializing Neutrino baseline...
  gui->init (bas, GUI_SIZE_X, GUI_SIZE_Y, GUI_NAME);                            // Initializing OpenGL context...
  ctx->init (bas, gui, GPU);                                                    // Initializing OpenCL context...
  S->init (bas, SHADER_HOME, SHADER_VERT, SHADER_GEOM, SHADER_FRAG);            // Initializing OpenGL shader...
  P->init (NODES);                                                              // Initializing OpenGL point array...
  C->init (NODES);                                                              // Initializing OpenGL color array...
  Q->init (bas);                                                                // Initializing OpenCL queue...
  K->init (bas, KERNEL_HOME, KERNEL_FILE, KERNEL_SX, KERNEL_SY, KERNEL_SZ);     // Initializing OpenCL kernel...

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// SETTING POINTS DATA /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  P->name = "voxel_center";
  C->name = "voxel_color";

  for(j = 0; j < NODES_Y; j++)
  {
    for(i = 0; i < NODES_X; i++)
    {
      // Setting point coordinates:
      P->data[j*NODES_X + i].x = i*DX + XMIN;
      P->data[j*NODES_X + i].y = j*DY + YMIN;
      P->data[j*NODES_X + i].z = 0.0;
      P->data[j*NODES_X + i].w = 1.0;

      // Setting point colors:
      C->data[j*NODES_X + i].r = 0.01*(rand () % 100);
      C->data[j*NODES_X + i].g = 0.01*(rand () % 100);
      C->data[j*NODES_X + i].b = 0.01*(rand () % 100);
      C->data[j*NODES_X + i].a = 1.0;
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// SETTING OPENCL KERNEL ARGUMENTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  K->setarg (P, 0);                                                             // Setting kernel argument...
  Q->acquire (P, 0);                                                            // Acquiring OpenGL/CL shared argument...
  Q->write (P, 0);                                                              // Uploading data on kernel...
  Q->release (P, 0);                                                            // Releasing OpenGL/CL shared argument...

  K->setarg (C, 1);                                                             // Setting kernel argument...
  Q->acquire (C, 1);                                                            // Acquiring OpenGL/CL shared argument...
  Q->write (C, 1);                                                              // Uploading data on kernel...
  Q->release (C, 1);                                                            // Releasing OpenGL/CL shared argument...

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// SETTING OPENGL SHADER ARGUMENTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  S->setarg (P, 0);                                                             // Setting shader argument...
  S->setarg (C, 1);                                                             // Setting shader argument...
  S->build ();                                                                  // Building shader program...

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// APPLICATION LOOP //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  while(!gui->closed ())                                                        // Opening gui...
  {
    bas->get_tic ();                                                            // Getting "tic" [us]...
    gui->clear ();                                                              // Clearing gui...
    gui->poll_events ();                                                        // Polling gui events...

    Q->acquire (P, 0);                                                          // Acquiring OpenGL/CL shared argument...
    Q->acquire (C, 1);                                                          // Acquiring OpenGL/CL shared argument...
    //ctx->execute (K, Q, WAIT);                                                  // Executing OpenCL kenrnel...
    Q->release (P, 0);                                                          // Releasing OpenGL/CL shared argument...
    Q->release (C, 1);                                                          // Releasing OpenGL/CL shared argument...

    gui->plot (S);                                                              // Plotting shared arguments...
    gui->refresh ();                                                            // Refreshing gui...
    bas->get_toc ();                                                            // Getting "toc" [us]...
  }

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// CLEANUP //////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  delete bas;                                                                   // Deleting Neutrino baseline...
  delete gui;                                                                   // Deleting OpenGL gui ...
  delete ctx;                                                                   // Deleting OpenCL context...
  delete S;                                                                     // Deleting OpenGL shader...
  delete P;                                                                     // Deleting OpenGL point...
  delete C;                                                                     // Deleting OpenGL color...
  delete Q;                                                                     // Deleting OpenCL queue...
  delete K;                                                                     // Deleting OpenCL kernel...

  return 0;
}
