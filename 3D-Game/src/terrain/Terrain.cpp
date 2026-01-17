#include "Terrain.h"

Terrain::Terrain(int gridX, int gridZ, glm::mat4 projectionMatrix)
{
	m_PositionX = gridX * m_TerrainSize;
	m_PositionZ = gridZ * m_TerrainSize;

	m_TerrainShader = new Shader("res/shaders/terrain/vs.glsl", "res/shaders/terrain/fs.glsl");
	m_TerrainShader->Use();
	m_TerrainShader->SetUniformMat4f("u_Projection", projectionMatrix);

	CreateTerrainData();
	CreateGLBuffers();
}

Terrain::~Terrain()
{
	delete m_TerrainShader;
}


void Terrain::CreateTerrainData()
{
	int verticesPerAxis = sqrt(m_VerticesCount);
	float dVertex = m_TerrainSize / verticesPerAxis;

	// Vertex Data
	for (int z = 0; z < verticesPerAxis; z++)
	{
		for (int x = 0; x < verticesPerAxis; x++)
		{
			float bottomLeftX = m_PositionX + x * dVertex;
			float bottomLeftZ = m_PositionZ - z * dVertex;

			// CCW order (bottom left -> top left)
			m_Vertices.emplace_back(GetTerrainVertexData(bottomLeftX, bottomLeftZ));
			m_Vertices.emplace_back(GetTerrainVertexData(bottomLeftX + dVertex, bottomLeftZ));
			m_Vertices.emplace_back(GetTerrainVertexData(bottomLeftX + dVertex, bottomLeftZ - dVertex));
			m_Vertices.emplace_back(GetTerrainVertexData(bottomLeftX, bottomLeftZ - dVertex));
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

void Terrain::Render(glm::mat4& viewMatrix)
{
	m_TerrainShader->Use();
	m_TerrainShader->SetUniformMat4f("u_View", viewMatrix);
	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_SHORT, 0);
}


TerrainVertex Terrain::GetTerrainVertexData(float positionX, float positionZ)
{
	TerrainVertex vertex;
	vertex.position = glm::vec3(positionX, 0.0f, positionZ);
	vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);

	float xtCoord = positionX / m_TerrainSize;
	float ytCoord = positionZ / m_TerrainSize;
	vertex.tCoord = glm::vec2(xtCoord, ytCoord);

	return vertex;
}
