#pragma once
#include "Object.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Starfield : public Object
{
public:
	Starfield(void);
	void TakeDown();
	bool Initialize(double inner_radius, double depth, int stars);
	virtual void Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, const float time, glm::vec3 light_pos = glm::vec3(0.0f, 0.0f, 0.0f));

	Shader solid_color;

private:

	// Utility function for conversion from degree to radians
	double toRadian(double d);

	std::vector<VertexAttributesP> vertex_list;
	typedef Object super;
};

