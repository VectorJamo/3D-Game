#include "Grass.h"

#include <GLAD/glad.h>
#include <cstdlib>
#include <ctime>

unsigned int Grass::m_VAO;
unsigned int Grass::m_VBO;
unsigned int Grass::m_IBO;

Grass::Grass(int numInstances)
	:m_NumInstances(numInstances)
{
	std::srand(std::time(NULL));

	m_Transformations = new glm::mat4[m_NumInstances];
	int min = -800;
	int max = 800;
	for (int i = 0; i < m_NumInstances; i++)
	{
		float x = (std::rand() % (max-min)) + min;
		float z = (std::rand() % (max - min)) + min;

		glm::vec3 translation = glm::vec3(x, 0.0f, z);

		m_Transformations[i] = glm::mat4(1.0f);
		m_Transformations[i] = glm::translate(m_Transformations[i], translation);
	}

	CreateGLBuffers();

	m_GrassTexture = new Texture("res/images/grassTexture.png");
}

Grass::~Grass()
{
	delete[] m_Transformations;
}

void Grass::Render()
{
	m_GrassTexture->Bind(0);
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
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

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void*)(sizeof(float)*3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (void*)(sizeof(float)*6));

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}