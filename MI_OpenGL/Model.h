#pragma once
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include "Mesh.h"
#include "Shader.h"
#include <string>
#include <vector>
#include "mi_opengl_global.h"
#include <memory>

class MI_OPENGL_EXPORT Model
{
public:
	Model(std::string const &path);
	~Model();

	void Draw(std::unique_ptr<Shader>& shader);
	void loadModel(std::string path);

	/*  Model Data  */
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

private:
	
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

