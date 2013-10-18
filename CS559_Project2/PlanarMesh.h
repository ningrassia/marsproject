#pragma once

#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;

class PlanarMesh
{
public:

	vec2 mesh_dimensions;

	typedef struct
	{
		vec3 position;
		vec3 color;
		//maybe material stuff but later.
	}vertexInfo;	
	static const int FLAT_MESH = 0;
	static const int SPHERE_MESH = 1;
	static const int CYLINDER_MESH = 2;
	
	enum direction {
		up,
		right,
		down,
		left,
		upleft,
		upright,
		downright,
		downleft
	};

	PlanarMesh();
	PlanarMesh(int height, int width, int type/*, vector<double> detail_vector*/);
	void Initialize();
	~PlanarMesh(void);

private:
	vector<vertexInfo> vertex_list;
	vector<vec3> triangle_list;
	bool OutOfBounds(int index, direction dir);

	vector<int> FindAdjacentVertices(int index);

};

