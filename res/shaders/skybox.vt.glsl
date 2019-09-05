#version 330 core

layout (location = 0) in vec4 aPos;

uniform mat4 projection;
uniform mat4 view;

out vec3 textureCoord;

void main()
{
    textureCoord = normalize(aPos.xyz);
    gl_Position = projection * view * aPos;
}
