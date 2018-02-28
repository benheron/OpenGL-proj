#include "Edge.h"

Edge::Edge(glm::vec3 vertStart, glm::vec3 vertEnd) : vertStart(vertStart), vertEnd(vertEnd)
{
	dir = vertEnd - vertStart;
}

Edge::~Edge()
{

}

glm::vec3 Edge::getDirection()
{
	return dir;
}

void Edge::setDirection(glm::vec3 d)
{
	dir = d;
}