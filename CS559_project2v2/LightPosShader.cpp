#include "LightPosShader.h"
#include <glm/glm.hpp>

#define BAD_GL_VALUE GLuint(-1)

LightPosShader::LightPosShader(void)
{
}

void LightPosShader::CustomSetup(const GLfloat * light_pos)
{
		if (this->light_pos_handle != BAD_GL_VALUE)
		glUniform3fv(this->light_pos_handle, 1, light_pos);
	this->GLReturnedError("Shader::CommonSetup - after time_handle");
}

bool LightPosShader::Initialize(char * vertex_shader_file, char * fragment_shader_file)
{
	if(!super::Initialize(vertex_shader_file, fragment_shader_file))
	{
		return false;
	}
	// just get the extra uniform's handle
	glUseProgram(this->program_id);
	this->light_pos_handle = glGetUniformLocation(this->program_id, (const GLchar *) "light_pos");
	glUseProgram(0);

	return !GLReturnedError("LightPosShader::Initialize - on exit");
}

LightPosShader::~LightPosShader(void)
{
}
