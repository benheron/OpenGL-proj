#include "GameOverState.h"




GameOverState::GameOverState(StateManager* manager, Platform *platform, EntityManager* em, KeyboardManager *km, TextImageManager *tim, int score) 
	: State(manager, platform), em(em), km(km), tim(tim), score(score)
{

}

GameOverState::~GameOverState()
{

}

bool GameOverState::eventHandler()
{
	return false;
}

void GameOverState::update(float dt)
{
	if (km->keyDown("space"))
	{
		stateManager->changeState(new GameState(stateManager, platform, em, km, tim));
	}
}

void GameOverState::load()
{
	glm::vec2 halfWinSize = platform->getWindowSize() / glm::vec2(2, 2);
	std::string str = std::to_string(score);
	glm::vec2 scorePos = halfWinSize + glm::vec2(0, 50);



	Text* score = new Text(glm::vec3(scorePos, 0), "arial", 32, str, tim);
	stateText.push_back(score);

	tryAgain = new Text(glm::vec3(halfWinSize,0), "arial", 32, "Press Space to try again", tim);
	stateText.push_back(tryAgain);

	
}

void GameOverState::unload()
{
	delete scoreText;
	delete tryAgain;
	
}