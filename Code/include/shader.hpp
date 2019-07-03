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
  GLuint compile (
                  const char* loc_shader_filename,                              // Shader file name.
                  shader_type loc_shader_type                                   // Shader type.
                 );
  // OpenGL shader build:
  GLuint build (
                const char* loc_vertex_filename,                                // Vertex shader file name.
                const char* loc_geometry_filename,                              // Geometry shader file name.
                const char* loc_fragment_filename                               // Fragment shader file name.
               );

  // Shader argument size: temporary variable for mismatch detection.
  GLsizei    old_size;

public:
  const char vertex_file_name[MAX_PATH_SIZE];                                   // Vertex source file name.
  const char geometry_file_name[MAX_PATH_SIZE];                                 // Geometry source file name.
  const char fragment_file_name[MAX_PATH_SIZE];                                 // Fragment source file name.
  GLuint     vertex;                                                            // Vertex shader id.
  GLuint     geometry;                                                          // Geometry shader id.
  GLuint     fragment;                                                          // Fragment shader id.
  GLuint     program;                                                           // OpenGL program.
  GLsizei    size;                                                              // Shader argument size.

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// CONSTRUCTOR ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  shader ();
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// INIT /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void init (
             neutrino*   loc_baseline,                                          // Neutrino baseline.
             const char* loc_vertex_filename,                                   // Vertex shader file name.
             const char* loc_geometry_filename,                                 // Geometry shader file name.
             const char* loc_fragment_filename                                  // Fragment shader file name.
            );
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// BUILD /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void build ();
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// SETARG "point" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void setarg (
               point* loc_data,                                                 // Data object.
               GLuint loc_layout_index                                          // Data layout index.
              );
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// SETARG "color" overload //////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void setarg (
               color* loc_data,                                                 // Data object.
               GLuint loc_layout_index                                          // Data layout index.
              );

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// DESTRUCTOR ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~shader ();
};

#endif
