/// @file

#define SIZE_WINDOW_X  800                                                      // Window x-size [px].
#define SIZE_WINDOW_Y  600                                                      // Window y-size [px].
#define WINDOW_NAME    "neutrino"                                               // Window name.

#define KDIM           1

#define XMIN          -1.0
#define XMAX           1.0
#define YMIN          -1.0
#define YMAX           1.0
#define NODES          10                                                       // Number of nodes.
#define DX             (XMAX - XMIN)/(float)(NODES - 1)
#define DY             (YMAX - YMIN)/(float)(NODES - 1)

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
  float4*   a               = new float4();
  float4*   b               = new float4();
  float4*   c               = new float4();

  queue*    q1              = new queue();                                      // OpenCL queue.

  size_t*   k1_size         = new size_t[KDIM];
  kernel*   k1              = new kernel();                                     // OpenCL kernel.

  size_t    i;
  size_t    j;

  k1_size[0] = NODES;

  baseline  ->init();                                                           // Initializing neutrino...
  gui       ->init(baseline, SIZE_WINDOW_X, SIZE_WINDOW_Y, WINDOW_NAME);        // Initializing gui window...
  message   ->init(baseline, "neutrino 2.0!", 1.0, 0.0, 0.0, 1.0);              // Initializing message...
  cl        ->init(baseline, gui->glfw_window, GPU);                            // Initializing OpenCL context...
  k1        ->init(baseline, "/Users/Erik/Documents/PROJECTS/BookhouseBoys/ezor/Neutrino/Code/kernel/thekernel.cl", k1_size, KDIM);
  q1        ->init(baseline);

  P         ->init(baseline, k1, 0, NODES);                                     // Initializin points...
  C         ->init(baseline, k1, 1, NODES);                                     // Initializing colors...
  //a         ->init(baseline, k1, 2, NODES);
  //b         ->init(baseline, k1, 4, NODES);
  //c         ->init(baseline, k1, 5, NODES);

  for(i = 0; i < NODES; i++)
  {
    P->set_x(i, XMIN + i*DX);
    P->set_y(i, 0.0);
    P->set_z(i, 0.0);
    P->set_w(i, 1.0);

    C->set_r(i, 1.0);
    C->set_g(i, 0.0);
    C->set_b(i, 0.0);
    C->set_a(i, 1.0);

    /*
    a->set_x(i, 1.0);
    a->set_y(i, 1.0);
    a->set_z(i, 1.0);
    a->set_w(i, 1.0);

    b->set_x(i, 1.0);
    b->set_y(i, 1.0);
    b->set_z(i, 1.0);
    b->set_w(i, 1.0);

    c->set_x(i, 0.0);
    c->set_y(i, 0.0);
    c->set_z(i, 0.0);
    c->set_w(i, 0.0);
    */
  }

  P->write(q1, k1, 0);
  C->write(q1, k1, 1);

  while (!gui->closed())                                                        // Opening window...
  {
    baseline->get_tic();                                                        // Getting "tic" [us]...

    gui->clear();                                                               // Clearing window...
    gui->poll_events();                                                         // Polling window events...

    P->acquire_gl(q1, k1, 0);
    C->acquire_gl(q1, k1, 1);
    //a->enqueue(q1, k1, 0);
    //b->enqueue(q1, k1, 1);
    //c->enqueue(q1, k1, 2);

    k1->execute(q1, WAIT);

    //a->dequeue(q1, k1, 0);
    //b->dequeue(q1, k1, 1);
    //c->dequeue(q1, k1, 2);
    P->release_gl(q1, k1, 0);
    C->release_gl(q1, k1, 1);

    //printf("a = %f, b = %f, c = %f\n", a->get_x(0), b->get_x(0), c->get_x(0));

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
