/// @file

// OPENGL:
#define USE_GRAPHICS                                                            // Define it in order to use OpenGL-OpenCL interoperability graphics.
#define SIZE_WINDOW_X  800                                                      // Window x-size [px].
#define SIZE_WINDOW_Y  600                                                      // Window y-size [px].
#define WINDOW_NAME    "neutrino 2.0"                                           // Window name.

// OPENCL:
#define QUEUE_NUM      1                                                        // Number of OpenCL queues [#].
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
#define NEIGHBOURS_NUM 4                                                        // Number of neighbour nodes [#].
#define UP             0                                                        // Up neighbour designator [#].
#define DOWN           1                                                        // Down neighbour designator [#].
#define LEFT           2                                                        // Left neighbour designator [#].
#define RIGHT          3                                                        // Right neighbour designator [#].

// INCLUDES:
#include "opengl.hpp"
#include "opencl.hpp"

int main ()
{
  neutrino* baseline  = new neutrino ();                                        // The Neutrino object.
  opengl*   gui       = new opengl ();                                          // The gui window object.
  opencl*   context   = new opencl ();                                          // The OpenCL context object.
  queue**   Q         = new queue*[QUEUE_NUM];                                  // OpenCL queue.
  size_t**  K_size    = new size_t*[KERNEL_NUM];                                // OpenCL kernel dimensions array...
  kernel**  K         = new kernel*[KERNEL_NUM];                                // OpenCL kernel array...

  node*     cell_node = new node ();                                            // Node array.
  bond*     cell_link = new bond ();                                            // Link array.
  int1      cell_number;                                                        // Number of cells.
  int1      cell_node_index;                                                    // Cell node index.
  int1      cell_neighbour_index[NEIGHBOURS_NUM];                               // Cell neighbour index.
  float4    cell_node_position;                                                 // Cell node position.
  color4    cell_node_color;                                                    // Cell node color.
  size_t    i;
  size_t    j;

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////// INITIALIZING NEUTRINO, OPENGL and OPENCL //////////////////
  ////////////////////////////////////////////////////////////////////////////////
  baseline->init (QUEUE_NUM, KERNEL_NUM);                                       // Initializing neutrino...
  gui->init (baseline, SIZE_WINDOW_X, SIZE_WINDOW_Y, WINDOW_NAME);              // Initializing window...
  context->init (baseline, gui->glfw_window, GPU);                              // Initializing OpenCL context...

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////// INITIALIZING OPENCL QUEUES /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  for(i = 0; i < QUEUE_NUM; i++)                                                // For each OpenCL queue:
  {
    Q[i] = new queue ();                                                        // OpenCL queue.
    Q[i]->init (baseline);                                                      // Initializing OpenCL queue...
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
    K[j]->init (
                baseline,                                                       // Neutrino baseline.
                baseline->prefix ("Code/kernel/thekernel.cl"),                  // Kernel file name.
                K_size[j],                                                      // Kernel dimensions array.
                KERNEL_DIM                                                      // Kernel dimension.
               );
  }

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// INITIALIZING CELLS ////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  cell_number.value = NODES;

  cell_node->init (baseline, cell_number);
  cell_link->init (baseline, cell_number);

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// SETTING CELLS DATA /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  for(j = 0; j < NODES_Y; j++)
  {
    for(i = 0; i < NODES_X; i++)
    {
      cell_node_index.value = j*NODES_X + i;                                    // Setting node index...

      cell_node_position.x  = i*DX + XMIN;
      cell_node_position.y  = j*DY + YMIN;
      cell_node_position.z  = 0.0;
      cell_node_position.w  = 1.0;

      cell_node_color.r     = 0.01*(rand () % 100);
      cell_node_color.g     = 0.01*(rand () % 100);
      cell_node_color.b     = 0.01*(rand () % 100);
      cell_node_color.a     = 1.0;

      cell_node->set_position (cell_node_index, cell_node_position);
      cell_node->set_color (cell_node_index, cell_node_color);

      if((i != 0) && (i != (NODES_X - 1)) && (j != 0) && (j != (NODES_Y - 1)))  // When on bulk:
      {
        cell_neighbour_index[UP].value    = NODES_X*(j + 1) + (i + 0);
        cell_neighbour_index[DOWN].value  = NODES_X*(j - 1) + (i + 0);
        cell_neighbour_index[LEFT].value  = NODES_X*(j + 0) + (i - 1);
        cell_neighbour_index[RIGHT].value = NODES_X*(j + 0) + (i + 1);

        cell_link->set_neighbour_index (cell_node_index, cell);
      }

      if((i == 0) && (j != 0) && (j != (NODES_Y - 1)))                          // When on left border (excluding extremes):
      {
        cell_neighbour_index[UP].value    = NODES_X*(j + 1) + (i + 0);
        cell_neighbour_index[DOWN].value  = NODES_X*(j - 1) + (i + 0);
        cell_neighbour_index[LEFT].value  = NODES_X*(j + 0) + (i + 0);
        cell_neighbour_index[RIGHT].value = NODES_X*(j + 0) + (i + 1);

        cell_link->set_neighbour_index (cell_node_index, cell);
      }

      if((i == (NODES_X - 1)) && (j != 0) && (j != (NODES_Y - 1)))              // When on right border (excluding extremes):
      {
        cell_neighbour_index[UP].value    = NODES_X*(j + 1) + (i + 0);
        cell_neighbour_index[DOWN].value  = NODES_X*(j - 1) + (i + 0);
        cell_neighbour_index[LEFT].value  = NODES_X*(j + 0) + (i - 1);
        cell_neighbour_index[RIGHT].value = NODES_X*(j + 0) + (i + 0);

        cell_link->set_neighbour_index (cell_node_index, cell);
      }

      if((j == 0) && (i != 0) && (i != (NODES_X - 1)))                          // When on bottom border (excluding extremes):
      {
        cell_neighbour_index[UP].value    = NODES_X*(j + 1) + (i + 0);
        cell_neighbour_index[DOWN].value  = NODES_X*(j + 0) + (i + 0);
        cell_neighbour_index[LEFT].value  = NODES_X*(j + 0) + (i - 1);
        cell_neighbour_index[RIGHT].value = NODES_X*(j + 0) + (i + 1);

        cell_link->set_neighbour_index (cell_node_index, cell);
      }

      if((j == (NODES_Y - 1)) && (i != 0) && (i != (NODES_X - 1)))              // When on high border (excluding extremes):
      {
        cell_neighbour_index[UP].value    = NODES_X*(j + 0) + (i + 0);
        cell_neighbour_index[DOWN].value  = NODES_X*(j - 1) + (i + 0);
        cell_neighbour_index[LEFT].value  = NODES_X*(j + 0) + (i - 1);
        cell_neighbour_index[RIGHT].value = NODES_X*(j + 0) + (i + 1);

        cell_link->set_neighbour_index (cell_node_index, cell);
      }

      if((i == 0) && (j == 0))                                                  // When on bottom left corner:
      {
        cell_neighbour_index[UP].value    = NODES_X*(j + 1) + (i + 0);
        cell_neighbour_index[DOWN].value  = NODES_X*(j + 0) + (i + 0);
        cell_neighbour_index[LEFT].value  = NODES_X*(j + 0) + (i + 0);
        cell_neighbour_index[RIGHT].value = NODES_X*(j + 0) + (i + 1);

        cell_link->set_neighbour_index (cell_node_index, cell);
      }

      if((i == (NODES_X - 1)) && (j == 0))                                      // When on bottom right corner:
      {
        cell_neighbour_index[UP].value    = NODES_X*(j + 1) + (i + 0);
        cell_neighbour_index[DOWN].value  = NODES_X*(j + 0) + (i + 0);
        cell_neighbour_index[LEFT].value  = NODES_X*(j + 0) + (i - 1);
        cell_neighbour_index[RIGHT].value = NODES_X*(j + 0) + (i + 0);

        cell_link->set_neighbour_index (cell_node_index, cell);
      }

      if((i == 0) && (j == (NODES_Y - 1)))                                      // When on top left corner:
      {
        cell_neighbour_index[UP].value    = NODES_X*(j + 0) + (i + 0);
        cell_neighbour_index[DOWN].value  = NODES_X*(j - 1) + (i + 0);
        cell_neighbour_index[LEFT].value  = NODES_X*(j + 0) + (i + 0);
        cell_neighbour_index[RIGHT].value = NODES_X*(j + 0) + (i + 1);

        cell_link->set_neighbour_index (cell_node_index, cell);
      }

      if((i == (NODES_X - 1)) && (j == (NODES_Y - 1)))                          // When on top right corner:
      {
        cell_neighbour_index[UP].value    = NODES_X*(j + 0) + (i + 0);
        cell_neighbour_index[DOWN].value  = NODES_X*(j - 1) + (i + 0);
        cell_neighbour_index[LEFT].value  = NODES_X*(j + 0) + (i - 1);
        cell_neighbour_index[RIGHT].value = NODES_X*(j + 0) + (i + 0);

        cell_link->set_neighbour_index (cell_node_index, cell);
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// SETTING OPENCL KERNEL ARGUMENTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  cell_node->push (Q[0]);
  cell_link->push (Q[0]);

  while(!gui->closed ())                                                        // Opening window...
  {
    baseline->get_tic ();                                                       // Getting "tic" [us]...

    gui->clear ();                                                              // Clearing window...
    gui->poll_events ();                                                        // Polling window events...

// EZOR: testing data structures.
/*
    cell_node->acquire (Q[0]);
    cell_link->acquire (Q[0]);

    K[0]->execute (Q[0], WAIT);

    cell_node->release (Q[0]);
    cell_link->release (Q[0]);

    gui->plot (
               cell_node,
               cell_link,
               PARTICLE_NUM,
               STYLE_SHADED
              );
 */
    gui->refresh ();                                                            // Refreshing window...

    baseline->get_toc ();                                                       // Getting "toc" [us]...
  }

  delete    baseline;
  delete    gui;
  delete    context;

  delete    cell_node;
  delete    cell_link;

  delete[]  Q;

  delete[]  K_size;
  delete[]  K;

  return 0;
}
