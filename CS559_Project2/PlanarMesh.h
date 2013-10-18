#pragma once

#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;

class PlanarMesh
{
public:

	typedef struct vertexInfo
	{
		vec3 position;
		vec3 color;
		//maybe material stuff but later.
	};
	
	static const int FLAT_MESH = 0;
	static const int SPHERE_MESH = 1;
	static const int CYLINDER_MESH = 2;

	PlanarMesh();
	PlanarMesh(int height, int width, int type/*, vector<double> detail_vector*/);
	~PlanarMesh(void);

private:
	vector<vertexInfo> vertex_list;
	vector<vec3> triangle_list;
	vec2 mesh_dimensions;

	void Initialize();

};

