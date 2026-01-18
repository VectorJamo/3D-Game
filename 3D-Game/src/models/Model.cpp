#include "Model.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

Model::Model(const std::string& path)
{
	LoadModel(path);
}

Model::~Model()
{
}

void Model::LoadModel(const std::string& path) 
{
	// Read the file
	std::vector<std::string> m_Lines;

	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cout << "Failed to load model file at: " << path << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		m_Lines.push_back(line);
	}

	// Parse the data
	std::vector<glm::vec3> m_Positions;
	std::vector<glm::vec3> m_Normals;
	std::vector<glm::vec2> m_TCoords;

	for (auto& line : m_Lines)
	{
		if (line[0] == 'v')
		{
			if (line[1] == 'n')
			{
				// Normal
				std::vector<std::string> sNormal = SplitStringBySpace(line);

				glm::vec3 normal;
				normal.x = std::stof(sNormal[1]); // skip index 0
				normal.y = std::stof(sNormal[2]);
				normal.z = std::stof(sNormal[3]);

				m_Normals.push_back(normal);
			}
			else if (line[1] == 't') {
				// TextCoord
				std::vector<std::string> sTCoord = SplitStringBySpace(line);

				glm::vec2 tCoord;
				tCoord.x = std::stof(sTCoord[1]); // skip index 0
				tCoord.y = std::stof(sTCoord[2]);

				m_TCoords.push_back(tCoord);
			}
			else {
				// Position
				std::vector<std::string> sPosition = SplitStringBySpace(line);

				glm::vec3 position;
				position.x = std::stof(sPosition[1]); // skip index 0
				position.y = std::stof(sPosition[2]);
				position.z = std::stof(sPosition[3]);

				m_Positions.push_back(position);
			}
		}
	}

	// Load the vertex data using the faces
	for (auto& line: m_Lines)
	{
		if (line[0] == 'f')
		{

		}
	}
}

std::vector<std::string> Model::SplitStringBySpace(std::string& str)
{
	std::vector<std::string> tokens;
	
	std::istringstream iss(str);
	std::string token;

	while (std::getline(iss, token, ' '))
	{
		if (!token.empty())
			tokens.push_back(token);
	}

	return tokens;
}
