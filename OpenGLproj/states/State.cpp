#include "State.h"

State::State(StateManager* stateManager, Platform* platform)
	:stateManager(stateManager), platform(platform), active(false)
{
	camera = new Camera(glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0));
	loaded = false;
}

void State::startLoading()
{
	active = true;
	if (!loaded)
	{
		load();
		loaded = true;
	}
}

void State::startUnloading()
{
	active = false;
	unload();
}





std::vector<Entity*> State::getRenderables()
{
	return entities;
}

std::vector<Text*> State::getStateText()
{
	return stateText;
}

Camera *State::getCamera()
{
	return camera;
}