#pragma once
#include <string>
#include <glm/glm.hpp>
#include <qopenglshaderprogram.h>

class Shader
{
public:
	unsigned int ID;//shader program id
	QOpenGLShaderProgram *shaderProgram;

	Shader(const char* vertexPath,const char* fragmentPath);
	~Shader();

	void use();
	void setInt(const std::string &name, int value) const;
};

