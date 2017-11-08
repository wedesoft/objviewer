#version 130
flat in mediump vec3 Ks;
flat in mediump float Ns;
out mediump vec3 fragColor;
void main()
{
  fragColor = pow(Ks, vec3(Ns, Ns, Ns));
}
