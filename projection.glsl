#version 130
in mediump vec3 point;
uniform mat4 projection;
void main()
{
  gl_Position = projection * vec4(point, 1);
}
