#include <iostream>

#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "states/GameState.h"

int main()
{
	Window window(800, 600, "3D-Game");

	window.SetClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	StateManager::SetCurrentScene(new GameState());

	while (!window.GetWindowShouldClose())
	{
		window.PollEvents();
		window.Clear();

		StateManager::GetCurrentScene()->Update();

		StateManager::GetCurrentScene()->Render();

		window.Render();
	}
}