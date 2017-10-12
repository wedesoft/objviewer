#version 130
in mediump vec3 point;
in mediump vec2 texcoord;
out mediump vec2 UV;
void main()
{
  gl_Position = vec4(point, 1);
  UV = texcoord;
}
