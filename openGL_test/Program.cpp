#include "Program.h"
#include <glad/glad.h> 
#include <iostream> 
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "AN_GL_utils.h"
#include "sceneAxis.h"
#include "sceneGrid.h"
#include <time.h>
#include "quatCamera.h"
#include "renderPost.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <vector>
#include <memory>
using namespace std;

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

auto cam = make_unique<Camera>(glm::vec3(0, 8, -20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
auto qcam = make_unique<quatCamera>();
//Camera *cam = new Camera(glm::vec3(0, 8, -20), -10.0f, 0.0f, glm::vec3(0, 1, 0));
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
		cam->speedX = deltaX*5;
		cam->speedY = deltaY*5;
		cam->updateCamVectors();
		break;
	case MOVE:
		cam->speedX = deltaX;
		cam->speedY = deltaY;
		qcam->translateLocal(deltaX/50, deltaY/50,0);
		break;
	case SCALE:
		cam->speedZ = deltaX;
		qcam->translateLocal(0.0f, 0.0f, deltaX/50);
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
		//cam->Target = glm::vec3(0, 0, 0);
		cam->Target = cam->Position + cam->Forward*30.0f;
		cam->computeDistance();
		cam->MODE = cam->MODE_ROTATE;
		PRESSMODE = ROTATE;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		cam->MODE = cam->MODE_MOVE;
		PRESSMODE = MOVE;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		cam->MODE = cam->MODE_ZOOM;
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
	//使用深度信息,画出来的结果有遮挡关系
	glEnable(GL_DEPTH_TEST);

	//关闭鼠标绘制
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

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//UV属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
#pragma endregion

#pragma region load Textures
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//texture载入,放到3号槽,这个槽序号需要在之后的主循环体中调用,需要小于16
	unsigned int textureA = loadImageToGPU(3,"F:/FFOutput/Pictures/02.TEX2/Frabic/Knitting_Patterns_02_Base_Color.jpg");
	//放到5号槽位
	unsigned int textureB = loadImageToGPU(5, "F:/FFOutput/Download/awesomeface.png");

#pragma endregion

#pragma region init matrixs
	/*
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));//位移矩阵
	trans = glm::rotate(trans, glm::radians(90.0f),glm::vec3(0,0,1));//旋转矩阵
	trans = glm::scale(trans, glm::vec3(1.1,0.8,1));//缩放矩阵
	上面三行的效果是,先缩放,再旋转,最后位移
	*/

	glm::mat4 modelMat = glm::mat4(1.0f);//物体矩阵
	glm::mat4 viewMat = glm::mat4(1.0f);//摄像机矩阵
	glm::mat4 projMat = glm::mat4(1.0f);//投射矩阵
	//摄像机张角45度,分辨率1000x1000,宽高比为1,nearest为0.1,faster为100
	projMat = glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, 0.1f, 100.0f);
	viewMat = cam->GetViewMatrix();
#pragma endregion

#pragma region render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);// 检查输入
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//清除并渲染背景
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色缓冲和深度缓冲


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
			myShader1->setInt("ourTexture", 3);//设置shader的两张贴图,读取之前设置的槽位
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
				// 检查并调用事件，交换缓冲
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
	//deletecam;
#pragma endregion

}


//void drawAxi()
//{
//	glPointSize(10);
//	glVertexArrayAttribBinding
//
//
//}

void glProgramModel(GLFWwindow* window)
{
#pragma region init
	//使用深度信息,画出来的结果有遮挡关系
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//关闭鼠标绘制
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	clock_t startTime, endTime;
#pragma endregion

	//create shader program
	auto myShader1 = make_unique<Shader>("vertexSource_textures.vert", "fragmentSource_textures.frag");
	auto axis = make_unique<sceneAxis>();
	auto grid = make_unique<sceneGrid>();

	auto rPost = make_unique<renderPost>();

#pragma region load VAO VBO
	//Mesh cube(verticesB);
	//Model *md = new Model("F:/FFOutput/Download/AOVs/glModels/A.obj");
	auto md2 = make_unique<Model>("F:/FFOutput/Download/AOVs/glModels/A.obj");
	//unique_ptr<Model> md2(new Model("F:/FFOutput/Download/AOVs/glModels/B.obj"));
	//Model *md2 = new Model("F:/FFOutput/Download/AOVs/glModels/B.obj");
	
	vector< std::unique_ptr<Model> > mods;
	mods.push_back(std::move(md2));

#pragma endregion

#pragma region load Textures
	// 为当前绑定的纹理对象设置环绕、过滤方式
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	////texture载入,放到3号槽,这个槽序号需要在之后的主循环体中调用,需要小于16
	//unsigned int textureA = loadImageToGPU(3, "F:/FFOutput/Pictures/02.TEX2/Frabic/Knitting_Patterns_02_Base_Color.jpg");
	////放到5号槽位
	//unsigned int textureB = loadImageToGPU(5, "F:/FFOutput/Download/awesomeface.png");

#pragma endregion

#pragma region init matrixs
	glm::mat4 modelMat = glm::mat4(1.0f);//物体矩阵
	glm::mat4 viewMat = glm::mat4(1.0f);//摄像机矩阵
	glm::mat4 projMat = glm::mat4(1.0f);//投射矩阵
	//摄像机张角45度,分辨率1000x1000,宽高比为1,nearest为0.1,faster为100
	projMat = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);
	viewMat = cam->GetViewMatrix();
	glm::mat4 ident = glm::mat4(1.0f);//单位矩阵

#pragma endregion
	//rPost->setUsePost(false);

#pragma region render loop

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);// 检查输入
		rPost->bind();
		//glDepthFunc(GL_LESS);
			
		modelMat = ident;
		for (unsigned int i = 0; i < mods.size(); i++)
		{
			//绘制物体
			//glStencilMask(0xFF);
			//glStencilFunc(GL_ALWAYS, 1, 0xFF);

			//SET MATERIAL -> Shader Program
			myShader1->use();
			myShader1->setMat4("viewMat", viewMat);
			myShader1->setMat4("projMat", projMat);
			myShader1->setMat4("modelMat", modelMat);
			mods[i]->Draw(myShader1);

			////绘制轮廓线
			//myShader_outline->use();
			////
			//glStencilMask(0x00);
			//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			//myShader_outline->setMat4("viewMat", viewMat);
			//myShader_outline->setMat4("projMat", projMat);
			//modelMat = glm::scale(modelMat, { 1.01,1.01,1.01 });
			//myShader_outline->setMat4("modelMat", modelMat);
			//mods[i]->Draw(myShader_outline);
			//glStencilMask(0xFF);
			//glClear(GL_STENCIL_BUFFER_BIT);
		}
		

		grid->Draw(viewMat, projMat);
		axis->Draw(viewMat, projMat);
		rPost->use();


		cam->setStop();
		//prepare for next render loop
				// 检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
		//camera
		cam->updateCamPos();
		viewMat = cam->GetViewMatrix();
		//viewMat = qcam->getViewMatrix();
	}
#pragma endregion


}
