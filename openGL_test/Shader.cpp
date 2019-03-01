#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GLFW/glfw3.h>
#include <glad/glad.h> 
#include <time.h>

using namespace std;

Shader::Shader(const char * vertexPath, const char * fragmentPath)
{
	//clock_t startTime, endTime;
	//startTime = clock();

	ifstream vertexFile;
	ifstream fragmentFile;
	stringstream vertexSStream;
	stringstream fragmentSStream;

	vertexFile.open(vertexPath);//从硬盘读取内容
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw exception("open file error");
		}

		vertexSStream << vertexFile.rdbuf();//读取文件缓冲内容到数据流
		fragmentSStream << fragmentFile.rdbuf();

		vertexFile.close();//关闭文件
		fragmentFile.close();

		string vertexString = vertexSStream.str();//转化数据流成string
		string fragmentString = fragmentSStream.str();

		const char* vertexSource = vertexString.c_str();
		const char* fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;

		//编译vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkError(vertex, "VERTEX");

		//编译fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkError(fragment, "FRAGMENT");

		//创建shader program 并链接 shadedr
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkError(ID, "PROGRAM");

		//删除使用后的shader
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}

	
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x,y,z);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::checkError(unsigned int idx, std::string type)
{
	int success;
	char infoLog[512];

	if (type != "PROGRAM") {
		glGetShaderiv(idx, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(idx,512,NULL,infoLog);
			cout << "shader compile error: " << infoLog << endl;
		}
	}
	else {
		glGetProgramiv(idx, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(idx, 512, NULL, infoLog);
			cout << "program linking error: " << infoLog << endl;
		}
	}
}