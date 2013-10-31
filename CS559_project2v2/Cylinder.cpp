#include "Cylinder.h"

using namespace std;
using namespace glm;

Cylinder::Cylinder()
{
}

bool Cylinder::Initialize(float radius, float height, int slices, int stacks) 
{
	// Initialize a flat mesh - Mesh::Inizialize(slices, stacks + 2)
	//  - stacks + 2 because we need an extra stack on top and bottom to form the flat bits of the cylinder
	// Modify the points of that flat mesh by:
	// - 'wrapping' them around to make the cylinder
	// - bringing the top and bottom together to form the flat sides
	// Make sure everything is centered around the origin or it'll be hard to manage

	BuildMesh(slices, stacks);
	BuildShape(radius, height, slices, stacks);
	if(!super::Initialize())
	{
		return false;
	}

}

void Cylinder::BuildShape(float radius, float height, int slices, int stacks)
{
	mat4 mv(1.0);

	// Loop through EACH INDEX.
	for(int i = 0; i < (slices * stacks); i++)
	{
		int curr_slice = i % slices;
		int curr_stack = i / slices;

		this->vertex_list[i].position.x = 0;
		this->vertex_list[i].position.y = curr_stack * (height / (float)stacks);
		this->vertex_list[i].position.z = radius;

		// Multiply the position by the modelview matrix to apply it to the current mv position
		this->vertex_list[i].position = vec3(vec4(this->vertex_list[i].position, 1) * mv);

		mv = rotate(mv, -float(360.0f / slices), vec3(0.0f, 1.0f, 0.0f));
		glLoadMatrixf(value_ptr(mv));
	}
}

Cylinder::~Cylinder()
{

}
