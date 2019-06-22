#ifndef shader_hpp
#define shader_hpp

#include "neutrino.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "SHADER" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class shader
{
private:
  neutrino* baseline;                                                           // Neutrino baseline.
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// PRIVATE METHODS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  // OpenGL shader compilation:
  GLuint    compile (
                     const char* loc_shader_filename,                           // Shader file name.
                     shader_type loc_shader_type                                // Shader type.
                    );
  // OpenGL shader build:
  GLuint    build (
                   const char* loc_vertex_filename,                             // Vertex shader file name.
                   const char* loc_geometry_filename,                           // Geometry shader file name.
                   const char* loc_fragment_filename                            // Fragment shader file name.
                  );


public:



  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// CONSTRUCTOR ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  shader ();

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// INIT /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  template <typename T, typename ... Args>
  GLuint init (
               const char* loc_vertex_filename,                                 // Vertex shader file name.
               const char* loc_geometry_filename,                               // Geometry shader file name.
               const char* loc_fragment_filename,                               // Fragment shader file name.
               const char* loc_var_name,                                        // Vertex shader 1st input variable name.
               Args...     args                                                 // Vertex shader extra input variable names.
              )
  {
    GLuint vertex;                                                              // Vertex shader.
    GLuint geometry;                                                            // Geometry shader.
    GLuint fragment;                                                            // Fragment shader.
    GLuint program;                                                             // Shader program.
    size_t i = 0;                                                               // Argument counter;

    if(i == 0)
    {
      vertex   = compile_shader (loc_vertex_filename, VERTEX);                  // Compiling vertex shader...
      geometry = compile_shader (loc_geometry_filename, GEOMETRY);              // Compiling geometry shader...
      fragment = compile_shader (loc_fragment_filename, FRAGMENT);              // Compiling fragment shader...

      program  = glCreateProgram ();                                            // Creating program...

      glAttachShader (program, vertex);                                         // Attaching vertex shader to program...
      glAttachShader (program, geometry);                                       // Attaching geometry shader to program...
      glAttachShader (program, fragment);                                       // Attaching fragment shader to program...

      glLinkProgram (program);                                                  // Linking program...

      return (program);                                                         // Returning shader program...
    }

    i++;

    glBindAttribLocation (program, 0, loc_var_name);                            // Binding point...
    init (args ...);

    if( i == sizeof...(args))
    {
      glAttachShader (program, vertex);                                         // Attaching vertex shader to program...
      glAttachShader (program, geometry);                                       // Attaching geometry shader to program...
      glAttachShader (program, fragment);                                       // Attaching fragment shader to program...
      glLinkProgram (program);                                                  // Linking program...

      return (program);                                                         // Returning shader program...
    }
  };

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DESTRUCTOR ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
  ~shader ();
#endif
