#version 410 core

layout (location = 0) in vec4 text_coordinates;                                 // vec2(position coordinates), vec2(texture coordinates).
out vec2 text_coordinates_vertex;                                               // Output texture coordinates (for fragment shader).
out vec4 text_color_vertex;                                                     // Output color RGBA (for fragment shader).
uniform mat4 View_matrix;                                                       // "View_matrix" matrix.
uniform mat4 Projection_matrix;                                                 // "Projection_matrix" matrix.
uniform vec4 text_color;                                                        // Text color (RGBA).

void main()
{
  vec4 point = vec4(text_coordinates.xy, 0.0 , 1.0);                            // Text texture coordinates...

  gl_Position = Projection_matrix*View_matrix*point;                            // Setting points...
  text_coordinates_vertex = text_coordinates.zw;                                // Forwarding variable to the fragment shader...
  text_color_vertex = text_color;                                               // Forwarding variable to the fragment shader...
}
