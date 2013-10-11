//Basic shader skeleton taken from the Basic Shader Examples from Perry Kivolowitz
//ADS per-fragment shading taken from OpenGL Cookbook
//Need to provide ambient, diffuse, specular, shininess, light position, and light intensity in uniforms!
//Note to self - inverse of transpose of modelview is the normal matrix!
#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;

out vec3 position;
out vec3 normal;

uniform mat4 modelview_matrix;
uniform mat3 normal_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp;

void main()
{
	normal = normalize( normal_matrix * vertex_normal);
	position = vec3( modelview_matrix * vec4(vertex_position,1.0) );
	gl_Position = mvp * vec4(vertex_position, 1.0);
}
