#ifndef neutrino_hpp
#define neutrino_hpp

  #include "opengl.hpp"
  #include "opencl.hpp"
  #include "data_types.hpp"
  #include "utilities.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// "NEUTRINO" CLASS //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class neutrino
  {
    private:

    public:
      char*       neutrino_path;
      opengl      theopengl;                                                    // The OpenGL object.
      opencl      theopencl;                                                    // The OpenCL object.

      neutrino();
      ~neutrino();
  };

#endif
