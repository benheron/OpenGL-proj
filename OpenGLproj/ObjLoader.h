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


/*
ObjMesh *LoadMesh(std::string filePath)
{
	std::ifstream file(filePath);
	std::string line;

	//If the file successfully opens
	if (file.is_open())
	{
		std::cout << "Hello";
	}
	else {
		std::cout << "File failed to open";
	}

	while (std::getline(file, line))
	{

		std::string curLine;
		file >> curLine;


		if (curLine.compare(0, 6, "mtllib") == 0) {
			std::string textureFile;

			file >> textureFile;
		}


		if (curLine.compare(0, 2, "v") == 0) {
			//found a vertex

			XMFLOAT3 vert;

			float vertX;
			float vertY;
			float vertZ;

			//VERTEX
			file >> vertX;
			file >> vertY;
			file >> vertZ;

			vert.x = vertX;
			vert.y = vertY;
			vert.z = vertZ;



			objVertices.push_back(vert);

		}

		//VERTEX TEXTURE COORDINATES
		if (curLine.compare(0, 3, "vt") == 0) {

			XMFLOAT2 vertT;

			float vertTX;
			float vertTY;


			file >> vertTX;
			file >> vertTY;

			vertT.x = vertTX;
			vertT.y = vertTY;

			objVertTextures.push_back(vertT);


		}

		//VERTEX NORMALS
		if (curLine.compare(0, 3, "vn") == 0) {

			XMFLOAT3 vertN;

			float vertNX;
			float vertNY;
			float vertNZ;

			file >> vertNX;
			file >> vertNY;
			file >> vertNZ;


			vertN.x = vertNX;
			vertN.y = vertNY;
			vertN.z = vertNZ;

			objNormals.push_back(vertN);



		}

		//FACE ELEMENT
		if (curLine.compare(0, 3, "f") == 0) {


			std::string fOne;
			std::string fTwo;
			std::string fThree;

			file >> fOne;
			file >> fTwo;
			file >> fThree;


			char curF[256];
			strcpy(curF, fOne.c_str());
			char *pch;
			pch = strtok(curF, "/");


			while (pch != NULL)
			{
				FaceVertex fv;

				int vertexIndex = atoi(pch);
				fv.vertex = vertexIndex - 1;
				pch = strtok(NULL, "/");

				int vtIndex = atoi(pch);
				fv.textPos = vtIndex - 1;
				pch = strtok(NULL, "/");

				int vnIndex = atoi(pch);
				fv.normal = vnIndex - 1;
				pch = strtok(NULL, "/");

				faceVertices.push_back(fv);
			}




			char curF2[256];
			strcpy(curF2, fTwo.c_str());
			char *pch2;
			pch2 = strtok(curF2, "/");


			while (pch2 != NULL)
			{
				FaceVertex fv;

				int vertexIndex = atoi(pch2);
				fv.vertex = vertexIndex - 1;
				pch2 = strtok(NULL, "/");

				int vtIndex = atoi(pch2);
				fv.textPos = vtIndex - 1;
				pch2 = strtok(NULL, "/");

				int vnIndex = atoi(pch2);
				fv.normal = vnIndex - 1;
				pch2 = strtok(NULL, "/");

				faceVertices.push_back(fv);
			}

			char curF3[256];
			strcpy(curF3, fThree.c_str());
			char *pch3;
			pch3 = strtok(curF3, "/");


			while (pch3 != NULL)
			{
				FaceVertex fv;

				int vertexIndex = atoi(pch3);
				fv.vertex = vertexIndex - 1;
				pch3 = strtok(NULL, "/");

				int vtIndex = atoi(pch3);
				fv.textPos = vtIndex - 1;
				pch3 = strtok(NULL, "/");

				int vnIndex = atoi(pch3);
				fv.normal = vnIndex - 1;
				pch3 = strtok(NULL, "/");

				faceVertices.push_back(fv);
			}
		}
	}
	ObjMesh *mesh = new ObjMesh();

	//test data structures
	std::vector<XMFLOAT3> vss;
	std::vector<XMFLOAT3> vss2;


	std::vector<int> iss;
	//



	mesh->numNormals = (USHORT)objNormals.size();
	mesh->normals = new ObjVertex[mesh->numNormals];

	for (int i = 0; i < mesh->numNormals; i++)
	{
		mesh->normals[i].pos.x = objNormals[i].x;
		mesh->normals[i].pos.y = objNormals[i].y;
		mesh->normals[i].pos.z = objNormals[i].z;
	}


	mesh->numTextCoords = (USHORT)objVertTextures.size();
	mesh->textCoords = new ObjVertex[mesh->numTextCoords];

	for (int i = 0; i < mesh->numVertices; i++)
	{
		mesh->textCoords[i].pos.x = objVertTextures[i].x;
		mesh->textCoords[i].pos.y = objVertTextures[i].y;
	}









	mesh->numIndices = (USHORT)faceVertices.size();
	mesh->indices = new USHORT[mesh->numIndices];

	mesh->normIndi = new USHORT[mesh->numIndices];
	mesh->textIndi = new USHORT[mesh->numIndices];





	//indices
	for (int i = 0; i < faceVertices.size(); i++)
	{
		mesh->indices[i] = faceVertices[i].vertex;
		mesh->normIndi[i] = faceVertices[i].normal;
		mesh->textIndi[i] = faceVertices[i].textPos;
	}

	mesh->numVertices = (USHORT)faceVertices.size();
	mesh->vertices = new ObjVertex[mesh->numVertices];



	//using all the faces to create new vertices does not work, unfortunately. Goes completely blank :/

	/ *for (int i = 0; i < faceVertices.size(); i+=3)
	{
	mesh->vertices->pos.x = objVertices[faceVertices[i].vertex].x;
	mesh->vertices->pos.y = objVertices[faceVertices[i+1].vertex].y;
	mesh->vertices->pos.z = objVertices[faceVertices[i+2].vertex].z;


	XMFLOAT3 pos;
	pos.x = objVertices[faceVertices[i].vertex].x;
	pos.y = objVertices[faceVertices[i + 1].vertex].y;
	pos.z = objVertices[faceVertices[i + 2].vertex].z;
	vss2.push_back(pos);

	//mesh->vertices->normal.x = objVertices[faceVertices[i].normal].x;
	//mesh->vertices->normal.y = objVertices[faceVertices[i+1].normal].y;
	//mesh->vertices->normal.z = objVertices[faceVertices[i+2].normal].z;

	//mesh->vertices->textCoords.x = objVertices[faceVertices[i].textPos].x;
	//mesh->vertices->textCoords.y = objVertices[faceVertices[i + 1].textPos].y;
	}* /

	//vertices
	mesh->numVertices = (USHORT)objVertices.size();
	mesh->vertices = new ObjVertex[mesh->numVertices];


	for (int i = 0; i < mesh->numVertices; i++)
	{
		mesh->vertices[i].pos.x = objVertices[i].x;
		mesh->vertices[i].pos.y = objVertices[i].y;
		mesh->vertices[i].pos.z = objVertices[i].z;

		mesh->vertices->normal.x = objNormals[i].x;
		mesh->vertices->normal.y = objNormals[i].y;
		mesh->vertices->normal.z = objNormals[i].z;


		XMFLOAT3 pos;
		pos.x = objVertices[i].x;
		pos.y = objVertices[i].y;
		pos.z = objVertices[i].z;


		vss.push_back(pos);
	}

	for (int i = 0; i < mesh->numVertices; i++)
	{
		mesh->vertices[i].pos.x = objVertices[i].x;
		mesh->vertices[i].pos.y = objVertices[i].y;
		mesh->vertices[i].pos.z = objVertices[i].z;

		XMFLOAT3 pos;
		pos.x = objVertices[i].x;
		pos.y = objVertices[i].y;
		pos.z = objVertices[i].z;


		vss.push_back(pos);
	}





	return mesh;
}*/