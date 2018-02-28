#pragma once

#include <glm/glm.hpp>
#include <vector>

class Face {
public:
	Face(glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3);
	Face(std::vector<glm::vec3> vertices);
	Face(std::vector<glm::vec3> vertices, glm::vec3 normal);
	~Face();

	glm::vec3 getVertex(int index);
	std::vector<glm::vec3> getVertices();
	glm::vec3 getNormal();

	void setNormal(glm::vec3 n);

protected:

	void generateNormal();

	std::vector<glm::vec3> vertices;
	glm::vec3 normal;
	
};