#pragma once
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include "Mesh.h"
#include "Shader.h"
#include <string>
#include <vector>

class OpenGLWindow;

class Model
{
public:
	Model(std::string const &path, OpenGLWindow *w);
	~Model();

	void Draw(Shader *shader);
	OpenGLWindow *window;

private:
	/*  Model Data  */
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.


	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

	QOpenGLBuffer VBO, EBO;
	QOpenGLVertexArrayObject VAO;
};

