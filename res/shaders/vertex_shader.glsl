#version 400 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 reflectedVector;
out vec3 refractedVector;

out vec3 pass_normal;
out vec2 pass_textureCoordinates;
out vec3 Position_worldspace;
out vec3 EyeDirection_cameraspace;
out vec3 lightDirection_cameraspace;
out vec3 normal_cameraspace;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 cameraPosition;
uniform vec3 lightPos;

uniform int mode;

void main()
{
	mat4 MVP = projection * view * model;
	gl_Position = MVP * aPos;

	Position_worldspace = (model * aPos).xyz;

	vec3 vertexPosition_cameraspace = (view * model * aPos).xyz;
	EyeDirection_cameraspace = vec3(0.0,0.0,0.0) - vertexPosition_cameraspace;

	vec3 lightPosition_cameraspace = (view * vec4(lightPos, 1.0)).xyz;
	lightDirection_cameraspace = lightPosition_cameraspace + EyeDirection_cameraspace;

	normal_cameraspace = (view * model * vec4(aNormal, 0.0)).xyz;
	pass_textureCoordinates = aTexCoord;
	pass_normal = mat3(transpose(inverse(model))) * aNormal;

	if (mode >= 3 && mode <= 4) {
		vec3 viewVector = normalize(cameraPosition - Position_worldspace.xyz);
		reflectedVector = reflect(viewVector, aNormal);
		refractedVector = refract(viewVector, aNormal, 1.0/1.2);
	}
}
