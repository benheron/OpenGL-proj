#pragma once
#include "State.h"
#include "StateManager.h"
#include "../entities/EntityManager.h"
#include "../Entity.h"
#include "../Keyboard.h"
#include "../entities/EntityManager.h"
#include "../text/Text.h"
#include "../Camera.h"
#include "../ObstacleBlock.h"




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

	/**
	@brief Render any sprites relevant to the state
	*/
	void render();


	//std::vector<Entity*> getRenderables();

	//std::vector<Entity*> getUIEntities();

	
protected:

	/**
	@brief Loads this State.
	*/
	virtual void load();

	/**
	@brief Unloads this State.
	*/
	virtual void unload();


	void playerHandling();


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


	int lastBlockIndex;

	float lowX, lowZ, highX, highZ;
	float xWidth, zWidth;

	Text *scoreInt;
	Text *scoreWord;

	float score;
};