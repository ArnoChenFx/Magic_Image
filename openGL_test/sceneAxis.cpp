#include <glad/glad.h> 
#include "sceneAxis.h"

const float axis[] = {
	0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	10.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	10.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	9.7f, 0.0f, 0.2f, 1.0f, 0.0f, 0.0f,
	10.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	9.7f, 0.0f, -0.2f, 1.0f, 0.0f, 0.0f,

	0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 10.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 10.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.2f, 9.7f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 10.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-0.2f, 9.7f, 0.0f, 0.0f, 1.0f, 0.0f,

	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f,
	0.2f, 0.0f, 9.7f, 0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f,
	-0.2f, 0.0f, 9.7f, 0.0f, 0.0f, 1.0f,
};

sceneAxis::sceneAxis()
{
	myShader = std::make_unique<Shader>("axis.vert", "line.frag");
	
	glGenVertexArrays(1, &VAO); // we can also generate multiple VAOs or buffers at the same time
	glGenBuffers(1, &VBO);

	//lines
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axis), axis, GL_STATIC_DRAW);

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);
}


sceneAxis::~sceneAxis()
{
}

void sceneAxis::Draw(glm::mat4 viewMat, glm::mat4 projMat)
{
	glm::mat4 modelMat = glm::mat4(1.0f);
	myShader->use();
	myShader->setMat4("viewMat", viewMat);
	myShader->setMat4("projMat", projMat);
	myShader->setMat4("modelMat", modelMat);

	glLineWidth(3);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 18);
	glLineWidth(1);

	//glBegin(GL_LINES);
	//glVertexAttrib3f(0, 100, 100, 100);
	//glVertexAttrib3f(0, 0, 0, 0);
	//glFlush();
}