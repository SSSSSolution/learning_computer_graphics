#include <stdlib.h>
#include <string>
#include <iostream>

#include "sb7_include/sb7.h"
#include "camera.h"
#include "shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace sb7;
using namespace curiosity;

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
        glfwWindowHint(GLFW_SAMPLES, 4);
    }

    virtual void startup()
    {
        char *root = getenv("PROJECT_ROOT");
        std::string rootDir(root);
        std::string vertexShaderPath = rootDir + std::string("/src/shader/12_light_source.vs");
        std::string fragmentShaderPath = rootDir + std::string("/src/shader/12_light_source.fs");
        sourceShader = new Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

        vertexShaderPath = rootDir + std::string("/src/shader/15_lighting_maps.vs");
        fragmentShaderPath = rootDir + std::string("/src/shader/15_lighting_maps.fs");
        objectShader = new Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

        glCreateBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glCreateVertexArrays(1, &sourceVAO);
        glBindVertexArray(sourceVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(0));
        glEnableVertexAttribArray(0);

        glCreateVertexArrays(1, &objectVAO);
        glBindVertexArray(objectVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glGenTextures(1, &diffuseTexture);
        glBindTexture(GL_TEXTURE_2D, diffuseTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrChannels;
        unsigned char *data = stbi_load("../src/media/container2.png",
                                        &width, &height, &nrChannels, 0);
        GLenum format = 0;
        if (nrChannels == 1) {
            format = GL_RED;
        } else if (nrChannels == 3) {
            format = GL_RGB;
        } else if (nrChannels == 4) {
            format = GL_RGBA;
        }
        std::cout << format << std::endl;
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format,
                         GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cerr << "image load failed!" << std::endl;
        }
        stbi_image_free(data);

        glGenTextures(1, &specularTexture);
        glBindTexture(GL_TEXTURE_2D, specularTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        data = stbi_load("../src/media/container2_specular.png",
                                        &width, &height, &nrChannels, 0);
        format = 0;
        if (nrChannels == 1) {
            format = GL_RED;
        } else if (nrChannels == 3) {
            format = GL_RGB;
        } else if (nrChannels == 4) {
            format = GL_RGBA;
        }
        std::cout << format << std::endl;
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format,
                         GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cerr << "image load failed!" << std::endl;
        }
        stbi_image_free(data);

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
                     RADIANS(fov), 0.1f, 100.0f);

        // 画光源
        sourceShader->use();
        vec3 lightPos(0.0f, 0.0f, 5.0f);
//        lightPos.x = 5.0f *sin(currentTime*0.1f);
//        lightPos.y = 5.0f * cos(currentTime*0.1f);
        vec3 lightColor(1.0f, 1.0f, 1.0f);
        vec3 objectColor(1.0f, 0.5f, 0.31f);
        modelMat = TransMat4::Translation(lightPos.x, lightPos.y, lightPos.z);
        rotateMat = TransMat4::Rotation(1.0f, 1.0f, 1.0f, (float)currentTime);

        sourceShader->setTransMat4("view", viewMat);
        sourceShader->setTransMat4("project", projectMat);
        sourceShader->setTransMat4("model", modelMat);
//        lightColor.x = sin(currentTime*2.0f);
//        lightColor.y = sin(currentTime*0.7f);
//        lightColor.z = sin(currentTime*1.3f);
        sourceShader->setVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);

        glBindVertexArray(sourceVAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 画物体
        objectShader->use();
        modelMat = TransMat4::Translation(0.0f, 0.0f, 0.0f);
        rotateMat = TransMat4::Rotation(1.0f, 1.0f, 1.0f, 20+(float)currentTime);
        modelMat = modelMat * rotateMat;

        objectShader->setTransMat4("view", viewMat);
        objectShader->setTransMat4("project", projectMat);
        objectShader->setTransMat4("model", modelMat);

        objectShader->setVec3("light.position", lightPos.x, lightPos.y, lightPos.z);
        objectShader->setVec3("light.ambient", lightColor.x * 0.2f, lightColor.y * 0.2f, lightColor.z * 0.2f);
        objectShader->setVec3("light.diffuse", lightColor.x * 0.5f, lightColor.y * 0.5f, lightColor.z * 0.5f);
        objectShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        vec3 viewPos = camera.getPosition();
        objectShader->setVec3("viewPos", viewPos.x, viewPos.y, viewPos.z);

        objectShader->setInt("material.diffuse", 0);
        objectShader->setInt("material.specular",1);
        objectShader->setFloat("material.shininess", 64.0f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseTexture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularTexture);

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
    GLuint diffuseTexture, specularTexture;

    Camera camera;

    float fov;
    GLuint modelLoc, viewLoc, projectLoc;
    TransMat4 viewMat, projectMat, modelMat, rotateMat;
};

DECLARE_MAIN(my_application);
