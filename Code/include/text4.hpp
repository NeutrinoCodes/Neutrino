/// @file

#ifndef text4_hpp
#define text4_hpp

  #include <stdio.h>

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

      cl_context        context;                                                // OpenCL context.
      font*             hershey;

    public:
      text4(cl_context thecontext, font* thefont, const char* text, GLfloat R, GLfloat G, GLfloat B, GLfloat A);
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
