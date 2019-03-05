#pragma once
#include <glm/glm.hpp>
#include <qopenglfunctions.h>
#include <qopenglwindow.h>
#include "Cameras.h"
#include "Model.h"
#include "Shader.h"
#include <string>
#include <QEvent>
#include <qwindow.h>

class OpenGLScene : public QWindow, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit OpenGLScene(QWindow *parent = nullptr);
	~OpenGLScene();

	virtual void initialize();

	void resizeEvent(QResizeEvent *event);

	//Camera *cam;
	float preX;
	float preY;
	
	const int LOOP = 0;
	const int MOVE = 1;
	const int SCALE = 2;
	const int ROTATE = 3;
	int PRESSMODE;

	Shader *myShader1;
	Model *md;
	Camera *cam;

	glm::mat4 modelMat;//ŒÔÃÂæÿ’Û
	glm::mat4 viewMat;//…„œÒª˙æÿ’Û
	glm::mat4 projMat;//Õ∂…‰æÿ’Û

	
	void render();
	void render(QPainter *painter);

	void setAnimating(bool animating);

private:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

	void initObjects();

	bool m_animating;

	QOpenGLContext *m_context;
	QOpenGLPaintDevice *m_device;

	bool hasInitialized;

	void setRender(bool start = false);

public slots:
	void renderLater();
	void renderNow();

protected:
	bool event(QEvent *event) override;
	void exposeEvent(QExposeEvent *event) override;

};

