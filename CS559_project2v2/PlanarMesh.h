//Based on "Top.h" in Perry Kivolowitz's Modern GL Example

#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"
#include "Shader.h"

class PlanarMesh: public Object
{
public:
	PlanarMesh();
	void TakeDown();
	// TODO:Intialize needs to be virtual? Initialize different for each Shape?
	bool Initialize(int slices, int stacks); // height will end up as stacks, width will end up as slices
	virtual void Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);

	Shader shader;
	Shader solid_color;
private:
	void BuildNormalVisualizationGeometry();
	std::vector<VertexAttributesPCN> vertex_list;
	typedef Object super;

};