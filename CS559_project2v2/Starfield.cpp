#define _USE_MATH_DEFINES

#include "Starfield.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>

using namespace std;
using namespace glm;



Starfield::Starfield(void)
{
	//don't need anything special here.
}

double Starfield::toRadian(double d)
{
	return (double)(d / 180.0f * M_PI);
}


bool Starfield::Initialize(double hither, double yon, int stars)
{
	// CHECK FOR ERRORS!
	if(this->GLReturnedError("Starfield::Initialize - on entry")) 
	{
		return false;
	}

	if(!super::Initialize())
	{
		return false;
	}

	//check our inputs for sanity!
	if((hither < 0) || (yon < hither) || (stars < 0))
	{
		return false;
	}

	//make a bunch of points 

	//seed the RNG - constant for testing!
	#ifdef _DEBUG
	srand(1);
	#else
	srand((unsigned int)(time(NULL)));
	#endif

	//generate points for the stars, and place them in the arrays!
	for(int i = 0; i < stars; i++)
	{
		double radius = (rand() % ((int)floor(yon-hither))) + hither; //generate a radius from between hither and yon
		double vert_angle = rand() % 180; //generate 2 angles - now we have a spherical position!
		double horiz_angle = rand() % 360;
		//create a new vertex with cartesian coordinates from our generated angles/radius
		VertexAttributesP vertex = VertexAttributesP(
			vec3((radius * sin(toRadian(vert_angle)) * cos(toRadian(horiz_angle))),
			(radius*sin(toRadian(vert_angle)) * sin(toRadian(horiz_angle))),
			(radius * cos(toRadian(vert_angle)))));
		this->vertex_list.push_back(vertex);
		//since we'll just draw these vertices as points, we don't care about connectivity
		//and just push each index on when we create a vertex
		this->vertex_indices.push_back(i);
	}

	//set up our handles
	if (!this->PostGLInitialize(&this->vertex_array_handle, &this->vertex_coordinate_handle, this->vertex_list.size() * sizeof(VertexAttributesPCN), &this->vertex_list[0]))
	{
		return false;
	}

	if(this->GLReturnedError("Starfield::Initialize - after PostGLInit"))
	{
		return false;
	}

	//set up our layout
	glVertexAttribPointer(0,3,GL_DOUBLE, GL_FALSE, sizeof(VertexAttributesP), (GLvoid *) 0);
	//activate our vertex stuff
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if(this->GLReturnedError("Starfield::Initialize - after attribute pointer"))
	{
		return false;
	}

	if(!this->solid_color.Initialize("solid_shader.vert","solid_shader.frag"))
	{
		return false;
	}

	if(this->GLReturnedError("Starfield::Initialize - after shader init"))
	{
		return false;
	}

	return true;
}

void Starfield::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, const float time)
{
	if(this->GLReturnedError("Starfield::Draw - on entry"))
	{
		return;
	}

	glEnable(GL_DEPTH_TEST);

	mat4 mvp = projection * modelview;
	mat3 nm = inverse(transpose(mat3(modelview)));

	solid_color.Use();
	this->GLReturnedError("Starfield::Draw - after use");
	solid_color.CommonSetup(time, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm));
	this->GLReturnedError("Starfield::Draw - after common setup");
	glBindVertexArray(this->vertex_array_handle);
	glPointSize(4.0f);
	glDrawElements(GL_POINTS, this->vertex_indices.size(), GL_UNSIGNED_INT, &this->vertex_indices[0]);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Starfield::TakeDown()
{
	this->vertex_list.clear();	// TODO: Check for memory leaks!!
	this->solid_color.TakeDown();
	super::TakeDown();
}
