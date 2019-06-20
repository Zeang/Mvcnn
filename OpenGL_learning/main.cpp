#include "shader.h"
#include "camera.h"
#include "model.h"
#include <vector>
#include <fstream>

extern Camera camera;

struct Point {
	glm::vec3 trans;
	glm::vec3 color;
};

int main()
{
	const string name1("10aa040f470500c6a66ef8df4909ded9");
	const string name2("1021a0914a7207aff927ed529ad90a11");

	const string name("1021a0914a7207aff927ed529ad90a11");
	const string path("data_past1/mesh/" + name + ".txt");
	const string model_dir("planet/planet.obj");
	Window mywindow("MVCNN", screenWidth, screenHeight);
	Shader InstanceShader("shaders/Instancing.vs", "shaders/Instancing.frag");
	Model sphere(model_dir.c_str());

	std::vector<glm::mat4> Trans;
	std::vector<glm::vec3> colors;
	
	ifstream fin(path);
	GLfloat x, y, z;
	GLfloat r, g, b;
	glm::mat4 model;
	GLfloat scale = 0.002;

	while (fin >> x >> y >> z >> r >> g >> b)
	{
		glm::vec3 trans(x, y, z);
		glm::vec3 color(r, g, b);
		color = glm::normalize(color);
		color.x = (color.x + 1) / 2;
		color.y = (color.y + 1) / 2;
		color.z = (color.z + 1) / 2;
		color = glm::normalize(color);

		glm::mat4 model;
		colors.push_back(color);
		model = glm::translate(model, trans);
		model = glm::scale(model, glm::vec3(scale));

		Trans.push_back(model);
	}
	
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.0001f, 10000.0f);
	glm::vec3 lightPos(0.0f, 10.0f, 5.0f);
	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

	InstanceShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(InstanceShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3f(glGetUniformLocation(InstanceShader.Program, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(InstanceShader.Program, "lightColor"), lightColor.x, lightColor.y, lightColor.z);

	//Game loop
	while (!glfwWindowShouldClose(mywindow.window))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//Check and call events
		glfwPollEvents();
		camera.ProcessKeyboard(deltaTime);

		glClearColor(0.4f, 0.38f, 0.42f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		InstanceShader.Use();
		glUniformMatrix4fv(glGetUniformLocation(InstanceShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
		glUniform3f(glGetUniformLocation(InstanceShader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		for (unsigned int i = 0; i < Trans.size(); i++)
		{
			InstanceShader.Use();
			glUniformMatrix4fv(glGetUniformLocation(InstanceShader.Program, "trans"), 1, GL_FALSE, glm::value_ptr(Trans[i]));
			glUniform3f(glGetUniformLocation(InstanceShader.Program, "color"), colors[i].x, colors[i].y, colors[i].z);
			sphere.Draw(InstanceShader);

		}
		
		glfwSwapBuffers(mywindow.window);

	}
	glfwTerminate();

	return 0;
}