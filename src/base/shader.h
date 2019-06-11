#ifndef SHADER_H
#define SHADER_H

#include "sb7_include/sb7.h"
#include <string>
#include "transmat4.h"

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
        void setTransMat4(const std::string &name, TransMat4 &mat4);
        void setVec3(const std::string name, float v1, float v2, float v3);

    private:
        void installShader(const char *shaderPath, GLuint *shader, GLuint shaderType);

    private:
        GLuint programID;
        GLuint vertexShader;
        GLuint fragmentShader;
    };

}

#endif // SHADERLOADER_H
