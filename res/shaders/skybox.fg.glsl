#version 400 core

in vec3 textureCoord;
out vec4 color;

uniform samplerCube cubemap;

void main() {             
    color = texture(cubemap, -textureCoord);
}
