#version 410 core

in vec2 texture;
out vec4 color;

uniform sampler2D text;
uniform vec3 text_color;

void main()
{
  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texture).r);
  color = vec4(textColor, 1.0) * sampled;
}
