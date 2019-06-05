#include <iostream>
#include "sb7_include/sb7.h"

using namespace std;
using namespace  sb7;

static GLuint compile_shaders();

static void checkCompile(GLuint shader)
{
    char infoLog[512];
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
}
class my_application : public sb7::application
{
public:
    virtual void render(double currentTime)
    {
        const GLfloat color[] = { (float)sin(currentTime)*0.5f + 0.5f,
                                  (float)cos(currentTime)*0.5f + 0.5f,
                                  0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, color);

        glUseProgram(rendering_program);

        GLfloat attrib[] = {(float)sin(currentTime) * 0.5f,
                            (float)cos(currentTime) * 0.6f,
                            0.0f, 0.0f };

        // Update the value of input attribute 0
        glVertexAttrib4fv(0, attrib);

        glDrawArrays(GL_PATCHES, 0, 3);
    }

    virtual void startup()
    {
        rendering_program = compile_shaders();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glCreateVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);
    }

private:
    GLuint rendering_program;
    GLuint vertex_array_object;
};

GLuint compile_shaders(void)
{
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint tess_control_shader;
    GLuint tess_envaluation_shader;
    GLuint program;

    static const GLchar * vertex_shader_source[] = {
        "#version 450 core                                                  \n"
        "                                                                   \n"
        "// 'offset' is an input vertex attribute                           \n"
        "layout(location = 0) in vec4 offset;                               \n"
        "                                                                   \n"
        "void main(void)                                                    \n"
        "{                                                                  \n"
        "   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),   \n"
        "                                    vec4(-0.25, -0.25, 0.5, 1.0),  \n"
        "                                    vec4(0.25, 0.25, 0.5, 1.0));   \n"
        "   gl_Position = vertices[gl_VertexID] + offset;                   \n"
        "}                                                                  \n"
    };

    static const GLchar *fragment_shader_source[] = {
        "#version 450 core                                                  \n"
        "                                                                   \n"
        "out vec4 color;                                                    \n"
        "                                                                   \n"
        "void main(void)                                                    \n"
        "{                                                                  \n"
        "   color = vec4(0.0, 0.8, 1.0, 1.0);                               \n"
        "}                                                                  \n"
    };

    static const GLchar *tess_control_source[] = {
        "#version 450 core                                                  \n"
        "                                                                   \n"
        "layout (vertices = 3) out;                                          \n"
        "                                                                   \n"
        "void main(void)                                                    \n"
        "{                                                                  \n"
        "   // Only if I am invocation 0..                                  \n"
        "   if (gl_InvocationID == 0)                                       \n"
        "   {                                                               \n"
        "       gl_TessLevelInner[0] = 5.0;                                 \n"
        "       gl_TessLevelOuter[0] = 5.0;                                 \n"
        "       gl_TessLevelOuter[1] = 5.0;                                 \n"
        "       gl_TessLevelOuter[2] = 5.0;                                 \n"
        "   }                                                               \n"
        "   // Everybody copies their input to their output                 \n"
        "   gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;                         \n"
        "}                                                                  \n"
    };

    static const GLchar *tess_envaluation_source[] =
    {
        "#version 450 core                                                  \n"
        "                                                                   \n"
        "layout(triangles, equal_spacing, cw) in;                           \n"
        "                                                                   \n"
        "void main(void)                                                    \n"
        "{                                                                  \n"
        "   gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +          \n"
        "                  (gl_TessCoord.y * gl_in[1].gl_Position) +          \n"
        "                  (gl_TessCoord.z * gl_in[2].gl_Position);          \n"
        "}                                                                  \n"
    };

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    checkCompile(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    checkCompile(fragment_shader);

    tess_control_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
    glShaderSource(tess_control_shader, 1, tess_control_source, NULL);
    glCompileShader(tess_control_shader);
    checkCompile(tess_control_shader);

    tess_envaluation_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
    glShaderSource(tess_envaluation_shader, 1, tess_envaluation_source, NULL);
    glCompileShader(tess_envaluation_shader);
    checkCompile(tess_envaluation_shader);


    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glAttachShader(program, tess_control_shader);
    glAttachShader(program, tess_envaluation_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);

    glDeleteShader(tess_control_shader);
    glDeleteShader(tess_envaluation_shader);
    glDeleteShader(fragment_shader);

    return program;
}

DECLARE_MAIN(my_application);
