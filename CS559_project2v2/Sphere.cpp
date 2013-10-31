// Method of producing sphere points from http://stackoverflow.com/questions/4081898/procedurally-generate-a-sphere-mesh

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <glm/glm.hpp>
#include "Sphere.h"

using namespace glm;
using namespace std;

Sphere::Sphere()
{
}

bool Sphere::Initialize(float radius, int slices, int stacks)
{
	// Initialize a flat mesh - Mesh::Inizialize(slices, stacks)
	// Modify the points of that flat mesh by:
	// - x = sin(PI * (curr_stack / stacks)) * cos(2PI * (curr_slice / slices))
	// - y = sin(PI * (curr_stack / stacks)) * sin(2PI * (curr_slice / slices))
	// - z = cos(PI * (curr_stack / stacks))
	// Keep in mind, these are all with radius of 1 - need to scale everything by radius
	// Make sure everything is centered around the origin or it'll be hard to manage

	BuildMesh(slices, stacks);
	BuildShape(radius, slices, stacks);
	if(!super::Initialize())
	{
		return false;
	}
}

void Sphere::BuildShape(float radius, int slices, int stacks)
{
	mat4 mv(1.0);
	//mv = translate(mv, vec3(0.0, 0.0f, -7.0f));
	//glLoadMatrixf(value_ptr(mv));

	// Loop through EACH INDEX.
	for(int i = 0; i < (slices * stacks); i++)
	{
		int curr_slice = i % slices;
		int curr_stack = i / slices;

		this->vertex_list[i].position.x = 0;
		// y will not change yet
		this->vertex_list[i].position.z = radius;

		this->vertex_list[i].position = vec3(vec4(this->vertex_list[i].position, 1) * mv);

		mv = rotate(mv, -float(360.0f / slices), vec3(0.0f, 1.0f, 0.0f));
		glLoadMatrixf(value_ptr(mv));
		
		//this->vertex_list[i].position.x = radius * (sin(M_PI * (curr_stack / float(stacks))) * cos(2.0 * M_PI * (curr_slice / float(slices))));
		//this->vertex_list[i].position.y = radius * (cos(M_PI * (curr_stack / stacks)));
		//this->vertex_list[i].position.z = radius * (sin(M_PI * (curr_stack / stacks)) * sin(2.0 * M_PI * (curr_slice / slices)));
	
		//this->vertex_list[i].position = vec3(vec4(this->vertex_list[i].position, 1) * mv);
	}
}

Sphere::~Sphere()
{
}
