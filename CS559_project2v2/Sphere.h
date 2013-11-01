#pragma once

#include "Mesh.h"

class Sphere:public Mesh
{
public:
	Sphere();
	bool Initialize(float radius, int slices, int stacks, glm::vec3 color);
	void BuildNormalVisualizationGeometry();
	void BuildShape(float radius, int slices, int stacks);
	~Sphere();
private:
	typedef Mesh super;
};

