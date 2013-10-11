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
		
	Mesh(int height, int width, int type);
	~Mesh(void);

private:
	vector<vertexInfo> vertexList;
	static const int FLAT_MESH;
	static const int SPHERE_MESH;
	static const int CYLINDER_MESH;
};

