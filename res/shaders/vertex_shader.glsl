#version 330 core

layout (location = 0) in vec4 v_coord;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 v_InTexCoord;

uniform mat4 u_MVP;
//out vec4 v_Color;
out vec2 v_TexCoord;

void main()
{
	gl_Position = u_MVP * v_coord;
	v_TexCoord = v_InTexCoord;
	//v_Color = vec4(v_normal,1.0);
}
