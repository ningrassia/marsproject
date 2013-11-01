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

bool Sphere::Initialize(float radius, int slices, int stacks, vec3 color)
{
	// Initialize a flat mesh - Mesh::Inizialize(slices, stacks)
	// Modify the points of that flat mesh by:
	// - x = sin(PI * (curr_stack / stacks)) * cos(2PI * (curr_slice / slices))
	// - y = sin(PI * (curr_stack / stacks)) * sin(2PI * (curr_slice / slices))
	// - z = cos(PI * (curr_stack / stacks))
	// Keep in mind, these are all with radius of 1 - need to scale everything by radius
	// Make sure everything is centered around the origin or it'll be hard to manage

	BuildMesh(slices, stacks, color);
	BuildShape(radius, slices, stacks);
	if(!super::Initialize())
	{
		return false;
	}

	return true;
}

void Sphere::BuildShape(float radius, int slices, int stacks)
{

	// Loop through EACH INDEX.
	for(int i = 0; i < (slices * stacks); i++)
	{
		int curr_slice = i % slices;
		int curr_stack = i / slices;

		//right now we're not adding the fan at top/bottom so may cause problems for texturing?
		float v_angle = -(float(M_PI) / 2.0f) + (float(curr_stack) * (float(M_PI) / float(stacks-1)));
		float h_angle = (2.0f * float(M_PI) * (float(curr_slice) / float(slices)));

		this->vertex_list[i].position.x = radius * cos(v_angle) * sin(h_angle);
		this->vertex_list[i].position.y = radius * sin(v_angle);
		this->vertex_list[i].position.z = radius * cos(v_angle) * cos(h_angle);
		
		// Update normals
		this->vertex_list[i].normal.x = cos(v_angle) * sin(h_angle);
		this->vertex_list[i].normal.y = sin(v_angle);
		this->vertex_list[i].normal.z = cos(v_angle) * cos(h_angle);
		
		// Add more points to vertex_indices for connectivity between the two sides after wrapping
		// Check if on far right edge - then connect with left edge
		if(curr_slice == slices - 1 && (curr_stack < stacks - 1)) 
		{
			this->vertex_indices.push_back(i);
			this->vertex_indices.push_back(i - slices + 1);
			this->vertex_indices.push_back(i + slices);

			this->vertex_indices.push_back(i - slices + 1);
			this->vertex_indices.push_back(i + 1);
			this->vertex_indices.push_back(i + slices);
		}
	}
}

Sphere::~Sphere()
{
}
