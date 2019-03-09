#pragma once
#include <memory>
#include "Shader.h"

class sceneAxis
{
public:
	sceneAxis();
	~sceneAxis();

	void Draw(glm::mat4 viewMat, glm::mat4 projMat);

	unsigned int VBO, VAO;

	std::unique_ptr<Shader> myShader;


};

