#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "sb7_include/sb7.h"
#include "camera.h"
#include "shader.h"
#include "model.h"
#include <iostream>

using namespace sb7;
using namespace curiosity;
using namespace std;

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
        glfwWindowHint(GLFW_SAMPLES, 4);
    }

    virtual void startup()
    {
        char *root = getenv("PROJECT_ROOT");
        std::string rootDir(root);
        std::string vertexShaderPath = rootDir + std::string("/src/shader/18_load_model.vs");
        std::string fragmentShaderPath = rootDir + std::string("/src/shader/18_load_model.fs");
        shader = new Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
        model = new Model("../src/model/nanosuit/nanosuit.obj");

        fov = 45.0f;
        camera.setMouseSensitivity(0.025f);
        camera.setMoveSpeed(0.25f);

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    virtual void render(double currentTime)
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        viewMat = camera.getViewMatrix();
        projectMat = TransMat4::Projection(
                    (float)(info.windowWidth)/(float)(info.windowHeight),
                     RADIANS(fov), 0.1f, 1000.0f);

        shader->use();

        modelMat = TransMat4::Translation(0.0f, 0.0f, -1.0f);

        shader->setTransMat4("view", viewMat);
        shader->setTransMat4("project", projectMat);
        shader->setTransMat4("model", modelMat);

        model->draw(*shader);
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
    Camera camera;
    Shader *shader;
    Model *model;
    float fov;
    TransMat4 viewMat, projectMat, modelMat;
};

DECLARE_MAIN(my_application);


















