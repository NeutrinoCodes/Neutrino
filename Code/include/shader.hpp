#ifndef shader_hpp
#define shader_hpp

#include "neutrino.hpp"
#include "host_datatypes.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "SHADER" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class shader
{
private:
  neutrino* baseline;                                                           // Neutrino baseline.

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
  GLuint    vertex;                                                             // Vertex shader id.
  GLuint    geometry;                                                           // Geometry shader id.
  GLuint    fragment;                                                           // Fragment shader id.
  GLuint    program;                                                            // OpenGL program.

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// CONSTRUCTOR ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  shader ();

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// INIT /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void      init (
                  neutrino* loc_baseline,                                       // Neutrino baseline.
                  const char* loc_vertex_filename,                              // Vertex shader file name.
                  const char* loc_geometry_filename,                            // Geometry shader file name.
                  const char* loc_fragment_filename                             // Fragment shader file name.
                 );

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// BUILD /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void      build ();

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// SETARG "point" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void      setarg (
                    point* loc_data,                                            // Data object.
                    GLuint loc_layout_index                                     // Data layout index.
                   );

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// SETARG "color" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void      setarg (
                    color* loc_data,                                            // Data object.
                    GLuint loc_layout_index                                     // Data layout index.
                   );

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// DESTRUCTOR ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~shader ();



#endif
