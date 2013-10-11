#include <fstream>
#include "Mars.h"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;


Mars::Mars(fstream marsfs)
{
	color = vec3(0.7f, 0.1f, 0.1f);
	radius = 50.0; //default starting value
	scale_factor = 5.0f; //default starting value


	//Need to use the filestream marsfs to set height and width, then create the mesh.
	/*
	Mesh marsMesh;
	int height;
	int width;
	*/
}


Mars::~Mars(void)
{
}
