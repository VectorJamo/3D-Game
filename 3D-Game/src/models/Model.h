#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Vertex.h"

class Model
{
private:
	std::vector<Vertex> m_Vertices;
	
	unsigned int m_VAO, m_VBO;

public:
	Model(const std::string& path);
	~Model();

private:
	void LoadModel(const std::string& path);
};

