/// @file

#ifndef opencl_hpp
#define opencl_hpp

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
    #include <math.h>

  #ifdef __APPLE__
    #include <OpenCL/opencl.h>
    #include <OpenGL/OpenGL.h>
  #else
    #include <CL/cl.h>
    #include <CL/cl_gl.h>
    #include <GL/gl.h>
  #endif

  #define KERNEL_NAME             "thekernel"
  #define KERNEL_OPTIONS          ""
  #define SIZE_TEXT_MAX 128                                                     // Maximum number of characters in a text string.

  /// **Declaration of "float4" data class:**
  /// "float4" are 4 arrays of "num_data" elements.
  /// These arrays are good because they can be readily used by OpenCL/GL:
  /// e.g. (x, y, z, w) can be a 4D vector in the projective space (homogeneous coordinates).
  class float4
  {
    private:
      int               err;                                                    // Declaring "error" code...
      unsigned int      i;                                                      // Declaring "i" index...

    public:
      float4(int num_data);
      ~float4();

      GLfloat*  x;                                                              // Declaring "x" data...
      GLfloat*  y;                                                              // Declaring "y" data...
      GLfloat*  z;                                                              // Declaring "z" data...
      GLfloat*  w;                                                              // Declaring "w" data...
      GLfloat*  data;                                                           // Declaring "data" data...
      int       size;                                                           // Declaring "size" [#]...
      GLuint    vao;                                                            // Declaring OpenGL Vertex Array Object...
      GLuint    vbo;                                                            // Declaring OpenGL Vertex Buffer Object...
      cl_mem    buffer;                                                         // Declaring OpenCL memory buffer...
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

    public:
      int4(int num_data);
      ~int4();

      GLint*    x;
      GLint*    y;
      GLint*    z;
      GLint*    w;
      GLint*    data;
      int       size;
      GLuint    vao;
      GLuint    vbo;
      cl_mem    buffer;
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



  const char* get_error(cl_int error);
  cl_uint     get_platforms();
  void        get_platform_info(cl_uint index_platform, cl_platform_info name_param);
  cl_uint     get_devices(cl_uint index_platform);
  void        get_device_info(cl_uint index_device, cl_device_info name_param);
  /// **Initialization of OpenCL computational context:**
  void        init_opencl_context();

  /// **Destruction of OpenCL computational context:**
  void        destroy_opencl_context();
  void        set_kernel_dimension(cl_uint dimension);
  void        set_kernel_global_size(size_t size);
  void        typeset(text4* text);
  void        set_float(float* data, int kernel_arg);
  void        set_int(int* data, int kernel_arg);
  void        set_point4(point4* points, int kernel_arg);
  void        set_color4(color4* colors, int kernel_arg);

  void        load_kernel(const char* filename_kernel);
  void        init_opencl_kernel();
  void        get_kernel_workgroup_size(cl_kernel kernel, cl_device_id device_id, size_t* local);
  void        execute_kernel();

  void        push_float4(float4* data, int kernel_arg);
  void        push_int4(int4* data, int kernel_arg);
  void        push_float(float* data, int kernel_arg);
  void        push_int(int* data, int kernel_arg);
  void        push_point4(cl_mem* CL_memory_buffer, int kernel_arg);
  void        push_color4(cl_mem* CL_memory_buffer, int kernel_arg);

  void        enqueue_task();
  void        wait_for_event();

  void        pop_float4(float4* data, int kernel_arg);
  void        pop_int4(int4* data, int kernel_arg);
  void        pop_float(float* data, int kernel_arg);
  void        pop_int(int* data, int kernel_arg);
  void        pop_point4(cl_mem* CL_memory_buffer, int kernel_arg);
  void        pop_color4(cl_mem* CL_memory_buffer, int kernel_arg);

  void        finish_queue();
  void        release_event();
  void        release_mem_object(cl_mem CL_memory_buffer);
  void        release_kernel();
  void        release_queue();
  void        release_program();
  void        release_context();

#endif
