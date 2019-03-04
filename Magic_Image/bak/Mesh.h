#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include <assimp/scene.h>
#include <qopenglbuffer.h>
#include <qopenglvertexarrayobject.h>
#include <qopengltexture.h>

class OpenGLWindow;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	aiString path;
};


class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	//Mesh(float verts[]);

	Mesh(std::vector<Vertex> vs,std::vector<unsigned int> is , std::vector<Texture> ts, OpenGLWindow *w);
	~Mesh();

	void Draw(Shader *shader);
	OpenGLWindow *window;

private:
	QOpenGLBuffer *VBO , *EBO;
	//unsigned int VAO
	QOpenGLVertexArrayObject *VAO;
	
	//unsigned int VBO, EBO;

	void setupMesh();
};