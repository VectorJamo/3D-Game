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

	static constexpr float m_FpsLogFrequency = 2.0f; // 2 sec
	double m_FpsLogCounter = 0.0;

public:
	Application();
	~Application();

	void Run();

	static double GetDeltaTime() { return m_DeltaTime; }

private:
	void LogFPS();
};

