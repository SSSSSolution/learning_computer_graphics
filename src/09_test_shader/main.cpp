#include "sb7_include/sb7.h"
#include "shader.h"
#include <string>
#include "stdlib.h"
#include "matrix.h"
#include "transmat4.h"

using namespace sb7;

class my_application : public sb7::application
{
public:
    virtual void render(double currentTime)
    {
        const GLfloat color[] = { 0.0f, 0.2f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, color);

        shader->use();
        glBindVertexArray(VAO);

        curiosity::TransMat4 transform = curiosity::TransMat4::Translation(0.5f, -0.5f, 0.0f);
        GLuint transformLoc = glGetUniformLocation(shader->getProgramID(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transform.dataPtr());

        curiosity::TransMat4 rotate = curiosity::TransMat4::Rotation(0.0f, 0.0f, 1.0f, (float)currentTime);
        GLuint rotateLoc = glGetUniformLocation(shader->getProgramID(), "rotate");
        glUniformMatrix4fv(rotateLoc, 1, GL_FALSE, rotate.dataPtr());

        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    virtual void startup()
    {
        char *root = getenv("PROJECT_ROOT");
        std::string rootDir(root);
        std::string vertexShaderPath = rootDir + std::string("/bin/shader/vertex.shader");
        std::string fragmentShaderPath = rootDir + std::string("/bin/shader/fragment.shader");
        shader = new curiosity::Shader(vertexShaderPath.c_str(),
                                   fragmentShaderPath.c_str());
        glCreateVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);

        float vertices[] = {
            0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
        };
        GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
        };
        glCreateVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glCreateBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferStorage(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glCreateBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

//        glVertexArrayVertexBuffer(VAO, );
//        glGenBuffers(1, &VBO);

//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
//        glEnableVertexAttribArray(0);
    }

private:
    curiosity::Shader *shader;
    GLuint vertex_array_object;
    GLuint VAO, VBO, EBO;

    curiosity::Matrix<float> model;
};

DECLARE_MAIN(my_application);

