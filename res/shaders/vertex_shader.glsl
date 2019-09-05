#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position = projection * view * model * aPos;
	FragPos = vec3(model * aPos);
	TexCoord = aTexCoord;
	Normal = mat3(transpose(inverse(model))) * aNormal;
}
