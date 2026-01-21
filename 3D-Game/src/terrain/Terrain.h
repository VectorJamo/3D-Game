#pragma once
#include "../graphics/Shader.h"
#include <glm/glm.hpp>
#include <vector>


struct TerrainVertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tCoord;
};

class Terrain
{
private:
	// Constants
	static constexpr float m_TerrainSize = 800;
	static int m_VerticesCount;

	// Terrain Data
	float m_PositionX, m_PositionZ;
	static constexpr float m_MaxHeight = 50.0f;
	static constexpr float m_MinHeight = -50.0f;

	std::vector<TerrainVertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

	// Height Map Data
	unsigned char* m_HeightMap;
	int m_HeightMapWidth, m_HeightMapHeight, m_NChannels;

	// OpenGL
	unsigned int m_VAO, m_VBO, m_IBO;

public:
	Terrain(int gridX, int gridZ);
	~Terrain();

	void Render();

private:
	void CreateTerrainData();
	void CreateGLBuffers();
	void LoadHeightMap(const std::string& path);
	float GetHeightFromHeightMap(int pixelXPos, int pixelYPos);
	TerrainVertex GetTerrainVertexData(float positionX, float positionZ, int vertexX, int vertexZ);
};

