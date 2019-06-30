#include "shader.hpp"

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// CONSTRUCTOR ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
shader::shader ()
{
  // Doing nothing.
}

/// # OpenGL shader compile function
/// ### Description:
/// Compiles an OpenGL shader.
GLuint shader::compile (
                        const char* loc_shader_filename,                        // GLSL shader file name.
                        shader_type loc_shader_type                             // GLSL shader type.
                       )
{
  GLuint  shader;                                                               // Shader.
  char*   shader_source;                                                        // Shader source.
  size_t  shader_size;                                                          // Shader size [characters].
  GLint   success;                                                              // "GL_COMPILE_STATUS" flag.
  GLchar* log;                                                                  // Buffer for OpenGL error log.
  GLsizei log_size;                                                             // Size of OpenGL error log.
  char    shader_fullname[MAX_PATH_SIZE];                                       // Shader full file name.

  // Adding NEUTRINO_PATH to relative path file name:
  snprintf (
            shader_fullname,                                                    // Destination string.
            sizeof shader_fullname,                                             // Size of destination string.
            "%s%s",                                                             // Merging two strings.
            baseline->neutrino_path->value,                                     // Source string 1 (NEUTRINO_PATH).
            loc_shader_filename                                                 // Source string 2 (relative path).
           );

  // Loading shader from file:
  baseline->load_file (
                       shader_fullname,                                         // Shader file.
                       &shader_source,                                          // Shader buffer.
                       &shader_size                                             // Shader buffer size.
                      );


  // Selecting shader type:
  switch(loc_shader_type)
  {
    case VERTEX:
      shader = glCreateShader (GL_VERTEX_SHADER);                               // Creating shader...
      break;

    case FRAGMENT:
      shader = glCreateShader (GL_FRAGMENT_SHADER);                             // Creating shader...
      break;

    case GEOMETRY:
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
void shader::init (
                   neutrino* loc_baseline                                       // Neutrino baseline.
                   const char* loc_vertex_filename,                             // Vertex shader file name.
                   const char* loc_geometry_filename,                           // Geometry shader file name.
                   const char* loc_fragment_filename                            // Fragment shader file name.
                  )
{
  vertex   = compile_shader (loc_vertex_filename, VERTEX);                      // Compiling vertex shader...
  geometry = compile_shader (loc_geometry_filename, GEOMETRY);                  // Compiling geometry shader...
  fragment = compile_shader (loc_fragment_filename, FRAGMENT);                  // Compiling fragment shader...
  program  = glCreateProgram ();                                                // Creating program...
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
////////////////////////////// SETARG "point" overload ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void shader::setarg (
                     point* loc_data,                                           // Data object.
                     GLuint loc_layout_index                                    // Data layout index.
                    )
{
  glBindAttribLocation (
                        program,                                                // OpenGL GLSL program.
                        loc_layout_index,                                       // Data layout index.
                        loc_data->name                                          // Data name.
                       );
};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// SETARG "color" overload ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void shader::setarg (
                     color* loc_data,                                           // Data object.
                     GLuint loc_layout_index                                    // Data layout index.
                    )
{
  glBindAttribLocation (
                        program,                                                // OpenGL GLSL program.
                        loc_layout_index,                                       // Data layout index.
                        loc_data->name                                          // Data name.
                       );
};

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// DESTRUCTOR /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
shader::~shader ()
{
  // Doing nothing.
}
