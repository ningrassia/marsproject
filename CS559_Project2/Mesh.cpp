#include "Mesh.h"

/* A Mesh contains:
*  - vertices
*  - connectivity information
*  - attribute data
*/
Mesh::Mesh()
{

}

Mesh::Mesh(int width, int height, int type/*, vector<double> detail_vector*/)
{

	//we need to find a way to generate vertices so that all triangles
	//share 2 vertices with the next/previous triangle.

	this->mesh_dimensions = vec2(width, height);
	switch(type)
	{
			case FLAT_MESH:
				flatMesh();
				break;
			case SPHERE_MESH:
				sphereMesh();
				break;
			case CYLINDER_MESH:
				cylinderMesh();
				break;
	}

}

void Mesh::flatMesh()
{
	//generate our vertices
	for(int i = 0; i < mesh_dimensions.y; i++)
	{
		for(int j = 0; j < mesh_dimensions.x; j++)
		{
			
		}
	}

	//generate our connectivity! this is the not-fun part!
	
	return;
}

void Mesh::sphereMesh()
{

}

void Mesh::cylinderMesh()
{

}

Mesh::~Mesh(void)
{
}
