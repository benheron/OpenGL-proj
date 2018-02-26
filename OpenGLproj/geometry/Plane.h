#pragma once

#include <glm/glm.hpp>

class Plane {
public:
	Plane();
	~Plane();

private:
	glm::vec3 normal;
	glm::vec3 pointOnPlane;
};