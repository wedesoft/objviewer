#version 130
in mediump vec2 UV;
out mediump vec3 fragColor;
uniform sampler2D map_Kd;
uniform sampler2D map_Ks;
void main()
{
  fragColor = 0.5 * texture(map_Kd, UV).rgb + 0.5 * texture(map_Ks, UV).rgb;
}
