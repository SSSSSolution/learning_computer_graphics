#include "sb7_include/sb7.h"

using namespace  sb7;

static GLuint compile_shaders();

class my_application : public sb7::application
{
public:
    virtual void render(double currentTime)
    {
        const GLfloat color[] = { 0.0f, 0.2f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, color);

        glUseProgram(rendering_program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    virtual void startup()
    {
        rendering_program = compile_shaders();
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
    GLuint program;

    static const GLchar * vertex_shader_source[] = {
        "#version 450 core                                                  \n"
        "                                                                   \n"
        "void main(void)                                                    \n"
        "{                                                                  \n"
        "   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),   \n"
        "                                    vec4(-0.25, -0.25, 0.5, 1.0),  \n"
        "                                    vec4(0.25, 0.25, 0.5, 1.0));   \n"
        "   gl_Position = vertices[gl_VertexID];                            \n"
        "}                                                                  \n"
    };

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);

    return program;
}

DECLARE_MAIN(my_application);
