#version 130
in mediump vec3 point;
in mediump vec2 texcoord;
in mediump vec3 vector;
uniform mat4 yaw;
uniform mat4 pitch;
uniform mat4 translation;
uniform mat4 projection;
out mediump vec2 UV;
void main()
{
  mat4 model = translation * yaw * pitch;
  gl_Position = projection * model * vec4(point, 1);
  UV = texcoord;
}
