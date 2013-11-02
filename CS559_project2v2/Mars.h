#pragma once
#include "sphere.h"
#include <string>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Mars :
	public Sphere
{
public:
	Mars(void);
	bool Initialize(char * filename, float radius, float max_offset, vec3 color);
	void ReadFile(char * filename, vector<float> mars_radius, int &slices, int &stacks);
	void BuildShape(vector<float> mars_radius, int slices, int stacks);
	~Mars(void);

private:
	typedef Sphere super;
};

