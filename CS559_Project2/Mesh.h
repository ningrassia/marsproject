#pragma once

#include <glm/glm.hpp>

using namespace glm;

class Mesh
{
public:

	typedef struct vertexInfo{
		vec3 position;
		//add more vertex information here!
	};
	Mesh(int height, int width);
	~Mesh(void);
};

