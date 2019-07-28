#version 330 core

layout (location = 0) in vec4 v_coord;
layout (location = 1) in vec3 v_normal;

uniform mat4 u_MVP;
out vec4 v_Color;

void main()
{
	gl_Position = u_MVP * v_coord;
	v_Color = vec4(v_normal,1.0);
}
