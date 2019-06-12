/// @file

// INCLUDES:
#include "opengl.hpp"
#include "opencl.hpp"

int main ()
{
  neutrino* stem      = new neutrino ();                                        // The Neutrino object.
  opengl*   gui       = new opengl ();                                          // The gui window object.
  opencl*   context   = new opencl ();                                          // The OpenCL context object.
  queue**   Q         = new queue*[QUEUE_NUM];                                  // OpenCL queue.
  size_t**  K_size    = new size_t*[KERNEL_NUM];                                // OpenCL kernel dimensions array...
  kernel**  K         = new kernel*[KERNEL_NUM];                                // OpenCL kernel array...

  node*     cell_node = new node ();                                            // Node array.
  bond*     cell_bond = new bond ();                                            // Bond array.
  int1      cell_number;                                                        // Number of cells.
  int1      cell_node_index;                                                    // Cell node index.
  int1      cell_bond_index[NEIGHBOURS];                                        // Cell neighbour index.
  float4    cell_node_position;                                                 // Cell node position.
  color4    cell_node_color;                                                    // Cell node color.
  size_t    i;
  size_t    j;

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////// INITIALIZING NEUTRINO, OPENGL and OPENCL //////////////////
  ////////////////////////////////////////////////////////////////////////////////
  stem->init (QUEUE_NUM, KERNEL_NUM);                                           // Initializing neutrino...
  gui->init (stem, SIZE_WINDOW_X, SIZE_WINDOW_Y, WINDOW_NAME);                  // Initializing window...
  context->init (stem, gui->glfw_window, GPU);                                  // Initializing OpenCL context...

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////// INITIALIZING OPENCL QUEUES /////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  for(i = 0; i < QUEUE_NUM; i++)                                                // For each OpenCL queue:
  {
    Q[i] = new queue ();                                                        // OpenCL queue.
    Q[i]->init (stem);                                                          // Initializing OpenCL queue...
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
                stem,                                                           // Neutrino baseline.
                stem->prefix ("Code/kernel/thekernel.cl"),                      // Kernel file name.
                K_size[j],                                                      // Kernel dimensions array.
                KERNEL_DIM                                                      // Kernel dimension.
               );
  }

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// INITIALIZING CELLS ////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  cell_number.value = NODES;

  cell_node->init (stem, cell_number);
  cell_bond->init (stem, cell_number);

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
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// SETTING OPENCL KERNEL ARGUMENTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  cell_node->push (Q[0]);
  cell_bond->push (Q[0]);

  while(!gui->closed ())                                                        // Opening window...
  {
    stem->get_tic ();                                                           // Getting "tic" [us]...

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

    stem->get_toc ();                                                           // Getting "toc" [us]...
  }

  delete    stem;
  delete    gui;
  delete    context;

  delete    cell_node;
  delete    cell_bond;

  delete[]  Q;

  delete[]  K_size;
  delete[]  K;

  return 0;
}
