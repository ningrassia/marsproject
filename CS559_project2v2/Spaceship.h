#pragma once

#include <glm/glm.hpp>
#include "Sphere.h"
#include "Cylinder.h"

using namespace glm;

class Spaceship
{
public:
	Spaceship(void);
	bool Initialize(int sliceDetail, int stackDetail, vec3 color);
	void Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void EnableNormals(bool dn);
	void TakeDown();
	~Spaceship(void);

private:
	Sphere sphere;
	Cylinder cylinder;
};

