#pragma once
#include "Model.h"
#include "Texture.h"
#include "ObjLoader.h"
#include <vector>
#include <unordered_map>

class ModelManager {
public:
	ModelManager();
	~ModelManager();

	Model* getModelByName(std::string s);
	Texture* getTextureByName(std::string s);

protected:

	std::unordered_map<std::string, Model*> models;
	std::unordered_map<std::string, Texture*> textures;

//	std::vector<Model*> models;


};