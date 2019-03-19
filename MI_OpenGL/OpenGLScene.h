#pragma once
#include <glm/glm.hpp>
#include <qopenglfunctions.h>
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include <string>
#include <QEvent>
#include <qwindow.h>
#include <qlist.h>
#include "mi_opengl_global.h"
#include <memory>
#include "sceneAxis.h"
#include "sceneGrid.h"
#include "renderPost.h"

class MI_OPENGL_EXPORT OpenGLScene : public QWindow, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit OpenGLScene(QWindow *parent = nullptr);
	~OpenGLScene();

	std::unique_ptr<Shader> defaultShader;
	Shader *myShader1;
	//Model *md;

	void setRender(bool start = false);
	QList<Model*> models;
private:
	std::unique_ptr<sceneAxis> axis;
	std::unique_ptr<sceneGrid> grid;
	std::unique_ptr<renderPost> rPost;

	std::unique_ptr<Camera> defaultCam;
	//Camera
	float preX;
	float preY;

	glm::mat4 modelMat;//ŒÔÃÂæÿ’Û
	glm::mat4 viewMat;//…„œÒª˙æÿ’Û
	glm::mat4 projMat;//Õ∂…‰æÿ’Û

	void render();
	void render(QPainter *painter);

	virtual void initialize();

	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

	void initObjects();
	void setAnimating(bool animating);
	bool m_animating;

	QOpenGLContext *m_context;
	//QOpenGLPaintDevice *m_device;

	bool hasInitialized;

	glm::vec3 GetRayFromMouse(float x,float y);

public slots:
	void renderLater();
	void renderNow();

protected:
	bool event(QEvent *event) override;
	void exposeEvent(QExposeEvent *event) override;

};

