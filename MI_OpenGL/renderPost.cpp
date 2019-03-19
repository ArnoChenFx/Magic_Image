#include <glad/glad.h> 
#include "renderPost.h"
#include <glm/glm.hpp>
#include <iostream>
using namespace std;

renderPost::renderPost()
{
	myShader = std::make_unique<Shader>("vertexSource_post.vert", "fragmentSource_post.frag");
	usePost = true;
	init();
}

void renderPost::init()
{
	float rectVertices[] = {
		//     ---- 位置 ----          - 纹理坐标 -
			-1.0,  1.0,  0.0f, 1.0f,   // 左上
			1.0, 1.0,   1.0f, 1.0f,   // 右上
			1.0, -1.0,   1.0f, 0.0f,   // 右下
			-1.0,  1.0,  0.0f, 1.0f,   // 左上
			1.0, -1.0,   1.0f, 0.0f,   // 右下
			-1.0, -1.0,  0.0f, 0.0f    // 左下
	};

	
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Generate texture
	
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

	GLuint rbo; // render buffer object
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR:FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Setup quad VAO
	
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), &rectVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)(2 * sizeof(GLfloat)));

}

void renderPost::bind()
{
	if(usePost) glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	else glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);//清除并渲染背景
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//清除颜色缓冲和深度缓冲
	glEnable(GL_DEPTH_TEST);
}

void renderPost::setUsePost(bool flag)
{
	usePost = flag;
}

void renderPost::use()
{
	if (!usePost) return;
	// Second pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	myShader->use();
	glBindVertexArray(quadVAO);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}