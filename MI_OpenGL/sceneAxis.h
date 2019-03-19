#pragma once
#include <memory>
#include "Shader.h"
#include "mi_opengl_global.h"
class MI_OPENGL_EXPORT sceneAxis
{
public:
	sceneAxis();
	~sceneAxis();

	void Draw(glm::mat4 viewMat, glm::mat4 projMat);

	unsigned int VBO, VAO;

	std::unique_ptr<Shader> myShader;


};

