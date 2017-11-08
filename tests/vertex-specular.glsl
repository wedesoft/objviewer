#version 130
uniform vec3 specular;
in mediump vec3 point;
flat out mediump vec3 Ks;
void main()
{
  gl_Position = vec4(point, 1);
  Ks = specular;
}
