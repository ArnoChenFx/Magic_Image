#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#include <GLFW/glfw3.h>
//#include <glad/glad.h> 
#include <time.h>
#include <qopengl.h>
#include <qopengltexture.h>
#include <qopenglbuffer.h>
#include <qopenglfunctions.h>

using namespace std;

Shader::Shader(const char * vertexPath, const char * fragmentPath)
{
	//clock_t startTime, endTime;
	//startTime = clock();

	ifstream vertexFile;
	ifstream fragmentFile;
	stringstream vertexSStream;
	stringstream fragmentSStream;

	vertexFile.open(vertexPath);//��Ӳ�̶�ȡ����
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw exception("open file error");
		}

		vertexSStream << vertexFile.rdbuf();//��ȡ�ļ��������ݵ�������
		fragmentSStream << fragmentFile.rdbuf();

		vertexFile.close();//�ر��ļ�
		fragmentFile.close();

		string vertexString = vertexSStream.str();//ת����������string
		string fragmentString = fragmentSStream.str();

		const char* vertexSource = vertexString.c_str();
		const char* fragmentSource = fragmentString.c_str();
		
		//unsigned int vertex, fragment;

		QOpenGLShader *vertex, *fragment;

		//����vertex shader
		
		vertex = new QOpenGLShader(QOpenGLShader::Vertex);
		vertex->compileSourceCode(vertexSource);
		//vertex = glCreateShader(GL_VERTEX_SHADER);
		//glShaderSource(vertex, 1, &vertexSource, NULL);
		//glCompileShader(vertex);


		//����fragment shader
		fragment = new QOpenGLShader(QOpenGLShader::Fragment);
		fragment->compileSourceCode(fragmentSource);

		//fragment = glCreateShader(GL_FRAGMENT_SHADER);
		//glShaderSource(fragment, 1, &fragmentSource, NULL);
		//glCompileShader(fragment);


		//����shader program ������ shadedr
		shaderProgram = new QOpenGLShaderProgram;
		shaderProgram->addShader(vertex);
		shaderProgram->addShader(fragment);
		shaderProgram->link();
		shaderProgram->bind();

		ID = shaderProgram->programId();
		//ID = glCreateProgram();
		//glAttachShader(ID, vertex);
		//glAttachShader(ID, fragment);
		//glLinkProgram(ID);
		//checkError(ID, "PROGRAM");

		//ɾ��ʹ�ú��shader
		vertex->destroyed();
		fragment->destroyed();

	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}

}

void Shader::use()
{
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	f->glUseProgram(ID);
	//glUseProgram(ID);
	//shaderProgram->bind();
}

void Shader::setInt(const std::string &name, int value) const
{
	//glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	shaderProgram->setUniformValue(name.c_str(), value);
}
