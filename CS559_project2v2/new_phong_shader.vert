// Taken from OpenGL Cookbook, "implementing per-vertex ADS Shading" p55

#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;

out vec3 light_intensity;

struct LightInfo {
	vec4 position; // Light position in eye coords.
	vec3 La; // Ambient light intensity
	vec3 Ld; // Diffuse light intensity
	vec3 Ls; // Specular light intensity
} Light;

//uniform vec4 position;
//uniform vec3 La;
//uniform vec3 Ld;
//uniform vec3 Ls;

//uniform LightInfo Light;

struct MaterialInfo {
	vec3 Ka; // Ambient reflectivity
	vec3 Kd; // Diffuse reflectivity
	vec3 Ks; // Specular reflectivity
	float shininess; // Specular shininess factor
} Material;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float shininess;

//uniform MaterialInfo Material;
uniform mat4 modelview_matrix;
uniform mat3 normal_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp;

void main()
{
	Light.position = vec4(7.0, 10.0, -5.0, 1.0);
	Light.La = vec3(.1, .1, .1);
	Light.Ld = vec3(.5, .5, .5);
	Light.Ls = vec3(1.0f, 1.0f, 1.0f);

	//Material.Ka = vec3(1.0f, 0.0f, 0.0f);
	//Material.Kd = vec3(1.0f, 0.0f, 0.0f);
	//Material.Ks = vec3(1.0f, 0.0f, 0.0f);
	//Material.shininess = 100.0;

	vec3 tnorm = normalize( normal_matrix * vertex_normal);
	vec4 eyeCoords = modelview_matrix * vec4(vertex_position,1.0);
	vec3 s = normalize(vec3(Light.position - eyeCoords));
	vec3 v = normalize(-eyeCoords.xyz);
	vec3 r = reflect( -s, tnorm );
	vec3 ambient = Light.La * Material.Ka;
	float sDotN = max( dot(s,tnorm), 0.0 );
	vec3 diffuse = Light.Ld * Material.Kd * sDotN;
	vec3 spec = vec3(0.0);

	if( sDotN > 0.0 )
		spec = Light.Ls * Material.Ks * pow( max( dot(r,v), 0.0 ), Material.shininess );

	light_intensity = ambient + diffuse + spec;
	gl_Position = mvp * vec4(vertex_position,1.0);
}