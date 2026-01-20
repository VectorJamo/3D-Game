#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Player
{
private:
	glm::vec3 m_Position; // Bottom-left backward position
	glm::vec3 m_Dimension;

	glm::vec3 m_Direction; // Direction vector. What direction the player is looking at. (m_Position + m_Direction) gives the lookAt position

public:
	Player();
	~Player();

	void Update();
	
	inline glm::vec3 GetPosition() const { return m_Position; }
	inline glm::vec3 GetDimension() const { return m_Dimension; }
};

