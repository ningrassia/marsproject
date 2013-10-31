#pragma once

#include "Mesh.h"

class Sphere:public Mesh
{
public:
	Sphere();
	bool Initialize(float radius, int slices, int stacks);
	void BuildShape(float radius, int slices, int stacks);
	~Sphere();
private:
	typedef Mesh super;
};

