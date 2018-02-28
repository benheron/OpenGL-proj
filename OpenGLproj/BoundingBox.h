#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "geometry/Face.h"
#include "geometry/Edge.h"
#include <algorithm>

struct Interval
{
	glm::vec3 point1;
	glm::vec3 point2;

	glm::vec3 dir;

	float minVal;
	float maxVal;
};


class BoundingBox
{
public:
	BoundingBox(glm::vec3 vMin3, glm::vec3 vMax3);
	~BoundingBox();

	void transformByMat4(glm::mat4 m);

	glm::vec3 getVMin();
	glm::vec3 getVMax();


	glm::vec3 getSupport(glm::vec3 dir);

	int getNumFaces();
	int getNumEdges();


	Edge* getEdge(int index);

	Face* getFace(int index);

	Interval projectOntoAxis(glm::vec3 pAxis);


	Interval getInterval(glm::vec3 pAxis);
	

private:

	void generateVertsAndInds();

	glm::vec4 vMin;
	glm::vec4 vMax;

	glm::vec4 newVMin;
	glm::vec4 newVMax;

	std::vector<glm::vec3> vertices;
	std::vector<int> indices;
	std::vector<Face*> faces;
	std::vector<Edge*> edges;




	std::vector<glm::vec3> newVertices;
	std::vector<Face*> newFaces;
	std::vector<Edge*> newEdges;
};