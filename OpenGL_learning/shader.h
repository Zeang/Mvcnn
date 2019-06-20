#pragma once
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <map>
#include <algorithm>
#include <vector>


class Shader
{
public:
	GLuint Program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void Use();
};

class Window
{
public:
	GLFWwindow* window;
	int Height;
	int Width;
	std::string window_name;

	Window(std::string name, int W, int H);


};

extern GLfloat vertices[];
extern float cubeVertices[];
extern GLfloat planeVertices[];
extern GLuint indices[];
extern glm::vec3 cubePositions[];

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;

extern bool keys[1024];
extern GLfloat deltaTime;
extern GLfloat lastFrame;

extern GLfloat lastX, lastY;
extern GLfloat pitch, yaw;
extern bool firstMouse;
extern glm::vec3 lightPos;
extern glm::vec3 pointLightPosition[];
extern GLfloat vegetationVertices[];
extern float quadVertices[];
extern float skyboxVertices[];
extern GLfloat points[];

extern const float screenWidth;
extern const float screenHeight;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
GLuint loadTexture(const GLchar* path);
GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);
GLuint loadCubemap(std::vector<const GLchar*> faces);
GLuint generateMultiSampleTexture(GLuint samples);
