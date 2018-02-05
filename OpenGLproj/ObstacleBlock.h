#pragma once
#include "entities/EntityManager.h"


class ObstacleBlock
{
public:
	ObstacleBlock(std::vector<Entity*> blockObstacles);
	~ObstacleBlock();

	void setXZLowHigh(float xLow, float xHigh, float zLow, float zHigh, float widthX, float widthZ);

	void generateObstacles(EntityManager *em);

	void changePosition(float zPos);

	void addZ(float speeddt);

	float getHighZ();

	glm::vec3 pos;
private:
	float lowX, highX, lowZ, highZ;
	float xWidth, zWidth;


	float randFloat(float fMin, float fMax);

	std::vector<Entity*> blockObstacles;

};