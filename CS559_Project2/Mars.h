#pragma once

#include <fstream>
#include "Mesh.h"

class Mars
{
public:
	Mars(fstream marsfs);
	~Mars(void);
private:
	static const vec3 color;
	Mesh marsMesh;
	int height;
	int width;
	double radius;
	float scale_factor; //factor to scale the mars data by
};

