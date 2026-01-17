#version 330 core

out vec4 color;

in vec2 v_TCoord;
in vec3 v_Normal;

uniform sampler2D u_TextureUnit;

void main()
{
	color = texture(u_TextureUnit, v_TCoord);
}