#include "ModelManager.h"

ModelManager::ModelManager()
{
	ObjLoader objLoad;

	Texture* testTexture = new Texture();
	testTexture->loadTexture("models/HouseTexture1.png");


	Model *obj = objLoad.loadObj("models/House2.obj");

	
	
	models["house"] = obj;
	textures["house"] = testTexture;
	



	Model *obj3 = objLoad.loadObj("models/militaryplane.obj");
	Texture* planeText = new Texture();
	planeText->loadTexture("models/textures/plane.png");

	models["plane"] = obj3;
	textures["plane"] = planeText;
	




}

ModelManager::~ModelManager()
{

}

Model* ModelManager::getModelByName(std::string s)
{
	return models[s];
}

Texture* ModelManager::getTextureByName(std::string s)
{
	return textures[s];
}