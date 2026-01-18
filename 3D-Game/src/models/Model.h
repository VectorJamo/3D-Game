#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Vertex.h"
#include "../graphics/Shader.h"

class Model
{
private:
	std::vector<Vertex> m_Vertices;
	
	unsigned int m_VAO, m_VBO;

public:
	Model(const std::string& path);
	~Model();

	void Render(Shader* shader);

private:
	void LoadModel(const std::string& path);
	void CreateGLBuffers();

	std::vector<std::string> SplitString(std::string& str, char delim);
};

