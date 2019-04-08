/// @file

#version 410 core

in  vec4 color_PC_geom;                                                         // (R, G, B, A) color, from vertex shader.
out vec4 color_PC_frag;                                                         // The rendered color.

//uniform sampler2D tex0;
/// @function
// Rendering points as smoothed circles:
void main(void)
{
  float r;                                                                      // Circle radius.
  float delta;                                                                  // Gradient magnitude.
  float alpha;                                                                  // Circle border smoothness.
  vec2 cxy = 2.0 * gl_PointCoord - 1.0;                                         // Circle center.

  r = 0.1*dot(cxy, cxy);                                                        // Computing circle radius...
  delta = fwidth(r);                                                            // Computing gradient magnitude...
  alpha = 1.0 - smoothstep(1.0 - delta, 1.0 + delta, r);                        // Computing border smoothness...
  //alpha = smoothstep(3.0, 0.0, r);
  color_PC_frag = alpha*color_PC_geom;                                                // Assigning "color" as OpenGL color...
  //color_frag = color_geom;
  //color_PC_frag = vec4(1.0, 0.0, 0.0, 1.0);
}
