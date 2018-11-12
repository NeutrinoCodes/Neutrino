/// @file

#define SIZE_WINDOW_X 800                                                       // Window x-size [px].
#define SIZE_WINDOW_Y 600                                                       // Window y-size [px].
#define WINDOW_NAME   "neutrino"                                                // Window name.

#include "neutrino.hpp"
#include "window.hpp"
#include "opencl.hpp"
#include "queue.hpp"
#include "kernel.hpp"

int main()
{
  neutrino* baseline        = new neutrino();                                   // The Neutrino object.
  window*   gui             = new window();                                     // The gui window object.
  opencl*   opencl_context  = new opencl();                                     // The OpenCL context object.
  text4*    message         = new text4();

  queue*    q1              = new queue();                                      // OpenCL queue.
  kernel*   k1              = new kernel();                                     // OpenCL kernel.
  kernel*   k2              = new kernel();                                     // OpenCL kernel.

  baseline->init();                                                             // Initializing neutrino...
  gui->init(baseline, SIZE_WINDOW_X, SIZE_WINDOW_Y, WINDOW_NAME);               // Initializing gui window...
  message->init(baseline, "neutrino 2.0!", 1.0, 1.0, 1.0, 1.0);                 // Initializing message...



  //opencl_context->init(baseline, gui_window->glfw_window, GPU);                 // Initializing OpenCL context...

  //baseline->context_id = opencl_context->context_id;
  //baseline->device_id = opencl_context->existing_device[opencl_context->choosen_device]->device_id;

  // SETUP:
  //q1->init(baseline);

  while (!gui->closed())                                                        // Opening window...
  {
                                                      // Polling GLFW events...
    //baseline->get_tic();                                                        // Getting "tic" [us]...
    gui->print(message);
    glfwPollEvents();           
    //baseline->get_toc();                                                        // Getting "toc" [us]...
  }

  return 0;
}
