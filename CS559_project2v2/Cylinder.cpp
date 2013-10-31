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

	//if(!flatMesh.Initialize(slices, stacks))
	//{
		return false;
	//}

}


Cylinder::~Cylinder(void)
{
}
