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
}

void GameState::render()
{

}

void GameState::load()
{
	player = em->getNewEntity("plane");

	entities.push_back(player);

	blockSpeed = 5;

	camera->setPosition(glm::vec3(0, 4, -3), false);
	camera->setLookAtPos(glm::vec3(0, 0, 0), false);
	camera->setUpVector(glm::vec3(0, 1, 0), false);

	
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
	}
	if (km->keyDown("s"))
	{
		z += 0.2;
	}
	if (km->keyDown("a"))
	{
		x -= 0.2;
	}
	if (km->keyDown("d"))
	{
		x += 0.2;
	}

	glm::vec3 np = glm::vec3(x, y, z);

	player->setPosition(np, true);


	float rx = 0, rz = 0;

	if (km->keyDown("right"))
	{
		rx += 0.1;
	}
	if (km->keyDown("left"))
	{
		rx -= 0.1;
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


