#version 300 es
in mediump vec3 point;
void main()
{
  gl_Position = vec4(point, 1);
}
