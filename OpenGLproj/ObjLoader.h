#pragma once
#include <string>
#include "Model.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream> 

#include <map>

struct FaceTuple {
	unsigned short vertexIndex;
	unsigned short UVIndex;
	unsigned short normalIndex;

	bool operator<(const FaceTuple that) const {
		return memcmp((void*)this, (void*)&that, sizeof(FaceTuple)) > 0;
	};
};

struct FaceTupleVectorData {
	glm::vec3 vertex;
	glm::vec2 UV;
	glm::vec3 vertNormal;

	bool operator<(const FaceTupleVectorData that) const {
		return memcmp((void*)this, (void*)&that, sizeof(FaceTupleVectorData)) > 0;
	};
};

class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	Model* loadObj(std::string filePath);

protected:
	int searchDuplicate(std::vector<FaceTuple> theTuples, FaceTuple tupleToCheck);

	int searchDuplicateMap(std::map<FaceTuple, unsigned short> &theTuples, FaceTuple &tupleToCheck);

	bool searchDuplicateMap2(std::map<FaceTupleVectorData, unsigned int> &theTuples, FaceTupleVectorData &tupleToCheck, unsigned int &indexDup);

	void checkLow(float val, float &low);
	void checkHigh(float val, float &high);

};

