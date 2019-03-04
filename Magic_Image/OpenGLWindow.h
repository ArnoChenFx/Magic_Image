#pragma once
#include <glm/glm.hpp>
#include <qopenglfunctions.h>
#include <qopenglwidget.h>
//#include <qopenglframebufferobject.h>
//#include <qopenglbuffer.h>
//#include <qopenglshaderprogram.h>
#include "Cameras.h"
#include "Model.h"
#include "Shader.h"
#include <qmatrix4x4.h>
#include <string>

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	OpenGLWindow(QWidget *parent = nullptr);
	~OpenGLWindow();

	virtual void initializeGL() override;

	virtual void resizeGL(int w, int h) override;

	virtual void paintGL() override;

	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *event);

	//Camera *cam;
	float preX;
	float preY;
	bool firstMouse;
	
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

	QOpenGLContext *m_context;
	void initObjects();
	void mousePressEvent(QMouseEvent *event) override;
	//void mouseMoveEvent(QMouseEvent *event) override;

	void mouseMove(QMouseEvent *event);
private:
	//virtual void wheelEvent(QWheelEvent *event) override;
	//virtual void mousePressEvent(QMouseEvent *event)override;
	
	//virtual void mouseReleaseEvent(QMouseEvent *event)override;
	//virtual void keyPressEvent(QKeyEvent *event)override;

	//void leftMousePressEvent(QMouseEvent *event);
	//void leftMouseReleaseEvent(QMouseEvent *event);
};

