#version 330 core

out vec4 color;

in vec2 v_TCoord;
in vec3 v_Normal;
in vec3 v_ViewSpacePos;

uniform sampler2D u_TextureUnit;

uniform vec3 u_DirectionalLight;
uniform vec4 u_LightColor;

uniform vec4 u_SkyColor;

void main()
{
	float ambientStrength = 0.3f;
	vec4 ambientLight = ambientStrength * u_LightColor;

	vec3 dirLightInverted = -u_DirectionalLight;

	float dirLightStrength = max(dot(v_Normal, dirLightInverted), 0.0f);
	vec4 dirLight = dirLightStrength * u_LightColor;

	// Fog calculation
	float fogIntensity = 0.0f;
	float distFromPlayer = length(v_ViewSpacePos);

	if(distFromPlayer < 50.0f)
	{
		fogIntensity = 0.0f;
	}else{
		fogIntensity = 1.0f - (50.0f/distFromPlayer);
	}
	
	vec4 finalColor = ((ambientLight + dirLight) * texture(u_TextureUnit, v_TCoord));
	color = mix(finalColor, u_SkyColor, fogIntensity);  
}