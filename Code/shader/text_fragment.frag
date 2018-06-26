#version 410 core

in vec2 text_coordinates_vertex;
in vec4 text_color_vertex;
out vec4 text_color_fragment;
uniform sampler2D text;

void main()
{
  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texture_coordinates_vertex).r);
  text_color_fragment = sampled*vec4(text_color_vertex);
}
