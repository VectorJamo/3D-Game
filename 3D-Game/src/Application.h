#pragma once
#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "states/GameState.h"

class Application
{
private:
	Window* m_Window;
	
	static double m_CurrentTime, m_LastTime, m_DeltaTime;

public:
	Application();
	~Application();

	void Run();

	static double GetDeltaTime() { return m_DeltaTime; }
};

