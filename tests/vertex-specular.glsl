#version 130
uniform vec3 specular;
uniform mediump float specular_exponent;
in mediump vec3 point;
flat out mediump vec3 Ks;
flat out mediump float Ns;
void main()
{
  gl_Position = vec4(point, 1);
  Ks = specular;
  Ns = specular_exponent;
}
