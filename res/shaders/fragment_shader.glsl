#version 400 core

uniform sampler2D TextureSampler;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform int 

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

void main()
{
	vec4 texColor = texture(TextureSampler, TexCoord);
	
	float ambientStrength = 0.2;
	vec3 lightColor = vec3(1.0,1.0,1.0);
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * texColor.xyz;
	color = vec4(result, 1.0);
	// color = vec4(Normal, 1.0);

	//grey
	float grey = (Normal.x + Normal.y+ Normal.z) / 3.0;
	vec3 g = vec3(grey, grey, grey);
	// color = vec4(g, 1.0);
}
