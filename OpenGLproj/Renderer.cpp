#include "Renderer.h"

Renderer::Renderer(EntityManager *em) : em(em)
{
	
	if (sp.loadProgram("Shaders/VertShader.vert", "Shaders/FragShader.frag") &&
		debugShader.loadProgram("Shaders/VertShader.vert", "Shaders/DebugFragShader.frag"))
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

		programID = sp.getProgramID();


		lightInt = glm::vec3(45);
		lightPos = glm::vec3(0, 80, -50);





		mvpID = glGetUniformLocation(programID, "mvp");
		viewMatID = glGetUniformLocation(programID, "v");
		modelMatID = glGetUniformLocation(programID, "m");

		glUseProgram(programID);
		lightID = glGetUniformLocation(programID, "lightDirCamera");

		glUseProgram(programID);
		lightPosID = glGetUniformLocation(programID, "lightPosCameraSpace");


		attenuationID = glGetUniformLocation(programID, "lightAttenuation");
		ambientID = glGetUniformLocation(programID, "ambientIntensity");
		lightIntID = glGetUniformLocation(programID, "lightIntensity");
		textureID = glGetUniformLocation(programID, "textureSampler");


		skyboxTexture = new Texture();
		skyboxTexture->loadTexture("models/textures/Skybox2.jpg");



		ObjLoader objLoad;

		Model* skyb = objLoad.loadObj("models/skybox.obj");
		skybox = new Entity();
		skybox->setModel(skyb);

		skybox->setTexture(skyboxTexture);
	}

	if (txtShader.loadProgram("Shaders/TextVertShader.vert", "Shaders/TextFragShader.frag"))
	{
		Text2DUniformID = glGetUniformLocation(txtShader.getProgramID(), "myTextureSampler");
	}

	if (skyboxShader.loadProgram("Shaders/SkyboxVertShader.vert", "Shaders/SkyboxFragShader.frag"))
	{
		skyboxTextID = glGetUniformLocation(skyboxShader.getProgramID(), "textureSampler");

		SBmvpID = glGetUniformLocation(skyboxShader.getProgramID(), "mvp");
		SBviewMatID = glGetUniformLocation(skyboxShader.getProgramID(), "v");
		SBmodelMatID = glGetUniformLocation(skyboxShader.getProgramID(), "m");
	}


}

Renderer::~Renderer()
{

}

void Renderer::render(std::vector<State*> states)
{
	//std::vector<Entity*> entities = em->getEntities();

	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (int j = 0; j < states.size(); j++)
	{
		Camera *c = states[j]->getCamera();

		

		std::vector<Entity*> entities = states[j]->getRenderables();

		glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 1.0f, 400.0f);
		glm::mat4 viewMat = glm::lookAt(
			c->getPosition(),
			c->getLookAtPos(),
			c->getUpVector());

		renderSkybox(c, projMat, viewMat);

		//lighting
		//glm::vec4 lightDirCameraSpace = viewMat * modelMat * g_lightDirection;
		glUseProgram(programID);
		

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

		
		glUniformMatrix4fv(viewMatID, 1, GL_FALSE, &viewMat[0][0]);
	

		
	
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



			glUniformMatrix4fv(modelMatID, 1, GL_FALSE, &modelMat[0][0]);


			bool nonuniformscale = false;
			if (nonuniformscale)
			{
				glm::transpose((glm::inverse(mvp)));
			}

			glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

			





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


		
		renderText(states[j]->getStateText());

		
	}
	



	








	//disable vertex position
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);











	//unbind program
	glUseProgram(NULL);





}


void Renderer::renderSkybox(Camera *c, glm::mat4 p, glm::mat4 v)
{
	glDepthMask(0);


	glUseProgram(skyboxShader.getProgramID());

	//get model matrix for this specific model
	glm::mat4 modelMat = skybox->getModelMatrix();
	//new mvp
	glm::mat4 mvp = p * v * modelMat;

	skybox->setPosition(c->getPosition(), 0);

	Model* m = skybox->getModel();
	//vertices buffer
	GLuint vertexBuffer = m->getVertexBuffer();

	//normal buffer
	GLuint uvBuffer = m->getUVBuffer();

	//normals buffer
	GLuint normalBuffer = m->getNormalBuffer();

	//indices buffer
	GLuint indexBuffer = m->getIndexBuffer();

	GLsizei indexSize = m->getVertexIndices().size();




	glUniformMatrix4fv(SBmvpID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(SBviewMatID, 1, GL_FALSE, &v[0][0]);
	glUniformMatrix4fv(SBmodelMatID, 1, GL_FALSE, &modelMat[0][0]);





	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, skybox->getTexture()->getTextureID());
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(skyboxTextID, 0);

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

	//set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, (void*)0);


	glDepthMask(1);
}

void Renderer::renderText(std::vector<Text*> stateText)
{
	GLuint txtProgramId = txtShader.getProgramID();

	glUseProgram(txtProgramId);

	for (int i = 0; i < stateText.size(); i++)
	{

		Model* m = stateText[i]->getModel();
		//vertices buffer
		GLuint vertexBuffer = m->getVertexBuffer2D();

		//normal buffer
		GLuint uvBuffer = m->getUVBuffer();


		GLsizei indexSize = m->getVertices2D().size();

		GLuint fontID =  stateText[i]->getFontTexture()->getTextureID();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fontID);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(Text2DUniformID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Draw call
		glDrawArrays(GL_TRIANGLES, 0, indexSize);

		glDisable(GL_BLEND);
	}

	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
}