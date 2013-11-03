#pragma once
#include "shader.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class LightPosShader :
	public Shader
{
public:
	LightPosShader(void);
	bool Initialize(char * vertex_shader_file, char * fragment_shader_file);
	void CustomSetup(const GLfloat * light_pos);
	~LightPosShader(void);
	GLuint light_pos_handle;
private:
	typedef Shader super;
};

