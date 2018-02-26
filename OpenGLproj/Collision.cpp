#include "Collision.h"

bool Collision::boxBoxCollision(BoundingBox *a, BoundingBox* b)
{
	glm::vec3 aMin = a->getVMin();
	glm::vec3 aMax = a->getVMax();

	glm::vec3 bMin = b->getVMin();
	glm::vec3 bMax = b->getVMax();

	if (aMax.x > bMin.x &&
		aMin.x < bMax.x &&
		aMax.y > bMin.y &&
		aMin.y < bMax.y &&
		aMax.z > bMin.z &&
		aMin.z < bMax.z)
	{
		return true;
	}

	return false;



	/*return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
		(aMin.y <= bMax.y && aMax.y >= bMin.y) &&
		(aMin.z <= bMax.z && aMax.z >= bMin.z);*/
}