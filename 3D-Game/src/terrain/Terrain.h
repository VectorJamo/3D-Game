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
	static constexpr int m_VerticesCount = 100;

	// Terrain Data
	float m_PositionX, m_PositionZ;

	std::vector<TerrainVertex> m_Vertices;
	std::vector<unsigned short> m_Indices;

	// OpenGL
	unsigned int m_VAO, m_VBO, m_IBO;
	Shader* m_TerrainShader;

public:
	Terrain(int gridX, int gridZ, glm::mat4 projectionMatrix);
	~Terrain();

	void Render(glm::mat4& viewMatrix);

private:
	void CreateTerrainData();
	void CreateGLBuffers();
	TerrainVertex GetTerrainVertexData(float positionX, float positionZ);
};

