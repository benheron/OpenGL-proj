#include "Entity.h"

Entity::Entity(glm::vec3 pos, glm::vec3 dimens) : pos(pos), dimensions(dimens)
{
	modelMatChanged = true;
	rotMatrix = glm::mat4(1.0);

	modelMatrix = glm::mat4(1.0);

	rotPitch = 0;
	rotYaw = 0;
	rotRoll = 0;

	pos = glm::vec3(0);
	modScale = glm::vec3(1.0);



	forwardVec = glm::vec3(0, 0, 1);
	upVec = glm::vec3(0, 1, 0);
	rightVec = glm::vec3(-1, 0, 0);

	speed = 0.2;

	//bbAllowance = glm::vec3(0.1, 0.1, 0.8);
	bbAllowance = glm::vec3(0, 0, 0);


}

Entity::~Entity()
{

}

void Entity::update(float dt)
{
	if (!modelMatChanged)
	{
		bb->transformByMat4(modelMatrix);
		return;
	}

	modelMatChanged = false;

	glm::mat4 mm = glm::mat4(1.0);


	//forwardVec = glm::rotate()

	//translate to new position
	mm = glm::translate(mm, pos);

	//rotate x
	mm = glm::rotate(mm, rotPitch, glm::vec3(1, 0, 0));
	//rotate y
	mm = glm::rotate(mm, rotYaw, glm::vec3(0, 1, 0));
	//rotate z
	mm = glm::rotate(mm, rotRoll, glm::vec3(0, 0, 1));

	//scale
	mm = glm::scale(mm, modScale);


	modelMatrix = mm;

	bb->transformByMat4(modelMatrix);

}


void Entity::setModel(Model *m)
{
	model = m;

	bb = new BoundingBox(model->getMinPos() + bbAllowance, model->getMaxPos() - bbAllowance);
}

glm::vec3 Entity::getPosition()
{
	return pos;
}

void Entity::setPosition(glm::vec3 p, bool add)
{
	if (add)
	{
		pos += p;
	}
	else {
		pos = p;
	}
	modelMatChanged = true;
}


void Entity::setYaw(float rot, bool add)
{
	if (add)
	{
		rotYaw += rot;
	}
	else {
		rotYaw = rot;
	}
	modelMatChanged = true;
}

void Entity::setPitch(float rot, bool add)
{
	if (add)
	{
		rotPitch += rot;
	}
	else {
		rotPitch = rot;
	}
	modelMatChanged = true;
}

void Entity::setRoll(float rot, bool add)
{
	if (add)
	{
		rotRoll += rot;
	}
	else {
		rotRoll = rot;
	}
	modelMatChanged = true;
}

Model* Entity::getModel()
{
	return model;
}

void Entity::setTexture(Texture *t)
{
	modTexture = t;
}

Texture *Entity::getTexture()
{
	return modTexture;
}


glm::mat4 Entity::getModelMatrix()
{
	if (!modelMatChanged)
	{
		return modelMatrix;
	}

	modelMatChanged = false;

	glm::mat4 mm = glm::mat4(1.0);


	//forwardVec = glm::rotate()

	//translate to new position
	mm = glm::translate(mm, pos);

	//rotate x
	mm = glm::rotate(mm, rotPitch, glm::vec3(1, 0, 0));
	//rotate y
	mm = glm::rotate(mm, rotYaw, glm::vec3(0, 1, 0));
	//rotate z
	mm = glm::rotate(mm, rotRoll, glm::vec3(0, 0, 1));

	//scale
	mm = glm::scale(mm, modScale);


	modelMatrix = mm;
	
	return modelMatrix;
}


void Entity::strafeLeft()
{
	/*glm::vec4 v = modelMatrix[0] * speed;
	glm::vec3 v1(v);*/

	glm::vec3 v1 = -rightVec * speed;

	pos += v1;



	//modelPos -= (rightVec * speed);
}

void Entity::strafeRight()
{
	//glm::vec4 v = modelMatrix[0] * speed;
	//glm::vec3 v1(v);

	glm::vec3 v1 = -rightVec * speed;

	pos -= v1;

	//modelPos += (rightVec * speed);
}

void Entity::moveForward()
{
	//modelMatrix[3] += modelMatrix[2] * speed;
	glm::vec4 v = modelMatrix[2] * speed;
	glm::vec3 v1(v);

	pos += v1;
}

void Entity::moveBackward()
{
	glm::vec4 v = modelMatrix[2] * speed;
	glm::vec3 v1(v);

	pos -= v1;
}

void Entity::setScale(glm::vec3 s)
{
	modScale = s;
}

glm::vec3 Entity::getDimensions()
{
	/*float xWidth = model->getWidth() * modScale.x;
	float yHeight = model->getHeight() * modScale.y;
	float zDepth = model->getDepth() * modScale.z;

	glm::vec3 dimensions = glm::vec3(xWidth, yHeight, zDepth);*/

	return dimensions;


}

BoundingBox *Entity::getBoundingBox()
{
	return bb;
}