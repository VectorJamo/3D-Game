#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../graphics/Texture.h"

class Grass
{
private:
	static unsigned int m_VAO, m_VBO, m_IBO;

	int m_NumInstances;
	glm::mat4* m_Transformations;

	Texture* m_GrassTexture;

public:
	Grass(int numInstances);
	~Grass();

	void Render();

private:
	void CreateGLBuffers();
};

