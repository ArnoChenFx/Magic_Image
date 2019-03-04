#include "OpenGLWindow.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "AN_GL_utils.h"
//#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glad/glad.h> 

OpenGLWindow::OpenGLWindow(QWidget *parent):QOpenGLWidget(parent), m_context(0)
{
	//resizeGL(1920,1080);
	this->resize(1920, 1080);

	firstMouse = true;
	PRESSMODE = LOOP;

	modelMat = QMatrix4x4();
	projMat = QMatrix4x4();
	modelMat = QMatrix4x4();
	//modelMat.
	//modelMat = glm::mat4(1.0f);//物体矩阵
	//viewMat = glm::mat4(1.0f);//摄像机矩阵
	//projMat = glm::mat4(1.0f);//投射矩阵
	//摄像机张角45度,分辨率1000x1000,宽高比为1,nearest为0.1,faster为100
	//projMat = glm::perspective(glm::radians(45.0f), (float)16 / (float)9, 0.1f, 100.0f);
	projMat.perspective(glm::radians(45.0f), (float)16 / (float)9, 0.1f, 100.0f);
	cam = new Camera(QVector3D(0, 8, -20), -10.0f, 0.0f, QVector3D(0, 1, 0));
}

OpenGLWindow::~OpenGLWindow()
{
	//makeCurrent();
	//delete myShader1;
	//delete cam;
	//doneCurrent();
}

void OpenGLWindow::initializeGL()
{
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);
	makeCurrent();

	//QOpenGLShaderProgram *m;
	//QOpenGLFramebufferObject *VAO;
	VBO = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	VBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
	EBO = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	EBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
	VAO.create();
	//VAO->setUsagePattern(QOpenGLBuffer::DynamicDraw);
	VAO.bind();
	//VBO->create();
	EBO.create();

	//create shader program
	myShader1 = new Shader("vertexSource_textures.vert", "fragmentSource_textures.frag");
	md = new Model("F:/FFOutput/Download/AOVs/glModels/untitled.obj", this);
	
	viewMat = cam->GetViewMatrix();
}

void OpenGLWindow::resizeGL(int w, int h)
{
	glViewport(0,0,w,h);
	projMat = QMatrix4x4();
	projMat.perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
}

void OpenGLWindow::paintGL()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//清除并渲染背景
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色缓冲和深度缓冲

	qDebug() << "GL WINDOW REFRESHED";
	for (unsigned int i = 0; i < 1; i++)
	{
		//makeCurrent();
		viewMat = cam->GetViewMatrix();
		//SET MATERIAL -> Shader Program
		myShader1->use();

		myShader1->shaderProgram->setUniformValue("modelMat", modelMat);
		//myShader1->shaderProgram->setUniformValue("viewMat", viewMat);
		//myShader1->shaderProgram->setUniformValue("projMat", projMat);
		//myShader1->setMat4("modelMat", modelMat);
		//myShader1->setMat4("viewMat", viewMat);
		//myShader1->setMat4("projMat", projMat);

		//md->Draw(myShader1);

		this->cam->setStop();
		//prepare for next render loop
				// 检查并调用事件，交换缓冲
		//glfwSwapBuffers(window);
		//glfwPollEvents();
		//m_context->swapBuffers(this);
		//camera
		cam->updateCamPos();
		viewMat = cam->GetViewMatrix();
	}
}

void OpenGLWindow::resizeEvent(QResizeEvent * event)
{
	
}

void OpenGLWindow::paintEvent(QPaintEvent * event)
{
}

void OpenGLWindow::initObjects()
{
	

	
}
