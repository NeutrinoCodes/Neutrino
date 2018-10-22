/// @file

#include "opengl.hpp"
#include "opencl.hpp"
#include "utilities.hpp"
#include "program.hpp"

int main()
{
  neutrino* theneutrino = new neutrino();                                       // The Neutrino object.

  setup();                                                                      // Executing Neutrino "setup" function...

  while (!glfwWindowShouldClose(window))                                        // Opening window...
  {
    theneutrino->get_tic();                                                     // Getting "tic" [us]...
    loop();                                                                     // Executing Neutrino "loop" function...
    theneutrino->get_toc();                                                     // Getting "toc" [us]...
  }

  terminate();                                                                  // Terminating Neutrino application...

  return 0;
}
