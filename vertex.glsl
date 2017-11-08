#version 130
in mediump vec3 point;
in mediump vec2 texcoord;
in mediump vec3 vector;
uniform mat4 yaw;
uniform mat4 pitch;
uniform mat4 translation;
uniform mat4 projection;
uniform vec3 ray;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform mediump float specular_exponent;
out mediump vec2 UV;
out mediump vec3 normal;
flat out mediump vec3 light;
flat out mediump vec3 Ka;
out mediump vec3 direction;
out mediump vec3 Kd;
flat out mediump vec3 Ks;
flat out mediump float Ns;
void main()
{
  mat4 model = translation * yaw * pitch;
  gl_Position = projection * model * vec4(point, 1);
  UV = texcoord;
  direction = (model * vec4(point, 1)).xyz;
  normal = (model * vec4(vector, 0)).xyz;
  light = ray;
  Ka = ambient;
  Kd = max(0.0, dot(normal, light)) * diffuse;
  Ks = specular;
  Ns = specular_exponent;
}
