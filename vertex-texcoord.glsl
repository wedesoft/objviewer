#version 130
layout(location = 0) in mediump vec3 point;
layout(location = 1) in mediump vec2 texcoord;
out mediump vec2 UV;
void main()
{
  gl_Position = vec4(point, 1);
  UV = texcoord;
}
