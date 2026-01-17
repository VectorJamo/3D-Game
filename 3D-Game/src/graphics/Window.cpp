#include "Window.h"

#include <iostream>
Window::Window(int width, int height, const char* title)
	:m_Window(nullptr), m_Width(width), m_Height(height), m_Title(title)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw." << std::endl;
	}
	else {

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (!m_Window)
		{
			std::cout << "Failed to create glfw window." << std::endl;
		}
		else {
			glfwMakeContextCurrent(m_Window);

			// Initialize GLAD
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
			}
			else {
				glViewport(0, 0, width, height);
			}
		}
	}
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
}

void Window::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::Render()
{
	glfwSwapBuffers(m_Window);
}

bool Window::GetWindowShouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}

Window* CreateBasicWindow()
{
	return new Window(800, 600, "GLFW Window");
}