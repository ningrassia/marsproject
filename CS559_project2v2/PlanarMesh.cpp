//Based on "Top.cpp" in Perry Kovolovitz's Modern GL Example
#include "PlanarMesh.h"

#include <iostream>

using namespace std;
using namespace glm;

PlanarMesh::PlanarMesh(void)
{
	// TODO:Color stuff later
}

// Sets up the list of normals
void PlanarMesh::BuildNormalVisualizationGeometry()
{
	const float normal_scalar = 0.125f;
	for (int j = 1; j <= 3; ++j)
	{
		// Point of normal ON plane
		this->normal_vertices.push_back(VertexAttributesP(this->vertex_list[this->vertex_indices[this->vertex_indices.size() - j]].position));
		// point of normal AWAY FROM plane
		this->normal_vertices.push_back(VertexAttributesP(this->vertex_list[this->vertex_indices[this->vertex_indices.size() - j]].position + this->vertex_list[this->vertex_indices[this->vertex_indices.size() - j]].normal * normal_scalar));
		// Push point on plane first, then away
		this->normal_indices.push_back(this->normal_vertices.size() - 2);
		this->normal_indices.push_back(this->normal_vertices.size() - 1);
	}
}

bool PlanarMesh::Initialize(int height, int width)
{
	// CHECK FOR ERRORS!
	if(this->GLReturnedError("PlanarMesh::Initialize - on entry")) 
	{
		return false;
	}

	if(!super::Initialize())
	{
		return false;
	}
	
	// Sanity check - this should never happen
	if(height <= 1 || width <= 1) 
	{
		return false;
	}

	/*
	* This makes vertices and connectivity for a FLAT, RECTANGULAR MESH
	* Possibly used when drawing a sphere, then positions modified
	*
	* 1.	Looping through the height and width, just make points
	* 2.	Go through the points and generate connectivity using a function that finds
	*		adjacent points
	* 3.	Connect a triangle ( /| ) if there is a point to the left, and connect a triangle ( |/ ) if there is a point to the right
	*		(Do not loop through the bottom row of points - already connected to points above it)
	* 4.	Generate normals for each point using a function, e.g. CalcNormal(vec3 position)
	* 5.	Push those normals onto their own list
	*/

	// When doing a flat mesh, all normals are straight on the Z axis - different for sphere and stuff
	const vec3 n = vec3(0.0f, 0.0f, 1.0f);

	// Here we just make the points and push them on our vertex_list
	for(int h = 0; h < height; h++)
	{
		for(int w = 0; w < width; w++)
		{
			VertexAttributesPCN vertex;
			vertex.position = vec3((float)w, (float)h, 0.0f);
			vertex.normal = n;
			vertex.color = vec3(1.0f, 0.0f, 0.0f); // TEMPORARY COLOR!
			this->vertex_list.push_back(vertex);
		}
	}

	// Here we generate connectivity for the triangles
	// We don't need to run on the bottom row because of how we generate the connectivity
	// Fill out the vertex_indices list
	for(int h = 0; h < (height-1); h++)
	{
		for(int w = 0; w < width; w++)
		{
			int index = (w + h * width); //each row is offset by "width" vertices.
			//Check for left, then generate left-style tri
			if((index % width) > 0) // If left vertex exists
			{
				// CONNECT LEFT TRIANGLE
				this->vertex_indices.push_back(index);
				this->vertex_indices.push_back(index + width);
				this->vertex_indices.push_back(index + (width - 1));

				//this->BuildNormalVisualizationGeometry();
			}

			//Check for right, then generate right-style tri
			if((index % width) < (width - 1))	// If right vertex exists
			{
				// CONNECT RIGHT TRIANGLE
				this->vertex_indices.push_back(index);
				this->vertex_indices.push_back(index + 1);
				this->vertex_indices.push_back(index + width);

				//this->BuildNormalVisualizationGeometry();
			}
		}
	}

	// Phong shader for mesh
	if (!this->PostGLInitialize(&this->vertex_array_handle, &this->vertex_coordinate_handle, this->vertex_list.size() * sizeof(VertexAttributesPCN), &this->vertex_list[0]))
	{
		return false;
	}

	if(this->GLReturnedError("PlanarMesh::Initialize - after PostGLInit"))
	{
		return false;
	}

	// Put in values for shader's LAYOUT variables
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) (sizeof(vec3) * 2));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) (sizeof(vec3) * 1));
	// Activate them
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//free our buffer and vertex array!
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if(this->GLReturnedError("PlanarMesh::Initialize - after attribute poniter"))
	{
		return false;
	}

	//// Solid Shader for normals
	//if (this->normal_vertices.size() > 0)
	//{
	//	if (!this->PostGLInitialize(&this->normal_array_handle, &this->normal_coordinate_handle, this->normal_vertices.size() * sizeof(VertexAttributesP), &this->normal_vertices[0]))
	//		return false;

	//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesP), (GLvoid *) 0);
	//	glEnableVertexAttribArray(0);
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//	glBindVertexArray(0);
	//}

	if (!this->shader.Initialize("phong_shader.vert", "phong_shader.frag"))
	{
		return false;
	}

	if(this->GLReturnedError("PlanarMesh::Initialize - after shader Init"))
	{
		return false;
	}

	//if (!this->solid_color.Initialize("solid_shader.vert", "solid_shader.frag"))
	//{
	//	return false;
	//}

	return true;
}

void PlanarMesh::TakeDown()
{
	this->vertex_list.clear();	// TODO: Check for memory leaks!!
	this->shader.TakeDown();
	super::TakeDown();
}

void PlanarMesh::Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, const float time)
{
	if(this->GLReturnedError("PlanarMesh::Draw - on entry"))
	{
		return;
	}

	glEnable(GL_DEPTH_TEST);

	mat4 mvp = projection * modelview;
	mat3 nm = inverse(transpose(mat3(modelview)));
	
	shader.Use();
	this->GLReturnedError("PlanarMesh::Draw - after use");
	shader.CommonSetup(time, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm));
	this->GLReturnedError("PlanarMesh::Draw - after common setup");
	glBindVertexArray(this->vertex_array_handle);
	glDrawElements(GL_TRIANGLES, this->vertex_indices.size(), GL_UNSIGNED_INT, &this->vertex_indices[0]);
	glBindVertexArray(0);
	glUseProgram(0);
}
