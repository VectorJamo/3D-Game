#pragma once
#include <string>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
private:
	unsigned int m_ShaderProgramID;
	const char* m_VertexShaderPath, * m_FragmentShaderPath;

public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	~Shader();

	void Use();

	void SetUniformVec4f(const char* uniformName, float x, float y, float z, float w);
	void SetUniformMat4f(const char* uniformName, glm::mat4 matrix);
	void SetUniform1i(const char* uniformName, int value);

	inline unsigned int GetShaderProgram() { return m_ShaderProgramID; }
private:
	std::string LoadShader(const char* filePath);
	unsigned int CompileShader(int shaderType, const char* shaderCode);
};
