#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 v_TCoord;
out vec3 v_Normal;

const float density = 0.007f;
const float gradient = 1.5f;

out float v_Visibility;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0f);


	v_TCoord = a_TCoord;
	v_Normal = a_Normal;

	vec3 viewSpacePos = vec3(u_View * u_Model * vec4(a_Position, 1.0f));
	float distFromPlayer = length(viewSpacePos);

	float visibility = exp(-pow((distFromPlayer*density), gradient));
	visibility = clamp(visibility, 0.0f, 1.0f);

	v_Visibility = visibility;
}