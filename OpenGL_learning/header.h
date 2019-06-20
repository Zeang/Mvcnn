#pragma once
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
extern string str_vertex_shader;
extern string str_fragment_shader;

void read_shader();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);