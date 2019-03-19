#pragma once
#include "Shader.h"
#include <memory>

class renderPost
{
public:
	renderPost();

	void use();
	void bind();
	void init();
	void setUsePost(bool flag);

private:
	
	std::unique_ptr<Shader> myShader;
	GLuint texColorBuffer;
	GLuint quadVAO, quadVBO;
	GLuint fbo;
	bool usePost;
};

