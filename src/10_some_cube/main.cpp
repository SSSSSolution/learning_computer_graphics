#include "sb7_include/sb7.h"
#include "shader.h"
#include "transmat4.h"
#include "vector3.h"
#include <stdlib.h>
#include <string>

using namespace sb7;

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

curiosity::Vector3<float> cubePositions[] = {
        curiosity::Vector3<float>( 0.0f,  0.0f,  0.0f),
//        curiosity::Vector3<float>( 2.0f,  5.0f, -15.0f),
//        curiosity::Vector3<float>(-1.5f, -2.2f, -2.5f),
//        curiosity::Vector3<float>(-3.8f, -2.0f, -12.3f),
//        curiosity::Vector3<float>( 2.4f, -0.4f, -3.5f),
//        curiosity::Vector3<float>(-1.7f,  3.0f, -7.5f),
//        curiosity::Vector3<float>( 1.3f, -2.0f, -2.5f),
//        curiosity::Vector3<float>( 1.5f,  2.0f, -2.5f),
//        curiosity::Vector3<float>( 1.5f,  0.2f, -1.5f),
//        curiosity::Vector3<float>(-1.3f,  1.0f, -1.5f)
};

class my_application : public sb7::application
{
public:
    virtual void render(double currentTime)
    {
        const GLfloat color[] = {0.3, 0.1, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, color);

        shader->use();

        glBindVertexArray(VAO);
        GLuint modelLoc = glGetUniformLocation(shader->getProgramID(),"model");
        GLuint rotateLoc = glGetUniformLocation(shader->getProgramID(), "rotate");
        curiosity::TransMat4 rotate = curiosity::TransMat4::Rotation(0.0f, 1.0f, 0.0f, (float)currentTime);
        glUniformMatrix4fv(rotateLoc, 1, GL_FALSE, rotate.dataPtr());

        for (int i = 0; i < 1; i++) {
            curiosity::TransMat4 model = curiosity::TransMat4::Translation(cubePositions[i].getX(),
                                              cubePositions[i].getY(),
                                              cubePositions[i].getZ());
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.dataPtr());
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }

    virtual void startup()
    {
        char *root = getenv("PROJECT_ROOT");
        std::string rootDir(root);
        std::string vertexShaderPath = rootDir + std::string("/bin/shader/10_some_cube.vs");
        std::string fragmentShaderPath = rootDir + std::string("/bin/shader/10_some_cube.fs");
        shader = new curiosity::Shader(vertexShaderPath.c_str(),
                                       fragmentShaderPath.c_str());

        glCreateVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glCreateBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                     vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    }

private:
    curiosity::Shader *shader;
    GLuint VAO, VBO;
};

DECLARE_MAIN(my_application);
