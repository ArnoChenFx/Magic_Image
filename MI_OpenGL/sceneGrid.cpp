#include <glad/glad.h>
#include "sceneGrid.h"
#include "glm/gtc/matrix_transform.hpp"


const float maxL = 1000;

const float line1[] = {
	-maxL / 2,  0.0f,  0.0f,
	maxL / 2,  0.0f, 0.0f
};

const float line2[] = {
	0.0f, 0.0f, maxL / 2,
	0.0f, 0.0f, -maxL / 2
};


sceneGrid::sceneGrid()
{
	myShader = std::make_unique<Shader>("line.vert", "line.frag");

	glGenVertexArrays(2, VAO); // we can also generate multiple VAOs or buffers at the same time
	glGenBuffers(2, VBO);

	//line1
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line1), line1, GL_STATIC_DRAW);

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//line2
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line2), line2, GL_STATIC_DRAW);

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	maxLength = maxL;

	colorA = 0.3;
	colorB = 0.2;
	num = maxLength;
	gridSize = maxLength / num;

}


sceneGrid::~sceneGrid()
{
}

void sceneGrid::Draw(glm::mat4 viewMat, glm::mat4 projMat)
{
	glm::mat4 modelMat = glm::mat4(1.0f);
	myShader->use();
	myShader->setMat4("viewMat", viewMat);
	myShader->setMat4("projMat", projMat);
	myShader->setMat4("modelMat", modelMat);
	GL_LINE_SMOOTH;
	
	for (int i = 0; i < num; i++) {

		if (i % 5 == 0) {
			glLineWidth(1);
			myShader->setFloat("Color", colorB);
		}
		else {
			glLineWidth(0.1);
			myShader->setFloat("Color", colorA);
		}

		float ls = -maxLength / 2 + gridSize * i;
		modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, ls));
		myShader->setMat4("modelMat", modelMat);

		//SET Model
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_LINES, 0, 2);

		modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(ls, 0, 0));
		myShader->setMat4("modelMat", modelMat);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_LINES, 0, 2);
	}

	glLineWidth(1);
}