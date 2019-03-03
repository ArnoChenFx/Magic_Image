#include "Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h> 

#include <iostream> 
#include "Program.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void initWindow()
{
	//初始化glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//opengl 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建glfw窗口
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "ARNO OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	//将glfw窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);

	//判断glad是否正确加载
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return;
	}


	//初始化glew
	//glewExperimental = true;
	//if (glewInit() != GLEW_OK) {
	//	std::cout << "Failed to init glew" << std::endl;
	//	glfwTerminate();
	//	return;
	//}

	//设置opengl窗口大小
	glViewport(0, 0, 1000, 1000);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);//背面剔除

	//设置glfw的callback.每次调整窗口大小都更新gl窗口大小
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//render
	glProgramModel(window);

	glfwTerminate();
}
