#version 410 core

in  vec4 fragment_color;                                                        // (R, G, B, A) color, from vertex shader.
out vec4 color;                                                                 // The rendered color.

void main(void)
{
  float r = 0.0;
  float delta = 0.0;
  float alpha = 1.0;
  vec2 cxy = 2.0 * gl_PointCoord - 1.0;
  r = dot(cxy, cxy);

  delta = fwidth(r);
  alpha = 1.0 - smoothstep(1.0 - delta, 1.0 + delta, r);

  color = fragment_color * alpha;                                               // Assigning "the_color" as OpenGL color...
}
