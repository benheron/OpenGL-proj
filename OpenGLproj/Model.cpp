#include "Model.h"

Model::Model(std::vector<glm::vec3> vertices, std::vector<glm::vec2> UVs, std::vector<glm::vec3> vertNormals, 
	std::vector<unsigned int> vertexIndices, std::vector<unsigned int> uvIndices, std::vector<unsigned int> normalIndices) :
	vertices(vertices), UVs(UVs), vertNormals(vertNormals), vertexIndices(vertexIndices), uvIndices(uvIndices), normalIndices(normalIndices)
{

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertNormals.size() * sizeof(glm::vec3), &vertNormals[0], GL_STATIC_DRAW);


	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);


	//Create IBO
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);




}

Model::~Model()
{
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

std::vector<glm::vec3> Model::getVertices()
{
	return vertices;
}

std::vector<glm::vec2> Model::getUVs()
{
	return UVs;
}
std::vector<glm::vec3> Model::getVertNormals()
{
	return vertNormals;
}

std::vector<unsigned int> Model::getVertexIndices()
{
	return vertexIndices;
}
std::vector<unsigned int> Model::getUVIndices()
{
	return uvIndices;
}
std::vector<unsigned int> Model::getNormalIndices()
{
	return normalIndices;
}

GLuint Model::getVertexBuffer()
{
	return vertexBuffer;
}

GLuint Model::getUVBuffer()
{
	return uvBuffer;
}

GLuint Model::getNormalBuffer()
{
	return normalBuffer;
}

GLuint Model::getIndexBuffer()
{
	return indexBuffer;
}