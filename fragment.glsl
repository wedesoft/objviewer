#version 130
in mediump vec2 UV;
in mediump vec3 normal;
flat in mediump vec3 Ka;
flat in mediump vec3 light;
in mediump vec3 direction;
in mediump vec3 Kd;
flat in mediump vec3 Ks;
out mediump vec3 fragColor;
uniform sampler2D tex;
void main()
{
  mediump float specular = max(0.0, dot(normalize(direction), reflect(light, normal)));
  fragColor = texture(tex, UV).rgb * (Ka + Kd) + Ks * pow(specular, 1);
}
