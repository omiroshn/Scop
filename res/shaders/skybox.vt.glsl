#version 330 core
layout (location = 0) in vec4 v_coord;

out vec3 textureCoord;

uniform mat4 u_MVP;

void main()
{
    textureCoord = normalize( v_coord.xyz );
    gl_Position = u_MVP * v_coord;
}
