/// @file

#define SIZE_WINDOW_X 800                                                       // Window x-size [px].
#define SIZE_WINDOW_Y 600                                                       // Window y-size [px].
#define WINDOW_NAME "neutrino"                                                  // Window name.

#include "neutrino.hpp"
#include "opengl.hpp"
#include "window.hpp"
#include "font.hpp"
#include "opencl.hpp"

int main()
{
  neutrino* N               = new neutrino();                                   // The Neutrino object.
  opengl*   opengl_context  = new opengl();                                     // The OpenGL context object.
  window*   gui_window      = new window();                                     // The gui window object.
  font*     gui_font        = new font();                                       // The gui font object.
  opencl*   opencl_context  = new opencl();                                     // The OpenCL context object.

  neutrino->init();                                                             // Initializing neutrino...
  opengl_context->init(N);                                                      // Initializing OpenGL context...
  gui_window->init(N, SIZE_WINDOW_X, SIZE_WINDOW_Y, WINDOW_NAME);               // Initializing gui window...
  gui_font->init();                                                             // Initializing gui font...
  opencl_context->init(gui_window->glfw_window, GPU);                           // Initializing OpenCL context...

  setup();                                                                      // Executing Neutrino "setup" function...

  while (!N->gui_window->closed())                                              // Opening window...
  {
    N->get_tic();                                                               // Getting "tic" [us]...
    loop();                                                                     // Executing Neutrino "loop" function...
    N->get_toc();                                                               // Getting "toc" [us]...
  }

  terminate();                                                                  // Terminating Neutrino application...

  return 0;
}
