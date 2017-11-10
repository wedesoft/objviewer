#version 130
in mediump vec2 UV;
uniform sampler2D map_Kd;
uniform sampler2D map_Ks;
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
  fragColor = texture(map_Kd, UV).rgb * (Ka + Kd) + texture(map_Ks, UV).rgb * Ks * specular;
}
