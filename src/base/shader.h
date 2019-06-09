#ifndef SHADER_H
#define SHADER_H

#include "sb7_include/sb7.h"

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

    private:
        void installShader(const char *shaderPath, GLuint *shader, GLuint shaderType);

    private:
        GLuint programID;
        GLuint vertexShader;
        GLuint fragmentShader;
    };

}

#endif // SHADERLOADER_H
