#pragma once

#include <qopenglfunctions.h>
#include <qopenglwidget.h>
#include <qopenglframebufferobject.h>
#include <qopenglbuffer.h>
#include <qopenglshaderprogram.h>
#include "Camera.h"
#include "Model.h"
#include <qmatrix4x4.h>

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

	Camera *cam;
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


	QMatrix4x4 modelMat;
	QMatrix4x4 viewMat;
	QMatrix4x4 projMat;

	QOpenGLContext *m_context;
	QOpenGLShaderProgram *program;

	void initObjects();

	QOpenGLBuffer VBO, EBO;
	QOpenGLVertexArrayObject VAO;
};

