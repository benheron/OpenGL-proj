#pragma once
#include <glm/glm.hpp>


class Edge {
public:
	Edge(glm::vec3 vertStart, glm::vec3 vertEnd);
	~Edge();


	glm::vec3 getDirection();
	void setDirection(glm::vec3 dir);

protected:

	glm::vec3 dir;

	glm::vec3 vertStart;
	glm::vec3 vertEnd;

};