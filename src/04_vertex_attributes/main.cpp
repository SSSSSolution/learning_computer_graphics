#include "sb7_include/sb7.h"

using namespace  sb7;

static GLuint compile_shaders();

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
    GLuint fragment_shader;
    GLuint program;

    static const GLchar * vertex_shader_source[] = {
        "#version 450 core                                                  \n"
        "                                                                   \n"
        "// 'offset' is an input vertex attribute                           \n"
        "layout(location = 0) in vec4 offset;                               \n"
        "                                                                   \n"
        "void main(void)                                                    \n"
        "{                                                                  \n"
        "   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0) + offset,   \n"
        "                                    vec4(-0.25, -0.25, 0.5, 1.0),  \n"
        "                                    vec4(0.25, 0.25, 0.5, 1.0));   \n"
//        "   if () {                                         \n"
//        "       gl_Position = vertices[gl_VertexID];                        \n"
//        "   } else {                                                        \n"
        "       gl_Position = vertices[gl_VertexID] + offset;               \n"
//        "   }                                                               \n"
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

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

DECLARE_MAIN(my_application);
