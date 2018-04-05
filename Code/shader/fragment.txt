#version 410 core

in  vec4 fragment_color;                                                        // (R, G, B, A) color, from vertex shader.
out vec4 color;                                                                 // The rendered color.

void main(void)
{
  color = fragment_color;                                                       // Assigning "the_color" as OpenGL color...
}
