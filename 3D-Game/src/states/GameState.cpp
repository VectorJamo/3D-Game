#include "GameState.h"
#include "../Application.h"
#include <iostream>

GameState::GameState(Window* window)
	:m_Window(window)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	m_Camera = new Camera(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

	// Terrain
	m_GrassTexture = new Texture("res/images/grass.png");
	m_GrassTexture->Bind(0);

	m_Terrains.emplace_back(new Terrain(0, 0, m_ProjectionMatrix));
	m_Terrains.emplace_back(new Terrain(-1, 0, m_ProjectionMatrix));
	m_Terrains.emplace_back(new Terrain(-1, 1, m_ProjectionMatrix));
	m_Terrains.emplace_back(new Terrain(0, 1, m_ProjectionMatrix));
}

GameState::~GameState()
{
	delete m_Camera;

	delete m_GrassTexture;
	
	for (auto& terrain : m_Terrains)
		delete terrain;
}

void GameState::Update()
{
	HandleInput();

	double xpos, ypos;
	glfwGetCursorPos(m_Window->GetWindowInstance(), &xpos, &ypos);
	m_Camera->Update(xpos, ypos, Application::GetDeltaTime());
}

void GameState::FixedUpdate()
{
}

void GameState::Render()
{
	for (auto& terrain : m_Terrains)
		terrain->Render(m_Camera->GetViewMatrix());
}

void GameState::HandleInput()
{
	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Camera->MoveForward(Application::GetDeltaTime());
	}
	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Camera->MoveLeft(Application::GetDeltaTime());
	}
	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Camera->MoveBackward(Application::GetDeltaTime());
	}
	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Camera->MoveRight(Application::GetDeltaTime());
	}

	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		m_Window->CloseWindow();
	}
}
