/// @file

#version 410 core

in  vec4 color_geom;                                                            // (R, G, B, A) color, from vertex shader.
out vec4 color_frag;                                                            // The rendered color.

/// @function
// Rendering points as smoothed circles:
void main(void)
{
  //float r = 0.0;                                                                // Circle radius.
  //float delta = 0.0;                                                            // Gradient magnitude.
  //float alpha = 1.0;                                                            // Circle border smoothness.
  //vec2 cxy = 2.0 * gl_PointCoord - 1.0;                                         // Circle center.

  //r = dot(cxy, cxy);                                                            // Computing circle radius...
  //delta = fwidth(r);                                                            // Computing gradient magnitude...
  //alpha = 1.0 - smoothstep(1.0 - delta, 1.0 + delta, r);                        // Computing border smoothness...
  //color_frag = alpha*color_geom;                                                // Assigning "color" as OpenGL color...
  color_frag = color_geom;
  //color_frag = vec4(1.0, 1.0, 1.0, 1.0);
}
