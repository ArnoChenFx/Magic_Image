#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include <assimp/scene.h>
#include "mi_opengl_global.h"

struct MI_OPENGL_EXPORT Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct MI_OPENGL_EXPORT Texture {
	unsigned int id;
	std::string type;
	aiString path;
};


class MI_OPENGL_EXPORT Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(float verts[]);

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh();

	void Draw(Shader *shader);

private:

	unsigned int VAO, VBO, EBO;

	void setupMesh();
};