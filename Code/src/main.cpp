/// @file

#include "neutrino.hpp"
#include "program.hpp"

int main()
{
  neutrino* theneutrino = new neutrino();                                       // The Neutrino object.

  setup();                                                                      // Executing Neutrino "setup" function...

  while (!theneutrino->thewindow->closed())                                     // Opening window...
  {
    theneutrino->get_tic();                                                     // Getting "tic" [us]...
    loop();                                                                     // Executing Neutrino "loop" function...
    theneutrino->get_toc();                                                     // Getting "toc" [us]...
  }

  terminate();                                                                  // Terminating Neutrino application...

  return 0;
}
