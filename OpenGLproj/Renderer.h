#pragma once
#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "ShaderProgram.h"
#include "ObjLoader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "entities/EntityManager.h"
#include "Platform.h"
#include "states/StateManager.h"


class Renderer
{
public:
	Renderer(EntityManager *em);
	~Renderer();

	void render(std::vector<State*> states);


protected:

	void renderSkybox(Camera *c, glm::mat4 p, glm::mat4 v);
	void renderText(std::vector<Text*> stateText);

	void renderDebug();



	EntityManager *em;

	glm::vec3 lightInt;
	glm::vec3 lightPos;
	float lightAttenuation = 1.0;

	ShaderProgram sp;
	ShaderProgram txtShader;
	ShaderProgram skyboxShader;
	ShaderProgram debugShader;


	GLuint programID;

	GLuint mvpID;
	GLuint viewMatID;
	GLuint modelMatID;
	GLuint lightID;
	GLuint ambientID;

	GLuint lightPosID;
	GLuint lightIntID;
	GLuint attenuationID;
	GLuint textureID;

	GLuint VertexArrayID;



	GLuint skyboxTextID;
	GLuint SBmvpID;
	GLuint SBviewMatID;
	GLuint SBmodelMatID;


	//text
	GLuint Text2DUniformID;

	Texture *skyboxTexture;
	Entity* skybox;


};