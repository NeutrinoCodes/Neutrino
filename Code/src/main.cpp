/// @file

#define SIZE_WINDOW_X  800                                                      // Window x-size [px].
#define SIZE_WINDOW_Y  600                                                      // Window y-size [px].
#define WINDOW_NAME    "neutrino 2.0"                                           // Window name.

#define KDIM           1

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
  neutrino* baseline        = new neutrino();                                   // The Neutrino object.
  window*   gui             = new window();                                     // The gui window object.
  opencl*   cl              = new opencl();                                     // The OpenCL context object.
  text4*    message         = new text4();                                      // Text message.
  point4*   P               = new point4();                                     // Point array.
  color4*   C               = new color4();                                     // Color array.                                    

  queue*    q1              = new queue();                                      // OpenCL queue.

  size_t*   k1_size         = new size_t[KDIM];
  kernel*   k1              = new kernel();                                     // OpenCL kernel.

  size_t    i;
  size_t    j;

  k1_size[0] = NODES;

  baseline  ->init();                                                           // Initializing neutrino...
  gui       ->init(baseline, SIZE_WINDOW_X, SIZE_WINDOW_Y, WINDOW_NAME);        // Initializing window...
  message   ->init(baseline, "neutrino 2.0!", 0.0, 1.0, 0.0, 1.0);              // Initializing message...
  cl        ->init(baseline, gui->glfw_window, GPU);                            // Initializing OpenCL context...

  k1        ->init(
                    baseline,
                    baseline->prefix("Code/kernel/thekernel.cl"),
                    k1_size,
                    KDIM
                  );

  q1        ->init(baseline);

  P         ->init(baseline, k1, 0, NODES);                                     // Initializing points...
  C         ->init(baseline, k1, 1, NODES);                                     // Initializing colors...

  for(j = 0; j < NODES_Y; j++)
  {
    for(i = 0; i < NODES_X; i++)
    {
      P->set_x(j*NODES_Y + i, XMIN + i*DX);
      P->set_y(j*NODES_Y + i, YMIN + j*DY);
      P->set_z(j*NODES_Y + i, 0.0);
      P->set_w(j*NODES_Y + i, 1.0);

      C->set_r(j*NODES_Y + i, 0.01*(rand() % 100));
      C->set_g(j*NODES_Y + i, 0.01*(rand() % 100));
      C->set_b(j*NODES_Y + i, 0.01*(rand() % 100));
      C->set_a(j*NODES_Y + i, 1.0);
    }
  }

  P->acquire_gl(q1, k1, 0);
  C->acquire_gl(q1, k1, 1);
  P->write(q1, k1, 0);
  C->write(q1, k1, 1);
  P->release_gl(q1, k1, 0);
  C->release_gl(q1, k1, 1);

  while (!gui->closed())                                                        // Opening window...
  {
    baseline->get_tic();                                                        // Getting "tic" [us]...

    gui->clear();                                                               // Clearing window...
    gui->poll_events();                                                         // Polling window events...

    P->acquire_gl(q1, k1, 0);
    C->acquire_gl(q1, k1, 1);

    k1->execute(q1, WAIT);

    P->release_gl(q1, k1, 0);
    C->release_gl(q1, k1, 1);

    gui->print(message);                                                        // Printing text...
    gui->plot(P, C, STYLE_POINT);
    gui->refresh();                                                             // Refreshing window...

    baseline->get_toc();                                                        // Getting "toc" [us]...
  }

  delete    baseline;
  delete    gui;
  delete    cl;
  delete    message;

  delete    P;
  delete    C;

  delete    q1;

  delete[]  k1_size;
  delete    k1;

  return 0;
}
