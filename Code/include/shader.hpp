/// @file     shader.hpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Declaration of an OpenGL "shader" class.
///
/// @details  This class has got methods for initializing and build an OpenGL shader of
/// [vertex](https://www.khronos.org/opengl/wiki/Vertex_Shader),
/// [geometry](https://www.khronos.org/opengl/wiki/Geometry_Shader) or
/// [fragment](https://www.khronos.org/opengl/wiki/Fragment_Shader)
/// type for graphics rendition of OpenCL data. The @link setarg @endlink methods of this class
/// is used to tell Neutrino which arguments are presents in the source file of each shader of
/// interest.

#ifndef shader_hpp
#define shader_hpp

#include "neutrino.hpp"
#include "data_classes.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// "shader" class ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class shader
/// ### OpenCL shader class.
/// Declares an OpenCL shader class. To be used in order to do graphics rendition of OpenCL data.
class shader : public neutrino                                                                      /// @brief **OpenGL shader.**
{
private:

  /// @brief    **OpenGL shader compilation.**
  /// @details  It compiles an OpenGL shader.
  GLuint compile (
                  std::string loc_shader_filename,                                                  ///< Shader file name.
                  shader_type loc_shader_type                                                       ///< Shader type.
                 );

public:
  GLuint     program;                                                                               ///< @brief **OpenGL program.**
  GLsizeiptr size;                                                                                  ///< @brief **OpenGL shader argument size.**

  /// @brief **Class constructor.**
  /// @details It does nothing.
  shader ();

  /// @brief **Class initializer.**
  /// @details It compiles the OpenGL vertex, geometry and fragment shader into an OpenGL program.
  void init ();

  /// @brief **Shader source adder function.**
  /// @details Loads an OpenGL shader source from its corresponding source file.
  void addsource (
                  std::string loc_shader_filename,                                                  ///< GLSL shader file name.
                  shader_type loc_shader_type                                                       ///< GLSL shader type.
                 );

  /// @brief    **OpenGL shader builder.**
  /// @details  It builds an OpenGL shader.
  void build ();

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////// setarg "functions" //////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @brief **OpenGL shader argument setter function.**
  /// @details Sets an argument in the OpenGL shader.
  void setarg (
               nu_int* loc_data,                                                                    ///< Data object.
               GLuint  loc_layout_index                                                             ///< Data layout index.
              );

  /// @overload setarg(nu_int2* loc_data, GLuint loc_layout_index)
  /// @details Sets an argument in the OpenGL shader.
  void setarg (
               nu_int2* loc_data,                                                                   ///< Data object.
               GLuint   loc_layout_index                                                            ///< Data layout index.
              );

  /// @overload setarg(nu_int3* loc_data, GLuint loc_layout_index)
  /// @details Sets an argument in the OpenGL shader.
  void setarg (
               nu_int3* loc_data,                                                                   ///< Data object.
               GLuint   loc_layout_index                                                            ///< Data layout index.
              );

  /// @overload setarg(nu_int4* loc_data, GLuint loc_layout_index)
  /// @details Sets an argument in the OpenGL shader.
  void setarg (
               nu_int4* loc_data,                                                                   ///< Data object.
               GLuint   loc_layout_index                                                            ///< Data layout index.
              );

  /// @overload setarg(nu_float* loc_data, GLuint loc_layout_index)
  /// @details Sets an argument in the OpenGL shader.
  void setarg (
               nu_float* loc_data,                                                                  ///< Data object.
               GLuint    loc_layout_index                                                           ///< Data layout index.
              );

  /// @overload setarg(nu_float2* loc_data, GLuint loc_layout_index)
  /// @details Sets an argument in the OpenGL shader.
  void setarg (
               nu_float2* loc_data,                                                                 ///< Data object.
               GLuint     loc_layout_index                                                          ///< Data layout index.
              );

  /// @overload setarg(nu_float3* loc_data, GLuint loc_layout_index)
  /// @details Sets an argument in the OpenGL shader.
  void setarg (
               nu_float3* loc_data,                                                                 ///< Data object.
               GLuint     loc_layout_index                                                          ///< Data layout index.
              );

  /// @overload setarg(nu_float4* loc_data, GLuint loc_layout_index)
  /// @details Sets an argument in the OpenGL shader.
  void setarg (
               nu_float4* loc_data,                                                                 ///< Data object.
               GLuint     loc_layout_index                                                          ///< Data layout index.
              );

  /// @brief **Class destructor.**
  /// @details It does nothing.
  ~shader ();
};

#endif
