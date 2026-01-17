#version 330 core

layout (location = 0) in vec2 a_Position;

out vec2 v_TextCoord;

void main()
{
	gl_Position = vec4(a_Position, 0.0f, 1.0f);
}