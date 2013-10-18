#include "PlanarMesh.h"

/* A Mesh contains:
*  - vertices
*  - connectivity information
*  - attribute data
*/
PlanarMesh::PlanarMesh()
{

}

PlanarMesh::PlanarMesh(int width, int height, int type/*, vector<double> detail_vector*/)
{

	//we need to find a way to generate vertices so that all triangles
	//share 2 vertices with the next/previous triangle.

	this->mesh_dimensions = vec2(width, height);

}


void PlanarMesh::Initialize()
{
	//generate our vertices
	for(int i = 0; i < mesh_dimensions.y; i++)
	{
		for(int j = 0; j < mesh_dimensions.x; j++)
		{
			vertexInfo info = {vec3(j, i, 0), vec3(0.7f, 0.2f, 0.2f)};
			vertex_list.push_back(info);
		}
	}

	for(int i = 0; i < vertex_list.size(); i++)
	{
		vec2 vertex_location = vec2(i % (int)mesh_dimensions.x, i % (int)mesh_dimensions.y);
		// TODO: cases for upper/lower/left/right edges
		// TODO: write function to get surrounding points
	}
	
	return;
}

PlanarMesh::~PlanarMesh(void)
{
}