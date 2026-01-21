#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "../graphics/Window.h"

class Player
{
private:
	Window* m_Window;

	glm::vec3 m_Position; // Bottom-left backward position
	glm::vec3 m_Dimension;

	static constexpr float m_PlayerSpeed = 100.0f;
	static constexpr float m_PlayerLookSpeed = 50.0f;
	static constexpr glm::vec3 m_UpVector = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 m_Direction; // Direction vector. What direction the player is looking at. (m_Position + m_Direction) gives the lookAt position

public:
	Player(Window* window);
	~Player();

	void Update(double deltaTime);
	
	inline glm::vec3 GetPosition() const { return m_Position; }
	inline glm::vec3 GetDimension() const { return m_Dimension; }
};

