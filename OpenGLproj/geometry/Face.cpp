#include "Face.h"

Face::Face(glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3)
{
	vertices.push_back(vert1);
	vertices.push_back(vert2);
	vertices.push_back(vert3);

	generateNormal();
}

Face::Face(std::vector<glm::vec3> vertices) : vertices(vertices)
{
	generateNormal();
}
 
Face::Face(std::vector<glm::vec3> vertices, glm::vec3 normal) : vertices(vertices), normal(normal)
{
}

Face::~Face()
{
}




void Face::generateNormal()
{
	glm::vec3 ba = vertices[1] - vertices[0];
	glm::vec3 ca = vertices[2] - vertices[0];

	normal = glm::cross(ba, ca);
	normal = glm::normalize(normal);
}



glm::vec3 Face::getVertex(int index)
{
	return vertices[index];
}

std::vector<glm::vec3> Face::getVertices()
{
	return vertices;
}

glm::vec3 Face::getNormal()
{
	return normal;
}

void Face::setNormal(glm::vec3 n)
{
	normal = n;
}
