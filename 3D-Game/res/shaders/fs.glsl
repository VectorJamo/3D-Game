#version 330 core

out vec4 color;

in vec2 v_TCoord;
in vec3 v_Normal;

uniform sampler2D textureUnit;

void main()
{
	vec4 sampledColor = texture(textureUnit, v_TCoord);
	if(sampledColor.w < 0.5f)
	{
		discard;
	}
	color = sampledColor;
}