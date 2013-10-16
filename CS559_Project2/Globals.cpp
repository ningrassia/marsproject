#include "Globals.h"


Globals::Globals(void)
{
	this->window_size = vec2(1366, 768);
	this->aspect_ratio = (float)(window_size.x / window_size.y);
	this->window_closed = true;

	this->near_plane = 5.0f;
	this->far_plane = 50.0f;
	this->fov = 50.0f;

	this->wireframe_enabled = false;
}