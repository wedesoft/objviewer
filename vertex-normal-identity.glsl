#version 130
in mediump vec3 point;
in mediump vec3 vector;
out mediump vec3 normal;
void main()
{
  gl_Position = vec4(point, 1);
  normal = vector;
}
