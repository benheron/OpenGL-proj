#include "ObstacleBlock.h"

ObstacleBlock::ObstacleBlock(std::vector<Entity*> blockObstacles) : blockObstacles(blockObstacles)
{

}

ObstacleBlock::~ObstacleBlock()
{

}

void ObstacleBlock::setXZLowHigh(float xLow, float xHigh, float zLow, float zHigh, float widthX, float widthZ)
{
	lowX = xLow;
	highX = xHigh;
	lowZ = zLow;
	highZ = zHigh;
	xWidth = widthX;
	zWidth = widthZ;
}

void ObstacleBlock::changePosition(float zPos)
{
	//float n = zWidth*(float(block) + 1.f);
	
	
	lowZ = zPos;
	highZ = zPos + zWidth;
	

	for (int i = 0; i < blockObstacles.size(); i++)
	{
		float xPos = randFloat(lowX, highX);
		float zPos = randFloat(lowZ, highZ);

		glm::vec3 v = glm::vec3(xPos, 0, zPos);

		blockObstacles[i]->setPosition(v, 0);
	}
}

void ObstacleBlock::addZ(float speeddt)
{
	glm::vec3 v = glm::vec3(0, 0, -speeddt);
	for (int i = 0; i < blockObstacles.size(); i++)
	{
		blockObstacles[i]->setPosition(v, 1);
	}
	lowZ -= speeddt;
	highZ -= speeddt;

}

float ObstacleBlock::randFloat(float fMin, float fMax)
{
	float f = (float)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

float ObstacleBlock::getHighZ()
{
	return highZ;
}

void ObstacleBlock::generateObstacles(EntityManager *em)
{

}