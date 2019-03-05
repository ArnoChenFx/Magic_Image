
#include <glad/glad.h> 
//#include <GLFW/glfw3.h>
#include "OpenGLWindow.h"
//#include "Camera.h"
//#include "Mesh.h"
#include "Model.h"
//#include "Shader.h"
#include "AN_GL_utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <qevent.h>
#include <qdebug.h>

static const char* vsShader = "attribute vec2 aPosition; void main() {gl_Position = vec4(aPosition, 0.0, 1.0);}";
static const char* fsShader = "precision mediump float; void main() {gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);}";

OpenGLWindow::OpenGLWindow(QWidget *parent):QOpenGLWidget(parent)
{
	this->resize(1920, 1080);
	firstMouse = true;
	PRESSMODE = LOOP;

	modelMat = glm::mat4(1.0f);//物体矩阵
	viewMat = glm::mat4(1.0f);//摄像机矩阵
	projMat = glm::mat4(1.0f);//投射矩阵
	projMat = glm::perspective(glm::radians(45.0f), (float)16 / (float)9, 0.1f, 100.0f);
	
}

OpenGLWindow::~OpenGLWindow()
{
	// Destroy OpenGL Handles
	delete cam;
	delete md;
	delete myShader1;
}

void OpenGLWindow::initializeGL()
{
	if (!gladLoadGL())
	{
		qDebug() << "Glad OpenGL Extensions couldn't load!";
	}
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);

	m_context = new QOpenGLContext(this);

	initObjects();
	
}

void OpenGLWindow::resizeGL(int w, int h)
{
	glViewport(0,0,w,h);
	projMat = glm::mat4(1.0f);//投射矩阵
	projMat = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
}

void OpenGLWindow::paintGL()
{
	render();
}

void OpenGLWindow::resizeEvent(QResizeEvent * event)
{
	
}

void OpenGLWindow::paintEvent(QPaintEvent * event)
{
}

void OpenGLWindow::initObjects()
{
	cam = new Camera(glm::vec3(0, 8, -20), -10.0f, 0.0f, glm::vec3(0, 1, 0));
	viewMat = cam->GetViewMatrix();
	myShader1 = new Shader("vertexSource_textures.vert", "fragmentSource_textures.frag");
	md = new Model("F:/FFOutput/Download/AOVs/glModels/A.obj");
}

void OpenGLWindow::mousePressEvent(QMouseEvent * event)
{
	qDebug() << "left press";
}


void OpenGLWindow::mouseMove(QMouseEvent * event)
{
	float deltaX, deltaY;
	float posX = event->pos().x();
	float posY = event->pos().y();
	deltaX = posX - preX;
	deltaY = event->pos().y() - preY;
	preX = posX;
	preY = posY;

	if (event->buttons() & Qt::LeftButton)
	{
		cam->processMovement(-deltaX, -deltaY);
		qDebug() << "rotate";
	}
	else if (event->buttons() & Qt::MiddleButton)
	{
		cam->speedX = deltaX;
		cam->speedY = deltaY;
		qDebug() << "move";
	}
	else if (event->buttons() & Qt::RightButton)
	{
		cam->speedZ = deltaX;
		qDebug() << "zoom";
	}
	render();
}

void OpenGLWindow::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//清除并渲染背景
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色缓冲和深度缓冲
	myShader1->use();
	myShader1->setMat4("modelMat", modelMat);
	myShader1->setMat4("viewMat", viewMat);
	myShader1->setMat4("projMat", projMat);

	md->Draw(myShader1);
	cam->setStop();

	//prepare for next render loop
			// 检查并调用事件，交换缓冲

	//glfwSwapBuffers(window);
	//glfwPollEvents();
	//m_context->swapBuffers();

	//camera
	cam->updateCamPos();
	viewMat = cam->GetViewMatrix();
}
