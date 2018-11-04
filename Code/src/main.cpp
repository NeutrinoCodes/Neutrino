/// @file

#define SIZE_WINDOW_X 800                                                       // Window x-size [px].
#define SIZE_WINDOW_Y 600                                                       // Window y-size [px].
#define WINDOW_NAME "neutrino"                                                  // Window name.

#include "neutrino.hpp"
#include "opengl.hpp"
#include "window.hpp"
#include "font.hpp"
#include "opencl.hpp"
#include "queue.hpp"
#include "kernel.hpp"

int main()
{
  neutrino* baseline        = new neutrino();                                   // The Neutrino object.
  opengl*   opengl_context  = new opengl();                                     // The OpenGL context object.
  window*   gui_window      = new window();                                     // The gui window object.
  font*     gui_font        = new font();                                       // The gui font object.
  opencl*   opencl_context  = new opencl();                                     // The OpenCL context object.

  queue*    q1              = new queue();                                      // OpenCL queue.
  kernel*   k1              = new kernel();                                     // OpenCL kernel.
  kernel*   k2              = new kernel();                                     // OpenCL kernel.

  baseline->init();                                                             // Initializing neutrino...
  opengl_context->init(baseline);                                               // Initializing OpenGL context...
  gui_window->init(SIZE_WINDOW_X, SIZE_WINDOW_Y, WINDOW_NAME);                  // Initializing gui window...
  gui_font->init();                                                             // Initializing gui font...
  opencl_context->init(baseline, gui_window->glfw_window, GPU);                 // Initializing OpenCL context...

  baseline->context_id = opencl_context->context_id;
  baseline->device_id = opencl_context->existing_device[opencl_context->choosen_device]->device_id;

  // SETUP:
  q1->init(baseline);

  while (!gui_window->closed())                                                 // Opening window...
  {
    baseline->get_tic();                                                        // Getting "tic" [us]...
    loop();                                                                     // Executing Neutrino "loop" function...
    baseline->get_toc();                                                        // Getting "toc" [us]...
  }

  terminate();                                                                  // Terminating Neutrino application...

  return 0;
}
