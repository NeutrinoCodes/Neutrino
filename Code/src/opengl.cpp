/// @file

#include "opengl.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "OPENGL" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
opengl::opengl()
{

}

// PRIVATE METHODS:
GLuint opengl::compile_shader(neutrino* loc_neutrino, const char* loc_shader_filename, shader_type loc_shader_type)
{
  GLuint    shader;                                                             // Shader.
  char*     shader_source;                                                      // Shader source.
  size_t    shader_size;                                                        // Shader size [characters].
  GLint 		success;                                                            // "GL_COMPILE_STATUS" flag.
  GLchar*		log;                                                                // Buffer for OpenGL error log.
  GLsizei 	log_size;                                                           // Size of OpenGL error log.
  char      shader_fullname[32768];                                             // Shader full file name.

  // Adding NEUTRINO_PATH to relative path file name:
  snprintf  (
              shader_fullname,                                                  // Destination string.
              sizeof shader_fullname,                                           // Size of destination string.
              "%s%s",                                                           // Merging two strings.
              loc_neutrino->neutrino_path,                                      // Source string 1 (NEUTRINO_PATH).
              loc_shader_filename                                               // Source string 2 (relative path).
            );

  // Loading shader from file:
  loc_neutrino->load_file (
                            shader_fullname,                                    // Shader file.
                            &shader_source,                                     // Shader buffer.
                            &shader_size                                        // Shader buffer size.
                          );

  switch(loc_shader_type)
  {
    case VERTEX:
      shader = glCreateShader(GL_VERTEX_SHADER);                                // Creating shader...
    break;

    case FRAGMENT:
      shader = glCreateShader(GL_FRAGMENT_SHADER);                              // Creating shader...
    break;
  }

  glShaderSource(shader,                                                        // Attaching source code to shader...
                 1,
                 (const char**)&shader_source,
                 (GLint*)&shader_size);
	glCompileShader(shader);                                                      // Compiling shader...
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);                           // Reading "GL_COMPILE_STATUS" flag...

  // Checking compiled shader code:
  if (!success)
  {
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);                       // Getting log length...
    log = (char*) malloc(log_size + 1);                                         // Allocating temporary buffer for log...
    log[log_size] = '\0';                                                       // Null-terminating log buffer...
    glGetShaderInfoLog(shader, log_size + 1, NULL, log);                        // Getting log...
    printf("%s\n", log);                                                        // Printing log...
    free(log);                                                                  // Freeing log...
    exit(1);                                                                    // Exiting...
  }

  loc_neutrino->free_file(shader_source);                                       // Freeing shader source file...

  return (shader);
}

GLuint opengl::build_shader(const char* filename_vertex, const char* filename_fragment)
{
  GLuint vertex;                                                                // Vertex shader.
  GLuint fragment;                                                              // Fragment shader.
  GLuint program;                                                               // Shader program.

  vertex = compile_shader(POINT_VERTEX_FILE, VERTEX);                           // Compiling vertex shader...
  fragment = compile_shader(POINT_FRAGMENT_FILE, FRAGMENT);                     // Compiling fragment shader...
  program = glCreateProgram();                                                  // Creating program...
  glBindAttribLocation(program, 0, "point");                                    // Binding "point" to "layout = 0" shader attribute...
  glBindAttribLocation(program, 1, "color");                                    // Binding "color" to "layout = 1" shader attribute...
  glAttachShader(program, vertex);                                              // Attaching vertex shader to program...
  glAttachShader(program, fragment);                                            // Attaching fragment shader to program...
  glLinkProgram(program);                                                       // Linking program...

  return (program);                                                             // Returning shader program...
}

// PUBLIC METHODS:
void opengl::init(neutrino* loc_neutrino)                                       // OpenGL initialization.
{
  int opengl_ver_major;                                                         // OpenGL version major number.
  int opengl_ver_minor;                                                         // OpenGL version minor number.
  int opengl_msaa;                                                              // OpenGL multisampling antialiasing factor.
  path* neutrino_path = new path();

  neutrino_path->value = loc_neutrino->neutrino_path->value;
  neutrino_path->size = loc_neutrino->neutrino_path->size;

  // Initializing GLFW context:
  printf("Action: initializing GLFW... ");

  if (glfwInit() == GLFW_TRUE)                                                  // Inititalizing GLFW context...
	{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ver_major);                      // Initializing GLFW hints... EZOR 05OCT2018: (was 4)
  	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ver_minor);                      // Initializing GLFW hints... EZOR 05OCT2018: (was 1)
  	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);                        // Initializing GLFW hints...
  	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);              // Initializing GLFW hints...
  	glfwWindowHint(GLFW_SAMPLES, msaa);                                         // Initializing GLFW hints... EZOR 05OCT2018: (was 4)

    printf("DONE!\n");
  }

  else
  {
    printf("Error:  unable to initialize GLFW!\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
  }

  // Initializing GLEW context:
  printf("Action: initializing GLEW... ");
  glewExperimental = GL_TRUE;                                                   // Ensuring that all extensions with valid entry points will be exposed...

	if (glewInit() == GLEW_OK)
	{

    printf("DONE!\n");
  }

  else
  {
    printf("Error:  unable to initialize GLEW!\n");
    exit(EXIT_FAILURE);
  }

  // Initializing shaders:
  printf("Action: initializing GLSL shaders... ");
  point_shader = build_shader(POINT_VERTEX_FILE, POINT_FRAGMENT_FILE);
  text_shader = build_shader(TEXT_VERTEX_FILE, TEXT_FRAGMENT_FILE);
  printf("DONE!\n");
}

opengl::~opengl()
{
  glfwTerminate();                                                              // Terminating GLFW...
}
