#include "Player.h"

Player::Player(Window* window, std::vector<Terrain*>& terrains)
	:m_Window(window), m_Terrains(terrains)
{
	m_Position = glm::vec3(0.0f, 10.0f, 0.0f);
	m_Dimension = glm::vec3(2.0f, 5.0f, -2.0f);

	m_Direction = glm::vec3(0.0f, 0.0f, -1.0f);

	m_Camera = new Camera(GetCameraPositionFromPlayer(), m_Direction);
}

Player::~Player()
{
}

void Player::Update(double mouseX, double mouseY, double deltaTime)
{
	float newPosY = m_Position.y + m_Drag * deltaTime;
	float terrainHeight = m_Terrains[0]->GetTerrainHeight(m_Position.x, m_Position.z);
	if (newPosY > terrainHeight)
	{
		m_Position.y = newPosY;
	}
	else {
		m_Position.y = terrainHeight;
	}

	m_Camera->Update(mouseX, mouseY, deltaTime);
	m_Direction = m_Camera->GetCameraDirection();

	glm::vec3 moveDirection = glm::vec3(m_Direction.x, m_Direction.y, m_Direction.z);

	glm::vec3 rightVector = glm::cross(moveDirection, m_UpVector);

	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_W) == GLFW_PRESS)
	{
		// Move forward
		m_Position += ((float)deltaTime * m_PlayerSpeed) * moveDirection;
	}
	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_A) == GLFW_PRESS)
	{
		// Move left
		m_Position -= ((float)deltaTime * m_PlayerSpeed) * rightVector;
	}
	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_S) == GLFW_PRESS)
	{
		// Move backward
		m_Position -= ((float)deltaTime * m_PlayerSpeed) * moveDirection;
	}
	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_D) == GLFW_PRESS)
	{
		// Move right
		m_Position += ((float)deltaTime * m_PlayerSpeed) * rightVector;
	}

	m_Camera->SetPosition(GetCameraPositionFromPlayer());
}

glm::vec3 Player::GetCameraPositionFromPlayer()
{
	float playerWidth = m_Dimension.x;
	float playerHeight = m_Dimension.y;
	float playerBreadth = m_Dimension.z;

	glm::vec3 cameraPosition;
	cameraPosition.x = m_Position.x + playerWidth / 2;
	cameraPosition.y = m_Position.y + playerHeight;
	cameraPosition.z = m_Position.z - playerBreadth / 2; // -z is forward

	return cameraPosition;
}
