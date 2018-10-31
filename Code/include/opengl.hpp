/// @file

#ifndef opengl_hpp
#define opengl_hpp

  #include "neutrino.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "OPENGL" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class opengl
  {
    private:
      GLuint        compile_shader();                                                 // OpenGL shader compilation.
      GLuint        build_shader();                                                   // OpenGL shader build.
      path*         neutrino_path;                                                    // Neutrino path.

    public:
                    opengl();

      void          init(path* loc_neutrino_path);                                    // OpenGL initialization.

      GLuint        compile_shader  (
                                      const char* loc_shader_filename,
                                      shader_type loc_shader_type
                                    );

      GLuint        build_shader    (
                                      const char* loc_filename_vertex,
                                      const char* loc_filename_fragment
                                    );


                    ~opengl();
  };

#endif
