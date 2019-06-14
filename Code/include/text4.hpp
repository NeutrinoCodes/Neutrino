/// @file

#ifndef text4_hpp
#define text4_hpp

  #include "neutrino.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// "TEXT4" CLASS ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class text4
{
private:
  neutrino* baseline;                                                           // Neutrino baseline.

  int       err;
  int       i;
  int       j;
  int       k;
  int       shift;
  int       even;
  int       odd;

  int       num_char;
  int       num_data;
  int       num_points;
  int       num_strokes;

  int*      char_code;
  int*      char_item;
  int*      char_numdata;
  int*      char_numpoints;
  int*      char_numstrokes;
  int*      char_kern;

  int*      data_index;
  int*      kern;
  int*      offset;

  GLfloat*  glyph_data;                                                         // Text "glyph" data.
  GLfloat*  color_data;                                                         // Text "color" data.

public:
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

  text4();
  void init (
             neutrino*   loc_baseline,
             const char* loc_text,
             GLfloat     loc_R,
             GLfloat     loc_G,
             GLfloat     loc_B,
             GLfloat     loc_A
            );

  ~text4();
};

#endif
