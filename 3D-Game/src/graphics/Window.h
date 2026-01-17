#pragma once
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* m_Window;
	int m_Width, m_Height;
	const char* m_Title;

public:
	Window(int width, int height, const char* title);
	~Window();

	void SetClearColor(float r, float g, float b, float a);

	void Clear();
	void PollEvents();
	void Render();

	bool GetWindowShouldClose() const;

	GLFWwindow* GetWindowInstance() const { return m_Window; }
};

Window* CreateBasicWindow();
