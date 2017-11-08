#version 130
uniform vec3 diffuse;
in mediump vec3 point;
flat out mediump vec3 Kd;
void main()
{
  gl_Position = vec4(point, 1);
  Kd = diffuse;
}
