#version 330 core

out vec4 color;

in vec2 v_TCoord;
in vec3 v_Normal;

uniform sampler2D u_TextureUnit;

void main()
{
	vec4 sampledColor = texture(u_TextureUnit, v_TCoord);

	if(sampledColor.w < 0.5f)
	{
		discard;
	}

	color = sampledColor;
}