#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
	:m_ShaderProgramID(0), m_VertexShaderPath(vertexShaderPath), m_FragmentShaderPath(fragmentShaderPath)
{
	// Load the shaders
	std::string vs, fs;
	vs = LoadShader(vertexShaderPath);
	fs = LoadShader(fragmentShaderPath);

	const char* vertexShaderSource = vs.c_str();
	const char* fragmentShaderSource = fs.c_str();

	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	m_ShaderProgramID = glCreateProgram();

	glAttachShader(m_ShaderProgramID, vertexShader);
	glAttachShader(m_ShaderProgramID, fragmentShader);
	glLinkProgram(m_ShaderProgramID);

	// Check if the shader linking was successful or not
	int success;
	char infoLog[512];
	glGetProgramiv(m_ShaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ShaderProgramID, 512, NULL, infoLog);
		std::cout << "|| Failed to attach shaders and create a shader program ||" << std::endl;
		std::cout << infoLog << std::endl;
	}

	// Delete the intermediates after the program is linked
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_ShaderProgramID);
}

void Shader::Use()
{
	glUseProgram(m_ShaderProgramID);
}

void Shader::SetUniformVec4f(const char* uniformName, float x, float y, float z, float w)
{
	int uniformLocation = glGetUniformLocation(m_ShaderProgramID, uniformName);
	if (uniformLocation == -1)
	{
		std::cout << "Uniform: " << uniformName << " does not exist." << std::endl;
		return;
	}
	glUniform4f(uniformLocation, x, y, z, w);
}

void Shader::SetUniformMat4f(const char* uniformName, glm::mat4 matrix)
{
	int uniformLocation = glGetUniformLocation(m_ShaderProgramID, uniformName);
	if (uniformLocation == -1)
	{
		std::cout << "Uniform: " << uniformName << " does not exist." << std::endl;
		return;
	}

	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniform1i(const char* uniformName, int value)
{
	int uniformLocation = glGetUniformLocation(m_ShaderProgramID, uniformName);
	if (uniformLocation == -1)
	{
		std::cout << "Uniform: " << uniformName << " does not exist." << std::endl;
		return;
	}
	glUniform1i(uniformLocation, value);
}

std::string Shader::LoadShader(const char* filePath)
{
	std::string fileContent;
	std::ifstream stream(filePath);

	std::string line;
	while (std::getline(stream, line))
	{
		fileContent += (line + '\n');
	}
	return fileContent;
}

unsigned int Shader::CompileShader(int shaderType, const char* shaderCode)
{
	unsigned int shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);

	// Check if vertex shader compilation was successful or not
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		if (shaderType == GL_VERTEX_SHADER)
		{
			std::cout << "|| VERTEX SHADER COMPILATION ERROR ||" << std::endl;
		}
		else {
			std::cout << "|| FRAGMENT SHADER COMPILATION ERROR ||" << std::endl;

		}
		std::cout << infoLog << std::endl;
		return -1;
	}
	return shader;
}