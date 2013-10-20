#include <iostream>

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

	// generate out triangles
	for(int i = 0; i < vertex_list.size(); i++)
	{
		// Get the 9 adjacent points
		vector<int> adjacent_vertices = FindAdjacentVertices(i);

		// Connect two traingles /| to the left and |/ to the right
		// Do not connect /| if L is out of bounds, left edge
		// Do not connect |/ if R is out of bounds, right edge
		// Treat top edge normally and skip bottom edge

		if(adjacent_vertices[down] != -1) {
			if(adjacent_vertices[left] != -1) {
				triangle_list.push_back(vec3(i, adjacent_vertices[down], adjacent_vertices[downleft]));
			}

			if(adjacent_vertices[right] != -1) {
				triangle_list.push_back(vec3(i, adjacent_vertices[right], adjacent_vertices[down]));
			}
		}
	}
	
	return;
}

vector<int> PlanarMesh::FindAdjacentVertices(int index)
{
	vector<int> adj_indices;

	// adj_indices has 8 indixes, starting at UL corner, clockwise to L
	for(int h = -1; h < 2; h++) {
		for(int v = -1; v < 2; v++) {
			// UL
			if(OutOfBounds(index, upleft)) { adj_indices.push_back(-1); } 
			else { adj_indices.push_back(index - mesh_dimensions.x - 1); }
			// U
			if(OutOfBounds(index, up)) { adj_indices.push_back(-1); }
			else { adj_indices.push_back(index - mesh_dimensions.x); }
			// UR
			if(OutOfBounds(index, upright)) { adj_indices.push_back(-1); }
			else { adj_indices.push_back(index - mesh_dimensions.x + 1); }
			// R
			if(OutOfBounds(index, right)) { adj_indices.push_back(-1); }
			else { adj_indices.push_back(index + 1); }
			// DR
			if(OutOfBounds(index, downright)) { adj_indices.push_back(-1); }
			else { adj_indices.push_back(index + mesh_dimensions.x + 1); }
			// D
			if(OutOfBounds(index, down)) { adj_indices.push_back(-1); }
			else { adj_indices.push_back(index + mesh_dimensions.x); }
			// DL
			if(OutOfBounds(index, downleft)) { adj_indices.push_back(-1); }
			else { adj_indices.push_back(index + mesh_dimensions.x - 1); }
			// L
			if(OutOfBounds(index, left)) { adj_indices.push_back(-1); }
			else { adj_indices.push_back(index - 1); }
		}
	}
	return adj_indices;
}

bool PlanarMesh::OutOfBounds(int index, direction dir)
{
	// TODO: ONLY L AND R ARE NECESSARY
	// REWRITE
	bool oob = false;

	switch(dir) {
		case upleft:
			// Check L and then U
			if(index % (int)mesh_dimensions.x == 0 || index / (int)mesh_dimensions.y == 0) {
				oob = true;
			}
			break;
		case up:
			// check U
			if(index / (int)mesh_dimensions.y == 0) {
				oob = true;
			}
			break;
		case upright:
			// check R and then U
			if(index % (int)mesh_dimensions.x == mesh_dimensions.x - 1 || index / (int)mesh_dimensions.y == 0) {
				oob = true;
			}
			break;
		case right:
			// check R
			if(index % (int)mesh_dimensions.x == mesh_dimensions.x - 1) {
				oob = true;
			}
			break;
		case downright:
			// check R and then D
			if(index % (int)mesh_dimensions.x == mesh_dimensions.x - 1 || index / (int)mesh_dimensions.y == mesh_dimensions.y - 1) {
				oob = true;
			}
			break;
		case down:
			// check D
			if(index / (int)mesh_dimensions.y == mesh_dimensions.y - 1) {
				oob = true;
			}
			break;
		case downleft:
			// check L and then D
			if(index % (int)mesh_dimensions.x == 0 || index / (int)mesh_dimensions.y == mesh_dimensions.y - 1) {
				oob = true;
			}
			break;
		case left:
			// check L
			if(index % (int)mesh_dimensions.x == 0) {
				oob = true;
			}
			break;
		default:
			cout << "invalid direction sent into PlanarMesh::IsOutOfBounds" << endl;
	}
	return oob;
}


PlanarMesh::~PlanarMesh(void)
{
}
