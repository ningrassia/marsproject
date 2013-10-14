#pragma once

#include <fstream>
#include "Mesh.h"

class Mars
{
public:
	Mars(char* filename);
	~Mars(void);
private:
	vec3 color;
	Mesh marsMesh;
	int height;
	int width;
	double radius;
	double temp_elevation;
	float scale_factor; //factor to scale the mars data by
	vector<double> elevation_array;
	ifstream marsfile;
};

