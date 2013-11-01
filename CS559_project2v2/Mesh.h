//Based on "Top.h" in Perry Kivolowitz's Modern GL Example

#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"
#include "Shader.h"

class Mesh: public Object
{
public:
	Mesh();
	void TakeDown();
	void BuildMesh(int slices, int stacks, glm::vec3 color); // height will end up as stacks, width will end up as slices
	bool Initialize();
	virtual void BuildShape();
	virtual void Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);

	Shader shader;
	Shader solid_color;
	~Mesh();
protected:
	std::vector<VertexAttributesPCN> vertex_list;
private:
	void BuildNormalVisualizationGeometry();
	typedef Object super;

};