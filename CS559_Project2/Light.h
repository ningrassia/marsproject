#pragma once

#include <glm/glm.hpp>

using namespace glm;

class Light
{
public:

	//just combine all light info into a struct!
	typedef struct lightInfo{
	vec4 light_position;
	vec3 light_intensity;
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
	float shininess; //the exponent in the specular equation!
	};

	lightInfo light_info;

	Light();
	Light(lightInfo light_info);
	~Light(void);

private:
};

