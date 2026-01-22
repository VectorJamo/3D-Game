#version 330 core

out vec4 color;

in vec2 v_TCoord;
in vec3 v_Normal;
in float v_Visibility;

uniform sampler2D u_TextureUnit;

uniform vec3 u_DirectionalLight;
uniform vec4 u_LightColor;
uniform vec4 u_SkyColor;

void main()
{
	vec4 sampledColor = texture(u_TextureUnit, v_TCoord);

	if(sampledColor.w < 0.5f)
	{
		discard;
	}

	float ambientStrength = 0.3f;
	vec4 ambientLight = ambientStrength * u_LightColor;

	vec3 dirLightInverted = -u_DirectionalLight;

	float dirLightStrength = max(dot(v_Normal, dirLightInverted), 0.0f);
	vec4 dirLight = dirLightStrength * u_LightColor;
	
	vec4 finalColor = ((ambientLight + dirLight) * texture(u_TextureUnit, v_TCoord));
	color = mix(u_SkyColor, finalColor, v_Visibility);  
}