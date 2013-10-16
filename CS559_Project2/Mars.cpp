#include <fstream>
#include <glm/glm.hpp>
#include <assert.h>
#include <iostream>

#include "Mars.h"

using namespace std;
using namespace glm;


Mars::Mars(/*char * filename*/)
{
	color = vec3(0.7f, 0.1f, 0.1f);
	radius = 50.0; //default starting value
	scale_factor = 5.0f; //default starting value

	/* TEMP: File not implemented yet
	//open up our input file!
	ifstream marsfile(filename, ifstream::in);
	//make sure we actually have a file opened!
	if(!marsfile)
	{
		cout << "Could not open mars file " << filename << ". Try again." <<endl;
	} */


	//Need to use the filestream marsfs to set height and width, then create the mesh.
	//Mesh marsMesh;
	int height;
	int width;
	
	//get first two ints from the file to get height and width!
	// TEMP: commented out
	//marsfile >> width;
	//marsfile >> height
	height =0;
	width = 0;

	//create our array of elevation info! 
	//indexing is width + height * (total width of input file)

	// TEMP: Not equal to 0
	double temp_elevation = 0;

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			//marsfile>>temp_elevation;
			elevation_array[j + (i*width)] = (temp_elevation*scale_factor + radius);
		}
	}

	//create a mesh!
	Mesh marsMesh = Mesh(width, height, Mesh::SPHERE_MESH);
	
}


Mars::~Mars(void)
{
}
