#version 410 core

layout (location = 0) in vec4 text_coordinates;                                 // vec2(position coordinates), vec2(texture coordinates).
out vec2 texture_coordinates;                                                   // Output texture coordinates.
uniform mat4 View_matrix;                                                       // "View_matrix" matrix.
uniform mat4 Projection_matrix;                                                 // "Projection_matrix" matrix.

void main()
{
  gl_Position = Projection_matrix*View_matrix*vec4(text_coordinates.xy, 0.0 , 1.0);  // Setting points...
  texture_coordinates = text_coordinates.zw;
}
