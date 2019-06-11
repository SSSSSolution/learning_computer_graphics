#version 450 core

layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec2 aTexCoord;

//out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

void main()
{
	gl_Position = project * view * model * vec4(aPos, 1.0f);
	//TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}
