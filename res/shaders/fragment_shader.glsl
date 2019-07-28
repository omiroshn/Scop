#version 330 core

uniform sampler2D u_Texture;

out vec4 color;
in vec4 v_Color;

void main()
{
	//vec4 texColor = texture(u_Texture, v_TexCoord);
	//color = texColor;
	color = v_Color;
}