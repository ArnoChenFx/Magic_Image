#include <glad/glad.h> 
#include "OpenGLScene.h"
#include "Model.h"
#include "AN_GL_utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <qdebug.h>
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <qevent.h>

OpenGLScene::OpenGLScene(QWindow *parent):QWindow(parent)
	, m_animating(false)
	, m_context(0)
	//, m_device(0)
{
	setSurfaceType(QWindow::OpenGLSurface);

	hasInitialized = false;

	modelMat = glm::mat4(1.0f);//ÎïÌå¾ØÕó
	viewMat = glm::mat4(1.0f);//ÉãÏñ»ú¾ØÕó
	projMat = glm::mat4(1.0f);//Í¶Éä¾ØÕó
	projMat = glm::perspective(glm::radians(45.0f), (float)16 / (float)9, 0.1f, 100.0f);
	cam = new Camera(glm::vec3(0, 8, -40), -10.0f, 0.0f, glm::vec3(0, 1, 0));
	viewMat = cam->GetViewMatrix();

}

OpenGLScene::~OpenGLScene()
{
	// Destroy OpenGL Handles
	delete cam;
	delete md;
	delete myShader1;
	//delete m_device;
}

void OpenGLScene::initialize()
{
	if (!gladLoadGL())
	{
		qDebug() << "Glad OpenGL Extensions couldn't load!";
	}

	hasInitialized = true;
	glEnable(GL_DEPTH_TEST);
	initObjects();
}

void OpenGLScene::initObjects()
{
	myShader1 = new Shader("vertexSource_textures.vert", "fragmentSource_textures.frag");
	md = new Model("F:/FFOutput/Download/AOVs/glModels/B.obj");
}



void OpenGLScene::render()
{
	const qreal retinaScale = devicePixelRatio();
	glViewport(0, 0, width() * retinaScale, height() * retinaScale);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Çå³ýÑÕÉ«»º³åºÍÉî¶È»º³å
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//Çå³ý²¢äÖÈ¾±³¾°

	cam->updateCamPos();
	viewMat = cam->GetViewMatrix();

	myShader1->use();
	myShader1->setMat4("modelMat", modelMat);
	myShader1->setMat4("viewMat", viewMat);
	myShader1->setMat4("projMat", projMat);

	md->Draw(myShader1);

	cam->setStop();
}

void OpenGLScene::renderNow()
{
	if (!isExposed())
		return;

	bool needsInitialize = false;

	if (!m_context) {
		m_context = new QOpenGLContext(this);
		m_context->setFormat(requestedFormat());
		m_context->create();

		needsInitialize = true;
	}

	m_context->makeCurrent(this);

	if (needsInitialize) {
		initializeOpenGLFunctions();
		initialize();
	}

	render();

	m_context->swapBuffers(this);

	if (m_animating)
		renderLater();
}



bool OpenGLScene::event(QEvent * event)
{
	switch (event->type()) {
	case QEvent::UpdateRequest:
		renderNow();
		return true;
	default:
		return QWindow::event(event);
	}
}

void OpenGLScene::exposeEvent(QExposeEvent * event)
{
	Q_UNUSED(event);

	if (isExposed())
		renderNow();
}

void OpenGLScene::render(QPainter * painter)
{
	Q_UNUSED(painter);
}

void OpenGLScene::renderLater()
{
	requestUpdate();
}

void OpenGLScene::setRender(bool start)
{
	setAnimating(false);
}

void OpenGLScene::setAnimating(bool animating)
{

	m_animating = animating;

	if (animating)
		renderLater();
}

void OpenGLScene::resizeEvent(QResizeEvent * event)
{
	if (!hasInitialized) return;

	int w = event->size().width();
	int h = event->size().height();
	glViewport(0, 0, w, h);
	projMat = glm::mat4(1.0f);//Í¶Éä¾ØÕó
	projMat = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);

	QWindow::resizeEvent(event);
}


void OpenGLScene::mousePressEvent(QMouseEvent * event)
{
	setRender(true);
	QWindow::mousePressEvent(event);
}

void OpenGLScene::mouseReleaseEvent(QMouseEvent * event)
{
	setRender(false);
	QWindow::mouseReleaseEvent(event);
}

void OpenGLScene::mouseMoveEvent(QMouseEvent * event)
{
	setRender(true);

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
		//qDebug() << "rotate";
	}
	else if (event->buttons() & Qt::MiddleButton)
	{
		cam->speedX = deltaX;
		cam->speedY = deltaY;
		//qDebug() << "move";
	}
	else if (event->buttons() & Qt::RightButton)
	{
		cam->speedZ = deltaX;
		//qDebug() << "zoom";
	}
	else
		return;

	renderNow();

	QWindow::mouseMoveEvent(event);
}
