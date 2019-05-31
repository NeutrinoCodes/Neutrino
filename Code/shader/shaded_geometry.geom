/// @file

#version 410 core

layout (points) in;                                                             // Input points.
layout (triangle_strip, max_vertices = 6) out;                                  // Output points.

in VS_OUT
{
  vec4 color_PC;
  vec4 point_PR;
  vec4 point_PU;
  vec4 point_PL;
  vec4 point_PD;
  vec4 normal_RU;
  vec4 normal_LD;
} gs_in[];

out vec4 color_PC_geom;

void main()
{
  vec4 light = vec4(0.0, 0.0, 1.0, 1.0);
  light.xyz = normalize(light.xyz);
  float diffusion_RU = clamp(dot(light.xyz, gs_in[0].normal_RU.xyz), 0.2, 1.0);
  float diffusion_LD = clamp(dot(light.xyz, gs_in[0].normal_RU.xyz), 0.2, 1.0);

  // RIGHT-UP triangle:
  color_PC_geom = gs_in[0].color_PC;
  color_PC_geom.xyz = diffusion_RU*color_PC_geom.xyz;
  gl_Position = gs_in[0].point_PU;
  EmitVertex();
  color_PC_geom = gs_in[0].color_PC;
  //color_PC_geom.xyz = diffusion_RU*color_PC_geom.xyz;
  color_PC_geom.xyz = vec3(1.0, 1.0, 1.0);                                      // EZOR 31JUN2019: smooth color test.
  gl_Position = gs_in[0].point_PR;
  EmitVertex();
  color_PC_geom = gs_in[0].color_PC;
  color_PC_geom.xyz = diffusion_RU*color_PC_geom.xyz;
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();

  // LEFT-DOWN triangle:
  color_PC_geom = gs_in[0].color_PC;
  color_PC_geom.xyz = diffusion_LD*color_PC_geom.xyz;
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();
  color_PC_geom = gs_in[0].color_PC;
  color_PC_geom.xyz = diffusion_LD*color_PC_geom.xyz;
  gl_Position = gs_in[0].point_PL;
  EmitVertex();
  color_PC_geom = gs_in[0].color_PC;
  color_PC_geom.xyz = diffusion_LD*color_PC_geom.xyz;
  gl_Position = gs_in[0].point_PD;
  EmitVertex();

  EndPrimitive();
}
