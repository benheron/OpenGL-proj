#pragma once
#include <vector>
#include "../Entity.h"
#include "../ModelManager.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Entity* getNewEntity(std::string ms);

	std::vector<Entity*> getEntities();
private:

	std::vector<Entity*> entities;
	ModelManager* mm;
};