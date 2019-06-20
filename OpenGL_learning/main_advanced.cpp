#include "shader.h"
#include "camera.h"
#include "model.h"


extern Camera camera;
int main()
{
	std::vector<glm::vec3> windows;
	windows.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
	windows.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
	windows.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	windows.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
	windows.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

	Window mywindow("Learn_Light", screenWidth, screenHeight);

	//Shader shader("model.ver", "model.frag");
	Shader shader("advanced.vs", "advanced.frag");
	Shader skyboxShader("skybox.vs", "skybox.frag");
	
	Model ourModel("nanosuit/nanosuit.obj");

	// Setup cube VAO
	GLuint cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, 864, &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);
	
	GLuint skyVAO, skyVBO;
	glGenVertexArrays(1, &skyVAO);
	glGenBuffers(1, &skyVBO);
	glBindVertexArray(skyVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
	glBufferData(GL_ARRAY_BUFFER, 432, &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	// Load textures
	GLuint cubeTexture = loadTexture("texture/container.jpg");
	GLuint floorTexture = loadTexture("texture/tex2.jpg");
	GLuint grassTexture = loadTexture("texture/fall_point.png");

	std::vector<const GLchar*> faces;
	faces.push_back("Skyboxs/skybox/right.jpg");
	faces.push_back("Skyboxs/skybox/left.jpg");
	faces.push_back("Skyboxs/skybox/top.jpg");
	faces.push_back("Skyboxs/skybox/bottom.jpg");
	faces.push_back("Skyboxs/skybox/back.jpg");
	faces.push_back("Skyboxs/skybox/front.jpg");
	GLuint skyboxTexture = loadCubemap(faces);
	

	while (!glfwWindowShouldClose(mywindow.window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		

		glfwPollEvents();
		camera.ProcessKeyboard(deltaTime);
		
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();
		glm::mat4 model;
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.Zoom, screenWidth / screenHeight, 0.1f, 100.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down

		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3f(glGetUniformLocation(shader.Program, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		glActiveTexture(GL_TEXTURE3);
		glUniform1i(glGetUniformLocation(shader.Program, "skybox"), 3);

		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
		ourModel.Draw(shader);
		
		//Draw skybox as last
		glDepthFunc(GL_LEQUAL);
		skyboxShader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(skyVAO);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(shader.Program, "skybox"), 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);


		glfwSwapBuffers(mywindow.window);

	}
	// Clean up
	//glDeleteFramebuffers(1, &framebuffer);

	glfwTerminate();

	return 0;


}