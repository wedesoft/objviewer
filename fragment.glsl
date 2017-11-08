#version 130
in mediump vec2 UV;
uniform sampler2D tex;
in mediump vec3 normal;
flat in mediump vec3 Ka;
in mediump vec3 Kd;
flat in mediump vec3 Ks;
flat in mediump float Ns;
flat in mediump vec3 light;
out mediump vec3 fragColor;
in mediump vec3 direction;
void main()
{
  mediump float specular = max(0.0, dot(normalize(direction), reflect(light, normal)));
  if (specular != 0.0)
    specular = pow(specular, Ns);
  fragColor = texture(tex, UV).rgb * (Ka + Kd) + Ks * specular;
}
