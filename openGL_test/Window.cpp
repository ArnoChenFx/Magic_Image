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
	//��ʼ��glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//opengl 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//����glfw����
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "ARNO OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	//��glfw���ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);

	//�ж�glad�Ƿ���ȷ����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return;
	}


	//��ʼ��glew
	//glewExperimental = true;
	//if (glewInit() != GLEW_OK) {
	//	std::cout << "Failed to init glew" << std::endl;
	//	glfwTerminate();
	//	return;
	//}

	//����opengl���ڴ�С
	glViewport(0, 0, 1000, 1000);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);//�����޳�

	//����glfw��callback.ÿ�ε������ڴ�С������gl���ڴ�С
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//render
	glProgramModel(window);

	glfwTerminate();
}
