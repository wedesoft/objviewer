#version 130
in mediump vec3 normal;
out mediump vec3 fragColor;
void main()
{
  fragColor = normal;
}
