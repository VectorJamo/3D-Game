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

	// Shall the compiler optimize this?
	m_Heights = new float* [m_VerticesCount];
	for (int i = 0; i < m_VerticesCount; i++)
	{
		m_Heights[i] = new float[m_VerticesCount];
		// Not necessary. But did this for debugging.
		for (int j = 0; j < m_VerticesCount; j++)
		{
			m_Heights[i][j] = 0.0f;
		}
	}

	CreateTerrainData();
	CreateGLBuffers();
}

Terrain::~Terrain()
{
	for (int i = 0; i < m_VerticesCount; i++)
	{
		delete[] m_Heights[i];
	}
	delete m_Heights;
}

void Terrain::CreateTerrainData()
{
	float dVertex = (float)m_TerrainSize / (float)(m_VerticesCount - 1);
	std::cout << dVertex << std::endl;

	// Vertex Data
	for (int z = 0; z < m_VerticesCount; z++)
	{
		for (int x = 0; x < m_VerticesCount; x++)
		{
			float bottomLeftX = m_PositionX + x * dVertex;
			float bottomLeftZ = m_PositionZ - z * dVertex;
			
			m_Heights[z][x] = GetHeightFromHeightMap(x, z);

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Terrain::LoadHeightMap(const std::string& path)
{
	stbi_set_flip_vertically_on_load(true);

	m_HeightMap = stbi_load(path.c_str(), &m_HeightMapWidth, &m_HeightMapHeight, &m_NChannels, 4);

	if (m_HeightMap == nullptr)
	{
		std::cout << "Failed to load heightmap" << std::endl;
	}
}

float Terrain::GetHeightFromHeightMap(int pixelXPos, int pixelYPos)
{
	// Here, we ignore the height of the first & last row and first & last column of the terrian so that the point where terrians meet, 
	// the height of the vertices that meet at the terrains junctions is 0.

	if (pixelXPos > 0 && pixelXPos < 255 && pixelYPos > 0 && pixelYPos < 255)
	{
		int offset = (pixelXPos * 4) + ((pixelYPos * m_HeightMapWidth)*4);

		unsigned char* r = &m_HeightMap[offset];
		unsigned char* g = &m_HeightMap[offset + 1];
		unsigned char* b = &m_HeightMap[offset + 2];
		unsigned char* a = &m_HeightMap[offset + 3];

		float normalized = int(*r) / 255.0f;

		float height = (m_MaxHeight - m_MinHeight) * normalized - (std::abs(m_MinHeight));

		return height;
	}
	return 0.0f;
}

void Terrain::Render()
{
	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
}

float Terrain::GetTerrainHeight(float worldX, float worldZ)
{
	// Get position relative to the terrain
	float worldTerrainPosX = worldX - m_PositionX;
	float worldTerrainPosZ = worldZ - m_PositionZ;
	
	float gridSquareSize = m_TerrainSize / (float)(m_VerticesCount - 1);

	// Get which vertex is the world position inside the terrain
	int gridX = worldTerrainPosX / gridSquareSize;
	int gridZ = -worldTerrainPosZ / gridSquareSize;

	if (gridX < 0 || gridX > m_VerticesCount - 1 || gridZ < 0 || gridZ > m_VerticesCount - 1)
	{
		return 0.0f;
	}

	float height = m_Heights[gridZ][gridX];

	return height;
}


TerrainVertex Terrain::GetTerrainVertexData(float positionX, float positionZ, int vertexX, int vertexZ)
{
	TerrainVertex vertex;
	float yPos = GetHeightFromHeightMap(vertexX, vertexZ);

	// TODO: Calculate Normal
	float hLeft = GetHeightFromHeightMap(vertexX - 1, vertexZ);
	float hRight = GetHeightFromHeightMap(vertexX + 1, vertexZ);
	float hDown = GetHeightFromHeightMap(vertexX, vertexZ - 1);
	float hUp = GetHeightFromHeightMap(vertexX, vertexZ + 1);
	
	float normalX = hLeft - hDown;
	float normalY = 1.0f; // Hack number? 
	float normalZ = hUp - hDown;

	vertex.position = glm::vec3(positionX, yPos, positionZ);
	vertex.normal = glm::normalize(glm::vec3(normalX, normalY, normalZ));

	float xtCoord = positionX / m_TerrainSize;
	float ytCoord = positionZ / m_TerrainSize;
	vertex.tCoord = glm::vec2(xtCoord, ytCoord);

	return vertex;
}
