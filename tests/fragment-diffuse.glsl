#version 130
flat in mediump vec3 Kd;
out mediump vec3 fragColor;
void main()
{
  fragColor = Kd;
}
