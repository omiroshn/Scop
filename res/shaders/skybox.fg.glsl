#version 330 core
out vec4 color;

in vec3 textureCoord;

uniform samplerCube cubemap;

void main()
{             
    color = texture(cubemap, -textureCoord);
}