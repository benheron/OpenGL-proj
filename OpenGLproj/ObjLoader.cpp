#include "ObjLoader.h"


ObjLoader::ObjLoader()
{

}

ObjLoader::~ObjLoader()
{

}

Model* ObjLoader::loadObj(std::string filePath)
{
	//std::ios_base::sync_with_stdio(false);
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> UVs;
	std::vector<glm::vec3> vertNormals;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;


	std::ifstream objFile(filePath);
	std::string line;



	{
		const char *path = filePath.c_str();

		FILE *file;
		errno_t err = fopen_s(&file, path, "r");
		if (file == NULL) {
			printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
			getchar();
			return false;
		}

		bool haveVT = false;
		bool haveVN = false;

		while (1) {

			char lineHeader[128];
			// read the first word of the line
			int res = fscanf_s(file, "%s", lineHeader, _countof(lineHeader));
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

					   // else : parse lineHeader

			if (strcmp(lineHeader, "v") == 0) {
				
				glm::vec3 vertex;
				fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				if (!haveVT)
				{
					haveVT = true;
				}
				glm::vec2 uv;
				fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
				uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
				UVs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				if (!haveVN)
				{
					haveVN = true;
				}
				glm::vec3 normal;
				fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				vertNormals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				int d = 0;
				if (haveVT)
				{
					//has both vt and vn
					if (haveVN)
					{
						std::string vertex1, vertex2, vertex3;
						unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

					

						int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
						if (matches != 9) {
							printf("File can't be read by our simple parser :-( Try exporting with other options\n");
							fclose(file);
							return false;
						}
						vertexIndices.push_back(vertexIndex[0] - 1);
						vertexIndices.push_back(vertexIndex[1] - 1);
						vertexIndices.push_back(vertexIndex[2] - 1);
						uvIndices.push_back(uvIndex[0] - 1);
						uvIndices.push_back(uvIndex[1] - 1);
						uvIndices.push_back(uvIndex[2] - 1);
						normalIndices.push_back(normalIndex[0] - 1);
						normalIndices.push_back(normalIndex[1] - 1);
						normalIndices.push_back(normalIndex[2] - 1);
					}
					//has only vt
					else {
						std::string vertex1, vertex2, vertex3;
						unsigned int vertexIndex[3], normalIndex[3];


						int matches = fscanf_s(file, "%d/%d/ %d/%d/ %d/%d/\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
						if (matches != 6) {
							printf("File can't be read by our simple parser :-( Try exporting with other options\n");
							fclose(file);
							return false;
						}
						vertexIndices.push_back(vertexIndex[0] - 1);
						vertexIndices.push_back(vertexIndex[1] - 1);
						vertexIndices.push_back(vertexIndex[2] - 1);
						normalIndices.push_back(normalIndex[0] - 1);
						normalIndices.push_back(normalIndex[1] - 1);
						normalIndices.push_back(normalIndex[2] - 1);
					}
				} 
				//has only vn
				else if (haveVN)
				{
					std::string vertex1, vertex2, vertex3;
					unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];


					int matches = fscanf_s(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
					if (matches != 6) {
						printf("File can't be read by our simple parser :-( Try exporting with other options\n");
						fclose(file);
						return false;
					}
					vertexIndices.push_back(vertexIndex[0] - 1);
					vertexIndices.push_back(vertexIndex[1] - 1);
					vertexIndices.push_back(vertexIndex[2] - 1);
					normalIndices.push_back(normalIndex[0] - 1);
					normalIndices.push_back(normalIndex[1] - 1);
					normalIndices.push_back(normalIndex[2] - 1);

				}
				//has neither vt or vn
				else {
					std::string vertex1, vertex2, vertex3;
					unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];


					int matches = fscanf_s(file, "%d// %d// %d//\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
					if (matches != 3) {
						printf("File can't be read by our simple parser :-( Try exporting with other options\n");
						fclose(file);
						return false;
					}
					vertexIndices.push_back(vertexIndex[0]-1);
					vertexIndices.push_back(vertexIndex[1]-1);
					vertexIndices.push_back(vertexIndex[2]-1);
				}
			}
			else {
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);
			}

		}

	}




/*
	if (!objFile.is_open())
	{
		std::cout << "File failed to open";
	}
	else
	{

		while (std::getline(objFile, line))
		{
			//std::vector<std::string> splits;
		//	boost::split(splits, line, boost::is_any_of(" "));
		//	std::stringstream objLine(line);
		//	std::string linePart;

		//	while (std::getline(objLine, linePart, ' '))
		//	//{
		//		splits.push_back(linePart);
		//	}

			std::string curLine;
			objFile >> curLine;

			//make sure not blank line
			if (curLine.compare(0, 2, "v") == 0)
			{
				glm::vec3 vert;

				objFile >> vert.x;
				objFile >> vert.y;
				objFile >> vert.z;


				vertices.push_back(vert);
			} 
			else if (curLine.compare(0, 3, "vt") == 0)
			{
				glm::vec2 UV;

				objFile >> UV.x;
				objFile >> UV.y;

				UVs.push_back(UV);

			}
			else if (curLine.compare(0, 3, "vn") == 0)
			{
					glm::vec3 vertNorm;

					objFile >> vertNorm.x;
					objFile >> vertNorm.y;
					objFile >> vertNorm.z;

					vertNormals.push_back(vertNorm);
			}
			else if (curLine.compare(0, 3, "f") == 0)
			{
				std::string firstFace;
				std::string secondFace;
				std::string thirdFace;

				objFile >> firstFace;
				objFile >> secondFace;
				objFile >> thirdFace;

				std::vector<std::string> faceIndices;

				faceIndices.push_back(firstFace);
				faceIndices.push_back(secondFace);
				faceIndices.push_back(thirdFace);

				for (int i = 0; i < faceIndices.size(); i++)
				{
					std::vector <std::string> fullFace;
					boost::split(fullFace, faceIndices[i], boost::is_any_of("/"));
					/ *while (std::getline(ssface, facePart, '/'))
					{
					fullFace.push_back(facePart);
					}* /

					int x = boost::lexical_cast<int>(fullFace[0]) - 1;

					vertexIndices.push_back(x);

					int y = boost::lexical_cast<int>(fullFace[1]) - 1;

					if (UVs.size() > 0)
					{
						uvIndices.push_back(y);
					}

					int z = boost::lexical_cast<int>(fullFace[2]) - 1;

					normalIndices.push_back(z);
				}
			}

				/ * //vertex
				if (splits[0] == "v")
				{
					glm::vec3 vert;

					//vert.x = boost::spirit_double_test

				//	vert.x = atof(splits[1].c_str());
				//	vert.y = atof(splits[2].c_str());;
					//vert.z = atof(splits[3].c_str());;


					vertices.push_back(vert);
				} else

				if (splits[0] == "vt")
				{
					glm::vec2 UV;

					UV.x = atof(splits[1].c_str());
					UV.y = atof(splits[2].c_str());;

					UVs.push_back(UV);
				} else

				if (splits[0] == "vn")
				{
					glm::vec3 vertNorm;

					vertNorm.x = atof(splits[1].c_str());
					vertNorm.y = atof(splits[2].c_str());;
					vertNorm.z = atof(splits[3].c_str());;

					vertNormals.push_back(vertNorm);
				} else

				if (splits[0] == "f")
				{
					for (unsigned int i = 1; i < splits.size(); i++)
					{
						/ *std::stringstream ssface(splits[i]);
						std::string facePart;* /

						std::vector <std::string> fullFace;
						boost::split(fullFace, splits[i], boost::is_any_of("/"));
					/ *	while (std::getline(ssface, facePart, '/'))
						{
							fullFace.push_back(facePart);
						}* /
						
						vertexIndices.push_back(std::stoul(fullFace[0]) - 1);

					//	if (UVs.size() > 0)
						{
							uvIndices.push_back(std::stoul(fullFace[1]) - 1);
						}
						
						normalIndices.push_back(std::stoul(fullFace[2]) - 1);

					}

				}* /
			//}
		}

		objFile.close();*/

		
		//REARRANGES  VECTORS SO THAT DRAW ARRAY CAN WORK

	float xHigh = 0, xLow = 9999;
	float yHigh = 0, yLow = 9999;
	float zHigh = 0, zLow = 9999;

	std::vector<glm::vec3> vertices2;
	std::vector<glm::vec2> UVs2;
	std::vector<glm::vec3> vertNormals2;
	//temp vertex rearrangement
	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = vertices[vertexIndex];
		glm::vec3 normal = vertNormals[normalIndex];

		float x = vertex.x;
		float y = vertex.y;
		float z = vertex.z;

		checkLow(x, xLow);
		checkHigh(x, xHigh);

		checkLow(y, yLow);
		checkHigh(y, yHigh);

		checkLow(z, zLow);
		checkHigh(z, zHigh);
	


		// Put the attributes in buffers
		vertices2.push_back(vertex);
		vertNormals2.push_back(normal);


		if (uvIndices.size() > 0)
		{
			unsigned int uvIndex = uvIndices[i];
			glm::vec2 uv = UVs[uvIndex];
			UVs2.push_back(uv);
		}
	}


	std::vector<glm::vec3> newVertices;
	std::vector<glm::vec2> newUVs;
	std::vector<glm::vec3> newVertNormals;

	std::vector<FaceTuple> faceTuples;

	std::vector<FaceTupleVectorData> faceTuplesVectorData;
	std::vector<unsigned int> newIndices;


	unsigned int newIndex2 = 0;
	std::map<FaceTupleVectorData, unsigned int> faceTuplesMap;
	for (int i = 0; i < vertices2.size(); i++)
	{
		FaceTupleVectorData ft;
		ft.vertex = vertices2[i];
		if (uvIndices.size() > 0)
		{
			ft.UV = UVs2[i];
		}
		else 
		{
			ft.UV = glm::vec2(-1);
		}
		ft.vertNormal = vertNormals2[i];

		unsigned int dupPos;
		bool isDup = searchDuplicateMap2(faceTuplesMap, ft, dupPos);

		if (!isDup)
		{
		//	unsigned short vertexIndex = vertexIndices[i];
		//	unsigned short normalIndex = normalIndices[i];


			newVertices.push_back(vertices2[i]);
		//	newUVs.push_back(UVs2[i]);
			newVertNormals.push_back(vertNormals2[i]);
				



			unsigned int newIndex = (unsigned int)newVertices.size() - 1;

				

			newIndices.push_back(newIndex);
			faceTuplesMap[ft] = newIndex;


			//UVs
			if (uvIndices.size() > 0)
			{
				newUVs.push_back(UVs2[i]);
				//newUVs.push_back(glm::vec2(-1));
			//	newUVs.push_back(UVs2[i]);
			//	unsigned short uvIndex = uvIndices[i];
				//newUVs.push_back(UVs2[i]);
			}
			else {
				newUVs.push_back(glm::vec2(0));
			}

			newIndex2++;
		}
		else {
			newIndices.push_back(dupPos);
		}

	}










	Model *m2 = new Model(newVertices, newUVs, newVertNormals, newIndices, uvIndices, normalIndices);


	return m2;
	
}

int ObjLoader::searchDuplicate(std::vector<FaceTuple> theTuples, FaceTuple tupleToCheck)
{
	int duplicatePos = -1;
	bool foundDuplicate = false;
	for (int i = 0; i < theTuples.size(); i++)
	{
		if (theTuples[i].vertexIndex == tupleToCheck.vertexIndex &&
			theTuples[i].UVIndex == tupleToCheck.UVIndex &&
			theTuples[i].normalIndex == tupleToCheck.normalIndex)
		{
			foundDuplicate = true;
			duplicatePos = i;
		}
	}
	return duplicatePos;
}

int ObjLoader::searchDuplicateMap(std::map<FaceTuple, unsigned short> &theTuples , FaceTuple &tupleToCheck)
{
	int duplicatePos;

	std::map<FaceTuple, unsigned short>::iterator it = theTuples.find(tupleToCheck);

	if (it == theTuples.end())
	{
		duplicatePos = -1;
	}
	else {
		duplicatePos = it->second;
	}

	return duplicatePos;
}


bool ObjLoader::searchDuplicateMap2(std::map<FaceTupleVectorData, unsigned int> &theTuples, FaceTupleVectorData &tupleToCheck, unsigned int &indexDup)
{
	bool duplicate;

	std::map<FaceTupleVectorData, unsigned int>::iterator it = theTuples.find(tupleToCheck);

	if (it == theTuples.end())
	{
		duplicate = false;
	}
	else {
		indexDup = it->second;
		duplicate = true;
	}

	return duplicate;
}


void ObjLoader::checkLow(float val, float &low)
{
	if (val < low)
	{
		low = val;
	}

	return;
}

void ObjLoader::checkHigh(float val, float &high)
{
	if (val > high)
	{
		high = val;
	}
}