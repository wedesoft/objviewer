#version 130
flat in mediump vec3 Ka;
out mediump vec3 fragColor;
void main()
{
  fragColor = Ka;
}
