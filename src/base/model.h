#ifndef MODEL_H
#define MODEL_H

#include "shader.h"
#include "mesh.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <vector>
namespace curiosity {

    class Model
    {
    public:
        Model(const char *path, bool gamma = false)
            : gammaCorrection(gamma) {
            loadModel(path);
        }

        void draw(Shader shader);
    private:
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                                  std::string typeName);

        unsigned int textureFromFile(const char *path, const std::string &directory, bool gamma = false);
    public:
        std::vector<Texture> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;
        bool gammaCorrection;
    };

}

#endif // MODEL_H
