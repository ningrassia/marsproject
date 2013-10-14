#pragma once
//Shader class taken from OGLTTA example
//Also uses code from OpenGL 4.0 Shading Language Cookbook by David Wolff.

#include <Gl/glew.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include <sstream>
#include <iostream>

using namespace std;

class Shader
{
public:
	Shader();
	void TakeDown();
	void Use();
	bool Initialize(char * vertex_shader_file, char * fragment_shader_file);

	GLuint modelview_matrix_handle;
	GLuint projection_matrix_handle;

	GLuint vertex_shader_id;
	GLuint fragment_shader_id;
	GLuint program_id;
	bool LoadShader(const char * file_name, GLuint shader_id);
	stringstream GetShaderLog(GLuint shader_id);

private:
	bool CheckGLErrors();
};

