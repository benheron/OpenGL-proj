#include "EntityManager.h"

EntityManager::EntityManager()
{
	mm = new ModelManager();
}

EntityManager::~EntityManager()
{
	delete mm;

	for (int i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}
}

Entity* EntityManager::getNewEntity(std::string ms)
{
	Model* m = mm->getModelByName(ms);
	Texture* t= mm->getTextureByName(ms);
	Entity *e = new Entity();
	e->setModel(m);
	e->setTexture(t);

	entities.push_back(e);

	return e;
}

std::vector<Entity*> EntityManager::getEntities()
{
	return entities;
}