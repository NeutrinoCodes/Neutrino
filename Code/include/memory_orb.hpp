/// @file

#ifndef memory_orb_hpp
#define memory_orb_hpp

  #include "neutrino.hpp"

  #define   SCALE             0.02f

  #define   WINGS_SPAN        SCALE*30.0f
  #define   WINGS_GAP         SCALE*10.0f
  #define   WINGS_HEIGHT      SCALE*3.0f

  #define   PITCH_SPAN        SCALE*20.0f
  #define   PITCH_GAP         SCALE*10.0f
  #define   PITCH_HEIGHT      SCALE*10.0f

  class memory_orb
  {
    private:
      neutrino*           baseline;                                             // Neutrino baseline.

    public:
      // WINGS:
      GLfloat*            wings_x;
      GLfloat*            wings_y;
      GLfloat*            wings_z;
      GLfloat*            wings_w;

      GLfloat*            wings_r;
      GLfloat*            wings_g;
      GLfloat*            wings_b;
      GLfloat*            wings_a;

      GLfloat*            wings_data;
      GLfloat*            wings_colors;

      GLuint              wings_data_vao;
      GLuint              wings_colors_vao;
      GLuint              wings_data_vbo;
      GLuint              wings_colors_vbo;

      GLint               wings_points;

      // PITCH LEVEL:
      GLfloat*            pitch_level_x;
      GLfloat*            pitch_level_y;
      GLfloat*            pitch_level_z;
      GLfloat*            pitch_level_w;

      GLfloat*            pitch_level_r;
      GLfloat*            pitch_level_g;
      GLfloat*            pitch_level_b;
      GLfloat*            pitch_level_a;

      GLfloat*            pitch_level_data;
      GLfloat*            pitch_level_colors;

      GLuint              pitch_level_data_vao;
      GLuint              pitch_level_colors_vao;
      GLuint              pitch_level_data_vbo;
      GLuint              pitch_level_colors_vbo;

      GLint               pitch_level_points;

                          memory_orb();

      void                init          (
                                          neutrino*   loc_baseline
                                        );

                          ~memory_orb();

  };

#endif
