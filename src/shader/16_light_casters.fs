#version 450

out vec4 FragColor;
in vec2 TexCoords;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light { 
	// vec3 direction; // 平行光

	// vec3 position; //点光源
	 float constant;
	 float linear;
	 float quadratic;

	vec3 position;	// 聚光
	vec3 direction;
	float cutOff;
	float outCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

in vec3 Normal;
in vec3 FragPos;
uniform vec3 viewPos;

void main()
{
	// 计算点光源衰减
	float distance = length(light.position - FragPos);
	float attenuation = 1.0/(light.constant + light.linear * distance +
						light.quadratic * (distance *distance));
	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

	// diffuse
	vec3 norm = normalize(Normal);
	// vec3 lightDir = normalize(-light.direction); // 平行光
	vec3 lightDir = normalize(light.position - FragPos); // 点光源
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); 
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	// vec3 result = diffuse + ambient + specular; // 平行光
	//vec3 result = ambient * attenuation + diffuse * attenuation + specular * attenuation; // 点光源
	float theta = dot(lightDir, normalize(-light.direction)); // 聚光
	float epsilon = light.cutOff - light.outCutOff;
	float intensity = clamp((theta-light.outCutOff)/epsilon, 0.0, 1.0);
	vec3 result = ambient + diffuse * intensity + specular * intensity;
	FragColor = vec4(result, 1.0);
}













