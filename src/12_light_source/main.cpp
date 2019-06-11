#include <stdlib.h>
#include <string>

#include "sb7_include/sb7.h"
#include "camera.h"
#include "shader.h"

using namespace sb7;
using namespace curiosity;

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

class my_application : public sb7::application
{
public:
    virtual void init()
    {
        strcpy(info.title, "OpenGL SuperBible Example");
        info.windowWidth = 1920;
        info.windowHeight = 1080;

#ifdef __APPLE__
        info.majorVersion = 3;
        info.minorVersion = 2;
#else
        info.majorVersion = 4;
        info.minorVersion = 3;
#endif
        info.samples = 0;
        info.flags.all = 0;
        info.flags.cursor = 1;
#ifdef _DEBUG
        info.flags.debug = 1;
#endif
    }

    virtual void startup()
    {
        char *root = getenv("PROJECT_ROOT");
        std::string rootDir(root);
        std::string vertexShaderPath = rootDir + std::string("/src/shader/12_light_source.vs");
        std::string fragmentShaderPath = rootDir + std::string("/src/shader/12_light_source.fs");
        sourceShader = new Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

        vertexShaderPath = rootDir + std::string("/src/shader/12_object.vs");
        fragmentShaderPath = rootDir + std::string("/src/shader/12_object.fs");
        objectShader = new Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

        glCreateBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glCreateVertexArrays(1, &sourceVAO);
        glBindVertexArray(sourceVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void *)(0));
        glEnableVertexAttribArray(0);

        glCreateVertexArrays(1, &objectVAO);
        glBindVertexArray(objectVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void *)(0));
        glEnableVertexAttribArray(0);

        fov = 45.0f;
        camera.setMouseSensitivity(0.025f);
        camera.setMoveSpeed(0.25f);

        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    virtual void render(double currentTime)
    {
        glClearColor(1.0f, 0.5f, 0.31f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        viewMat = camera.getViewMatrix();
        projectMat = TransMat4::Projection(
                    (float)(info.windowWidth)/(float)(info.windowHeight),
                     RADIANS(fov), 0.1f, 100.0f);
//        viewMat = TransMat4::Identity();
//        projectMat = TransMat4::Identity();

        // 画光源
        sourceShader->use();
        modelMat = TransMat4::Translation(0.0f, 0.0f, 0.0f);
        rotateMat = TransMat4::Rotation(1.0f, 1.0f, 1.0f, (float)currentTime);
//        modelMat = modelMat * rotateMat;

        sourceShader->setTransMat4("view", viewMat);
        sourceShader->setTransMat4("project", projectMat);
        sourceShader->setTransMat4("model", modelMat);
        sourceShader->setVec3("lightColor",1.0f, 1.0f, 0.0f);

        glBindVertexArray(sourceVAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 画物体
        objectShader->use();
        modelMat = TransMat4::Translation(3.0f, 3.0f, -5.0f);
        rotateMat = TransMat4::Rotation(1.0f, 1.0f, 1.0f, 20+(float)currentTime);
        modelMat = modelMat * rotateMat;

        objectShader->setTransMat4("view", viewMat);
        objectShader->setTransMat4("project", projectMat);
        objectShader->setTransMat4("model", modelMat);
        objectShader->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
        objectShader->setVec3("lightColor", 1.0f, 1.0f, 0.0f);
        glBindVertexArray(objectVAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    virtual void onKey(int button, int action)
    {
        if (button == GLFW_KEY_W && (GLFW_REPEAT == action || GLFW_PRESS == action)) {
            camera.processKeyboard(curiosity::Camera::FORWARD);
        } else if (button == GLFW_KEY_S && (GLFW_REPEAT == action || GLFW_PRESS == action)) {
            camera.processKeyboard(curiosity::Camera::BACKWARD);
        } else if (button == GLFW_KEY_A && (GLFW_REPEAT == action || GLFW_PRESS == action)) {
            camera.processKeyboard(curiosity::Camera::LEFT);
        } else if (button == GLFW_KEY_D && (GLFW_REPEAT == action || GLFW_PRESS == action)) {
            camera.processKeyboard(curiosity::Camera::RIGHT);
        }
    }

    virtual void onMouseMove(int x, int y)
    {
        static int lastX, lastY;
        static bool firstMouse = true;
        if (firstMouse) {
            lastX = info.windowWidth/2.0f;
            lastY = info.windowHeight/2.0f;
            firstMouse = false;
        }

        float xoffset = x - lastX;
        float yoffset = y - lastY;
        lastX = x;
        lastY = y;

        camera.processMouseMove(xoffset, yoffset);
    }

private:
    Shader *sourceShader;
    Shader *objectShader;
    GLuint sourceVAO, objectVAO, VBO;

    Camera camera;

    float fov;
    GLuint modelLoc, viewLoc, projectLoc;
    TransMat4 viewMat, projectMat, modelMat, rotateMat;
};

DECLARE_MAIN(my_application);
