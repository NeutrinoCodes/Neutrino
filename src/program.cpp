#include "program.hpp"

void setup()
{
  //load_vertex("/Users/Erik/.CMVolumes/Erik Zorzin/Erik/SPFGL/SPFGL/Shaders/Squares.vert");                                          // Loading OpenGL vertex shader file...
  //load_fragment("/Users/Erik/.CMVolumes/Erik Zorzin/Erik/SPFGL/SPFGL/Shaders/Squares.frag");                                        // Loading OpenGL fragment shader file...
  //load_kernel("/Users/Erik/.CMVolumes/Erik Zorzin/Erik/SPFGL/SPFGL/Kernels/main_kernel.cl");
  //window("pippo", 800, 600, 100);                                                                                             // Instantiating window...
}

void loop()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void terminate()
{
    //quit();
}
