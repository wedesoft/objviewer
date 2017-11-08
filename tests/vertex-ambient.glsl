#version 130
uniform vec3 ambient;
in mediump vec3 point;
flat out mediump vec3 Ka;
void main()
{
  gl_Position = vec4(point, 1);
  Ka = ambient;
}
