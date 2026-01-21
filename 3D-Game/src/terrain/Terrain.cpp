#include "Terrain.h"

#include "../../utils/stb_image.h"
#include <iostream>

int Terrain::m_VerticesCount;
Terrain::Terrain(int gridX, int gridZ)
{
	m_PositionX = gridX * m_TerrainSize;
	m_PositionZ = gridZ * m_TerrainSize;

	LoadHeightMap("res/images/terrain/heightmap.png");
	m_VerticesCount = m_HeightMapHeight;

	CreateTerrainData();
	CreateGLBuffers();
}

Terrain::~Terrain()
{
}

void Terrain::CreateTerrainData()
{
	float dVertex = (float)m_TerrainSize / (float)m_VerticesCount;

	// Vertex Data
	for (int z = 0; z < m_VerticesCount; z++)
	{
		for (int x = 0; x < m_VerticesCount; x++)
		{
			float bottomLeftX = m_PositionX + x * dVertex;
			float bottomLeftZ = m_PositionZ - z * dVertex;


			// CCW order (bottom left -> top left)
			m_Vertices.emplace_back(GetTerrainVertexData(bottomLeftX, bottomLeftZ, x, z));
			m_Vertices.emplace_back(GetTerrainVertexData(bottomLeftX + dVertex, bottomLeftZ, x+1, z));
			m_Vertices.emplace_back(GetTerrainVertexData(bottomLeftX + dVertex, bottomLeftZ - dVertex, x+1, z+1));
			m_Vertices.emplace_back(GetTerrainVertexData(bottomLeftX, bottomLeftZ - dVertex, x, z+1));
		}
	}

	// Index Data
	int numTerrainQuads = m_Vertices.size() / 4;
	for (int i = 0; i < numTerrainQuads; i++)
	{
		// Again, CCW order
		m_Indices.push_back(4 * i + 0);
		m_Indices.push_back(4 * i + 1);
		m_Indices.push_back(4 * i + 2);
		m_Indices.push_back(4 * i + 2);
		m_Indices.push_back(4 * i + 3);
		m_Indices.push_back(4 * i + 0);
	}
}

void Terrain::CreateGLBuffers()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(TerrainVertex), &m_Vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)sizeof(glm::vec3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)(sizeof(glm::vec3)*2));

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned short), &m_Indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Terrain::LoadHeightMap(const std::string& path)
{
	stbi_set_flip_vertically_on_load(false);

	m_HeightMap = stbi_load(path.c_str(), &m_HeightMapWidth, &m_HeightMapHeight, &m_NChannels, 4);

	if (m_HeightMap == nullptr)
	{
		std::cout << "Failed to load heightmap" << std::endl;
	}
	std::cout << "Width:" << m_HeightMapWidth << std::endl;
	std::cout << "Height:" << m_HeightMapHeight << std::endl;
	std::cout << "Num Channels:" << m_NChannels << std::endl;
}

float Terrain::GetHeightFromHeightMap(int pixelXPos, int pixelYPos)
{
	if (pixelXPos > 0 && pixelXPos < 256 && pixelYPos > 0 && pixelYPos < 256)
	{
		int offset = (pixelXPos * 4) + ((pixelYPos * m_HeightMapWidth)*4);

		unsigned char* r = &m_HeightMap[offset];
		unsigned char* g = &m_HeightMap[offset + 1];
		unsigned char* b = &m_HeightMap[offset + 2];

		float normalized = int(*r) / 255.0f;

		float height = (m_MaxHeight - m_MinHeight) * normalized - (std::abs(m_MinHeight));

		return height;
	}
	return 0.0f;
}

void Terrain::Render()
{
	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_SHORT, 0);
}


TerrainVertex Terrain::GetTerrainVertexData(float positionX, float positionZ, int vertexX, int vertexZ)
{
	TerrainVertex vertex;
	float yPos = GetHeightFromHeightMap(vertexX, vertexZ);
	
	vertex.position = glm::vec3(positionX, yPos, positionZ);
	vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);

	float xtCoord = positionX / m_TerrainSize;
	float ytCoord = positionZ / m_TerrainSize;
	vertex.tCoord = glm::vec2(xtCoord, ytCoord);

	return vertex;
}
