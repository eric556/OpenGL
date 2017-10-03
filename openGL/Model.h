#pragma once
#include "Mesh.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include "SOIL.h"

class Model {
public:
	Model(GLchar* path) {
		this->loadModel(path);
	}
	void Draw(Shader shader);
private:
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	GLint TextureFromFile(const char* path, string directory);
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

