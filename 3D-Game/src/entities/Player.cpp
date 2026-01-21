#include "Player.h"

Player::Player(Window* window)
	:m_Window(window)
{
	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Dimension = glm::vec3(2.0f, 5.0f, -2.0f);

	m_Direction = glm::vec3(0.0f, 0.0f, -1.0f);
}

Player::~Player()
{
}

void Player::Update(double deltaTime)
{
	
	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_W) == GLFW_PRESS)
	{
		// Move forward
		m_Position += ((float)deltaTime * m_PlayerSpeed) * m_Direction;
	}
	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_A) == GLFW_PRESS)
	{
		// Move left
	}
	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_S) == GLFW_PRESS)
	{
		// Move backward
		m_Position -= ((float)deltaTime * m_PlayerSpeed) * m_Direction;
	}
	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_D) == GLFW_PRESS)
	{
		// Move right
	}
}
