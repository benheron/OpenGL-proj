#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(glm::vec3 p, glm::vec3 lookAtPos, glm::vec3 upVector);
	~Camera();

	void setPosition(glm::vec3 p, bool add);
	glm::vec3 getPosition();

	void setLookAtPos(glm::vec3 p, bool add);
	glm::vec3 getLookAtPos();

	void setUpVector(glm::vec3 p, bool add);
	glm::vec3 getUpVector();


private:
	glm::vec3 position;
	glm::vec3 lookAtPos;
	glm::vec3 upVector;


};