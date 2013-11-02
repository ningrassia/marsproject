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
	virtual void Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);

	Shader shader;
	Shader solid_color;
	~Mesh();
protected:
	virtual void BuildShape();
	virtual void BuildNormalVisualizationGeometry();
	glm::vec3 CrossProduct(int index, int vertex_position1, int vertex_position2);
	virtual void CalcNormals(int slices, int stacks);
	std::vector<VertexAttributesPCN> vertex_list;
private:
	typedef Object super;

};