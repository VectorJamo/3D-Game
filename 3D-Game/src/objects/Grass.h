#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../graphics/Texture.h"
#include "../terrain/Terrain.h"

class Grass
{
private:
	static unsigned int m_VAO, m_VBO, m_IBO, m_TBO; // m_TBO -> Transformation buffer (mat4s)

	int m_NumInstances;
	glm::mat4* m_Transformations;

	Texture* m_GrassTexture;

	std::vector<Terrain*>& m_Terrains;

public:
	Grass(int numInstances, std::vector<Terrain*>& terrains);
	~Grass();

	void Render();

private:
	void CreateGLBuffers();
};

