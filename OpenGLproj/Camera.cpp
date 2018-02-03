#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 lookAtPos, glm::vec3 upVector = glm::vec3(0, 1, 0)) : position(position), lookAtPos(lookAtPos), upVector(upVector)
{

}

Camera::~Camera()
{

}

void Camera::setPosition(glm::vec3 p, bool add)
{
	if (add)
	{
		position += p;
	}
	else {
		position = p;
	}
}

glm::vec3 Camera::getPosition()
{
	return position;
}

void Camera::setLookAtPos(glm::vec3 p, bool add)
{
	if (add)
	{
		lookAtPos += p;
	}
	else {
		lookAtPos = p;
	}
}

glm::vec3 Camera::getLookAtPos()
{
	return lookAtPos;
}

void Camera::setUpVector(glm::vec3 p, bool add)
{
	if (add)
	{
		upVector += p;
	}
	else {
		upVector = p;
	}
}

glm::vec3 Camera::getUpVector()
{
	return upVector;
}