#ifndef MESH_H
#define MESH_H
#include "vec3.h"
#include "vec2.h"
#include <string>
#include <vector>
#include "shader.h"
#include "sb7_include/sb7.h"

namespace curiosity {

    struct Vertex {
        vec3 position;
        vec3 normal;
        vec2 texCoords;

        vec3 tangent;
        vec3 bitTangent;
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh
    {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
             std::vector<Texture> textures)
            : vertices_(vertices), indices_(indices), textures_(textures) {
            setupMesh();
        }

        void draw(Shader shader);
    private:
         void setupMesh();

    public:
        std::vector<Vertex> vertices_; //　顶点集合
        std::vector<unsigned int> indices_; //索引？
        std::vector<Texture> textures_; // 纹理集合
        GLuint VAO;
    private:
        GLuint VBO, EBO;
    };

}

#endif // MESH_H
