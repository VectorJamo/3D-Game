#version 330 core

out vec4 color;

in vec2 v_TCoord;
in vec3 v_Normal;
in vec3 v_ViewSpacePos;

uniform sampler2D u_BlendMap;
uniform sampler2D u_GrassTexture;
uniform sampler2D u_GrassFlowersTexture;
uniform sampler2D u_MudTexture;
uniform sampler2D u_PathTexture;

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

	// Texture calculation
	vec4 blendMapColor = texture(u_BlendMap, v_TCoord);
	float grassTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
	
	vec2 tiledTextCoords = v_TCoord * 100.0f;
	
	// no color = grass, red = mud, green = grass flowers, blue = path
	vec4 grassTextureColor = texture(u_GrassTexture, tiledTextCoords) * grassTextureAmount;
	vec4 mudTextureColor = texture(u_MudTexture, tiledTextCoords) * blendMapColor.r;
	vec4 grassFlowersTextureColor = texture(u_GrassFlowersTexture, tiledTextCoords) * blendMapColor.g;
	vec4 pathTextureColor = texture(u_PathTexture, tiledTextCoords) * blendMapColor.b;

	vec4 finalTextureColor = grassTextureColor + mudTextureColor + grassFlowersTextureColor + pathTextureColor;
	
	vec4 finalColor = ((ambientLight + dirLight) * finalTextureColor);

	color = mix(finalColor, u_SkyColor, fogIntensity);  
}