#pragma once
#include "StateManager.h"
#include "../entities/EntityManager.h"
#include "../Keyboard.h"
#include "../text/Text.h"
#include "../Camera.h"
#include "../ObstacleBlock.h"
#include "../Collision.h"

class GameOverState;

class GameState : public State
{
public:
	GameState(StateManager* manager, Platform *platform, EntityManager* em, KeyboardManager *km, TextImageManager *tim);
	virtual ~GameState();

	/**
	@brief Handles any events such as keyboard/mouse input.

	@return true to exit, false to continue.
	*/
	bool eventHandler();

	/**
	@brief Update any internal values.

	@param dt - delta time.
	*/
	void update(float dt);

	
protected:

	/**
	@brief Loads this State.
	*/
	virtual void load();

	/**
	@brief Unloads this State.
	*/
	virtual void unload();


	void playerHandling(float dt);


	void generateObstaclesPositions();

	void placeObstacles(int block);

	float randFloat(float fMin, float fMax);
	
	std::vector<std::vector<Entity*>> houses;

	std::vector<ObstacleBlock*> obstacles;

	Entity *player;

	EntityManager *em;
	KeyboardManager *km;
	TextImageManager *tim;

	float blockSpeed;

	int numHousesPerBlock;
	int numBlocks;


	float distHousetravelled;
	float blockWidth;
	int blockIndex;

	int firstBlockIndex;
	int lastBlockIndex;

	float lowX, lowZ, highX, highZ;
	float xWidth, zWidth;

	Text *scoreInt;
	Text *scoreWord;

	float score;

	bool gameEnd;

	
};