/// @file     shader.cpp
/// @author   Erik ZORZIN
/// @date     24OCT2019
/// @brief    Definition of an OpenCL "shader" class.

#include "shader.hpp"

nu::shader::shader ()
{
  neutrino::action ("initializing OpenGL shader object...");                                        // Printing message...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  program = glCreateProgram ();                                                                     // Creating program...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  neutrino::done ();                                                                                // Printing message...
}

void nu::shader::addsource
(
 std::string     loc_shader_filename,                                                               // GLSL shader file name.
 nu::shader_type loc_shader_type                                                                    // GLSL shader type.
)
{
  GLuint      loc_shader;                                                                           // Shader.
  std::string loc_shader_source;                                                                    // Shader source.
  GLchar**    loc_shader_source_c;                                                                  // Shader source, C style string.
  GLint*      loc_shader_source_c_size;                                                             // Shader source size.
  GLint       loc_success;                                                                          // "GL_COMPILE_STATUS" flag.
  GLchar*     loc_log;                                                                              // Buffer for OpenGL error log.
  GLsizei     loc_log_size;                                                                         // Size of OpenGL error log.

  neutrino::action ("loading OpenGL shader source from file...");                                   // Printing message...

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  // Loading shader from file:
  loc_shader_source           = neutrino::read_file (
                                                     loc_shader_filename                            // Shader file.
                                                    );
  loc_shader_source_c         = new char*[1]();                                                     // Building temporary shader source char buffer...
  loc_shader_source_c[0]      = new char[loc_shader_source.size ()]();                              // Building temporary source char buffer...
  loc_shader_source.copy (loc_shader_source_c[0], loc_shader_source.size ());                       // Building string source buffer...
  loc_shader_source_c_size    = new GLint[1]();                                                     // Building shader source size array...
  loc_shader_source_c_size[0] = (GLint)loc_shader_source.size ();                                   // Setting shader source size...

  // Selecting shader type:
  switch(loc_shader_type)
  {
    case VERTEX:
      loc_shader = glCreateShader (GL_VERTEX_SHADER);                                               // Creating shader...
      break;

    case FRAGMENT:
      loc_shader = glCreateShader (GL_FRAGMENT_SHADER);                                             // Creating shader...
      break;

    case GEOMETRY:
      loc_shader = glCreateShader (GL_GEOMETRY_SHADER);                                             // Creating shader...
      break;
  }

  neutrino::done ();                                                                                // Printing message...

  neutrino::action ("attaching OpenGL shader source to shader object...");                          // Printing message...

  // Attaching source code to shader:
  glShaderSource
  (
   loc_shader,                                                                                      // GLSL shader.
   1,                                                                                               // Number of shaders.
   (const GLchar**)loc_shader_source_c,                                                             // Shader source.
   loc_shader_source_c_size                                                                         // Shader size: NULL = null-terminated string.
  );

  neutrino::done ();                                                                                // Printing message...

  delete[] loc_shader_source_c;                                                                     // Deleting buffer...
  delete[] loc_shader_source_c_size;                                                                // Deleting buffer size array...

  neutrino::action ("compiling OpenGL shader...");                                                  // Printing message...
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

  neutrino::done ();                                                                                // Printing message...

  neutrino::action ("attaching OpenGL shader to OpenGL program...");                                // Printing message...
  glAttachShader (program, loc_shader);                                                             // Attaching shader to program...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  neutrino::done ();                                                                                // Printing message...
}

void nu::shader::build (
                        size_t loc_points                                                           // Number of points to be rendered...
                       )
{
  GLuint i;                                                                                         // Index.

  neutrino::action ("linking OpenGL shader sources...");                                            // Printing message...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  glLinkProgram (program);                                                                          // Linking program...
  glFinish ();                                                                                      // Waiting for OpenGL to finish...
  neutrino::done ();                                                                                // Printing message...

  size = (GLsizei)loc_points;                                                                       // Setting shader size...

  // Setting shader arguments:
  neutrino::action ("setting OpenGL shader arguments...");                                          // Printing message...

  for(i = 0; i < neutrino::container.size (); i++)
  {
    switch(container[i]->type)
    {
      case NU_INT:
        ((nu::int1*)neutrino::container[i])->name   = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::int1*)neutrino::container[i], i);
        break;

      case NU_INT2:
        ((nu::int2*)neutrino::container[i])->name   = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::int2*)neutrino::container[i], i);
        break;

      case NU_INT3:
        ((nu::int3*)neutrino::container[i])->name   = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::int3*)neutrino::container[i], i);
        break;

      case NU_INT4:
        ((nu::int4*)neutrino::container[i])->name   = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::int4*)neutrino::container[i], i);
        break;

      case NU_FLOAT:
        ((nu::float1*)neutrino::container[i])->name = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::float1*)neutrino::container[i], i);
        break;

      case NU_FLOAT2:
        ((nu::float2*)neutrino::container[i])->name = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::float2*)neutrino::container[i], i);
        break;

      case NU_FLOAT3:
        ((nu::float3*)neutrino::container[i])->name = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::float3*)neutrino::container[i], i);
        break;

      case NU_FLOAT4:
        ((nu::float4*)neutrino::container[i])->name = std::string ("arg_") + std::to_string (i);
        this->setarg ((nu::float4*)neutrino::container[i], i);
        break;
    }
  }

  neutrino::done ();                                                                                // Printing message...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// setarg "functions" //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void nu::shader::setarg
(
 nu::int1* loc_data,                                                                                // Data object.
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

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void nu::shader::setarg
(
 nu::int2* loc_data,                                                                                // Data object.
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

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void nu::shader::setarg
(
 nu::int3* loc_data,                                                                                // Data object.
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

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void nu::shader::setarg
(
 nu::int4* loc_data,                                                                                // Data object.
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

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void nu::shader::setarg
(
 nu::float1* loc_data,                                                                              // Data object.
 GLuint      loc_layout_index                                                                       // Data layout index.
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

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void nu::shader::setarg
(
 nu::float2* loc_data,                                                                              // Data object.
 GLuint      loc_layout_index                                                                       // Data layout index.
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

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void nu::shader::setarg
(
 nu::float3* loc_data,                                                                              // Data object.
 GLuint      loc_layout_index                                                                       // Data layout index.
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

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void nu::shader::setarg
(
 nu::float4* loc_data,                                                                              // Data object.
 GLuint      loc_layout_index                                                                       // Data layout index.
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

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

void nu::shader::setarg
(
 nu::float16* loc_data,                                                                             // Data object.
 GLuint       loc_layout_index                                                                      // Data layout index.
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

  glFinish ();                                                                                      // Waiting for OpenGL to finish...

  delete loc_name_buffer;
};

nu::shader::~shader ()
{
  // Doing nothing.
}
