#ifndef shader_hpp
#define shader_hpp

#include "neutrino.hpp"
#include "datatypes.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "SHADER" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class shader
{
private:
  neutrino* baseline;                                                           // Neutrino baseline.
  // OpenGL shader compilation:
  GLuint compile (
                  std::string loc_shader_filename,                              // Shader file name.
                  shader_type loc_shader_type                                   // Shader type.
                 );
  // OpenGL shader build:
  GLuint build (
                std::string loc_vertex_filename,                                // Vertex shader file name.
                std::string loc_geometry_filename,                              // Geometry shader file name.
                std::string loc_fragment_filename                               // Fragment shader file name.
               );

  // Shader argument size: temporary variable for mismatch detection.
  GLsizei     old_size;

public:
  std::string shader_home;                                                      // [NU_MAX_PATH_SIZE]; // Shader home directory.
  std::string vertex_file_name;                                                 // [NU_MAX_PATH_SIZE]; // Vertex source file name.
  std::string geometry_file_name;                                               // [NU_MAX_PATH_SIZE]; // Geometry source file name.
  std::string fragment_file_name;                                               // [NU_MAX_PATH_SIZE]; // Fragment source file name.
  GLuint      vertex;                                                           // Vertex shader id.
  GLuint      geometry;                                                         // Geometry shader id.
  GLuint      fragment;                                                         // Fragment shader id.
  GLuint      program;                                                          // OpenGL program.
  GLsizei     size;                                                             // Shader argument size.

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// CONSTRUCTOR ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  shader ();
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// INIT /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void init (
             neutrino*   loc_baseline,                                          // Neutrino baseline.
             std::string loc_shader_home,                                       // Shader home directory.
             std::string loc_vertex_file_name,                                  // Vertex shader file name.
             std::string loc_geometry_file_name,                                // Geometry shader file name.
             std::string loc_fragment_file_name                                 // Fragment shader file name.
            );
  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// BUILD /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void build ();
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// SETARG "float1G" overload ////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void setarg (
               float1G* loc_data,                                               // Data object.
               GLuint   loc_layout_index                                        // Data layout index.
              );
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
