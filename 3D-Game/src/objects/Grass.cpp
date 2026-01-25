#include "Grass.h"

#include <GLAD/glad.h>
#include <cstdlib>
#include <ctime>

unsigned int Grass::m_VAO;
unsigned int Grass::m_VBO;
unsigned int Grass::m_IBO;
unsigned int Grass::m_TBO;

Grass::Grass(int numInstances, std::vector<Terrain*>& terrains)
	:m_NumInstances(numInstances), m_Terrains(terrains)
{
	std::srand(std::time(NULL));

	m_Transformations = new glm::mat4[m_NumInstances];
	int min = -300;
	int max = 300;
	for (int i = 0; i < m_NumInstances; i++)
	{
		float x = (std::rand() % (max - min)) + min;
		float z = (std::rand() % (max - min)) + min;
		float rotationAngle = (std::rand() % 360);

		glm::vec3 translation = glm::vec3(x, m_Terrains[0]->GetTerrainHeight(x, z)+1.0f, z);

		m_Transformations[i] = glm::mat4(1.0f);
		m_Transformations[i] = glm::translate(m_Transformations[i], translation);
		m_Transformations[i] = glm::rotate(m_Transformations[i], glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	CreateGLBuffers();

	m_GrassTexture = new Texture("res/images/terrain/grassTexture.png");
}

Grass::~Grass()
{
	delete[] m_Transformations;
}

void Grass::Render()
{
	m_GrassTexture->Bind(0);
	glBindVertexArray(m_VAO);
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0, m_NumInstances);
}

void Grass::CreateGLBuffers()
{
	float vertices[] = {
		// Positions		// Normals		  // Texture Coordinates
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	};
	unsigned char indices[] = {
		0, 1, 2, 2, 3, 0
	};

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_TBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_TBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * m_NumInstances, m_Transformations, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void*)(sizeof(float)*3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void*)(sizeof(float)*6));

	glBindBuffer(GL_ARRAY_BUFFER, m_TBO);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4)*4, 0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4)*4, (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4)*4, (void*)(sizeof(glm::vec4)*2));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4)*4, (void*)(sizeof(glm::vec4)*3));
	glVertexAttribDivisor(3, 1); // Per-instance
	glVertexAttribDivisor(4, 1); // Per-instance
	glVertexAttribDivisor(5, 1); // Per-instance
	glVertexAttribDivisor(6, 1); // Per-instance

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}