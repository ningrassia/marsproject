#pragma once

#include "Mesh.h"

class Cylinder: public Mesh
{
public:
	Cylinder();
	bool Initialize(float radius, float height, int slices, int stacks);
	//virtual void Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	~Cylinder(void);
};

