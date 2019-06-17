#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_specular1;

void main()
{
	FragColor = texture(texture_specular1, TexCoords);
	//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}


