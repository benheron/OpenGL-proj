#include "GameState.h"
#include "GameOverState.h"

GameState::GameState(StateManager* manager, Platform *platform, EntityManager *em, KeyboardManager *km, TextImageManager *tim) : State(manager, platform), em(em), km(km), tim(tim)
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
	player->update(dt);
	if (!gameEnd)
	{
		score += 20 * dt;

		playerHandling(dt);

		for (int i = 0; i < numBlocks; i++)
		{


			if (obstacles[i]->collide(player->getBoundingBox()))
			{

				gameEnd = true;


			}


			obstacles[i]->update(dt);
			obstacles[i]->addZ(blockSpeed*dt);



			if (obstacles[i]->getHighZ() < -90)
			{
				obstacles[i]->changePosition(obstacles[lastBlockIndex]->getHighZ());
				obstacles[i]->update(dt);

				if (lastBlockIndex >= (numBlocks - 1))
				{
					lastBlockIndex = 0;
					firstBlockIndex = 1;
				}
				else {
					lastBlockIndex += 1;

					firstBlockIndex++;
					if (firstBlockIndex >= (numBlocks - 1))
					{
						firstBlockIndex = 0;
					}
				}
			}
		}



		int curScore = int(score);

		std::string str = std::to_string(curScore);

		scoreInt->changeTextEnd(str);
	}


	if (gameEnd)
	{
		stateManager->changeState(new GameOverState(stateManager, platform, em, km, tim, score));
	}

}


void GameState::load()
{
	gameEnd = false;

	numHousesPerBlock = 20;
	numBlocks = 5;

	firstBlockIndex = 0;
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

	//camera->setPosition(glm::vec3(0, 0, 0), false);
	//camera->setLookAtPos(glm::vec3(0, 0, 4), false);
	//camera->setUpVector(glm::vec3(0, 1, 0), false);


	lowX = -48.f;
	highX = 48.f;
	lowZ = 16.f;
	highZ = 96.f;

	xWidth = highX - lowX;
	zWidth = highZ - lowZ;

   
	


	//first position
	float theZLow = lowZ;


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





	//uiload
	score = 0;
	scoreWord = new Text(glm::vec3(10.f, 550.f, 0), "arial", 32, "Score:", tim);

	

	scoreInt = new Text(glm::vec3(100.f, 550.f, 0), "arial", 32, "0000000", tim);

	stateText.push_back(scoreWord);
	stateText.push_back(scoreInt);
	
}

void GameState::unload()
{
	for (int i = 0; i < obstacles.size(); i++)
	{
		delete obstacles[i];
	}

	delete scoreInt;
	delete scoreWord;
}



void GameState::playerHandling(float dt)
{
	bool m = false;
	bool t = false;

	if (km->keyDown("a"))
	{
		player->moveLeft(dt);
		m = true;
	}

	if (km->keyDown("d"))
	{
		player->moveRight(dt);
		m = true;
	}


	if (km->keyDown("left"))
	{
		player->rotateFurtherLeft(dt);
		m = true;
		t = true;
	}

	if (km->keyDown("right"))
	{
		player->rotateFurtherRight(dt);
		m = true;
		t = true;
	}
	

	player->setMoving(m);
	player->setTilting(t);

	float rr = player->getRoll();

	float rotSpeed = 2*dt;

	if (!m)
	{
		if (rr < -0.02)
		{
			rr += rotSpeed;
		}
		else if (rr > 0.02) {
			rr -= rotSpeed;
		}
		else {
			rr = 0;
		}
	}

	player->setRoll(rr, false);
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


