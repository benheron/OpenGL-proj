#pragma once
#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.h"


class Entity {
public:
	Entity(Model* m_);
	~Entity();


	void setPosition(glm::vec3 pos, bool add);
	glm::vec3 getPosition();

//	void setRotation(glm::vec3 rot, glm::vec3 axis);

	void setTexture(Texture* t);
	Texture* getTexture();
	
	//x
	void setYaw(float rot, bool add);
	//y
	void setPitch(float rot, bool add);
	//z
	void setRoll(float rot, bool add);

	void setScale(glm::vec3 s);

	Model* getModel();

	glm::mat4 getModelMatrix();

	void strafeLeft();
	void strafeRight();

	void moveForward();

	void moveBackward();


protected:
	bool modelMatChanged;

	Model *model;
	glm::mat4 modelMatrix;
	glm::mat4 rotMatrix;
	glm::vec3 modScale;
	//rotation
	//x axis
	float rotPitch;
	//y axis
	float rotYaw;
	//z-axis
	float rotRoll;

	float speed;

	glm::vec3 modelPos;
	Texture *modTexture;

	glm::vec3 forwardVec;
	glm::vec3 upVec;
	glm::vec3 rightVec;
	
};