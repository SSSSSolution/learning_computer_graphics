#version 450 core

out vec4 FragColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

// 材质
struct Material {
	sampler2D diffuse;	// 一般设置成物体本身的颜色
	sampler2D specular; // 一般设置成光源的颜色

	float shininess;
};

// 平行光
struct DirLight {
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// 点光源
struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// 聚光


uniform Material material;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

// 计算平行光
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// 计算漫反射系数
	float diff = max(dot(normal, lightDir), 0.0);
	// 计算镜面反射系数
	vec3 refectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// 合并结果
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
	vec3 diffuse = light.diffuse * spec * texture(material.diffuse, TexCoords).rgb;
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	return ambient + diffuse + specular;
}

// 计算点光源
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// 计算漫反射系数
	float diff = max(dot(normal, lightDir), 0.0);
	// 计算镜面反射系数
	vec3 refectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	// 衰减
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
						light.quadratic * (distance * distance));

	// 合并结果
	vec3 ambient = attenuation * light.ambient * texture(material.diffuse, TexCoords).rgb;
	vec3 diffuse = attenuation * light.diffuse * spec * texture(material.diffuse, TexCoords).rgb;
	vec3 specular = attenuation * light.specular * spec * texture(material.specular, TexCoords).rgb;

	return ambient + diffuse + specular;
}


void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(ViewPos - FragPos);

	vec3 result = CalcDirLight(dirLight, norm, viewDir);

	for (int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(PointLight[i], norm, viewDir);

	FragColor = vec4(result, 1.0f);
}


























