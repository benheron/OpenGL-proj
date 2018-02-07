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
#include "Texture.h"
#include "Keyboard.h"
#include "Entity.h"
#include "Platform.h"
#include "states/StateManager.h"
#include "states/GameState.h"
#include "Renderer.h"
#include "text/TextImageManager.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;



//Starts up SDL, creates window, and initializes OpenGL
//bool init();

//Initializes matrices and clear color
//bool initGL();

//Input handler
void handleKeys(SDL_Event keyType, bool bKeyDown, int x, int y);

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close();

float time2;


GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;



//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQuad = true;
bool gTimeStop = false;
GLuint colorbuffer;


GLuint VertexArrayID;
GLuint textureBuffer;


ObjLoader objLoad;

//shaders
ShaderProgram sp;


KeyboardManager *kbManager;


GLuint mvpID;
GLuint viewMatID;
GLuint modelMatID;
GLuint lightID;
GLuint ambientID;

GLuint lightPosID;

GLuint lightIntID;

GLuint modelTexture;
GLuint textureID;


GLuint attenuationID;

float lightAttenuation = 1.0;



std::vector<unsigned int> indices;
std::vector<glm::vec3> vertices;
std::vector<glm::vec3> normals;

std::vector<Entity*> entities;

Entity *e;
glm::vec3 lightInt = glm::vec3(4);
glm::vec3 lightPos = glm::vec3(4, 4, 2);

/*
bool init()
{

	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialise! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//create the window
		gWindow = SDL_CreateWindow("SDL Tut", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		//check if window created
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gContext = SDL_GL_CreateContext(gWindow);
			
			//check gContext
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{

				glewExperimental = GL_TRUE;

				GLenum err = glewInit();

				if (err != GLEW_OK)
				{
					printf("Unable to initialize GLEW!%s\n", glewGetErrorString(err));
				}

				//use vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}
				
				//initialise openGl
				if (!initGL())
				{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}
	}
	return success;
}

*/


/*
bool initGL()
{
	bool success = true;

	if (!sp.loadProgram())
	{
		success = false;
	}
	else
	{
		gProgramID = sp.getProgramID();
		{




			glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

			// Enable depth test
			glEnable(GL_DEPTH_TEST);
			// Accept fragment if it closer to the camera than the former one
			glDepthFunc(GL_LESS);
			
			glGenVertexArrays(1, &VertexArrayID);
			glBindVertexArray(VertexArrayID);
			// Cull triangles which normal is not towards the camera
			glEnable(GL_CULL_FACE);

			mvpID = glGetUniformLocation(gProgramID, "mvp");
			viewMatID = glGetUniformLocation(gProgramID, "v");
			modelMatID = glGetUniformLocation(gProgramID, "m");

			glUseProgram(gProgramID);
			lightID = glGetUniformLocation(gProgramID, "lightDirCamera");

			glUseProgram(gProgramID);
			lightPosID = glGetUniformLocation(gProgramID, "lightPosCameraSpace");


			attenuationID = glGetUniformLocation(gProgramID, "lightAttenuation");

			ambientID = glGetUniformLocation(gProgramID, "ambientIntensity");

			lightIntID = glGetUniformLocation(gProgramID, "lightIntensity");


			textureID = glGetUniformLocation(gProgramID, "textureSampler");

			



			Texture* testTexture = new Texture();
			//modelTexture = testTexture->loadDDS("uvmap.dds");
			testTexture->loadTexture("models/HouseTexture1.png");
			//modelTexture = testTexture->getTextureID();

			Model *obj = objLoad.loadObj("models/House2.obj");
			e = new Entity(obj);

			e->setTexture(testTexture);

			entities.push_back(e);

			Model *obj2 = objLoad.loadObj("untitled.obj");
			Entity *e2 = new Entity(obj2);


			Texture* testTexture2 = new Texture();
			testTexture2->loadTexture("buildingtexture.png");
			//testTexture2->loadDDS("uvmap1.dds");
			e2->setTexture(testTexture2);

			//entities.push_back(e2);



			//VBO data
			vertices = obj->getVertices();
			indices = obj->getVertexIndices();
			std::vector<glm::vec2> UVs = obj->getUVs();

			normals = obj->getVertNormals();

			
		}
	}

	return success;
}*/


void handleKeys(SDL_Event events, bool bKeyDown, int x, int y)
{

	switch (events.key.keysym.sym)
	{
	case SDLK_a: kbManager->setKeyDown("a", bKeyDown); break;
	case SDLK_b: kbManager->setKeyDown("b", bKeyDown); break;
	case SDLK_c: kbManager->setKeyDown("c", bKeyDown); break;
	case SDLK_d: kbManager->setKeyDown("d", bKeyDown); break;
	case SDLK_e: kbManager->setKeyDown("e", bKeyDown); break;
	case SDLK_f: kbManager->setKeyDown("f", bKeyDown); break;
	case SDLK_g: kbManager->setKeyDown("g", bKeyDown); break;
	case SDLK_h: kbManager->setKeyDown("h", bKeyDown); break;
	case SDLK_i: kbManager->setKeyDown("i", bKeyDown); break;
	case SDLK_j: kbManager->setKeyDown("j", bKeyDown); break;
	case SDLK_k: kbManager->setKeyDown("k", bKeyDown); break;
	case SDLK_l: kbManager->setKeyDown("l", bKeyDown); break;
	case SDLK_m: kbManager->setKeyDown("m", bKeyDown); break;
	case SDLK_n: kbManager->setKeyDown("n", bKeyDown); break;
	case SDLK_o: kbManager->setKeyDown("o", bKeyDown); break;
	case SDLK_p: kbManager->setKeyDown("p", bKeyDown); break;
	case SDLK_q: kbManager->setKeyDown("q", bKeyDown); break;
	case SDLK_r: kbManager->setKeyDown("r", bKeyDown); break;
	case SDLK_s: kbManager->setKeyDown("s", bKeyDown); break;
	case SDLK_t: kbManager->setKeyDown("t", bKeyDown); break;
	case SDLK_u: kbManager->setKeyDown("u", bKeyDown); break;
	case SDLK_v: kbManager->setKeyDown("v", bKeyDown); break;
	case SDLK_w: kbManager->setKeyDown("w", bKeyDown); break;
	case SDLK_x: kbManager->setKeyDown("x", bKeyDown); break;
	case SDLK_y: kbManager->setKeyDown("y", bKeyDown); break;
	case SDLK_z: kbManager->setKeyDown("z", bKeyDown); break;

	case SDLK_0: kbManager->setKeyDown("0", bKeyDown); break;
	case SDLK_1: kbManager->setKeyDown("1", bKeyDown); break;
	case SDLK_2: kbManager->setKeyDown("2", bKeyDown); break;
	case SDLK_3: kbManager->setKeyDown("3", bKeyDown); break;
	case SDLK_4: kbManager->setKeyDown("4", bKeyDown); break;
	case SDLK_5: kbManager->setKeyDown("5", bKeyDown); break;
	case SDLK_6: kbManager->setKeyDown("6", bKeyDown); break;
	case SDLK_7: kbManager->setKeyDown("7", bKeyDown); break;
	case SDLK_8: kbManager->setKeyDown("8", bKeyDown); break;
	case SDLK_9: kbManager->setKeyDown("9", bKeyDown); break;
	case SDLK_SPACE: kbManager->setKeyDown("space", bKeyDown); break;

	case SDLK_UP: kbManager->setKeyDown("up", bKeyDown); break;
	case SDLK_DOWN: kbManager->setKeyDown("down", bKeyDown); break;
	case SDLK_LEFT: kbManager->setKeyDown("left", bKeyDown); break;
	case SDLK_RIGHT: kbManager->setKeyDown("right", bKeyDown); break;
	case SDLK_ESCAPE: kbManager->setKeyDown("esc", bKeyDown); break;

	case SDLK_LSHIFT: kbManager->setKeyDown("shift", bKeyDown); break;
	case SDLK_RSHIFT: kbManager->setKeyDown("shift", bKeyDown); break;

	}
	//Toggle quad
	/*if (key == 'q')
	{
		gRenderQuad = !gRenderQuad;
	}

	if (key == 't')
	{
		gTimeStop = !gTimeStop;
	}*/

}

void update()
{
	

}

glm::vec4 g_lightDirection = glm::vec4(0.5, 0.5f, 0.5f, 0.0f);


//glm::vec3 lightPos = glm::vec3(4, 4, 4);
void render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	


	//Render quad
	//if (gRenderQuad)
	{
		glUseProgram(gProgramID);
		
		//lighting
		//glm::vec4 lightDirCameraSpace = viewMat * modelMat * g_lightDirection;

		glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 1.0f, 8000.0f);
		glm::mat4 viewMat = glm::lookAt(
			glm::vec3(4, 4, 3),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0));

		glm::vec3 lightCameraPos = viewMat * glm::vec4(lightPos, 1);
		glm::mat4 matInverse = glm::inverse(viewMat);
		//glm::vec4 lightDirModelSpace = matInverse * lightDirCameraSpace;

		//glUniform3fv(lightID, 1, glm::value_ptr(lightCameraPos));


		glUniform3f(lightPosID, lightCameraPos.x, lightCameraPos.y, lightCameraPos.z);
		//glUniform3fv(lightPosID, 1, &lightPos[0]);

		glm::vec3 ambientIntensity = glm::vec3(0.2, 0.2, 0.2);
		glUniform3fv(ambientID, 1, &ambientIntensity[0]);
		glUniform3fv(lightIntID, 1, &lightInt[0]);
		//glUniform3f(lightPosID, lightPos.x, lightPos.y, lightPos.z);


		glUniform1f(attenuationID, lightAttenuation);



		for (int i = 0; i < entities.size(); i++)
		{
			//get model matrix for this specific model
			glm::mat4 modelMat = entities[i]->getModelMatrix();
			//new mvp
			glm::mat4 mvp = projMat * viewMat * modelMat;

			Model* m = entities[i]->getModel();
			//vertices buffer
			GLuint vertexBuffer = m->getVertexBuffer();

			//normal buffer
			GLuint uvBuffer = m->getUVBuffer();

			//normals buffer
			GLuint normalBuffer = m->getNormalBuffer();

			//indices buffer
			GLuint indexBuffer = m->getIndexBuffer();

			GLsizei indexSize = m->getVertexIndices().size();
			





			bool nonuniformscale = false;
			if (nonuniformscale)
			{
				glm::transpose((glm::inverse(mvp)));
			}

			glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

			glUniformMatrix4fv(modelMatID, 1, GL_FALSE, &modelMat[0][0]);
			glUniformMatrix4fv(viewMatID, 1, GL_FALSE, &viewMat[0][0]);





			//TEST THIS ONE INSTEAD OF ONE ABOVE AFTER WORKING
			//

			// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entities[i]->getTexture()->getTextureID());
			// Set our "myTextureSampler" sampler to use Texture Unit 0
			glUniform1i(textureID, 0);

			//enable vertex position
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glVertexAttribPointer(
				0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);


			// 2nd attribute buffer : colors
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
			glVertexAttribPointer(
				1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
				2,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);


			// 3rd attribute buffer : normals
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
			glVertexAttribPointer(
				2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);







			//VERTICES + INDICES - make sure to get rid of ObjLoader function to rearrange vertices

			//set index data and render
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, (void*)0);
		}





	
		


		//disable vertex position
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//unbind program
		glUseProgram(NULL);

	}
}

void close()
{
//	glDeleteBuffers(1, &vertexBuffer);
//	glDeleteBuffers(1, &gIBO);
//	glDeleteBuffers(1, &normalBuffer);
//	glDeleteBuffers(1, &uvBuffer);
	glDeleteProgram(gProgramID);
//	glDeleteVertexArrays(1, &VertexArrayID);


	//Destroy window	
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}


int main( int argc, char* args[] )
{

	Platform *platform = new Platform("OpenGL project!", glm::vec2(640, 480));
	//Start up SDL and create window
	/*if( !init() )
	{
		printf( "Failed to initialize!\n" );
		return 1;
	}*/

	EntityManager *em = new EntityManager();
	kbManager = new KeyboardManager();

	TextImageManager *tim = new TextImageManager("res/fonts/fontarial.txt");
	
	StateManager *stateManager = new StateManager();
	GameState *gs = new GameState(stateManager, platform, em, kbManager, tim);
	stateManager->addState(gs);

	Renderer* renderer = new Renderer(em);


	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
		
	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);


	unsigned int lastTime = SDL_GetTicks();

	//Enable text input
	//SDL_StartTextInput();

	//While application is running
	while( !quit )
	{

		unsigned int current = SDL_GetTicks();
		float dt = (float)(current - lastTime) / 1000.0f;
		lastTime = current;


		if (dt > 0.050)
		{
			dt = 0.050;
		}

		//Handle events on queue
		while( SDL_PollEvent( &e ))
		{
			//User requests quit
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_KEYDOWN:
				handleKeys(e, true, x, y);
				break;
			case SDL_KEYUP:
				handleKeys(e, false, x, y);
				break;
			}
		}

		stateManager->update(dt);


		renderer->render(stateManager->getStates());
		//update();

		//Render quad
		//render();
			
		//Update screen
		SDL_GL_SwapWindow( platform->getWindow() );
	}
		
	//Disable text input
	//SDL_StopTextInput();
	

	//Free resources and close SDL
	close();

	return 0;
}
