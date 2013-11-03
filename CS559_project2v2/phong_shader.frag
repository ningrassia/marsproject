//Taken from Perry Kivolowitz's Modern GL Example

#version 400

layout (location = 0) out vec4 FragColor;

flat in vec3 color;
in vec3 position;
in vec3 normal;
in vec3 light_pos;
const float shininess = 100.0f;

vec3 ads( )
{
  vec3 n = normal;

  if (!gl_FrontFacing)
	n = -n;

  vec3 s = normalize(light_pos - position);
  vec3 v = normalize(-position);
  vec3 r = reflect(-s, n);
  float s_dot_n = max(dot(s, n), 0.0);

  return color * s_dot_n + (s_dot_n > 0 ? color * pow(max(dot(r, v), 0.0), shininess) : vec3(0.0));
}

void main()
{
	FragColor = vec4(ads(), 1.0);
}
