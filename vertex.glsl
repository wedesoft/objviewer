#version 130
in mediump vec3 point;
in mediump vec2 texcoord;
in mediump vec3 vector;
uniform mat4 translation;
uniform mat4 projection;
out mediump vec2 UV;
void main()
{
  gl_Position = projection * translation * vec4(point, 1);
  UV = texcoord;
}
