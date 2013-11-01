#include "Spaceship.h"

Spaceship::Spaceship(void)
{
	
}

// Initialize() initializes a sphere and cylinder
bool Spaceship::Initialize(int sliceDetail, int stackDetail, vec3 color)
{
	if(!sphere.Initialize(1, sliceDetail, stackDetail, color))
	{
		return false;
	}

	if(!cylinder.Initialize(1, 1, sliceDetail, stackDetail, color))
	{
		return false;
	}
	
	return true;
}



void Spaceship::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	mat4 mv = translate(modelview, vec3(0.0f, -3.0f, 0.0f));

	sphere.Draw(projection, mv, size, time);

	mv = scale(mv, vec3(1.0f, 4.0f, 1.0f));
	cylinder.Draw(projection, mv, size, time);

	mv = translate(mv, vec3(0.0f, 1.0f, 0.0f));
	mv = scale(mv, vec3(1.0f, .5f, 1.0f));
	sphere.Draw(projection, mv, size, time);

	
}

void Spaceship::TakeDown()
{
	cylinder.TakeDown();
	sphere.TakeDown();
}

void Spaceship::EnableNormals(bool dn)
{
	sphere.EnableNormals(dn);
	cylinder.EnableNormals(dn);
}

Spaceship::~Spaceship()
{
	
}
