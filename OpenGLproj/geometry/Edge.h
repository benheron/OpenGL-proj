#pragma once
#include <glm/glm.hpp>


class Edge {
public:
	Edge(glm::vec3 vertStart, glm::vec3 vertEnd);
	~Edge();

protected:
	glm::vec3 vertStart;
	glm::vec3 vertEnd;

};