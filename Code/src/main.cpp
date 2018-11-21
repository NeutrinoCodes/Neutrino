/// @file

#define SIZE_WINDOW_X 800                                                       // Window x-size [px].
#define SIZE_WINDOW_Y 600                                                       // Window y-size [px].
#define WINDOW_NAME   "neutrino"                                                // Window name.

#define KDIM          1

#define XMIN          -1.0
#define XMAX           1.0
#define YMIN          -1.0
#define YMAX           1.0
#define NODES         10                                                        // Number of nodes.
#define DX            (XMAX - XMIN)/(float)NODES
#define DY            (YMAX - YMIN)/(float)NODES

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
  gui       ->init(baseline, SIZE_WINDOW_X, SIZE_WINDOW_Y, WINDOW_NAME);        // Initializing gui window...
  message   ->init(baseline, "neutrino 2.0!", 1.0, 1.0, 1.0, 1.0);              // Initializing message...
  cl        ->init(baseline, gui->glfw_window, GPU);                            // Initializing OpenCL context...
  P         ->init(baseline, NODES);                                            // Initializin points...
  C         ->init(baseline, NODES);                                            // Initializing colors...
  k1        ->init(baseline, "/Users/Erik/Documents/PROJECTS/BookhouseBoys/ezor/Neutrino/Code/kernel/thekernel.cl", k1_size, KDIM);
  q1        ->init(baseline);

  for(i = 0; i < NODES; i++)
  {
    P->x[i] = XMIN + i*DX;
    P->y[i] = 0.0;
    P->z[i] = 0.0;
    P->w[i] = 1.0;

    C->r[i] = 1.0;
    C->g[i] = 0.0;
    C->b[i] = 0.0;
    C->a[i] = 1.0;
  }

  P->set(k1, 0);
  C->set(k1, 1);

  while (!gui->closed())                                                        // Opening window...
  {
    baseline->get_tic();                                                        // Getting "tic" [us]...

    gui->clear();                                                               // Clearing window...
    gui->poll_events();                                                         // Polling window events...

    P->push(q1, k1, 0);
    C->push(q1, k1, 1);
    k1->execute(q1, WAIT);
    P->pop(q1, k1, 0);
    C->pop(q1, k1, 1);


    gui->print(message);                                                        // Printing text...
    gui->plot(P, C, STYLE_POINT);
    gui->refresh();                                                             // Refreshing window...



    baseline->get_toc();                                                        // Getting "toc" [us]...
  }

  delete baseline;
  delete gui;
  delete cl;
  delete message;
  delete P;
  delete C;

  delete q1;

  delete k1_size;
  delete k1;

  return 0;
}
