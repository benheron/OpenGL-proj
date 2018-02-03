#pragma once
#include "State.h"
#include "StateManager.h"
#include "../entities/EntityManager.h"
#include "../Entity.h"
#include "../Keyboard.h"
#include "../entities/EntityManager.h"
#include "../Camera.h"



class GameState : public State
{
public:
	GameState(StateManager* manager, Platform *platform, EntityManager* em, KeyboardManager *km);
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


	std::vector<Entity*> getRenderables();

	Camera* getCamera();
	
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

	

	Entity *player;

	EntityManager *em;
	KeyboardManager *km;

	float blockSpeed;


	
};