#version 410 core

layout (location = 0) in vec2 text_reference;                                   // Text reference position.
layout (location = 1) in vec2 text_points;                                      // Text points.
out vec2 texture;                                                               // Output texture.
uniform mat4 View_matrix;                                                       // "View_matrix" matrix.
uniform mat4 Projection_matrix;                                                 // "Projection_matrix" matrix.

void main()
{
  gl_Position = Projection_matrix*View_matrix*vec4(text_reference, 0.0 , 1.0);  // Setting points...
  texture = text_points;
}
