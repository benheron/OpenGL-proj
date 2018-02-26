#include "BoundingBox.h"

BoundingBox::BoundingBox(glm::vec3 vMin3, glm::vec3 vMax3)
{
	vMin = glm::vec4(vMin3, 1);
	vMax = glm::vec4(vMax3, 1);
}

BoundingBox::~BoundingBox()
{

}

void BoundingBox::transformByMat4(glm::mat4 m)
{
	newVMin = m * vMin;
	newVMax = m * vMax;
}

glm::vec3 BoundingBox::getVMin()
{
	return glm::vec3(newVMin);
}

glm::vec3 BoundingBox::getVMax()
{
	return glm::vec3(newVMax);
}