#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace curiosity {

    Shader::Shader(const char *vertexPath,
                   const char *fragmentPath)
    {
        programID = glCreateProgram();

        installShader(vertexPath, &vertexShader, GL_VERTEX_SHADER);
        installShader(fragmentPath, &fragmentShader, GL_FRAGMENT_SHADER);

        // 链接着色器
        int success;
        char infoLog[512];
        glAttachShader(programID, vertexShader);
        glAttachShader(programID, fragmentShader);
        glLinkProgram(programID);
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(programID, 512, NULL, infoLog);
            std::cout << "program link error: " << infoLog << endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::installShader(const char *shaderPath, GLuint *shader, GLuint shaderType)
    {
        std::string shaderSrc;
        std::stringstream srcStream;
        int success;
        char infoLog[512];

        if (!shaderPath)
            return;

        // 加载源码
        std::ifstream shaderFile(shaderPath);
        if (!shaderFile) {
            std::cerr << "can't open shader file: " << shaderPath << endl;
            return;
        }
        srcStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderSrc = srcStream.str();
        // 编译源码
        *shader = glCreateShader(shaderType);
        const char * shaderCode = shaderSrc.c_str();
        glShaderSource(*shader, 1, &shaderCode, NULL);
        glCompileShader(*shader);
        glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(*shader, 512, NULL, infoLog);
            std::cout << shaderPath << ": shader compile failed: "
                      << infoLog << endl;
        }
    }

}
