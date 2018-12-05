#include "memory_orb.hpp"

memory_orb::memory_orb()
{

}

void memory_orb::init (
                        neutrino* loc_baseline
                      )
{
  baseline = loc_baseline;                                                      // Getting Neutrino baseline...
  baseline->action("initializing memory orb...");                               // Printing message...

  size_t i;

  // WINGS:
  wings_points = 8;

  wings_x       = new GLfloat[wings_points];                                    // "wings_x" data array.
  wings_y       = new GLfloat[wings_points];                                    // "wings_y" data array.
  wings_z       = new GLfloat[wings_points];                                    // "wings_z" data array.
  wings_w       = new GLfloat[wings_points];                                    // "wings_w" data array.

  wings_r       = new GLfloat[wings_points];                                    // "wings_r" data array.
  wings_g       = new GLfloat[wings_points];                                    // "wings_g" data array.
  wings_b       = new GLfloat[wings_points];                                    // "wings_b" data array.
  wings_a       = new GLfloat[wings_points];                                    // "wings_a" data array.

  wings_data    = new GLfloat[4*wings_points];                                  // "wings_data" array.
  wings_colors  = new GLfloat[4*wings_points];                                  // "wings_color" array.

  wings_x[0]    = -0.5f*(WINGS_SPAN);
  wings_y[0]    =  0.0f;
  wings_z[0]    =  0.0f;
  wings_w[0]    =  1.0f;
  wings_r[0]    =  0.0f;
  wings_g[0]    =  1.0f;
  wings_b[0]    =  0.0f;
  wings_a[0]    =  0.9f;

  wings_x[1]    = -0.5f*(WINGS_GAP);
  wings_y[1]    =  0.0f;
  wings_z[1]    =  0.0f;
  wings_w[1]    =  1.0f;
  wings_r[1]    =  0.0f;
  wings_g[1]    =  1.0f;
  wings_b[1]    =  0.0f;
  wings_a[1]    =  0.9f;

  wings_x[2]    = -0.5f*(WINGS_GAP);
  wings_y[2]    =  0.0f;
  wings_z[2]    =  0.0f;
  wings_w[2]    =  1.0f;
  wings_r[2]    =  0.0f;
  wings_g[2]    =  1.0f;
  wings_b[2]    =  0.0f;
  wings_a[2]    =  0.9f;

  wings_x[3]    = -0.5f*(WINGS_GAP);
  wings_y[3]    = -1.0f*(WINGS_HEIGHT);
  wings_z[3]    =  0.0f;
  wings_w[3]    =  1.0f;
  wings_r[3]    =  0.0f;
  wings_g[3]    =  1.0f;
  wings_b[3]    =  0.0f;
  wings_a[3]    =  0.9f;

  wings_x[4]    =  0.5f*(WINGS_SPAN);
  wings_y[4]    =  0.0f;
  wings_z[4]    =  0.0f;
  wings_w[4]    =  1.0f;
  wings_r[4]    =  0.0f;
  wings_g[4]    =  1.0f;
  wings_b[4]    =  0.0f;
  wings_a[4]    =  0.9f;

  wings_x[5]    =  0.5f*(WINGS_GAP);
  wings_y[5]    =  0.0f;
  wings_z[5]    =  0.0f;
  wings_w[5]    =  1.0f;
  wings_r[5]    =  0.0f;
  wings_g[5]    =  1.0f;
  wings_b[5]    =  0.0f;
  wings_a[5]    =  0.9f;

  wings_x[6]    =  0.5f*(WINGS_GAP);
  wings_y[6]    =  0.0f;
  wings_z[6]    =  0.0f;
  wings_w[6]    =  1.0f;
  wings_r[6]    =  0.0f;
  wings_g[6]    =  1.0f;
  wings_b[6]    =  0.0f;
  wings_a[6]    =  0.9f;

  wings_x[7]    =  0.5f*(WINGS_GAP);
  wings_y[7]    = -1.0f*(WINGS_HEIGHT);
  wings_z[7]    =  0.0f;
  wings_w[7]    =  1.0f;
  wings_r[7]    =  0.0f;
  wings_g[7]    =  1.0f;
  wings_b[7]    =  0.0f;
  wings_a[7]    =  0.9f;

  for (i = 0; i < wings_points; i++)
  {
    wings_data  [4*i + 0] = wings_x[i];
    wings_data  [4*i + 1] = wings_y[i];
    wings_data  [4*i + 2] = wings_z[i];
    wings_data  [4*i + 3] = wings_w[i];

    wings_colors[4*i + 0] = wings_r[i];
    wings_colors[4*i + 1] = wings_g[i];
    wings_colors[4*i + 2] = wings_b[i];
    wings_colors[4*i + 3] = wings_a[i];
  }

  glGenVertexArrays(1, &wings_data_vao);                                    // Generating glyph VAO...
  glBindVertexArray(wings_data_vao);                                        // Binding glyph VAO...
  glGenBuffers(1, &wings_data_vbo);                                         // Generating glyph VBO...

  glBindBuffer(GL_ARRAY_BUFFER, wings_data_vbo);                            // Binding glyph VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(wings_points),
               wings_data,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, wings_data_vbo);                            // Binding glyph VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

  glGenVertexArrays(1, &wings_colors_vao);                                  // Generating color VAO...
  glBindVertexArray(wings_colors_vao);                                      // Binding color VAO...
  glGenBuffers(1, &wings_colors_vbo);                                       // Generating color VBO...
  glBindBuffer(GL_ARRAY_BUFFER, wings_colors_vbo);                          // Binding color VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(wings_points),
               wings_colors,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, wings_colors_vbo);                          // Binding color VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

  delete[] wings_data;
  delete[] wings_colors;

  // PITCH LEVEL:
  pitch_level_points = 4;

  pitch_level_x       = new GLfloat[pitch_level_points];                        // "pitch_level_x" data array.
  pitch_level_y       = new GLfloat[pitch_level_points];                        // "pitch_level_y" data array.
  pitch_level_z       = new GLfloat[pitch_level_points];                        // "pitch_level_z" data array.
  pitch_level_w       = new GLfloat[pitch_level_points];                        // "pitch_level_w" data array.

  pitch_level_r       = new GLfloat[pitch_level_points];                        // "pitch_level_r" data array.
  pitch_level_g       = new GLfloat[pitch_level_points];                        // "pitch_level_g" data array.
  pitch_level_b       = new GLfloat[pitch_level_points];                        // "pitch_level_b" data array.
  pitch_level_a       = new GLfloat[pitch_level_points];                        // "pitch_level_a" data array.

  pitch_level_data    = new GLfloat[4*pitch_level_points];                      // "pitch_level_data" array.
  pitch_level_colors  = new GLfloat[4*pitch_level_points];                      // "pitch_level_color" array.

  pitch_level_x[0]    = -0.5f*(PITCH_SPAN);
  pitch_level_y[0]    =  0.0f;
  pitch_level_z[0]    =  0.0f;
  pitch_level_w[0]    =  1.0f;
  pitch_level_r[0]    =  0.0f;
  pitch_level_g[0]    =  1.0f;
  pitch_level_b[0]    =  0.0f;
  pitch_level_a[0]    =  0.9f;

  pitch_level_x[1]    = -0.5f*(PITCH_GAP);
  pitch_level_y[1]    =  0.0f;
  pitch_level_z[1]    =  0.0f;
  pitch_level_w[1]    =  1.0f;
  pitch_level_r[1]    =  0.0f;
  pitch_level_g[1]    =  1.0f;
  pitch_level_b[1]    =  0.0f;
  pitch_level_a[1]    =  0.9f;

  pitch_level_x[2]    =  0.5f*(PITCH_SPAN);
  pitch_level_y[2]    =  0.0f;
  pitch_level_z[2]    =  0.0f;
  pitch_level_w[2]    =  1.0f;
  pitch_level_r[2]    =  0.0f;
  pitch_level_g[2]    =  1.0f;
  pitch_level_b[2]    =  0.0f;
  pitch_level_a[2]    =  0.9f;

  pitch_level_x[3]    =  0.5f*(PITCH_GAP);
  pitch_level_y[3]    =  0.0f;
  pitch_level_z[3]    =  0.0f;
  pitch_level_w[3]    =  1.0f;
  pitch_level_r[3]    =  0.0f;
  pitch_level_g[3]    =  1.0f;
  pitch_level_b[3]    =  0.0f;
  pitch_level_a[3]    =  0.9f;

  for (i = 0; i < pitch_level_points; i++)
  {
    pitch_level_data  [4*i + 0] = pitch_level_x[i];
    pitch_level_data  [4*i + 1] = pitch_level_y[i];
    pitch_level_data  [4*i + 2] = pitch_level_z[i];
    pitch_level_data  [4*i + 3] = pitch_level_w[i];

    pitch_level_colors[4*i + 0] = pitch_level_r[i];
    pitch_level_colors[4*i + 1] = pitch_level_g[i];
    pitch_level_colors[4*i + 2] = pitch_level_b[i];
    pitch_level_colors[4*i + 3] = pitch_level_a[i];
  }

  glGenVertexArrays(1, &pitch_level_data_vao);                                    // Generating glyph VAO...
  glBindVertexArray(pitch_level_data_vao);                                        // Binding glyph VAO...
  glGenBuffers(1, &pitch_level_data_vbo);                                         // Generating glyph VBO...

  glBindBuffer(GL_ARRAY_BUFFER, pitch_level_data_vbo);                            // Binding glyph VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(pitch_level_points),
               pitch_level_data,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_0);                                          // Enabling "layout = 0" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, pitch_level_data_vbo);                            // Binding glyph VBO...
  glVertexAttribPointer(LAYOUT_0, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 0" attribute in vertex shader...

  glGenVertexArrays(1, &pitch_level_colors_vao);                                  // Generating color VAO...
  glBindVertexArray(pitch_level_colors_vao);                                      // Binding color VAO...
  glGenBuffers(1, &pitch_level_colors_vbo);                                       // Generating color VBO...
  glBindBuffer(GL_ARRAY_BUFFER, pitch_level_colors_vbo);                          // Binding color VBO...
  glBufferData(GL_ARRAY_BUFFER,                                                 // Creating and initializing a buffer object's data store...
               4*sizeof(GLfloat)*(pitch_level_points),
               pitch_level_colors,
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(LAYOUT_1);                                          // Enabling "layout = 1" attribute in vertex shader...
  glBindBuffer(GL_ARRAY_BUFFER, pitch_level_colors_vbo);                          // Binding color VBO...
  glVertexAttribPointer(LAYOUT_1, 4, GL_FLOAT, GL_FALSE, 0, 0);                 // Specifying the format for "layout = 1" attribute in vertex shader...

  delete[] pitch_level_data;
  delete[] pitch_level_colors;

  baseline->done();
}

memory_orb::~memory_orb()
{
  // WINGS:
  glDeleteBuffers(1, &wings_data_vbo);                                      // Releasing OpenGL glyph VBO...
  glDeleteBuffers(1, &wings_data_vao);                                      // Releasing OpenGL glyph VAO...
  glDeleteBuffers(1, &wings_colors_vbo);                                    // Releasing OpenGL color VBO...
  glDeleteBuffers(1, &wings_colors_vao);                                    // Releasing OpenGL color VAO...

  delete[] wings_x;
  delete[] wings_y;
  delete[] wings_z;
  delete[] wings_w;
  delete[] wings_r;
  delete[] wings_g;
  delete[] wings_b;
  delete[] wings_a;

  // PITCH LEVEL:
  glDeleteBuffers(1, &pitch_level_data_vbo);                                      // Releasing OpenGL glyph VBO...
  glDeleteBuffers(1, &pitch_level_data_vao);                                      // Releasing OpenGL glyph VAO...
  glDeleteBuffers(1, &pitch_level_colors_vbo);                                    // Releasing OpenGL color VBO...
  glDeleteBuffers(1, &pitch_level_colors_vao);                                    // Releasing OpenGL color VAO...

  delete[] pitch_level_x;
  delete[] pitch_level_y;
  delete[] pitch_level_z;
  delete[] pitch_level_w;
  delete[] pitch_level_r;
  delete[] pitch_level_g;
  delete[] pitch_level_b;
  delete[] pitch_level_a;
}
