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
 neutrino* loc_baseline                                                                             // Neutrino baseline.
)
{
  baseline = loc_baseline;                                                                          // Getting Neutrino baseline...
  baseline->action ("initializing OpenGL shader object...");                                        // Printing message...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  program  = glCreateProgram ();                                                                    // Creating program...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  baseline->done ();                                                                                // Printing message...
}

void shader::addsource
(
 std::string loc_shader_filename,                                                                   // GLSL shader file name.
 shader_type loc_shader_type                                                                        // GLSL shader type.
)
{
  GLuint      loc_shader;                                                                           // Shader.
  std::string loc_shader_source;                                                                    // Shader source.
  GLchar**    loc_shader_source_c;                                                                  // Shader source, C style string.
  GLint*      loc_shader_source_c_size;                                                             // Shader source size.
  GLint       loc_success;                                                                          // "GL_COMPILE_STATUS" flag.
  GLchar*     loc_log;                                                                              // Buffer for OpenGL error log.
  GLsizei     loc_log_size;                                                                         // Size of OpenGL error log.

  baseline->action ("loading OpenGL shader source from file...");                                   // Printing message...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Loading shader from file:
  loc_shader_source           = baseline->read_file (
                                                     loc_shader_filename                            // Shader file.
                                                    );
  loc_shader_source_c         = new char*[1]();                                                     // Building temporary shader source char buffer...
  loc_shader_source_c[0]      = new char[loc_shader_source.size ()]();                              // Building temporary source char buffer...
  loc_shader_source.copy (loc_shader_source_c[0], loc_shader_source.size ());                       // Building string source buffer...
  loc_shader_source_c_size    = new GLint[1]();                                                     // Building shader source size array...
  loc_shader_source_c_size[0] = loc_shader_source.size ();                                          // Setting shader source size...

  // Selecting shader type:
  switch(loc_shader_type)
  {
    case NU_VERTEX:
      loc_shader = glCreateShader (GL_VERTEX_SHADER);                                               // Creating shader...
      break;

    case NU_FRAGMENT:
      loc_shader = glCreateShader (GL_FRAGMENT_SHADER);                                             // Creating shader...
      break;

    case NU_GEOMETRY:
      loc_shader = glCreateShader (GL_GEOMETRY_SHADER);                                             // Creating shader...
      break;
  }

  baseline->done ();                                                                                // Printing message...

  baseline->action ("attaching OpenGL shader source to shader object...");                          // Printing message...

  // Attaching source code to shader:
  glShaderSource
  (
   loc_shader,                                                                                      // GLSL shader.
   1,                                                                                               // Number of shaders.
   (const GLchar**)loc_shader_source_c,                                                             // Shader source.
   loc_shader_source_c_size                                                                         // Shader size: NULL = null-terminated string.
  );

  baseline->done ();                                                                                // Printing message...

  delete[] loc_shader_source_c;                                                                     // Deleting buffer...
  delete[] loc_shader_source_c_size;                                                                // Deleting buffer size array...

  baseline->action ("compiling OpenGL shader...");                                                  // Printing message...
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

  baseline->done ();                                                                                // Printing message...

  baseline->action ("attaching OpenGL shader to OpenGL program...");                                // Printing message...
  glAttachShader (program, loc_shader);                                                             // Attaching shader to program...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  baseline->done ();                                                                                // Printing message...
}

void shader::build ()
{
  baseline->action ("linking OpenGL shader sources...");                                            // Printing message...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  glLinkProgram (program);                                                                          // Linking program...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  baseline->done ();                                                                                // Printing message...
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

  size                           = loc_data->data.size ();

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

  size                           = loc_data->data.size ();

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

  size                           = loc_data->data.size ();

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

  size                           = loc_data->data.size ();

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

  size                           = loc_data->data.size ();

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

  size                           = loc_data->data.size ();

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

  size                           = loc_data->data.size ();

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

  size                           = loc_data->data.size ();

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

shader::~shader ()
{
  // Doing nothing.
}
