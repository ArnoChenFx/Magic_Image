#include "Program.h"
#include <glad/glad.h> 
#include <iostream> 
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "AN_GL_utils.h"

#include <time.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#pragma region Model Data
	// set up vertex data (and buffer(s)) and configure vertex attributes
	//data
float vertices[] = {
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

float verticesB[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

glm::vec3 cubePositions[] = {
glm::vec3(0.0f,  0.0f,  0.0f),
glm::vec3(2.0f,  5.0f, -15.0f),
glm::vec3(-1.5f, -2.2f, -2.5f),
glm::vec3(-3.8f, -2.0f, -12.3f),
glm::vec3(2.4f, -0.4f, -3.5f),
glm::vec3(-1.7f,  3.0f, -7.5f),
glm::vec3(1.3f, -2.0f, -2.5f),
glm::vec3(1.5f,  2.0f, -2.5f),
glm::vec3(1.5f,  0.2f, -1.5f),
glm::vec3(-1.3f,  1.0f, -1.5f)
};

#pragma endregion

#pragma region Attribute Data
float preX;
float preY;
bool firstMouse = true;
Camera *cam = new Camera(glm::vec3(0, 8, -20), -10.0f, 0.0f, glm::vec3(0, 1, 0));
const int LOOP = 0;
const int MOVE = 1;
const int SCALE = 2;
const int ROTATE = 3;
int PRESSMODE = LOOP;
#pragma endregion

#pragma region Mouse callback

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow* window, double posX, double posY)
{
	if (firstMouse == true) {
		preX = posX;
		preY = posY;
		firstMouse = false;
	}
	float deltaX, deltaY;
	deltaX = posX - preX;
	deltaY = posY - preY;
	preX = posX;
	preY = posY;

	switch (PRESSMODE)
	{
	case LOOP:
		break;
	case ROTATE:
		cam->processMovement(-deltaX, -deltaY);
		break;
	case MOVE:
		cam->speedX = deltaX;
		cam->speedY = deltaY;
		break;
	case SCALE:
		cam->speedZ = deltaX;
		break;
	default:
		return;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		PRESSMODE = ROTATE;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		PRESSMODE = MOVE;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		PRESSMODE = SCALE;
		break;
	default:
		return;
	}

	else if (action == GLFW_RELEASE)
	{
		PRESSMODE = LOOP;
		cam->setStop();
	}

	return;

}

#pragma endregion


void glProgram(GLFWwindow* window)
{
#pragma region init
	//ʹ�������Ϣ,�������Ľ�����ڵ���ϵ
	glEnable(GL_DEPTH_TEST);

	//�ر�������
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	clock_t startTime, endTime;
#pragma endregion

	//create shader program
	Shader *myShader1 = new Shader("vertexSource2_uv.vert", "fragmentSource2_uv.frag");
	
#pragma region load VAO VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//UV����
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
#pragma endregion

#pragma region load Textures
	// Ϊ��ǰ�󶨵������������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//texture����,�ŵ�3�Ų�,����������Ҫ��֮�����ѭ�����е���,��ҪС��16
	unsigned int textureA = loadImageToGPU(3,"F:/FFOutput/Pictures/02.TEX2/Frabic/Knitting_Patterns_02_Base_Color.jpg");
	//�ŵ�5�Ų�λ
	unsigned int textureB = loadImageToGPU(5, "F:/FFOutput/Download/awesomeface.png");

#pragma endregion

#pragma region init matrixs
	/*
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));//λ�ƾ���
	trans = glm::rotate(trans, glm::radians(90.0f),glm::vec3(0,0,1));//��ת����
	trans = glm::scale(trans, glm::vec3(1.1,0.8,1));//���ž���
	�������е�Ч����,������,����ת,���λ��
	*/

	glm::mat4 modelMat = glm::mat4(1.0f);//�������
	glm::mat4 viewMat = glm::mat4(1.0f);//���������
	glm::mat4 projMat = glm::mat4(1.0f);//Ͷ�����
	//������Ž�45��,�ֱ���1000x1000,���߱�Ϊ1,nearestΪ0.1,fasterΪ100
	projMat = glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, 0.1f, 100.0f);
	viewMat = cam->GetViewMatrix();
#pragma endregion

#pragma region render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);// �������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//�������Ⱦ����
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ�������Ȼ���


		for (unsigned int i = 0; i < 10; i++)
		{
			//SET Model Matrix
			glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			modelMat = glm::rotate(modelMat, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
			myShader1->setMat4("modelMat", modelMat);

			//SET View and Projection Matrixs here


			//SET MATERIAL -> Shader Program
			myShader1->use();
			//SET MATERIAL -> Texture
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, textureA);
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, textureB);
			//SET MATERIAL -> Unifrom Attributes
			myShader1->setInt("ourTexture", 3);//����shader��������ͼ,��ȡ֮ǰ���õĲ�λ
			myShader1->setInt("ourTextureB", 5);
			myShader1->setMat4("modelMat", modelMat);
			myShader1->setMat4("viewMat", viewMat);
			myShader1->setMat4("projMat", projMat);


			//SET Model
			glBindVertexArray(VAO);
			//DrallCall
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		cam->setStop();
		//prepare for next render loop
				// ��鲢�����¼�����������
		glfwSwapBuffers(window);
		glfwPollEvents();
				//camera
		cam->updateCamPos();
		viewMat = cam->GetViewMatrix();
	}
#pragma endregion

#pragma region clear
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete myShader1;
	delete cam;
#pragma endregion

}


void glProgramModel(GLFWwindow* window)
{
#pragma region init
	//ʹ�������Ϣ,�������Ľ�����ڵ���ϵ
	glEnable(GL_DEPTH_TEST);

	//�ر�������
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	clock_t startTime, endTime;
#pragma endregion

	//create shader program
	Shader *myShader1 = new Shader("vertexSource_textures.vert", "fragmentSource_textures.frag");

#pragma region load VAO VBO
	//Mesh cube(verticesB);
	Model md("F:/FFOutput/Download/AOVs/glModels/A.obj");
	//nanosuit/nanosuit.obj

#pragma endregion

#pragma region load Textures
	// Ϊ��ǰ�󶨵������������û��ơ����˷�ʽ
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	////texture����,�ŵ�3�Ų�,����������Ҫ��֮�����ѭ�����е���,��ҪС��16
	//unsigned int textureA = loadImageToGPU(3, "F:/FFOutput/Pictures/02.TEX2/Frabic/Knitting_Patterns_02_Base_Color.jpg");
	////�ŵ�5�Ų�λ
	//unsigned int textureB = loadImageToGPU(5, "F:/FFOutput/Download/awesomeface.png");

#pragma endregion

#pragma region init matrixs
	/*
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));//λ�ƾ���
	trans = glm::rotate(trans, glm::radians(90.0f),glm::vec3(0,0,1));//��ת����
	trans = glm::scale(trans, glm::vec3(1.1,0.8,1));//���ž���
	�������е�Ч����,������,����ת,���λ��
	*/

	glm::mat4 modelMat = glm::mat4(1.0f);//�������
	glm::mat4 viewMat = glm::mat4(1.0f);//���������
	glm::mat4 projMat = glm::mat4(1.0f);//Ͷ�����
	//������Ž�45��,�ֱ���1000x1000,���߱�Ϊ1,nearestΪ0.1,fasterΪ100
	projMat = glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, 0.1f, 100.0f);
	viewMat = cam->GetViewMatrix();
#pragma endregion

#pragma region render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);// �������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//�������Ⱦ����
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ�������Ȼ���


		for (unsigned int i = 0; i < 1; i++)
		{
			//SET Model Matrix
			//glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			//modelMat = glm::rotate(modelMat, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
			//myShader1->setMat4("modelMat", modelMat);

			//SET View and Projection Matrixs here


			//SET MATERIAL -> Shader Program
			myShader1->use();

			//SET MATERIAL -> Texture
			//glActiveTexture(GL_TEXTURE3);
			//glBindTexture(GL_TEXTURE_2D, textureA);
			//glActiveTexture(GL_TEXTURE5);
			//glBindTexture(GL_TEXTURE_2D, textureB);
			//SET MATERIAL -> Unifrom Attributes
			//myShader1->setInt("ourTextureA", 3);//����shader��������ͼ,��ȡ֮ǰ���õĲ�λ
			//myShader1->setInt("ourTextureB", 5);

			myShader1->setMat4("modelMat", modelMat);
			myShader1->setMat4("viewMat", viewMat);
			myShader1->setMat4("projMat", projMat);

			md.Draw(myShader1);
			//cube.Draw(myShader1);

		}

		cam->setStop();
		//prepare for next render loop
				// ��鲢�����¼�����������
		glfwSwapBuffers(window);
		glfwPollEvents();
		//camera
		cam->updateCamPos();
		viewMat = cam->GetViewMatrix();
	}
#pragma endregion

#pragma region clear
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);

	delete myShader1;
	delete cam;
#pragma endregion

}