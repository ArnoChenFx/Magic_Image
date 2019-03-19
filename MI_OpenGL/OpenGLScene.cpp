#include <glad/glad.h> 
#include "OpenGLScene.h"
#include "Model.h"
#include "GL_utils.h"
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

	modelMat = glm::mat4(1.0f);//ŒÔÃÂæÿ’Û
	viewMat = glm::mat4(1.0f);//…„œÒª˙æÿ’Û
	projMat = glm::mat4(1.0f);//Õ∂…‰æÿ’Û
	projMat = glm::perspective(glm::radians(45.0f), (float)16 / (float)9, 0.1f, 100.0f);
	defaultCam = std::make_unique<Camera>(glm::vec3(0, 8, -20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	viewMat = defaultCam->GetViewMatrix();

	renderNow();
}

OpenGLScene::~OpenGLScene()
{
	// Destroy OpenGL Handles
	//delete cam;	
	//delete myShader1;
	//delete md;
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
	defaultShader = std::make_unique<Shader>("vertexSource_textures.vert", "fragmentSource_textures.frag");
	axis = std::make_unique<sceneAxis>();
	grid = std::make_unique<sceneGrid>();
	rPost = std::make_unique<renderPost>();
	rPost->setUsePost(false);
}



void OpenGLScene::render()
{
	const qreal retinaScale = devicePixelRatio();
	glViewport(0, 0, width() * retinaScale, height() * retinaScale);

	rPost->bind();
	

	defaultCam->updateCamPos();
	viewMat = defaultCam->GetViewMatrix();

	defaultShader->use();
	defaultShader->setMat4("modelMat", modelMat);
	defaultShader->setMat4("viewMat", viewMat);
	defaultShader->setMat4("projMat", projMat);

	for (int i = 0; i < models.size(); i++)
	{
		models[i]->Draw(defaultShader);
	}
	grid->Draw(viewMat, projMat);
	axis->Draw(viewMat, projMat);
	rPost->use();

	defaultCam->setStop();
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


glm::vec3 OpenGLScene::GetRayFromMouse(float x,float y)
{
	glm::vec2 ray_nds = glm::vec2(x, y);
	glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);
	glm::mat4 invProjMat = glm::inverse(defaultCam->GetViewMatrix());
	glm::vec4 eyeCoords = invProjMat * ray_clip;
	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
	glm::mat4 invViewMat = glm::inverse(defaultCam->GetViewMatrix());
	glm::vec4 rayWorld = invViewMat * eyeCoords;
	glm::vec3 rayDirection = glm::normalize(glm::vec3(rayWorld));

	return rayDirection;
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
	projMat = glm::mat4(1.0f);//Õ∂…‰æÿ’Û
	projMat = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);

	QWindow::resizeEvent(event);
}

void OpenGLScene::wheelEvent(QWheelEvent * event)
{
	setRender(true);

	float delta = event->angleDelta().y();
	defaultCam->speedZ = delta/2;
	renderNow();

	QWindow::wheelEvent(event);
}


void OpenGLScene::mousePressEvent(QMouseEvent * event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		defaultCam->Target = defaultCam->Position + defaultCam->Forward*30.0f;
		defaultCam->computeDistance();
		defaultCam->MODE = defaultCam->MODE_ROTATE;

	}
	else if (event->buttons() & Qt::MiddleButton)
	{
		defaultCam->MODE = defaultCam->MODE_MOVE;
	}
	else if (event->buttons() & Qt::RightButton)
	{
		defaultCam->MODE = defaultCam->MODE_ZOOM;
	}
	setRender(true);
	QWindow::mousePressEvent(event);
}

void OpenGLScene::mouseReleaseEvent(QMouseEvent * event)
{
	setRender(false);
	defaultCam->setStop();
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
		defaultCam->speedX = deltaX * 5;
		defaultCam->speedY = deltaY * 5;
		defaultCam->updateCamVectors();
		//qDebug() << "rotate";
	}
	else if (event->buttons() & Qt::MiddleButton)
	{

		defaultCam->speedX = deltaX;
		defaultCam->speedY = deltaY;
		//qDebug() << "move";
	}
	else if (event->buttons() & Qt::RightButton)
	{
		defaultCam->speedZ = deltaX;
		//qDebug() << "zoom";
	}
	else
		return;

	renderNow();

	QWindow::mouseMoveEvent(event);
}

