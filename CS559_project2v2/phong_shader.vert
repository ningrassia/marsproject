//Taken from Perry Kivolowitz's Modern GL Example

#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec3 vertex_color;

uniform mat4 mvp;
uniform mat4 modelview_matrix;
uniform mat3 normal_matrix;
uniform vec3 light_pos;

flat out vec3 color;
out vec3 normal;
out vec3 position;
out vec3 light_pos;

void main()
{
	color = vertex_color;
	normal = normalize(normal_matrix * vertex_normal);
	position = vec3(modelview_matrix * vec4(vertex_position,1.0));
	light_pos = vec3(modelview_matrix * vec4(light_pos, 1.0));
	gl_Position = mvp * vec4(vertex_position, 1.0);
}
