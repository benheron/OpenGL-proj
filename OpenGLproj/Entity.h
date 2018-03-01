#pragma once
#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.h"
#include "BoundingBox.h"


class Entity {
public:
	Entity(glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0));
	~Entity();

	void update(float dt);

	void setModel(Model *m);

	void setPosition(glm::vec3 p, bool add = false);
	glm::vec3 getPosition();

	glm::vec3 getDimensions();

//	void setRotation(glm::vec3 rot, glm::vec3 axis);

	void setTexture(Texture* t);
	Texture* getTexture();
	
	//x
	void setYaw(float rot, bool add);
	//y
	void setPitch(float rot, bool add);
	//z
	void setRoll(float rot, bool add);

	float getRoll();


	void setScale(glm::vec3 s);

	Model* getModel();

	glm::mat4 getModelMatrix();

	void strafeLeft(float dt);
	void strafeRight(float dt);

	void moveForward(float dt);

	void moveBackward(float dt);

	BoundingBox *getBoundingBox();

	//hacky player code
	void moveRight(float dt);
	void moveLeft(float dt);

	void setMoving(bool m);

	void setTilting(bool t);



	void rotateFurtherRight(float dt);

	void rotateFurtherLeft(float dt);

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

	glm::vec3 pos;
	Texture *modTexture;

	glm::vec3 forwardVec;
	glm::vec3 upVec;
	glm::vec3 rightVec;

	glm::vec3 dimensions;
	
	BoundingBox *bb;

	glm::vec3 bbAllowance;


	bool moving;

	bool tilting;
};