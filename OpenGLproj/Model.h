#pragma once
#include <vector>
#include <gl/glew.h>
#include <glm/glm.hpp>

class Model {
public:
	Model(std::vector<glm::vec3> vertices, std::vector<glm::vec2> UVs, std::vector<glm::vec3> vertNormals,
		std::vector<unsigned int> vertexIndices, std::vector<unsigned int> uvIndices, std::vector<unsigned int> normalIndices);
	~Model();


	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec2> getUVs();
	std::vector<glm::vec3> getVertNormals();

	std::vector<unsigned int> getVertexIndices();
	std::vector<unsigned int> getUVIndices();
	std::vector<unsigned int> getNormalIndices();

	GLuint getVertexBuffer();
	GLuint getUVBuffer();
	GLuint getNormalBuffer();

	GLuint getIndexBuffer();


protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> UVs;
	std::vector<glm::vec3> vertNormals;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;


	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;

	GLuint indexBuffer;

	glm::vec3 median;
};