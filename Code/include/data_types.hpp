#ifndef data_types_hpp
#define deta_types_hpp

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
    #include <OpenGL/OpenGL.h>
  #else
    #include <GL/gl.h>
  #endif

  #ifdef __APPLE__
    #include <OpenCL/opencl.h>
  #else
    #include <CL/cl.h>
    #include <CL/cl_gl.h>
  #endif

  #include "opencl.hpp"

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
      void      push(queue* q, kernel* k, int kernel_arg);
      void      pop(queue* q, kernel* k, int kernel_arg);
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
      void      push(queue* q, kernel* k, int kernel_arg);
      void      pop(queue* q, kernel* k, int kernel_arg);
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
      void      push(queue* q, kernel* k, int kernel_arg);
      void      pop(queue* q, kernel* k, int kernel_arg);
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
      void      push(queue* q, kernel* k, int kernel_arg);
      void      pop(queue* q, kernel* k, int kernel_arg);
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
      void      push(queue* q, kernel* k, int kernel_arg);
      void      pop(queue* q, kernel* k, int kernel_arg);
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
      GLuint            LAYOUT_1;                                               // "layout = 1" attribute in vertex shader.

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
      void      push(queue* q, kernel* k, int kernel_arg);
      void      pop(queue* q, kernel* k, int kernel_arg);
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

      GLfloat* glyph_data;                                                      // Text "glyph" data.
      GLfloat* color_data;                                                      // Text "color" data.
      GLuint   LAYOUT_0;                                                        // "layout = 0" attribute in vertex shader.
      GLuint   LAYOUT_1;                                                        // "layout = 1" attribute in vertex shader.

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

      void init();
  };

#endif
