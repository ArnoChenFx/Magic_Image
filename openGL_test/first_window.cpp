#include "first_window.h"
#include <glad/glad.h> 
//#include <GL/glew.h>
#include <iostream> 
#include "Shader.h"
#include "Camera.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <time.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*


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
Camera *cam = new Camera(glm::vec3(0, 0, 3), -10.0f, 175.0f, glm::vec3(0, 1, 0));
const int LOOP = 0;
const int MOVE = 1;
const int SCALE = 2;
const int ROTATE = 3;
int PRESSMODE = LOOP;
#pragma endregion

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
		printf("left mouse\n");
		PRESSMODE = ROTATE;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		printf("middle mouse\n");
		PRESSMODE = MOVE;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		printf("right mouse\n");
		PRESSMODE = SCALE;
		break;
	default:
		return;
	}

	else if (action == GLFW_RELEASE)
	{
		PRESSMODE = LOOP;
		cam->setStop();
		printf("release mode\n");
	}

	return;

}


void initRender(GLFWwindow* window)
{
	Shader *testShader = new Shader("vertexSource0.vert", "fragmentSource0.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	//data
	float vertices[] = {
	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	0.5f, -0.5f, 0.0f,  // ���½�
	-0.5f, -0.5f, 0.0f, // ���½�
	-0.5f, 0.5f, 0.0f   // ���Ͻ�
	};


	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	//����һ��VBO����;���㻺�����(Vertex Buffer Objects, VBO)
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	//VBO
	//���´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//��֮ǰ����Ķ������ݸ��Ƶ�������ڴ���
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
	//GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ
	//GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣

	//EBO,��֮ǰ�����indices���ݸ��Ƶ�������ڴ���
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//��������OpenGL����ν�����������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// ..:: ��ʼ������ :: ..
	//// 1. �󶨶����������
	//glBindVertexArray(VAO);
	//// 2. �����ǵĶ������鸴�Ƶ�һ�����㻺���У���OpenGLʹ��
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//// 3. �������ǵ��������鵽һ�����������У���OpenGLʹ��
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//// 4. �趨��������ָ��
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	// ..:: ���ƴ��루��Ⱦѭ���У� :: ..
	//glUseProgram(shaderProgram);
	//glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0)
	//glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//Ĭ��ģʽ
	while (!glfwWindowShouldClose(window))
	{
		// �������
		processInput(window);

		//��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		testShader->use();
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(0);

		// ��鲢�����¼�����������
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1, &EBO);

	delete testShader;
}

void initRender2(GLFWwindow* window)
{
	//create shader program
	Shader *testShader1 = new Shader("vertexSource1.vert","fragmentSource1.frag");
	Shader *testShader2 = new Shader("vertexSource0.vert", "fragmentSource2.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	//data
	float firstTriangle[] = {
	 -0.9f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
	 -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // ����
	 -0.45f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	};
	float secondTriangle[] = {
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	};

	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
	glGenBuffers(2, VBOs);
	// first triangle setup
	// --------------------
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	//glEnableVertexAttribArray(0);
	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
	// second triangle setup
	// ---------------------
	glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
	glEnableVertexAttribArray(0);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//Ĭ��ģʽ
	while (!glfwWindowShouldClose(window))
	{
		// �������
		processInput(window);

		//��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//1
		testShader1->use();
		// draw the first triangle using the data from our first VAO
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);	// this call should output an orange triangle

		//2
		testShader2->use();

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		testShader2->setFloat("ourColor", greenValue);

		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);	// this call should output a yellow triangle

		// ��鲢�����¼�����������
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	delete testShader1;
	delete testShader2;
	
}

void initRender3(GLFWwindow* window)
{
	//create shader program
	Shader *testShader1 = new Shader("vertexSource2_uv.vert", "fragmentSource2_uv.frag");

	clock_t startTime, endTime;
	

	// set up vertex data (and buffer(s)) and configure vertex attributes
	//data
	float h = 0.5;
	float w = h * 9 / 16.0f;
	float vertices[] = {
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
			 h,  w, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
			 h, -w, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
			-h, -w, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
			-h,  w, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
	};
	float vertices2[] = {
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
	};


	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,  // first Triangle
		2, 3, 0   // second Triangle
	};

	unsigned int VBO, VAO ,EBO;
	glGenVertexArrays(1, &VAO); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//UV����
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//texture����
	unsigned int texture;
	glGenTextures(1, &texture);
	//�ŵ�3�Ų�λ
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ���ز���������
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char *data = stbi_load("F:/FFOutput/Download/AOVs/AOV_rgb.png", &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//textureB����
	unsigned int textureB;
	glGenTextures(1, &textureB);
	//�ŵ�5�Ų�λ
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, textureB);
	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ���ز���������
	int widthB, heightB, nrChannelsB;
	unsigned char *dataB = stbi_load("F:/FFOutput/Download/AOVs/bot_0.effectsResult.png", &widthB, &heightB, &nrChannelsB, 0);

	if (dataB)
	{
		if(nrChannelsB==3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthB, heightB, 0, GL_RGB, GL_UNSIGNED_BYTE, dataB);
		else if (nrChannelsB == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthB, heightB, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataB);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(dataB);

	glm::mat4 trans = glm::mat4(1.0f);//��λ����
	//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));//λ�ƾ���
	//trans = glm::rotate(trans, glm::radians(90.0f),glm::vec3(0,0,1));//��ת����
	//trans = glm::scale(trans, glm::vec3(1.1,0.8,1));//���ž���
	//�������е�Ч����,������,����ת,���λ��
	
	glm::mat4 modelMat = glm::mat4(1.0f);//�������
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1, 0, 0));

	//�������0,0-3λ��,��������Ҫ�ƶ�0,0,3
	glm::mat4 viewMat = glm::mat4(1.0f);//���������
	viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3));

	//������Ž�45��,�ֱ���1000x1000,��߱�Ϊ1,nearestΪ0.1,fasterΪ100
	glm::mat4 projMat = glm::mat4(1.0f);//Ͷ�����
	projMat = glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window))
	{
		//startTime = clock();
		//trans = glm::translate(trans, glm::vec3(0.001f, 0.0f, 0.0f));
		//trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(0, 0, 1));

		//glm::mat4 trans = glm::mat4(1.0f);
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0, 0, 1));

		// �������
		processInput(window);

		//��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//1
		testShader1->use();
		testShader1->setInt("ourTexture", 3);//����shader��������ͼ
		testShader1->setInt("ourTextureB", 5);
		unsigned int transfromLoc = glGetUniformLocation(testShader1->ID, "transform");
		glUniformMatrix4fv(transfromLoc,1,GL_FALSE,glm::value_ptr(modelMat));

		glUniformMatrix4fv(glGetUniformLocation(testShader1->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniformMatrix4fv(glGetUniformLocation(testShader1->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(testShader1->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));


		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		// ��鲢�����¼�����������
		glfwSwapBuffers(window);
		glfwPollEvents();

		//endTime = clock();
		//std::cout << "draw one picture : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete testShader1;
}

void initRender4(GLFWwindow* window)
{
	//ʹ�������Ϣ,�������Ľ�����ڵ���ϵ
	glEnable(GL_DEPTH_TEST);

	//�ر�������
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	//create shader program
	Shader *testShader1 = new Shader("vertexSource2_uv.vert", "fragmentSource2_uv.frag");
	//Camera *cam = new Camera(glm::vec3(0,0,3),glm::vec3(0,0,0), glm::vec3(0, 1, 0));

	clock_t startTime, endTime;

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

	//texture����
	unsigned int texture;
	glGenTextures(1, &texture);
	//�ŵ�3�Ų�λ
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ���ز���������
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char *data = stbi_load("F:/FFOutput/Pictures/02.TEX2/Frabic/Knitting_Patterns_02_Base_Color.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//textureB����
	unsigned int textureB;
	glGenTextures(1, &textureB);
	//�ŵ�5�Ų�λ
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, textureB);

	// ���ز���������
	int widthB, heightB, nrChannelsB;
	unsigned char *dataB = stbi_load("F:/FFOutput/Download/awesomeface.png", &widthB, &heightB, &nrChannelsB, 0);

	if (dataB)
	{
		if (nrChannelsB == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthB, heightB, 0, GL_RGB, GL_UNSIGNED_BYTE, dataB);
		else if (nrChannelsB == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthB, heightB, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataB);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(dataB);

	glm::mat4 trans = glm::mat4(1.0f);//��λ����
	//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));//λ�ƾ���
	//trans = glm::rotate(trans, glm::radians(90.0f),glm::vec3(0,0,1));//��ת����
	//trans = glm::scale(trans, glm::vec3(1.1,0.8,1));//���ž���
	//�������е�Ч����,������,����ת,���λ��

	glm::mat4 modelMat = glm::mat4(1.0f);//�������
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1, 0, 0));

	//�������0,0-3λ��,��������Ҫ�ƶ�0,0,3
	glm::mat4 viewMat = glm::mat4(1.0f);//���������
	//viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3));
	viewMat = cam->GetViewMatrix();

	//������Ž�45��,�ֱ���1000x1000,��߱�Ϊ1,nearestΪ0.1,fasterΪ100
	glm::mat4 projMat = glm::mat4(1.0f);//Ͷ�����
	projMat = glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window))
	{

		// �������
		processInput(window);

		//��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//�����ɫ�������Ȼ���
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam->updateCamPos();
		viewMat = cam->GetViewMatrix();

		testShader1->use();
		testShader1->setInt("ourTexture", 3);//����shader��������ͼ
		testShader1->setInt("ourTextureB", 5);

		//testShader1->setMat4("transform", trans);
		testShader1->setMat4("modelMat", modelMat);
		testShader1->setMat4("viewMat", viewMat);
		testShader1->setMat4("projMat", projMat);

		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			testShader1->setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		cam->setStop();

		// ��鲢�����¼�����������
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete testShader1;
	delete cam;
}

*/