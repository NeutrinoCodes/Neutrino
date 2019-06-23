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
                  neutrino* loc_baseline                                        // Neutrino baseline.
                 );

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// SETARG TEMPLATE ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  template <typename T>
  void setarg (
               T       loc_data,                                                // Data object.
               cl_uint loc_layout_index                                         // Layout index.
              )
  {
    glBindAttribLocation (
                          program,
                          loc_layout_index,
                          loc_data->name
                         );                                                     // Binding data...
  };

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// DESTRUCTOR ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~shader ();

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////// SETARG "point" SPECIALIZATION ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  template <>
  void shader::setarg <point*>(
                               point* loc_data,                                 // Data object.
                               GLuint loc_layout_index                          // Layout index.
                              )
  {
    glBindAttribLocation (
                          program,                                              // OpenGL GLSL program.
                          loc_layout_index,                                     // Layout index.
                          loc_data->name                                        // Data name.
                         );                                                     // Binding point data...
  };

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////// SETARG "color" SPECIALIZATION ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  template <>
  void shader::setarg <color*>(
                               color* loc_data,                                 // Data object.
                               GLuint loc_layout_index                          // Layout index.
                              )
  {
    glBindAttribLocation (
                          program,                                              // OpenGL GLSL program.
                          loc_layout_index,                                     // Layout index.
                          loc_data->name                                        // Data name.
                         );                                                     // Binding color data...
  };
#endif
