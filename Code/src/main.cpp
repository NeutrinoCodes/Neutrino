/// @file

// OPENGL:
#define USE_GRAPHICS                                                            // Define it in order to use OpenGL-OpenCL interoperability graphics.
#define SIZE_WINDOW_X 800                                                       // Window x-size [px].
#define SIZE_WINDOW_Y 600                                                       // Window y-size [px].
#define WINDOW_NAME   "neutrino 2.0"                                            // Window name.

// OPENCL:
#define KERNEL_DIM    1                                                         // Dimension of OpenCL kernels [#].

// MESH:
#define XMIN          -1.0                                                      // XMIN spatial boundary [m].
#define XMAX          1.0                                                       // XMAX spatial boundary [m].
#define YMIN          -1.0                                                      // YMIN spatial boundary [m].
#define YMAX          1.0                                                       // YMAX spatial boundary [m].
#define NODES_X       100                                                       // Number of nodes in "X" direction [#].
#define NODES_Y       100                                                       // Number of nodes in "Y" direction [#].
#define NODES         NODES_X* NODES_Y                                          // Total number of nodes [#].
#define DX            (float)((XMAX - XMIN)/(NODES_X - 1))                      // DX mesh spatial size [m].
#define DY            (float)((YMAX - YMIN)/(NODES_Y - 1))                      // DY mesh spatial size [m].

// CELL:
#define NEIGHBOURS    4                                                         // Number of neighbour nodes [#].
#define UP            0                                                         // Up neighbour designator [#].
#define DOWN          1                                                         // Down neighbour designator [#].
#define LEFT          2                                                         // Left neighbour designator [#].
#define RIGHT         3                                                         // Right neighbour designator [#].

// INCLUDES:
#include "opengl.hpp"
#include "opencl.hpp"

int main ()
{
  neutrino* baseline = new neutrino ();                                         // The Neutrino object.
  opengl*   gui      = new opengl ();                                           // The gui window object.
  opencl*   context  = new opencl ();                                           // The OpenCL context object.
  queue*    Q        = new queue ();                                            // OpenCL queue.
  kernel*   K        = new kernel ();                                           // OpenCL kernel array...
  point*    P        = new point ();

  /*
     node*     cell_node = new node ();                                            // Node array.
     bond*     cell_bond = new bond ();                                            // Bond array.
     int1      cell_number;                                                        // Number of cells.
     int1      cell_node_index;                                                    // Cell node index.
     int1      cell_bond_index[NEIGHBOURS];                                        // Cell neighbour index.
     float4    cell_node_position;                                                 // Cell node position.
     color4    cell_node_color;                                                    // Cell node color.
     size_t    i;
     size_t    j;
   */

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// INITIALIZATION ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  baseline->init (QUEUE_NUM, KERNEL_NUM);                                       // Initializing Neutrino...
  gui->init (baseline, SIZE_WINDOW_X, SIZE_WINDOW_Y, WINDOW_NAME);              // Initializing OpenGL context...
  context->init (baseline, gui->glfw_window, GPU);                              // Initializing OpenCL context...
  Q->init (baseline);                                                           // Initializing OpenCL queue...
  // Initializing OpenCL kernel...
  K->init (
           baseline,                                                            // Neutrino baseline.
           baseline->prefix ("Code/kernel/thekernel.cl"),                       // Kernel file name.
           NODES,                                                               // Kernel dimensions array.
           KERNEL_DIM                                                           // Kernel dimension.
          );
  P->init (NODES);                                                              // Initializing point array..

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// SETTING POINTS DATA /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  for(j = 0; j < NODES_Y; j++)
  {
    for(i = 0; i < NODES_X; i++)
    {
      cell_node_index.value = j*NODES_X + i;                                    // Setting node index...

      P[j*NODES_X + i].x    = i*DX + XMIN;
      P[j*NODES_X + i].y    = j*DY + YMIN;
      P[j*NODES_X + i].z    = 0.0;
      P[j*NODES_X + i].w    = 1.0;

      P[j*NODES_X + i].r    = 0.01*(rand () % 100);
      P[j*NODES_X + i].g    = 0.01*(rand () % 100);
      P[j*NODES_X + i].b    = 0.01*(rand () % 100);
      P[j*NODES_X + i].a    = 1.0;

      /*
         if((i != 0) && (i != (NODES_X - 1)) && (j != 0) && (j != (NODES_Y - 1)))  // When on bulk:
         {
         cell_bond_index[UP].value    = NODES_X*(j + 1) + (i + 0);
         cell_bond_index[DOWN].value  = NODES_X*(j - 1) + (i + 0);
         cell_bond_index[LEFT].value  = NODES_X*(j + 0) + (i - 1);
         cell_bond_index[RIGHT].value = NODES_X*(j + 0) + (i + 1);

         cell_bond->set_bond_index (
                                   cell_node_index,
                                   cell_bond_index
                                  );
         }

         if((i == 0) && (j != 0) && (j != (NODES_Y - 1)))                          // When on left border (excluding extremes):
         {
         cell_bond_index[UP].value    = NODES_X*(j + 1) + (i + 0);
         cell_bond_index[DOWN].value  = NODES_X*(j - 1) + (i + 0);
         cell_bond_index[LEFT].value  = NODES_X*(j + 0) + (i + 0);
         cell_bond_index[RIGHT].value = NODES_X*(j + 0) + (i + 1);

         cell_bond->set_bond_index (cell_node_index, cell_bond_index);
         }

         if((i == (NODES_X - 1)) && (j != 0) && (j != (NODES_Y - 1)))              // When on right border (excluding extremes):
         {
         cell_bond_index[UP].value    = NODES_X*(j + 1) + (i + 0);
         cell_bond_index[DOWN].value  = NODES_X*(j - 1) + (i + 0);
         cell_bond_index[LEFT].value  = NODES_X*(j + 0) + (i - 1);
         cell_bond_index[RIGHT].value = NODES_X*(j + 0) + (i + 0);

         cell_bond->set_bond_index (cell_node_index, cell_bond_index);
         }

         if((j == 0) && (i != 0) && (i != (NODES_X - 1)))                          // When on bottom border (excluding extremes):
         {
         cell_bond_index[UP].value    = NODES_X*(j + 1) + (i + 0);
         cell_bond_index[DOWN].value  = NODES_X*(j + 0) + (i + 0);
         cell_bond_index[LEFT].value  = NODES_X*(j + 0) + (i - 1);
         cell_bond_index[RIGHT].value = NODES_X*(j + 0) + (i + 1);

         cell_bond->set_bond_index (cell_node_index, cell_bond_index);
         }

         if((j == (NODES_Y - 1)) && (i != 0) && (i != (NODES_X - 1)))              // When on high border (excluding extremes):
         {
         cell_bond_index[UP].value    = NODES_X*(j + 0) + (i + 0);
         cell_bond_index[DOWN].value  = NODES_X*(j - 1) + (i + 0);
         cell_bond_index[LEFT].value  = NODES_X*(j + 0) + (i - 1);
         cell_bond_index[RIGHT].value = NODES_X*(j + 0) + (i + 1);

         cell_bond->set_bond_index (cell_node_index, cell_bond_index);
         }

         if((i == 0) && (j == 0))                                                  // When on bottom left corner:
         {
         cell_bond_index[UP].value    = NODES_X*(j + 1) + (i + 0);
         cell_bond_index[DOWN].value  = NODES_X*(j + 0) + (i + 0);
         cell_bond_index[LEFT].value  = NODES_X*(j + 0) + (i + 0);
         cell_bond_index[RIGHT].value = NODES_X*(j + 0) + (i + 1);

         cell_bond->set_bond_index (cell_node_index, cell_bond_index);
         }

         if((i == (NODES_X - 1)) && (j == 0))                                      // When on bottom right corner:
         {
         cell_bond_index[UP].value    = NODES_X*(j + 1) + (i + 0);
         cell_bond_index[DOWN].value  = NODES_X*(j + 0) + (i + 0);
         cell_bond_index[LEFT].value  = NODES_X*(j + 0) + (i - 1);
         cell_bond_index[RIGHT].value = NODES_X*(j + 0) + (i + 0);

         cell_bond->set_bond_index (cell_node_index, cell_bond_index);
         }

         if((i == 0) && (j == (NODES_Y - 1)))                                      // When on top left corner:
         {
         cell_bond_index[UP].value    = NODES_X*(j + 0) + (i + 0);
         cell_bond_index[DOWN].value  = NODES_X*(j - 1) + (i + 0);
         cell_bond_index[LEFT].value  = NODES_X*(j + 0) + (i + 0);
         cell_bond_index[RIGHT].value = NODES_X*(j + 0) + (i + 1);

         cell_bond->set_bond_index (cell_node_index, cell_bond_index);
         }

         if((i == (NODES_X - 1)) && (j == (NODES_Y - 1)))                          // When on top right corner:
         {
         cell_bond_index[UP].value    = NODES_X*(j + 0) + (i + 0);
         cell_bond_index[DOWN].value  = NODES_X*(j - 1) + (i + 0);
         cell_bond_index[LEFT].value  = NODES_X*(j + 0) + (i - 1);
         cell_bond_index[RIGHT].value = NODES_X*(j + 0) + (i + 0);

         cell_bond->set_bond_index (cell_node_index, cell_bond_index);
         }
       */
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// SETTING OPENCL KERNEL ARGUMENTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  K->setarg (P, 0);
  Q->write (P);

  while(!gui->closed ())                                                        // Opening window...
  {
    baseline->get_tic ();                                                       // Getting "tic" [us]...

    gui->clear ();                                                              // Clearing window...
    gui->poll_events ();                                                        // Polling window events...

    Q->acquire (P, 0);
    context->execute (K, Q, WAIT);
    Q->release (P, 0);

    gui->plot (
               cell_node,
               cell_link,
               PARTICLE_NUM,
               STYLE_SHADED
              );

    gui->refresh ();                                                            // Refreshing window...

    baseline->get_toc ();                                                       // Getting "toc" [us]...
  }

  delete baseline;
  delete gui;
  delete context;
  delete Q;
  delete K;
  delete P;

  return 0;
}
