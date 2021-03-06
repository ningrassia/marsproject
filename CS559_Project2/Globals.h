#pragma once
#include <glm/glm.hpp>
#include <vector>

using namespace glm;

class Globals
{
public:
	Globals();
	glm::ivec2 window_size;
	float aspect_ratio;
	bool window_closed;

	float near_plane, far_plane, fov;

	bool wireframe_enabled;
	
	std::vector<std::string> onscreen_text;
};

