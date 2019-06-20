#include "shader.h"



Window::Window(std::string name, int W, int H)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);


	this->window = glfwCreateWindow(W, H, name.c_str(), nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	/**********************************/
	//Êó±êÊäÈë
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	std::cout << "Width:\t" << width << std::endl;
	std::cout << "Height:\t" << height << std::endl;
	glViewport(0, 0, width, height);
	
	//Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	////

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	///*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	///*glFrontFace(GL_CW);*/

	//glEnable(GL_PROGRAM_POINT_SIZE);
	//glEnable(GL_MULTISAMPLE);

}