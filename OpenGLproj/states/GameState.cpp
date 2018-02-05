#include "GameState.h"

GameState::GameState(StateManager* manager, Platform *platform, EntityManager *em, KeyboardManager *km) : State(manager, platform), em(em), km(km)
{

}

GameState::~GameState()
{

}

bool GameState::eventHandler()
{
	return false;
}

void GameState::update(float dt)
{
	playerHandling();

	for (int i = 0; i < numBlocks; i++)
	{
		obstacles[i]->addZ(blockSpeed*dt);

		if (obstacles[i]->getHighZ() < -90)
		{
			obstacles[i]->changePosition(obstacles[lastBlockIndex]->getHighZ());

			if (lastBlockIndex >= (numBlocks - 1))
			{
				lastBlockIndex = 0;
			}
			else {
				lastBlockIndex += 1;
			}
		}
	}


	
}

void GameState::render()
{

}

void GameState::load()
{
	numHousesPerBlock = 20;
	numBlocks = 5;

	lastBlockIndex = numBlocks - 1;

	distHousetravelled = 0;
	blockWidth = 64.f;
	blockIndex = 0;

	player = em->getNewEntity("plane");

	entities.push_back(player);


	distHousetravelled = 0;
	blockSpeed = 30;

	camera->setPosition(glm::vec3(0, 14, -75), false);
	camera->setLookAtPos(player->getModel()->getMedian(), false);
	camera->setUpVector(glm::vec3(0, 1, 0), false);


	lowX = -48.f;
	highX = 48.f;
	lowZ = -48.f;
	highZ = 48.f;

	xWidth = highX - lowX;
	zWidth = highZ - lowZ;

   
	


	//first position
	float theZLow = -48.f;


	for (int i = 0; i < numBlocks; i++)
	{
		std::vector<Entity*> ev2;
		


		for (int j = 0; j < numHousesPerBlock; j++)
		{
			Entity *e = em->getNewEntity("house");
			e->setScale(glm::vec3(2, 2, 2));
			ev2.push_back(e);

			entities.push_back(e);
		}
		ObstacleBlock *ob = new ObstacleBlock(ev2);
		ob->setXZLowHigh(lowX, highX, lowZ, highZ, xWidth, zWidth);
		ob->changePosition(theZLow);
		obstacles.push_back(ob);

		theZLow = ob->getHighZ();

	}

	player->setPosition(glm::vec3(0, 0, -49), 0);

	
}

void GameState::unload()
{

}



void GameState::playerHandling()
{
	float x = 0, y = 0, z = 0;
	//No per frame update needed
	

	if (km->keyDown("w"))
	{
		z -= 0.2;
		player->moveForward();
		z -= 0.2;
		
	}
	if (km->keyDown("s"))
	{
		z += 0.2;
		player->moveBackward();
	}
	if (km->keyDown("a"))
	{
		x -= 0.2;
		player->strafeLeft();
	}
	if (km->keyDown("d"))
	{
		x += 0.2;
		player->strafeRight();
	}

	glm::vec3 np = glm::vec3(x, y, z);

	//camera->setPosition(np, true);

	//player->setPosition(np, true);


	float rx = 0, rz = 0;

	if (km->keyDown("right"))
	{
		rx -= 0.03;
	}
	if (km->keyDown("left"))
	{
		rx += 0.03;
	}
	if (km->keyDown("up"))
	{
		rz += 0.1;
	}
	if (km->keyDown("down"))
	{
		rz -= 0.1;
	}

	player->setYaw(rx, true);
	player->setRoll(rz, true);
}

void GameState::generateObstaclesPositions()
{
	

	int density = 22;
	for (int i = 0; i < numBlocks; i++)
	{
		placeObstacles(i);
	}
	
}


void GameState::placeObstacles(int block)
{
	float n = zWidth*(float(block) + 1.f);
	
	for (int i = 0; i < numHousesPerBlock; i++)
	{
		float xPos = randFloat(lowX, highX);
		float zPos = randFloat(lowZ + n, highZ + n);

		glm::vec3 v = glm::vec3(xPos, 0, zPos);

		houses[block][i]->setPosition(v, 0);
	}
}

float GameState::randFloat(float fMin, float fMax)
{
	float f = (float)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}