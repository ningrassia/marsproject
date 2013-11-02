#pragma once

#include <glm/glm.hpp>
#include "Mesh.h"

class Cylinder: public Mesh
{
public:
	Cylinder();
	bool Initialize(float base_radius, float top_radius, float height, int slices, int stacks, glm::vec3 color);
	void BuildNormalVisualizationGeometry();
	void BuildShape(float base_radius, float top_radius, float height, int slices, int stacks);
	~Cylinder();
private:
	typedef Mesh super;
};

