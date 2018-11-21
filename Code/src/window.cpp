#include "window.hpp"

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "WINDOW" CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
window::window()
{

}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// PRIVATE METHODS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
// Grasp arcball action:
void window::grasp			(
													float* 	p,																						// Point on unitary ball.
													int 		x,																						// "Near clipping-plane" x-coordinate.
													int 		y																							// "Near clipping-plane" y-coordinate.
												)
{
	float  op_sq;																																	// Center "o" to "p" squared distance.

	glfwGetWindowSize(glfw_window, &window_size_x, &window_size_y);							  // Getting window size...
  p[0] =   2.0*x/window_size_x - 1.0;                                           // Computing point on unitary ball [x]...
  p[1] = -(2.0*y/window_size_y - 1.0);                                          // Computing point on unitary ball [y] (axis inverted according to OpenGL)...
  p[2] =   0.0;                                                                 // Computing point on unitary ball [z]...
	op_sq = p[0]*p[0] + p[1]*p[1];                                                // Computing "op" squared...

  if (op_sq <= 1.0)																															// Checking p to ball-center distance...
	{
    p[2] = sqrt(1.0 - op_sq);  																									// Pythagoras' theorem...
	}

  else
	{
    normalize(p);  																										          // Normalizing if too far...
	}
}

// Arcball computation:
void window::arcball()
{
	float a[3]; 																															    // Mouse vector, world coordinates.
	float b[3]; 																															    // Mouse vector, world coordinates.
	float axis[3];																										   		      // Arcball axis of rotation.
	float theta;																																	// Arcball angle of rotation.

	if (arcball_on &&((mouse_x != mouse_x_old) || (mouse_y != mouse_y_old)))      // If mouse has been dragged (= left click + move):
	{
		grasp(a, mouse_x_old, mouse_y_old);							  			                    // Building mouse world vector (old)...
		grasp(b, mouse_x, mouse_y);												   					              // Building mouse world vector...
		theta = ROTATION_FACTOR*angle(a, b);                                        // Calculating arcball angle...
    normalize(a);
    normalize(b);
    cross(axis, a, b);									            				                    // Calculating arcball axis of rotation...
    normalize(axis);
    rotate(R, R_old, axis, theta);                                              // Calculating rotation matrix...
	}
}

// Shader compilation:
GLuint window::compile_shader	(
																neutrino* loc_baseline,
																const char* loc_shader_filename,
																shader_type loc_shader_type
															)
{
  GLuint    shader;                                                             // Shader.
  char*     shader_source;                                                      // Shader source.
  size_t    shader_size;                                                        // Shader size [characters].
  GLint 		success;                                                            // "GL_COMPILE_STATUS" flag.
  GLchar*		log;                                                                // Buffer for OpenGL error log.
  GLsizei 	log_size;                                                           // Size of OpenGL error log.
  char      shader_fullname[MAX_PATH_SIZE];                                     // Shader full file name.

  // Adding NEUTRINO_PATH to relative path file name:
  snprintf  (
              shader_fullname,                                                  // Destination string.
              sizeof shader_fullname,                                           // Size of destination string.
              "%s%s",                                                           // Merging two strings.
              loc_baseline->neutrino_path->value,                               // Source string 1 (NEUTRINO_PATH).
              loc_shader_filename                                               // Source string 2 (relative path).
            );

  // Loading shader from file:
  loc_baseline->load_file (
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

  loc_baseline->free_file(shader_source);                                       // Freeing shader source file...

  return (shader);																															// Returning shader...
}

// Shader build:
GLuint window::build_shader	(
															neutrino* 	loc_baseline,													// Neutrino baseline.
															const char* loc_vertex_filename,									// Vertex shader file name.
															const char* loc_fragment_filename									// Fragment shader file name.
														)
{
  GLuint vertex;                                                                // Vertex shader.
  GLuint fragment;                                                              // Fragment shader.
  GLuint program;                                                               // Shader program.

  vertex = compile_shader(loc_baseline, loc_vertex_filename, VERTEX);           // Compiling vertex shader...
  fragment = compile_shader(loc_baseline, loc_fragment_filename, FRAGMENT);     // Compiling fragment shader...
  program = glCreateProgram();                                                  // Creating program...
  glBindAttribLocation(program, 0, "point");                                    // Binding "point" to "layout = 0" shader attribute...
  glBindAttribLocation(program, 1, "color");                                    // Binding "color" to "layout = 1" shader attribute...
  glAttachShader(program, vertex);                                              // Attaching vertex shader to program...
  glAttachShader(program, fragment);                                            // Attaching fragment shader to program...
  glLinkProgram(program);                                                       // Linking program...

  return (program);                                                             // Returning shader program...
}

 // Window initialization:
void window::init				(
													neutrino* 	loc_baseline,															// Neutrino baseline.
													int 				loc_window_size_x,												// Window x-size [px].
													int 				loc_window_size_y,												// Window y-size [px].
													const char*	loc_title																	// Window title.
												)
{
  window_size_x = loc_window_size_x;                                            // Initializing window x-size [px]...
  window_size_y = loc_window_size_y;                                            // Initializing window y-size [px]...
	title = loc_title;																														// Initializing window title...
  aspect_ratio = (double)window_size_x/(double)window_size_y;                 	// Initializing window aspect ration []...
  mouse_x = 0;                                                                  // Initializing mouse x-coordinate [px]...
  mouse_y = 0;                                                                  // Initializing mouse y-coordinate [px]...
  mouse_x_old = 0;                                                              // Initializing mouse x-coordinate backup [px]...
  mouse_y_old = 0;                                                              // Initializing mouse y-coordinate backup [px]...
  scroll_x = 0;                                                                 // Initializing scroll x-coordinate [px]...
  scroll_y = 0;                                                                 // Initializing scroll y-coordinate [px]...
  zoom = 0;                                                                     // Initializing zoom coefficient...
  arcball_on = false;                                                           // Initializing arcball activation flag...

	int opengl_ver_major;                                                         // OpenGL version major number.
  int opengl_ver_minor;                                                         // OpenGL version minor number.
  int opengl_msaa;                                                              // OpenGL multisampling antialiasing factor.

  opengl_ver_major = 4;                                                         // EZOR 04NOV2018: to be generalized by iterative search.
  opengl_ver_minor = 1;                                                         // EZOR 04NOV2018: to be generalized by iterative search.
  opengl_msaa = 4;                                                              // EZOR: 3 or 4 sample is good due to the general oversampling-decimation method.

  // Initializing GLFW context:
  loc_baseline->action  (
                          "initializing GLFW...",
                          MAX_MESSAGE_SIZE
                        );

  if (glfwInit() == GLFW_TRUE)                                                  // Inititalizing GLFW context...
	{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_ver_major);               // Initializing GLFW hints... EZOR 05OCT2018: (was 4)
  	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_ver_minor);               // Initializing GLFW hints... EZOR 05OCT2018: (was 1)
  	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);                        // Initializing GLFW hints...
  	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);              // Initializing GLFW hints...
  	glfwWindowHint(GLFW_SAMPLES, opengl_msaa);                                  // Initializing GLFW hints... EZOR 05OCT2018: (was 4)

    loc_baseline->done();																													// Printing message...
  }

  else
  {
    printf("Error:  unable to initialize GLFW!\n");															// Printing message...
		glfwTerminate();																														// Terminating GLFW context...
		exit(EXIT_FAILURE);																													// Exiting...
  }

  glfw_window = glfwCreateWindow	(
																		window_size_x,                              // Window x-size [px].
                                 		window_size_y,                              // Window y-size [px].
                                 		title,                                      // Window title.
                                 		NULL,                                       // Monitor.
                                 		NULL																				// Share.
																	);
  if (!glfw_window)
	{
		printf("Error:  unable to create window!\n");																// Printing message...
    glfwTerminate();																														// Terminating GLFW context...
    exit(EXIT_FAILURE);																													// Exiting...
  }

  glfwSetWindowUserPointer(glfw_window, this);																	// Getting window pointer...
  glfwMakeContextCurrent(glfw_window);                                          // Making the context of this window current for the calling thread...

  glfwSetWindowRefreshCallback(glfw_window, refresh_callback);                  // Setting refresh callback...
  glfwSetKeyCallback(glfw_window, key_pressed_callback);                        // Setting key pressed callback...
	glfwSetMouseButtonCallback(glfw_window, mouse_pressed_callback);              // Setting mouse pressed callback...
	glfwSetCursorPosCallback(glfw_window, mouse_moved_callback);                  // Setting mouse moved callback...
	glfwSetScrollCallback(glfw_window, mouse_scrolled_callback);                  // Setting mouse scrolled callback...

	// Initializing GLEW context:
  loc_baseline->action  (
                          "initializing GLEW...",
                          MAX_MESSAGE_SIZE
                        );

  glewExperimental = GL_TRUE;                                                   // Ensuring that all extensions with valid entry points will be exposed...

	if (glewInit() == GLEW_OK)																										// Checking GLEW initialization...
	{

    loc_baseline->done();																													// Printing message...
  }

  else
  {
    printf("Error:  unable to initialize GLEW!\n");															// Printing message...
    exit(EXIT_FAILURE);																													// Exiting...
  }

	// Initializing shaders:
  loc_baseline->action  (
                          "initializing GLSL shaders...",
                          MAX_MESSAGE_SIZE
                        );

	point_shader = build_shader	(
																loc_baseline,																		// Neutrino baseline.
																POINT_VERTEX_FILE,															// Vertex shader file name.
																POINT_FRAGMENT_FILE															// Fragment shader file name.
															);

  text_shader = build_shader	(
																loc_baseline,																		// Neutrino baseline.
																TEXT_VERTEX_FILE,																// Vertex shader file name.
																TEXT_FRAGMENT_FILE															// Fragment shader file name.
															);
  loc_baseline->done();																														// Printing message...

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                                         // Setting color for clearing window...
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing window...
  glEnable(GL_DEPTH_TEST);                                                      // Enabling depth test...
  glEnable(GL_PROGRAM_POINT_SIZE);                                              // Enabling "gl_PointSize" in vertex shader...
  glLineWidth(LINE_WIDTH);                                                      // Setting line width...

  translate(T, initial_translation);                                            // Setting initial Translation_matrix matrix...
  perspective(P, FOV*M_PI/180.0, aspect_ratio, NEAR_Z_CLIP, FAR_Z_CLIP);        // Setting Projection_matrix matrix...

	glfwSwapBuffers(glfw_window);                                                 // Swapping front and back buffers...
  glfwPollEvents();                                                             // Polling GLFW events...
}

bool window::closed()
{
  return(glfwWindowShouldClose(glfw_window));																		// Returning window closure status...
}

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CALLBACKS ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
// Refresh callback:
void window::refresh_callback					(
																				GLFWwindow* loc_window									// Window.
																			)
{
	window* win = (window*) glfwGetWindowUserPointer(loc_window);									// Getting window pointer...
	win->refresh();																																// Calling refresh retpoline...
}

// Key-pressed callback:
void window::key_pressed_callback			(
																				GLFWwindow* loc_window,									// Window.
																				int 				loc_key,										// Key.
																				int 				loc_scancode,								// Scancode.
																				int 				loc_action,									// Action.
																				int 				loc_mods										// Mods.
																			)
{
	window* win = (window*) glfwGetWindowUserPointer(loc_window);									// Getting window pointer...
	win->key_pressed(loc_key, loc_scancode, loc_action, loc_mods);								// Calling key pressed retpoline...
}

// Mouse-pressed callback:
void window::mouse_pressed_callback		(
																				GLFWwindow* loc_window,									// Window.
																				int 				loc_button,									// Button.
																				int 				loc_action,									// Action.
																				int 				loc_mods										// Mods.
																			)
{
	window* win = (window*) glfwGetWindowUserPointer(loc_window);									// Getting window pointer...
	win->mouse_pressed(loc_button, loc_action, loc_mods);													// Calling mouse pressed retpoline...
}

// Mouse-moved callback:
void window::mouse_moved_callback			(
																				GLFWwindow* loc_window,									// Window.
																				double 			loc_xpos,										// Mouse x-position [px].
																				double 			loc_ypos										// Mouse y-position [px].
																			)
{
	window* win = (window*) glfwGetWindowUserPointer(loc_window);									// Getting window pointer...
	win->mouse_moved(loc_xpos, loc_ypos);																					// Calling mouse moved retpoline...
	win->arcball();																																// Computing arcball...
}

// Mouse-scrolled callback:
void window::mouse_scrolled_callback	(
																				GLFWwindow*	loc_window,									// Window.
																				double 			loc_xoffset,								// Mouse scroll x-offset [px].
																				double 			loc_yoffset									// Mouse scroll y-offset [px].
																			)
{
	window* win = (window*) glfwGetWindowUserPointer(loc_window);									// Getting window pointer...
	win->mouse_scrolled(loc_xoffset, loc_yoffset);																// Calling mouse scrolled retpoline...
}

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////// PRIVATE RETPOLINES /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
// Key-pressed retpoline:
void window::key_pressed					(
																		int loc_key,																// Key.
																		int loc_scancode,														// Scancode.
																		int loc_action,															// Action.
																		int loc_mods																// Mods.
																	)
{
	// Checking key pressed:
  if 	(
				loc_key 		== GLFW_KEY_ESCAPE &&
				loc_action 	== GLFW_PRESS
			)
  {
    glfwSetWindowShouldClose(glfw_window, GL_TRUE);															// Setting window "closed" flag...
  }
}

// Mouse-pressed retpoline:
void window::mouse_pressed				(
																		int loc_button,															// Button.
																		int loc_action,															// Action.
																		int loc_mods																// Mods.
																	)
{
	// Checking whether mouse button has been pressed:
  if  (
				loc_button 			== GLFW_MOUSE_BUTTON_LEFT &&
				loc_action 			== GLFW_PRESS &&
				arcball_on 			== false
			)
  {
    glfwGetCursorPos(glfw_window, &mouse_x, &mouse_y);                          // Getting mouse position...
    mouse_x_old = mouse_x;																											// Backing up mouse position...
    mouse_y_old = mouse_y;																											// Backing up mouse position...
    arcball_on = true;																													// Turning on arcball...
  }

  else
  {
    arcball_on = false;																													// Turning off arcball...
  }

	// Checking whether mouse button released:
  if 	(
				loc_button == GLFW_MOUSE_BUTTON_LEFT &&
				loc_action == GLFW_RELEASE)
  {
    R_old[0] = R[0]; R_old[4] = R[4]; R_old[8]  = R[8];  R_old[12] = R[12];		  // Backing up Rotation_matrix matrix...
    R_old[1] = R[1]; R_old[5] = R[5]; R_old[9]  = R[9];  R_old[13] = R[13];			// Backing up Rotation_matrix matrix...
    R_old[2] = R[2]; R_old[6] = R[6]; R_old[10] = R[10]; R_old[14] = R[14];		  // Backing up Rotation_matrix matrix...
    R_old[3] = R[3]; R_old[7] = R[7]; R_old[11] = R[11]; R_old[15] = R[15];		  // Backing up Rotation_matrix matrix...
  }
}

// Mouse-moved retpoline:
void window::mouse_moved						(
																			double loc_xpos,													// Mouse position [px].
																			double loc_ypos														// Mouse position [px].
																		)
{
	// Checking arcball "on" flag:
  if (arcball_on)
  {
    mouse_x = loc_xpos;																													// Getting mouse position...
    mouse_y = loc_ypos;																													// Getting mouse position...
  }
}

// Mmouse-scrolled retpoline:
void window::mouse_scrolled					(
																			double loc_xoffset,												// Mouse scrolled x-position [px].
																			double loc_yoffset												// Mouse scrolled y-position [px].
																		)
{
  float translation[3];                                                         // Translation vector.

  scroll_x = loc_xoffset;																												// Getting scroll position...
  scroll_y = loc_yoffset;																												// Getting scroll position...
  zoom = T[14];																							                    // Getting z-axis translation...

	// Checking y-position:
  if (scroll_y > 0)
  {
    zoom *= ZOOM_FACTOR;																												// Zooming-in...
  }

	// Checking y-position:
  if (scroll_y < 0)
  {
    zoom /= ZOOM_FACTOR;																												// Zooming-out...
  }

  translation[0] = 0.0;                                                         // Building translation vector...
  translation[1] = 0.0;                                                         // Building translation vector...
  translation[2] = zoom;                                                        // Building translation vector...
  translate(T, translation);                                                    // Building translation matrix...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PUBLIC RETPOLINES /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
// Window clearance retpoline:
void window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                           // Clearing window...
}

// Window refresh retpoline:
void window::refresh()
{
  glfwSwapBuffers(glfw_window);                                                 // Swapping front and back buffers...
}

void window::poll_events()
{
	glfwPollEvents();                                                             // Polling GLFW events...
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// PUBLIC METHODS ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
// Plot function:
void window::plot(point4* points, color4* colors, plot_style ps)
{
  multiplicate(V, T, R);                                                        // Setting View_matrix matrix...

  switch(ps)
  {
    case STYLE_POINT:
      glUseProgram(point_shader);                                               // Using shader...

			// Setting View_matrix matrix on shader:
      glUniformMatrix4fv	(	// Getting variable's uniform location:
														glGetUniformLocation	(
																										point_shader,								// Program.
																										"View_matrix"								// Variable.
																									),
                         		1,                                                  // # of matrices to be modified.
                         		GL_FALSE,                                           // FALSE = column major.
                         		&V[0]																								// View matrix.
													);

			// Setting Projection_matrix matrix on shader:
      glUniformMatrix4fv	(	// Getting variable's uniform location:
														glGetUniformLocation	(
																										point_shader,								// Program.
																										"Projection_matrix"					// Variable.
																									),
                         		1,                                                  // # of matrices to be modified.
                         		GL_FALSE,                                           // FALSE = column major.
                         		&P[0]																								// Projection matrix.
													);
      break;

    default:
    glUseProgram(point_shader);                                               	// Using shader...

		// Setting View_matrix matrix on shader:
		glUniformMatrix4fv		(	// Getting variable's uniform location:
														glGetUniformLocation	(
																										point_shader,								// Program.
                                            				"View_matrix"								// Variable.
																									),
                       			1,                                     	            // # of matrices to be modified.
                       			GL_FALSE,                                	          // FALSE = column major.
                       			&V[0]																								// View matrix.
													);

		// Setting Projection_matrix matrix on shader:
    glUniformMatrix4fv		(	// Getting variable's uniform location:
														glGetUniformLocation	(
																										point_shader,								// Program.
																										"Projection_matrix"					// Variable.
																									),
                       			1,                                                  // # of matrices to be modified.
                       			GL_FALSE,                                           // FALSE = column major.
                       			&P[0]																								// Projection matrix.
													);
    break;
  }

  // Binding "points" array:
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, points->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

  // Binding "colors" array:
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, colors->vbo);                                   // Binding VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

  // Drawing:
  glDrawArrays(GL_POINTS, 0, points->size);                                     // Drawing "points"...

  // Finishing:
  glDisableVertexAttribArray(LAYOUT_0);                                         // Unbinding "points" array...
  glDisableVertexAttribArray(LAYOUT_1);                                         // Unbinding "colors" array...
}

// Print function:
void window::print(text4* text)
{
  multiplicate(V, T, R);                                                        // Setting View_matrix matrix...
  glUseProgram(text_shader);                                                    // Using shader...

	// Setting View_matrix matrix on shader:
	glUniformMatrix4fv		(	// Getting variable's uniform location:
													glGetUniformLocation	(
																									text_shader,									// Program.
																									"View_matrix"									// Variable.
																								),
                     			1,																										// # of matrices to be modified.
                     			GL_FALSE,																							// FALSE = column major.
                     			&V[0]																									// View matrix.
												);

	// Setting Projection_matrix matrix on shader:
  glUniformMatrix4fv		(	// Getting variable's uniform location:
													glGetUniformLocation	(
																									text_shader,									// Program.
																									"Projection_matrix"						// Variable.
																								),
                     			1,																										// # of matrices to be modified.
                     			GL_FALSE,																							// FALSE = column major.
                     			&P[0]																									// Projection matrix.
												);

  // Binding "glyph" array:
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, text->glyph_vbo);                               // Binding glyph VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

  // Binding "color" array:
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, text->color_vbo);                               // Binding color VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

  // Drawing:
  glDrawArrays(GL_LINES, 0, text->size);                                        // Drawing "glyphs"...
	//refresh();

  // Finishing:
  glDisableVertexAttribArray(LAYOUT_0);                                         // Unbinding "glyph" array...
  glDisableVertexAttribArray(LAYOUT_1);                                         // Unbinding "color" array...
}

window::~window()
{
	glfwTerminate();                                                              // Terminating GLFW...
}
