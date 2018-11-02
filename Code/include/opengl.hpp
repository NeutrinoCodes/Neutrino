/// @file

#ifndef opengl_hpp
#define opengl_hpp

  /// These files are relative to the NEUTRINO_PATH environmental variable:
  #define POINT_VERTEX_FILE       "/Code/shader/vertex.vert"
  #define POINT_FRAGMENT_FILE     "/Code/shader/fragment.frag"
  #define TEXT_VERTEX_FILE        "/Code/shader/text_vertex.vert"
  #define TEXT_FRAGMENT_FILE      "/Code/shader/text_fragment.frag"

  typedef enum
  {
    STYLE_POINT,
    STYLE_WIREFRAME,
    STYLE_SHADED
  } plot_style;

  typedef enum
  {
    VERTEX,
    FRAGMENT
  } shader_type;

  #include "neutrino.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "OPENGL" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class opengl
  {
    private:
      GLuint        compile_shader();                                           // OpenGL shader compilation.
      GLuint        build_shader();                                             // OpenGL shader build.
      path*         neutrino_path;                                              // Neutrino path.

    public:
                    opengl();

      void          init(neutrino* loc_neutrino);                               // OpenGL initialization.

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
