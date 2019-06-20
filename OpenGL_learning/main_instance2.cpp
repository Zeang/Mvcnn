#include "shader.h"
#include "camera.h"
#include "model.h"

extern Camera camera;

int main()
{
	Window mywindow("Learn_Instance", screenWidth, screenHeight);
	
	//Shader shader("Instance.vs", "Instance.frag");
	Shader instanceShader("shaders/Instancing.vs", "shaders/Instancing.frag");
	//Shader planetShader("shaders_past/planet.vs", "shaders_past/planet.frag");

	Model rock("rock/rock.obj");
	//Model planet("planet/planet.obj");
	glm::mat4 projection = glm::perspective(45.0f, screenWidth / screenHeight, 1.0f, 10000.0f);
	//planetShader.Use();
	//glUniformMatrix4fv(glGetUniformLocation(planetShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	instanceShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(instanceShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


	
	GLuint amount = 1000;
	glm::mat4* modelMatrices;
	modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime());
	GLfloat radius = 150.0;
	GLfloat offset = 25.0f;
	for (GLuint i = 0; i < amount; i++)
	{
		glm::mat4 model;
		//1.Translation: displace along circle with 'radius' in range [-offset, offset]
		GLfloat angle = (GLfloat)i / (GLfloat)amount * 360.0f;
		GLfloat displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat x = sin(angle) * radius + displacement;
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat y =-2.5f + displacement * 0.4f;
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));
		//2. Scale: Scale between 0.05 and 0.25f
		GLfloat scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));

		//3.Rotation: add random rotation around a (semi)randomly picked rotation axis vevctor
		GLfloat rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
		//4 Now add to list of matrices
		modelMatrices[i] = model;

	}

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
	
	for (GLuint i = 0; i < rock.meshes.size(); i++)
	{
		GLuint VAO = rock.meshes[i].VAO;
		//Vertex Buffer Object
		/*GLuint buffer;
		glBindVertexArray(VAO);
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);*/
		//Vertex Attributes
		glBindVertexArray(VAO);
		GLsizei vec4Size = sizeof(glm::vec4);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(vec4Size));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(2 * vec4Size));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(3 * vec4Size));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);

	}


	//Game loop
	while (!glfwWindowShouldClose(mywindow.window))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		camera.ProcessKeyboard(deltaTime);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//planetShader.Use();
		//glUniformMatrix4fv(glGetUniformLocation(planetShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
		instanceShader.Use();
		glUniformMatrix4fv(glGetUniformLocation(instanceShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));

		//planetShader.Use();
		////Draw Planet
		//glm::mat4 model;
		//model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		//glUniformMatrix4fv(glGetUniformLocation(planetShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//planet.Draw(planetShader);

		instanceShader.Use();
		glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id);
		for (GLuint i = 0; i < rock.meshes.size(); i++)
		{
			glBindVertexArray(rock.meshes[i].VAO);
			glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
			glBindVertexArray(0);
		}
		static int Number = 0;
		Number++;
		if (Number >= 100)
		{
			Number = 0;
			std::cout << 1.0 / deltaTime << std::endl;
		}


		glfwSwapBuffers(mywindow.window);
	}

	delete[] modelMatrices;
	glfwTerminate();
	return 0;
}