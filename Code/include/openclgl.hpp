/// @file

#ifndef opencl_hpp
#define opencl_hpp

  #define CL_USE_DEPRECATED_OPENCL_1_2_APIS
  #define KERNEL_NAME             "thekernel"
  #define KERNEL_OPTIONS          ""
  #define SIZE_TEXT_MAX 128                                                     // Maximum number of characters in a text string.
  #define SIZE_WINDOW_X 800                                                     // Window x-size [px].
  #define SIZE_WINDOW_Y 600                                                     // Window y-size [px].
  #define ZOOM_FACTOR 1.05f                                                     // Zoom factor [> 1.0].
  #define ROTATION_FACTOR 2.0f                                                  // Rotation factor [].
  #define NEAR_Z_CLIP 0.1f                                                      // Near z-clipping distance [> 0.0].
  #define FAR_Z_CLIP 100.0f                                                     // Far z-clipping distance [< +inf].
  #define FOV 60.0f                                                             // Field of view [deg].
  #define LINE_WIDTH 3                                                          // Line width [px].

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include <GL/glew.h>

  #ifdef __WINDOWS__
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define GLFW_EXPOSE_NATIVE_WGL
  #endif

  #ifdef __linux__
    #define GLFW_EXPOSE_NATIVE_X11
    #define GLFW_EXPOSE_NATIVE_GLX

  #endif

  #include <GLFW/glfw3.h>
  #include <GLFW/glfw3native.h>

  #ifdef __APPLE__
    #include <OpenCL/opencl.h>
    #include <OpenGL/OpenGL.h>
  #else
    #include <CL/cl.h>
    #include <CL/cl_gl.h>
    #include <GL/gl.h>
  #endif

  #include "linear_algebra.hpp"
  #include "projective_geometry.hpp"
  #include "utilities.hpp"

  extern  GLFWwindow*				window;                                             // Window handle.

  class kernel
  {
    private:

    public:
      kernel();
      ~kernel();

      cl_kernel               thekernel;

      char*                   source_file;
      size_t                  source_size;
      char*                   source;

      cl_program              program;
      size_t                  size;
      cl_uint                 dimension;
      cl_event                event;
  };

  /// **Declaration of "float1" data class:**
  /// "float1" is an array of "num_data" elements.
  class float1
  {
    private:
      int               err;                                                    // Declaring "error" code...
      unsigned int      i;                                                      // Declaring "i" index...
      // NOTE: There is no need for "unfolded-data" because these data are 1xN.
      GLuint            LAYOUT_0;                                               // "layout = 0" attribute in vertex shader.

    public:
      float1(int num_data);
      ~float1();

      cl_float*    x;                                                           // Declaring "x" data...

      int       size;                                                           // Declaring "size" [#]...
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;                                                         // Declaring OpenCL memory buffer...

      void      init();
      void      set(kernel* k, int kernel_arg);
      void      push(kernel* k, int kernel_arg);
      void      pop(kernel* k, int kernel_arg);
  };

  /// **Declaration of "int1" data class:**
  /// "int4" is an array of "num_data" elements.
  class int1
  {
    private:
      int               err;
      unsigned int      i;
      // NOTE: There is no need for "unfolded-data" because these data are 1xN.
      GLuint            LAYOUT_0;                                               // "layout = 0" attribute in vertex shader.

    public:
      int1(int num_data);
      ~int1();

      cl_int*      x;

      int       size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;

      void      init();
      void      set(kernel* k, int kernel_arg);
      void      push(kernel* k, int kernel_arg);
      void      pop(kernel* k, int kernel_arg);
  };

  /// **Declaration of "float4" data class:**
  /// "float4" are 4 arrays of "num_data" elements.
  /// These arrays are good because they can be readily used by OpenCL/GL:
  /// e.g. (x, y, z, w) can be a 4D vector in the projective space (homogeneous coordinates).
  class float4
  {
    private:
      int               err;                                                    // Declaring "error" code...
      unsigned int      i;                                                      // Declaring "i" index...
      GLfloat*          data;                                                   // Declaring unfolded data array...
      GLuint            LAYOUT_0;                                               // "layout = 0" attribute in vertex shader.

    public:
      float4(int num_data);
      ~float4();

      cl_float*    x;                                                           // Declaring "x" data...
      cl_float*    y;                                                           // Declaring "y" data...
      cl_float*    z;                                                           // Declaring "z" data...
      cl_float*    w;                                                           // Declaring "w" data...

      int       size;                                                           // Declaring "size" [#]...
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;                                                         // Declaring OpenCL memory buffer...

      void      init();
      void      set(kernel* k, int kernel_arg);
      void      push(kernel* k, int kernel_arg);
      void      pop(kernel* k, int kernel_arg);
  };

  /// **Declaration of "int4" data class:**
  /// "int4" are 4 arrays of "num_data" elements.
  /// These arrays are good because they can be readily used by OpenCL/GL:
  /// e.g. (x, y, z, w) can be a 4D vector in the projective space (homogeneous coordinates).
  class int4
  {
    private:
      int               err;
      unsigned int      i;
      GLint*            data;                                                   // Declaring unfolded data array...
      GLuint            LAYOUT_0;                                               // "layout = 0" attribute in vertex shader.

    public:
      int4(int num_data);
      ~int4();

      cl_int*      x;
      cl_int*      y;
      cl_int*      z;
      cl_int*      w;

      int       size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;

      void      init();
      void      set(kernel* k, int kernel_arg);
      void      push(kernel* k, int kernel_arg);
      void      pop(kernel* k, int kernel_arg);
  };

  /// **Declaration of "point4" data class:**
  /// "point4" are 4 arrays of "num_data" elements.
  /// These arrays are used to represent the coordinates of 4D points
  /// (in the homogeneous coordinates "x, y, z, w") that will we used by
  /// OpenCL/GL for the 3D graphical rendition in the "plot" function.
  class point4
  {
    private:
      int               err;
      unsigned int      i;
      GLfloat*          data;
      GLuint            LAYOUT_0;                                               // "layout = 0" attribute in vertex shader.

    public:
      point4(int num_data);
      ~point4();

      GLfloat*  x;
      GLfloat*  y;
      GLfloat*  z;
      GLfloat*  w;

      int size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;

      void      init();
      void      set(kernel* k, int kernel_arg);
      void      push(kernel* k, int kernel_arg);
      void      pop(kernel* k, int kernel_arg);
  };

  /// **Declaration of "color4" data class:**
  /// "color4" are 4 arrays of "num_data" elements.
  /// These arrays are used to represent the color of 4D points
  /// (in the color coordinates "r, g, b, a") that will we used by OpenCL/GL
  /// for the 3D graphical rendition in the "plot" function.
  class color4
  {
    private:
      int               err;
      unsigned int      i;
      GLfloat*          data;
      GLuint            LAYOUT_1 = 1;                                           // "layout = 1" attribute in vertex shader.

    public:
      color4(int num_data);
      ~color4();

      GLfloat*  r;
      GLfloat*  g;
      GLfloat*  b;
      GLfloat*  a;

      int       size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;

      void      init();
      void      set(kernel* k, int kernel_arg);
      void      push(kernel* k, int kernel_arg);
      void      pop(kernel* k, int kernel_arg);
  };

  /// **Declaration of "text4" data class:**
  /// "text4" is a 4D vector in the homogeneous coordinates "x, y, z, w"
  /// indicating the origin of a "text" having color "r, g, b, a".
  /// The text is by default instatiated on the X-Y plane,
  /// parallel to the X-axis.
  /// It will we used by OpenCL/GL for the 3D graphical rendition in
  /// the "print" function.
  class text4
  {
    private:
      int      err;
      int      i;
      int      j;
      int      k;
      int      shift;
      int      even;
      int      odd;

      int      num_char;
      int      num_data;
      int      num_points;
      int      num_strokes;

      int*     char_code;
      int*     char_item;
      int*     char_numdata;
      int*     char_numpoints;
      int*     char_numstrokes;
      int*     char_kern;

      int*     data_index;
      int*     kern;
      int*     offset;

    public:
      text4(const char* text, GLfloat R, GLfloat G, GLfloat B, GLfloat A);
      ~text4();

      GLfloat*  x;
      GLfloat*  y;
      GLfloat*  z;
      GLfloat*  w;

      GLfloat*  r;
      GLfloat*  g;
      GLfloat*  b;
      GLfloat*  a;

      int       size;

      GLuint    glyph_vao;
      GLuint    color_vao;
      GLuint    glyph_vbo;
      GLuint    color_vbo;
  };

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// FILES ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void        load_point_vertex(char* neutrino_path, const char* filename_vertex);
  void        load_point_fragment(char* neutrino_path, const char* filename_fragment);
  void        load_text_vertex(char* neutrino_path, const char* filename_vertex);
  void        load_text_fragment(char* neutrino_path, const char* filename_fragment);

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// WINDOW ////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  typedef enum
    {
      STYLE_POINT,
      STYLE_WIREFRAME,
      STYLE_SHADED
    } plot_style;

  void        init_window();
  void        init_shaders();
  void        init_screen();
  void        refresh_screen();
  void        clear_screen();

  /// **Initialization of OpenGL graphic context:**
  void        init_opengl_context();

  /// **Destruction of OpenGL graphic context:**
  void        destroy_opengl_context();
  void        get_arcball_vector(float* p, int x, int y);
  void        arcball();
  void        plot(point4* points, color4* colors, plot_style ps);
  void        print(text4* text);

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////// WINDOW's CALLBACKS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  void        key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  void        mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
  void        cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
  void        scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
  void        window_refresh_callback(GLFWwindow* window);

  const char* get_error(cl_int error);
  cl_uint     get_platforms();
  void        get_platform_info(cl_uint index_platform, cl_platform_info name_param);
  cl_uint     get_devices(cl_uint index_platform);
  void        get_device_info(cl_uint index_device, cl_device_info name_param);
  void        init_opencl_context();
  void        destroy_opencl_context();

  void        typeset(text4* text);
  void        load_kernel(kernel* k);
  void        init_opencl_kernel(kernel* k);
  void        get_kernel_workgroup_size(kernel* k, cl_device_id device_id, size_t* local);
  void        execute_kernel(kernel* k);
  void        enqueue_task(kernel* k);
  void        wait_for_event(kernel* k);
  void        release_event(kernel* k);
  void        release_kernel(kernel* k);
  void        release_program(kernel* k);
  void        finish_queue();
  void        release_mem_object(cl_mem CL_memory_buffer);
  void        release_queue();
  void        release_context();

#endif
