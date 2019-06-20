#include "shader.h"
#include "camera.h"

extern Camera  camera;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	GLfloat cameraSpeed = 0.05f;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
	

}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	//��һ�ν��� ����LastX LastYΪ��ǰ��xpos, ypos
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		std::cout << "lastX: " << lastX << std::endl;
		std::cout << "lastY: " << lastY << std::endl;
		firstMouse = false;
	}

	//�ҳ�ƫ������ע��Y�������
	GLfloat xoffset = xpos - lastX;	
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMoveMent(xoffset, yoffset);

}
