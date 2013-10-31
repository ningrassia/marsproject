#pragma once

#include "Mesh.h"

class Cylinder: public Mesh
{
public:
	Cylinder();
	bool Initialize(float radius, float height, int slices, int stacks, vec3 color);
	void BuildShape(float radius, float height, int slices, int stacks);
	~Cylinder();
private:
	typedef Mesh super;
};

