/// @file

#define SIZE_WINDOW_X 800                                                       // Window x-size [px].
#define SIZE_WINDOW_Y 600                                                       // Window y-size [px].
#define WINDOW_NAME   "neutrino"                                                // Window name.
#define NODES         100                                                       // Number of nodes.

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
  kernel*   k1              = new kernel();                                     // OpenCL kernel.
  kernel*   k2              = new kernel();                                     // OpenCL kernel.

  baseline  ->init();                                                           // Initializing neutrino...
  gui       ->init(baseline, SIZE_WINDOW_X, SIZE_WINDOW_Y, WINDOW_NAME);        // Initializing gui window...
  message   ->init(baseline, "neutrino 2.0!", 1.0, 1.0, 1.0, 1.0);              // Initializing message...
  cl        ->init(baseline, gui->glfw_window, GPU);                            // Initializing OpenCL context...
  P         ->init(baseline, NODES);                                            // Initializin points...
  C         ->init(baseline, NODES);                                            // Initializing colors...




  //baseline->context_id = opencl_context->context_id;
  //baseline->device_id = opencl_context->existing_device[opencl_context->choosen_device]->device_id;

  // SETUP:
  //q1->init(baseline);

  while (!gui->closed())                                                        // Opening window...
  {
    baseline->get_tic();                                                        // Getting "tic" [us]...

    gui->clear();                                                               // Clearing window...
    gui->poll_events();                                                         // Polling window events...
    gui->print(message);                                                        // Printing text...
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
  delete k1;
  delete k2;

  return 0;
}
