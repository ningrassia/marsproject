#define _USE_MATH_DEFINES

#include "Mars.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>


using namespace std;

Mars::Mars(void)
{
}

bool Mars::Initialize(char * filename, float radius, float max_offset, vec3 color)
{
	vector<float> mars_radius;
	int slices;
	int stacks;
	float temp_offset;

	ifstream myfile(filename);
	if(!myfile.is_open())
	{
		cout << "file " << filename << " could not be opened." << endl;
		return false;
	}
	// first two values are slices, then stacks.
	myfile >> slices;
	myfile >> stacks;
	for(int i = 0; i < (slices * stacks); i++)
	{
		myfile >>temp_offset;
		mars_radius.push_back(radius + (temp_offset * max_offset));
	}

	BuildMesh(slices, stacks, color);
	BuildShape(mars_radius, slices, stacks);
	super::CalcNormals(slices, stacks);
	super::BuildNormalVisualizationGeometry();
	if(!Mesh::Initialize())
	{
		return false;
	}
	return true;
}

void Mars::BuildShape(vector<float> mars_radius, int slices, int stacks)
{
		// Loop through EACH INDEX.
	for(int i = 0; i < (slices * stacks); i++)
	{
		int curr_slice = i % slices;
		int curr_stack = i / slices;

		//right now we're not adding the fan at top/bottom so may cause problems for texturing?
		float v_angle = -(float(M_PI) / 2.0f) + (float(curr_stack) * ((float(M_PI) / float(stacks - 1))));
		float h_angle = (2.0f * float(M_PI) * (float(curr_slice) / float(slices - 1)));

		this->vertex_list[i].position.x = mars_radius[i] * cos(v_angle) * sin(h_angle);
		this->vertex_list[i].position.y = mars_radius[i] * sin(v_angle);
		this->vertex_list[i].position.z = mars_radius[i] * cos(v_angle) * cos(h_angle);
	}
}


Mars::~Mars(void)
{
}
