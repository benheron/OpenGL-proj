#pragma once
#include <vector>
#include <gl/glew.h>
#include <glm/glm.hpp>

class Model {
public:
	Model(std::vector<glm::vec3> vertices, std::vector<glm::vec2> UVs, std::vector<glm::vec3> vertNormals,
		std::vector<unsigned int> vertexIndices, float width, float height, float depth, glm::vec3 medianPos);
	~Model();


	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec2> getUVs();
	std::vector<glm::vec3> getVertNormals();

	std::vector<unsigned int> getVertexIndices();

	float getWidth();
	float getHeight();
	float getDepth();

	glm::vec3 getMedian();


	GLuint getVertexBuffer();
	GLuint getUVBuffer();
	GLuint getNormalBuffer();

	GLuint getIndexBuffer();


protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> UVs;
	std::vector<glm::vec3> vertNormals;
	std::vector<unsigned int> vertexIndices;


	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;

	GLuint indexBuffer;

	glm::vec3 median;

	float width, height, depth;
};