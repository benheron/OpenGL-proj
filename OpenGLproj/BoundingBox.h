#pragma once

#include <glm/glm.hpp>

class BoundingBox
{
public:
	BoundingBox(glm::vec3 vMin3, glm::vec3 vMax3);
	~BoundingBox();

	void transformByMat4(glm::mat4 m);

	glm::vec3 getVMin();
	glm::vec3 getVMax();

private:
	glm::vec4 vMin;
	glm::vec4 vMax;

	glm::vec4 newVMin;
	glm::vec4 newVMax;

};