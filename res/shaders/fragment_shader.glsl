#version 330 core

uniform sampler2D u_Texture;

out vec4 color;
//in vec4 v_Color;
in vec2 v_TexCoord;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
}