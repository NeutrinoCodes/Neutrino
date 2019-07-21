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
  GLsizei old_size;

public:
  char    shader_home[NU_MAX_PATH_SIZE];                                        // Shader home directory.
  char    vertex_file_name[NU_MAX_PATH_SIZE];                                   // Vertex source file name.
  char    geometry_file_name[NU_MAX_PATH_SIZE];                                 // Geometry source file name.
  char    fragment_file_name[NU_MAX_PATH_SIZE];                                 // Fragment source file name.
  GLuint  vertex;                                                               // Vertex shader id.
  GLuint  geometry;                                                             // Geometry shader id.
  GLuint  fragment;                                                             // Fragment shader id.
  GLuint  program;                                                              // OpenGL program.
  GLsizei size;                                                                 // Shader argument size.

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// CONSTRUCTOR ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  shader ();
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// INIT /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void init (
             neutrino*   loc_baseline,                                          // Neutrino baseline.
             const char* loc_shader_home,                                       // Shader home directory.
             const char* loc_vertex_file_name,                                  // Vertex shader file name.
             const char* loc_geometry_file_name,                                // Geometry shader file name.
             const char* loc_fragment_file_name                                 // Fragment shader file name.
            );
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// BUILD /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void build ();
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// SETARG "float4G" overload ////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void setarg (
               float4G* loc_data,                                               // Data object.
               GLuint   loc_layout_index                                        // Data layout index.
              );
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// DESTRUCTOR ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~shader ();
};

#endif
