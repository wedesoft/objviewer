#version 130
flat in mediump vec3 Ks;
out mediump vec3 fragColor;
void main()
{
  fragColor = Ks;
}
