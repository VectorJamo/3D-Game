#include "Application.h"
#include <iostream>

double Application::m_CurrentTime = 0.0;
double Application::m_LastTime = 0.0;
double Application::m_DeltaTime = 0.0;

Application::Application()
{
	m_Window = new Window(800, 600, "3D-Game");
	m_Window->SetClearColor(0.0f, 1.0f, 0.0f, 1.0f);

	StateManager::SetCurrentScene(new GameState());
}

Application::~Application()
{
	delete m_Window;
}

void Application::Run()
{
	m_LastTime = glfwGetTime();
	while (!m_Window->GetWindowShouldClose())
	{
		m_CurrentTime = glfwGetTime();
		m_DeltaTime = m_CurrentTime - m_LastTime;
		m_LastTime = glfwGetTime();
		
		m_Window->PollEvents();
		m_Window->Clear();

		StateManager::GetCurrentScene()->Update();
		StateManager::GetCurrentScene()->Render();

		m_Window->Render();
	}
}
