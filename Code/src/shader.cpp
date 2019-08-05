#include "shader.hpp"

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// CONSTRUCTOR ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
shader::shader ()
{
  // Doing nothing.
}

/// # OpenGL shader init function
/// ### Description:
/// Initializes an OpenGL shader.
void shader::init (
                   neutrino* loc_baseline,                                      // Neutrino baseline.
                   string    loc_shader_home,                                   // Shader home directory.
                   string    loc_vertex_file_name,                              // Vertex shader file name.
                   string    loc_geometry_file_name,                            // Geometry shader file name.
                   string    loc_fragment_file_name                             // Fragment shader file name.
                  )
{
  shader_home        = loc_shader_home;                                         // Getting shader home directory...

  // Building up vertex file full name:
  vertex_file_name   = shader_home +                                            // Shader home directory.
                       "/" +
                       loc_vertex_file_name;                                    // Vertex shader file name.

  // Building up geometry file full name:
  geometry_file_name = shader_home +                                            // Shader home directory.
                       "/" +
                       loc_geometry_file_name;                                  // Geometry shader file name.

  // Building up fragment file full name:
  fragment_file_name = shader_home +                                            // Shader home directory.
                       "/" +
                       loc_fragment_file_name;                                  // Fragment shader file name.

  vertex             = compile (vertex_file_name, NU_VERTEX);                   // Compiling vertex shader...
  geometry           = compile (geometry_file_name, NU_GEOMETRY);               // Compiling geometry shader...
  fragment           = compile (fragment_file_name, NU_FRAGMENT);               // Compiling fragment shader...
  program            = glCreateProgram ();                                      // Creating program...
}

/// # OpenGL shader compile function
/// ### Description:
/// Compiles an OpenGL shader.
GLuint shader::compile (
                        string      loc_shader_filename,                        // GLSL shader file name.
                        shader_type loc_shader_type                             // GLSL shader type.
                       )
{
  GLuint  shader;                                                               // Shader.
  string  shader_source;                                                        // Shader source.
  size_t  shader_size;                                                          // Shader size [characters].
  GLint   success;                                                              // "GL_COMPILE_STATUS" flag.
  GLchar* log;                                                                  // Buffer for OpenGL error log.
  GLsizei log_size;                                                             // Size of OpenGL error log.
  char    shader_fullname [NU_MAX_PATH_SIZE];                                   // Shader full file name.

  shader_fullname = loc_shader_filename;                                        // Setting shader full file name...
  strncpy (
           shader_fullname,
           loc_shader_filename,
           strlen (loc_shader_filename)
          );

  // Loading shader from file:
  baseline->load_file (
                       loc_shader_filename,                                     // Shader file.
                       &shader_source,                                          // Shader buffer.
                       &shader_size                                             // Shader buffer size.
                      );

  // Selecting shader type:
  switch(loc_shader_type)
  {
    case NU_VERTEX:
      shader = glCreateShader (GL_VERTEX_SHADER);                               // Creating shader...
      break;

    case NU_FRAGMENT:
      shader = glCreateShader (GL_FRAGMENT_SHADER);                             // Creating shader...
      break;

    case NU_GEOMETRY:
      shader = glCreateShader (GL_GEOMETRY_SHADER);                             // Creating shader...
      break;
  }

  // Attaching source code to shader:
  glShaderSource (
                  shader,                                                       // GLSL shader.
                  1,                                                            // # of shaders.
                  (const char**)&shader_source,                                 // Shader source.
                  (GLint*)&shader_size                                          // Shader size.
                 );

  glCompileShader (shader);                                                     // Compiling shader...

  // Reading "GL_COMPILE_STATUS" flag:
  glGetShaderiv (
                 shader,                                                        // GLSL shader.
                 GL_COMPILE_STATUS,                                             // Requested shader parameter.
                 &success                                                       // Success status flag.
                );

  // Checking compiled shader code:
  if(!success)
  {
    glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &log_size);                      // Getting log length...
    log           = (char*) malloc (log_size + 1);                              // Allocating temporary buffer for log...
    log[log_size] = '\0';                                                       // Null-terminating log buffer...
    glGetShaderInfoLog (shader, log_size + 1, NULL, log);                       // Getting log...
    printf ("%s\n", log);                                                       // Printing log...
    free (log);                                                                 // Freeing log...
    exit (1);                                                                   // Exiting...
  }

  baseline->free_file (shader_source);                                          // Freeing shader source file...

  return (shader);                                                              // Returning shader...
}

/// # OpenGL shader init function
/// ### Description:
/// Initializes an OpenGL shader.
void shader::build ()
{
  glAttachShader (program, vertex);                                             // Attaching vertex shader to program...
  glAttachShader (program, geometry);                                           // Attaching geometry shader to program...
  glAttachShader (program, fragment);                                           // Attaching fragment shader to program...
  glLinkProgram (program);                                                      // Linking program...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// SETARG "float1G" overload /////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void shader::setarg (
                     float1G* loc_data,                                         // Data object.
                     GLuint   loc_layout_index                                  // Data layout index.
                    )
{
  glBindAttribLocation (
                        program,                                                // OpenGL GLSL program.
                        loc_layout_index,                                       // Data layout index.
                        loc_data->name                                          // Data name.
                       );

  if(old_size == 0)
  {
    size     = loc_data->size;
    old_size = size;

  }

  else
  {
    size = loc_data->size;
    if(size != old_size)
    {
      baseline->error ("shader argument size mismatch!");
      exit (EXIT_FAILURE);
    }
  }

};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// SETARG "float4G" overload /////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void shader::setarg (
                     float4G* loc_data,                                         // Data object.
                     GLuint   loc_layout_index                                  // Data layout index.
                    )
{
  glBindAttribLocation (
                        program,                                                // OpenGL GLSL program.
                        loc_layout_index,                                       // Data layout index.
                        loc_data->name                                          // Data name.
                       );

  if(old_size == 0)
  {
    size     = loc_data->size;
    old_size = size;

  }

  else
  {
    size = loc_data->size;
    if(size != old_size)
    {
      baseline->error ("shader argument size mismatch!");
      exit (EXIT_FAILURE);
    }
  }

};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// DESTRUCTOR /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
shader::~shader ()
{
  // Doing nothing.
}
