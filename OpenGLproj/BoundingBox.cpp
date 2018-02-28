#include "BoundingBox.h"

BoundingBox::BoundingBox(glm::vec3 vMin3, glm::vec3 vMax3)
{
	vMin = glm::vec4(vMin3, 1);
	vMax = glm::vec4(vMax3, 1);

	generateVertsAndInds();
}

BoundingBox::~BoundingBox()
{

}

void BoundingBox::transformByMat4(glm::mat4 m)
{
	newVMin = m * vMin;
	newVMax = m * vMax;

	for (int i = 0; i < vertices.size(); i++)
	{
		glm::vec4 v = glm::vec4(vertices[i], 1);
		glm::vec4 newV = m * v;

		newVertices[i] = glm::vec3(newV);
	}

	for (int i = 0; i < faces.size(); i++)
	{
		glm::vec4 n = glm::vec4(faces[i]->getNormal(), 0);

		glm::vec4 newN = m*n;
		newFaces[i]->setNormal(newN);


	}

	for (int i = 0; i < edges.size(); i++)
	{
		glm::vec4 e = glm::vec4(edges[i]->getDirection(), 0);

		glm::vec4 newE = m*e;
		newEdges[i]->setDirection(newE);
	}
}

glm::vec3 BoundingBox::getVMin()
{
	return glm::vec3(newVMin);
}

glm::vec3 BoundingBox::getVMax()
{
	return glm::vec3(newVMax);
}

void BoundingBox::generateVertsAndInds()
{
	glm::vec3 v = glm::vec3(vMax.x, vMin.y, vMin.z);
	glm::vec3 v2 = glm::vec3(vMax.x, vMin.y, vMax.z);
	glm::vec3 v3 = glm::vec3(vMin.x, vMin.y, vMax.z);
	glm::vec3 v4 = glm::vec3(vMin.x, vMin.y, vMin.z);
	glm::vec3 v5 = glm::vec3(vMax.x, vMax.y, vMin.z);
	glm::vec3 v6 = glm::vec3(vMax.x, vMax.y, vMax.z);
	glm::vec3 v7 = glm::vec3(vMin.x, vMax.y, vMax.z);
	glm::vec3 v8 = glm::vec3(vMin.x, vMax.y, vMin.z);

	vertices.push_back(v);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);
	vertices.push_back(v8);

	newVertices.push_back(v);
	newVertices.push_back(v2);
	newVertices.push_back(v3);
	newVertices.push_back(v4);
	newVertices.push_back(v5);
	newVertices.push_back(v6);
	newVertices.push_back(v7);
	newVertices.push_back(v8);


	indices = {4,0,3,4,3,7,2,6,7,2,7,3,1,5,2,5,6,2,0,4,1,4,5,1,4,7,5,7,6,5,0,1,2,0,2,3};

	std::vector<glm::vec3> normals;

	for (int i = 0; i < indices.size(); i+=3)
	{
		Face* f = new Face(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]);
		Face* f2 = new Face(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]);
		faces.push_back(f);
		newFaces.push_back(f2);

		Edge* e1 = new Edge(vertices[indices[i]], vertices[indices[i + 1]]);
		Edge* e2 = new Edge(vertices[indices[i+1]], vertices[indices[i + 2]]);
		Edge* e3 = new Edge(vertices[indices[i+2]], vertices[indices[i]]);

		edges.push_back(e1);
		edges.push_back(e2);
		edges.push_back(e3);


		Edge* ne1 = new Edge(vertices[indices[i]], vertices[indices[i + 1]]);
		Edge* ne2 = new Edge(vertices[indices[i + 1]], vertices[indices[i + 2]]);
		Edge* ne3 = new Edge(vertices[indices[i + 2]], vertices[indices[i]]);

		newEdges.push_back(ne1);
		newEdges.push_back(ne2);
		newEdges.push_back(ne3);


	}

	
	int d = 0;
}


glm::vec3 BoundingBox::getSupport(glm::vec3 dir)
{
	float bestProjection = -99999;
	glm::vec3 bestVert = glm::vec3(-1);

	for (int i = 0; i < newVertices.size(); i++)
	{
		glm::vec3 v = newVertices[i];
		float projection = glm::dot(v, dir);

		if (projection > bestProjection)
		{
			bestProjection = projection;
			bestVert = v;
		}
	}

	return bestVert;
}

Interval BoundingBox::projectOntoAxis(glm::vec3 pAxis)
{

	glm::vec3 minValestPoint;
	glm::vec3 maxValestPoint;


	float minVal = 9999;
	float maxVal = -9999;


	float bDotB = glm::dot(pAxis, pAxis);

	for (int i = 0; i < newVertices.size(); i++)
	{
		float aDotB = glm::dot(newVertices[i], pAxis);

		glm::vec3 newPoint = (aDotB / bDotB) * pAxis;

		float np = newPoint.x + newPoint.y + newPoint.z;

		if (np < minVal)
		{
			minValestPoint = newPoint;
			minVal = np;
		}

		if (np > maxVal)
		{
			maxValestPoint = newPoint;
			maxVal = np;
		}
		
	}

	Interval ival;
	ival.point1 = minValestPoint;
	ival.point2 = maxValestPoint;
	ival.dir = maxValestPoint - minValestPoint;
	ival.minVal = minVal;
	ival.maxVal = maxVal;

	return ival;
}

int BoundingBox::getNumFaces()
{
	return newFaces.size();
}

int BoundingBox::getNumEdges()
{
	return newEdges.size();
}

Face* BoundingBox::getFace(int index)
{
	return newFaces[index];
}

Edge* BoundingBox::getEdge(int index)
{
	return newEdges[index];
}

Interval BoundingBox::getInterval(glm::vec3 pAxis)
{
	float minVal, maxVal;

	minVal = maxVal = glm::dot(pAxis, newVertices[0]);

	for (int i = 1; i < newVertices.size(); i++)
	{
		float val = glm::dot(pAxis, newVertices[i]);

		minVal = std::min(minVal, val);	
		maxVal = std::max(maxVal, val);
	}

	Interval ival;
	ival.minVal = minVal;
	ival.maxVal = maxVal;

	return ival;
}