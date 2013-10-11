//Basic shader skeleton taken from the Basic Shader Examples from Perry Kivolowitz
//ADS per-fragment shading taken from OpenGL Cookbook
//Need to provide ambient, diffuse, specular, shininess, light position, and light intensity in uniforms!
//we also need to implement object color

#version 400

layout (location = 0) out vec4 FragColor;

in vec3 position;
in vec3 normal;

uniform vec4 light_position;
uniform vec3 light_intensity;
uniform vec3 diffuse;
uniform vec3 ambient;
uniform vec3 specular;
uniform float shininess; //the exponent in the specular equation!

vec3 ads( )
{
	vec3 n = normalize( normal );
	vec3 s = normalize( vec3(light_position) - position );
	vec3 v = normalize(vec3(-position));
	vec3 r = reflect( -s, n );
	return LightIntensity * ( ambient + diffuse * max( dot(s, n), 0.0 ) + specular * pow( max( dot(r,v), 0.0 ), shininess ) );
}

void main()
{
	FragColor = vec4(ads(), 1.0);
}
