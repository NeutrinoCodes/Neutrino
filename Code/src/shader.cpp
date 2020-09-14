/// @file     shader.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definition of an OpenCL "shader" class.

#include "shader.hpp"

shader::shader ()
{
  // Doing nothing.
}

void shader::init
(
 neutrino*   loc_baseline,                                                                          // Neutrino baseline.
 std::string loc_shader_home,                                                                       // Shader home directory.
 std::string loc_vertex_file_name,                                                                  // Vertex shader file name.
 std::string loc_geometry_file_name,                                                                // Geometry shader file name.
 std::string loc_fragment_file_name                                                                 // Fragment shader file name.
)
{
  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  shader_home        = loc_shader_home;                                                             // Getting shader home directory...

  // Building up vertex file full name:
  vertex_file_name   = shader_home +                                                                // Shader home directory.
                       std::string ("/") +
                       loc_vertex_file_name;                                                        // Vertex shader file name.

  // Building up geometry file full name:
  geometry_file_name = shader_home +                                                                // Shader home directory.
                       std::string ("/") +
                       loc_geometry_file_name;                                                      // Geometry shader file name.

  // Building up fragment file full name:
  fragment_file_name = shader_home +                                                                // Shader home directory.
                       std::string ("/") +
                       loc_fragment_file_name;                                                      // Fragment shader file name.

  vertex             = compile (vertex_file_name, NU_VERTEX);                                       // Compiling vertex shader...
  geometry           = compile (geometry_file_name, NU_GEOMETRY);                                   // Compiling geometry shader...
  fragment           = compile (fragment_file_name, NU_FRAGMENT);                                   // Compiling fragment shader...
  program            = glCreateProgram ();                                                          // Creating program...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
}

GLuint shader::compile
(
 std::string loc_shader_filename,                                                                   // GLSL shader file name.
 shader_type loc_shader_type                                                                        // GLSL shader type.
)
{
  GLuint        loc_shader;                                                                         // Shader.
  std::string   loc_shader_source;                                                                  // Shader source.
  GLchar const* loc_shader_source_c;                                                                // Shader source, C style string.
  GLint         loc_success;                                                                        // "GL_COMPILE_STATUS" flag.
  GLchar*       loc_log;                                                                            // Buffer for OpenGL error log.
  GLsizei       loc_log_size;                                                                       // Size of OpenGL error log.

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Loading shader from file:
  loc_shader_source   = baseline->read_file (
                                             loc_shader_filename                                    // Shader file.
                                            );

  loc_shader_source_c = loc_shader_source.c_str ();                                                 // Converting C++ string to C string...

  // Selecting shader type:
  switch(loc_shader_type)
  {
    case NU_VERTEX:
      vertex_source   = loc_shader_source;
      loc_shader      = glCreateShader (GL_VERTEX_SHADER);                                          // Creating shader...
      break;

    case NU_FRAGMENT:
      fragment_source = loc_shader_source;
      loc_shader      = glCreateShader (GL_FRAGMENT_SHADER);                                        // Creating shader...
      break;

    case NU_GEOMETRY:
      geometry_source = loc_shader_source;
      loc_shader      = glCreateShader (GL_GEOMETRY_SHADER);                                        // Creating shader...
      break;
  }

  // Attaching source code to shader:
  glShaderSource
  (
   loc_shader,                                                                                      // GLSL shader.
   1,                                                                                               // Number of shaders.
   &loc_shader_source_c,                                                                            // Shader source.
   NULL                                                                                             // Shader size: NULL = null-terminated string.
  );

  glCompileShader (loc_shader);                                                                     // Compiling shader...

  // Reading "GL_COMPILE_STATUS" flag:
  glGetShaderiv
  (
   loc_shader,                                                                                      // GLSL shader.
   GL_COMPILE_STATUS,                                                                               // Requested shader parameter.
   &loc_success                                                                                     // Success status flag.
  );

  // Checking compiled shader code:
  if(!loc_success)
  {
    glGetShaderiv (loc_shader, GL_INFO_LOG_LENGTH, &loc_log_size);                                  // Getting log length...
    loc_log = (char*) calloc (loc_log_size + 1, sizeof(GLchar));                                    // Allocating temporary buffer for log...
    glGetShaderInfoLog (loc_shader, loc_log_size + 1, NULL, loc_log);                               // Getting log...
    std::string loc_log_string (loc_log);
    std::cout << loc_log_string << std::endl;                                                       // Printing log...
    free (loc_log);                                                                                 // Freeing log...
    exit (1);                                                                                       // Exiting...
  }

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  return (loc_shader);                                                                              // Returning shader...
}

void shader::build ()
{
  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  glAttachShader (program, vertex);                                                                 // Attaching vertex shader to program...
  glAttachShader (program, geometry);                                                               // Attaching geometry shader to program...
  glAttachShader (program, fragment);                                                               // Attaching fragment shader to program...
  glLinkProgram (program);                                                                          // Linking program...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// setarg "functions" //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void shader::setarg
(
 nu_int* loc_data,                                                                                  // Data object.
 GLuint  loc_layout_index                                                                           // Data layout index.
)
{
  size_t loc_name_size;
  char*  loc_name_buffer;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  loc_name_size                  = loc_data->name.size ();                                          // Getting source size...
  loc_name_buffer                = new char[loc_name_size + 1]();
  loc_data->name.copy (loc_name_buffer, loc_name_size);
  loc_name_buffer[loc_name_size] = '\0';

  glBindAttribLocation (
                        program,                                                                    // OpenGL GLSL program.
                        loc_layout_index,                                                           // Data layout index.
                        loc_name_buffer                                                             // Data name.
                       );

  size                           = loc_data->size;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void shader::setarg
(
 nu_int2* loc_data,                                                                                 // Data object.
 GLuint   loc_layout_index                                                                          // Data layout index.
)
{
  size_t loc_name_size;
  char*  loc_name_buffer;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  loc_name_size                  = loc_data->name.size ();                                          // Getting source size...
  loc_name_buffer                = new char[loc_name_size + 1]();
  loc_data->name.copy (loc_name_buffer, loc_name_size);
  loc_name_buffer[loc_name_size] = '\0';

  glBindAttribLocation (
                        program,                                                                    // OpenGL GLSL program.
                        loc_layout_index,                                                           // Data layout index.
                        loc_name_buffer                                                             // Data name.
                       );

  size                           = loc_data->size;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void shader::setarg
(
 nu_int3* loc_data,                                                                                 // Data object.
 GLuint   loc_layout_index                                                                          // Data layout index.
)
{
  size_t loc_name_size;
  char*  loc_name_buffer;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  loc_name_size                  = loc_data->name.size ();                                          // Getting source size...
  loc_name_buffer                = new char[loc_name_size + 1]();
  loc_data->name.copy (loc_name_buffer, loc_name_size);
  loc_name_buffer[loc_name_size] = '\0';

  glBindAttribLocation (
                        program,                                                                    // OpenGL GLSL program.
                        loc_layout_index,                                                           // Data layout index.
                        loc_name_buffer                                                             // Data name.
                       );

  size                           = loc_data->size;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void shader::setarg
(
 nu_int4* loc_data,                                                                                 // Data object.
 GLuint   loc_layout_index                                                                          // Data layout index.
)
{
  size_t loc_name_size;
  char*  loc_name_buffer;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  loc_name_size                  = loc_data->name.size ();                                          // Getting source size...
  loc_name_buffer                = new char[loc_name_size + 1]();
  loc_data->name.copy (loc_name_buffer, loc_name_size);
  loc_name_buffer[loc_name_size] = '\0';

  glBindAttribLocation (
                        program,                                                                    // OpenGL GLSL program.
                        loc_layout_index,                                                           // Data layout index.
                        loc_name_buffer                                                             // Data name.
                       );

  size                           = loc_data->size;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void shader::setarg
(
 nu_float* loc_data,                                                                                // Data object.
 GLuint    loc_layout_index                                                                         // Data layout index.
)
{
  size_t loc_name_size;
  char*  loc_name_buffer;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  loc_name_size                  = loc_data->name.size ();                                          // Getting source size...
  loc_name_buffer                = new char[loc_name_size + 1]();
  loc_data->name.copy (loc_name_buffer, loc_name_size);
  loc_name_buffer[loc_name_size] = '\0';

  glBindAttribLocation (
                        program,                                                                    // OpenGL GLSL program.
                        loc_layout_index,                                                           // Data layout index.
                        loc_name_buffer                                                             // Data name.
                       );

  size                           = loc_data->size;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void shader::setarg
(
 nu_float2* loc_data,                                                                               // Data object.
 GLuint     loc_layout_index                                                                        // Data layout index.
)
{
  size_t loc_name_size;
  char*  loc_name_buffer;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  loc_name_size                  = loc_data->name.size ();                                          // Getting source size...
  loc_name_buffer                = new char[loc_name_size + 1]();
  loc_data->name.copy (loc_name_buffer, loc_name_size);
  loc_name_buffer[loc_name_size] = '\0';

  glBindAttribLocation (
                        program,                                                                    // OpenGL GLSL program.
                        loc_layout_index,                                                           // Data layout index.
                        loc_name_buffer                                                             // Data name.
                       );

  size                           = loc_data->size;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void shader::setarg
(
 nu_float3* loc_data,                                                                               // Data object.
 GLuint     loc_layout_index                                                                        // Data layout index.
)
{
  size_t loc_name_size;
  char*  loc_name_buffer;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  loc_name_size                  = loc_data->name.size ();                                          // Getting source size...
  loc_name_buffer                = new char[loc_name_size + 1]();
  loc_data->name.copy (loc_name_buffer, loc_name_size);
  loc_name_buffer[loc_name_size] = '\0';

  glBindAttribLocation (
                        program,                                                                    // OpenGL GLSL program.
                        loc_layout_index,                                                           // Data layout index.
                        loc_name_buffer                                                             // Data name.
                       );

  size                           = loc_data->size;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void shader::setarg
(
 nu_float4* loc_data,                                                                               // Data object.
 GLuint     loc_layout_index                                                                        // Data layout index.
)
{
  size_t loc_name_size;
  char*  loc_name_buffer;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  loc_name_size                  = loc_data->name.size ();                                          // Getting source size...
  loc_name_buffer                = new char[loc_name_size + 1]();
  loc_data->name.copy (loc_name_buffer, loc_name_size);
  loc_name_buffer[loc_name_size] = '\0';

  glBindAttribLocation (
                        program,                                                                    // OpenGL GLSL program.
                        loc_layout_index,                                                           // Data layout index.
                        loc_name_buffer                                                             // Data name.
                       );

  size                           = loc_data->size;

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

shader::~shader ()
{
  // Doing nothing.
}
