#version 130
in mediump vec2 UV;
out mediump vec3 fragColor;
uniform sampler2D map_Kd;
void main()
{
  fragColor = texture(map_Kd, UV).rgb;
}
