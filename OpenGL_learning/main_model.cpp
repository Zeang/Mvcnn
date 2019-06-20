#include "shader.h"
#include "camera.h"
#include "model.h"
const float screenWidth = 800;
const float screenHeight = 600;

extern Camera camera;
int main()
{
	Window mywindow("Learn_Light", screenWidth, screenHeight);

	Shader shader("model.ver", "model.frag");
	
	//Load models
	
	Model ourModel("nanosuit/nanosuit.obj");

	while (!glfwWindowShouldClose(mywindow.window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		camera.ProcessKeyboard(deltaTime);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();

		//π€≤Ïæÿ’Û
		glm::mat4 view;
		//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		view = camera.GetViewMatrix();
		//Õ∂”∞æÿ’Û
		glm::mat4 projection;
		projection = glm::perspective(45.0f, (screenWidth / screenHeight), 0.1f, 100.0f);

		//glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		/******************************///The position of light

		// Draw the loaded model
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		ourModel.Draw(shader);

		glfwSwapBuffers(mywindow.window);

	}
	
	glfwTerminate();

	return 0;


}