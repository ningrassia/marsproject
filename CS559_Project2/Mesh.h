#pragma once

#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;

class Mesh
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

	Mesh();
	Mesh(int height, int width, int type/*, vector<double> detail_vector*/);
	~Mesh(void);

private:
	vector<vertexInfo> vertexList;
	vector<vec3> connectivityList;
	vec2 mesh_dimensions;

	void flatMesh();
	void sphereMesh();
	void cylinderMesh();

};

