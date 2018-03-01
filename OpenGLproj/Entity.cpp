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

	speed = 20;

	//bbAllowance = glm::vec3(0.1, 0.1, 0.8);
	bbAllowance = glm::vec3(0, 0, 0);

	moving = false;
	tilting = false;

}

Entity::~Entity()
{

}

void Entity::update(float dt)
{
	bb->transformByMat4(modelMatrix);

	if (!modelMatChanged)
	{
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

	if (rotRoll > 0)
	{
		int d = 0;
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


void Entity::strafeLeft(float dt)
{
	/*glm::vec4 v = modelMatrix[0] * speed;
	glm::vec3 v1(v);*/

	glm::vec3 v1 = -rightVec * speed *dt;

	pos += v1;


	modelMatChanged = true;
	//modelPos -= (rightVec * speed);
}

void Entity::strafeRight(float dt)
{
	//glm::vec4 v = modelMatrix[0] * speed;
	//glm::vec3 v1(v);

	glm::vec3 v1 = -rightVec * speed *dt;

	pos -= v1;

	modelMatChanged = true;
	//modelPos += (rightVec * speed);
}

void Entity::moveForward(float dt)
{
	//modelMatrix[3] += modelMatrix[2] * speed;
	glm::vec4 v = modelMatrix[2] * speed;
	glm::vec3 v1(v);

	pos += v1;
}

void Entity::moveBackward(float dt)
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

void Entity::moveRight(float dt)
{
	strafeRight(dt);

	if (rotRoll < 3.14159 / 7)
	{
		rotRoll += 3 * dt;
	}

	if (!tilting && rotRoll > 3.14159 / 7)
	{
		rotRoll -= 2 * dt;
	}



	/*if (!tilting)
	{
		if (rotRoll > 3.14159 / 7)
		{
			rotRoll = 3.14159 / 7;
		}
	}*/
}

void Entity::moveLeft(float dt)
{
	strafeLeft(dt);

	
	if (rotRoll > -3.14159 / 7)
	{
		rotRoll -= 3 * dt;
	}

	if (!tilting && rotRoll < -3.14159 / 7)
	{
		rotRoll += 2 * dt;
	}


	//if (rotRoll)




	/*if (!tilting)
	{
		if (rotRoll < -3.14159 / 7)
		{
			
			rotRoll = -3.14159 / 7;
		}
	}*/
	
}

void Entity::setMoving(bool m)
{
	moving = m;
}

void Entity::setTilting(bool t)
{
	tilting = t;
}

float Entity::getRoll()
{
	return rotRoll;
}

void Entity::rotateFurtherRight(float dt)
{
	glm::vec3 v1 = -rightVec * (speed/3) *dt;

	pos -= v1;

	modelMatChanged = true;

	rotRoll += 5 * dt;

	if (rotRoll > 3.14159 / 2)
	{
		rotRoll = 3.14159 / 2;
	}
}

void Entity::rotateFurtherLeft(float dt)
{
	glm::vec3 v1 = -rightVec * (speed/3) *dt;

	pos += v1;


	modelMatChanged = true;

	rotRoll -= 5 * dt;
	if (rotRoll < -3.14159 / 2)
	{
		rotRoll = -3.14159 / 2;
	}
}