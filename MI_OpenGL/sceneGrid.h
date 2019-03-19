#pragma once
#include <memory>
#include "Shader.h"
#include "mi_opengl_global.h"
class MI_OPENGL_EXPORT sceneGrid
{
public:
	sceneGrid();
	~sceneGrid();

	void Draw(glm::mat4 viewMat, glm::mat4 projMat);

	unsigned int VBO[2], VAO[2];

	std::unique_ptr<Shader> myShader;

private:
	float maxLength;
	float colorA;
	float colorB;
	float num;
	float gridSize;
};

