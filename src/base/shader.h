#ifndef SHADER_H
#define SHADER_H

#include "sb7_include/sb7.h"
#include <string>

namespace curiosity {

    class Shader
    {
    public:
        Shader(const char *vertexPath,
               const char *fragmentPath);

        inline void use() {
            glUseProgram(programID);
        }

        inline GLuint getProgramID() {
            return programID;
        }

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;

    private:
        void installShader(const char *shaderPath, GLuint *shader, GLuint shaderType);

    private:
        GLuint programID;
        GLuint vertexShader;
        GLuint fragmentShader;
    };

}

#endif // SHADERLOADER_H
