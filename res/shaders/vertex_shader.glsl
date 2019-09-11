#version 400 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 pass_textureCoordinates;
out vec3 pass_normal;
out vec3 reflectedVector;
out vec3 refractedVector;

// out vec3 FragPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 cameraPosition;

void main()
{
	// vec4 worldPosition = model * aPos;
	// gl_Position = projection * view * worldPosition;
	// FragPos = vec3(model * aPos);
	// pass_textureCoordinates = aTexCoord;
	// Normal = mat3(transpose(inverse(model))) * aNormal;

	// vec3 unitNormal = normalize(aNormal);
	// vec3 viewVector = normalize(worldPosition.xyz - cameraPosition);
	// reflectedVector = reflect(viewVector, Normal);
	//// Normal = normalize(aNormal);

	vec4 worldPosition = model * aPos;
	gl_Position = projection * view * worldPosition;

	pass_textureCoordinates = aTexCoord;
	pass_normal = aNormal;
	vec3 unitNormal = normalize(aNormal);

	vec3 viewVector = normalize(worldPosition.xyz - cameraPosition);
	reflectedVector = reflect(viewVector, unitNormal);
	refractedVector = refract(viewVector, unitNormal, 1.0/1.1);
}
