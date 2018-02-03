#include "Renderer.h"

Renderer::Renderer(EntityManager *em) : em(em)
{
	
	if (sp.loadProgram())
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


		lightInt = glm::vec3(4);
		lightPos = glm::vec3(4, 4, 2);





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

		glUseProgram(programID);

		//lighting
		//glm::vec4 lightDirCameraSpace = viewMat * modelMat * g_lightDirection;

		glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 1.0f, 8000.0f);
		glm::mat4 viewMat = glm::lookAt(
			c->getPosition(),
			c->getLookAtPos(),
			c->getUpVector());

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






	}
	



	








	//disable vertex position
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//unbind program
	glUseProgram(NULL);





}