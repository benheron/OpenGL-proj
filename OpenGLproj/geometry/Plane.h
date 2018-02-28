#pragma once

#include <glm/glm.hpp>

class Plane {
public:
	Plane();
	~Plane();

	glm::vec3 getNormal();

private:
	float a, b, c, d; //where the plane equation is ax + by + cz + d;



	glm::vec3 normal;
	glm::vec3 pointOnPlane;
};