#pragma once
#include "StateManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../terrain/Terrain.h"

#include "../graphics/Window.h"
#include "../graphics/Texture.h"
#include "../graphics/Camera.h"

#include <vector>

class GameState : public StateManager
{
private:
	Window* m_Window;
	glm::mat4 m_ProjectionMatrix;
	
	Camera* m_Camera;

	// Terrain
	Texture* m_GrassTexture;

	std::vector<Terrain*> m_Terrains;

public:
	GameState(Window* window);
	~GameState();

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void HandleInput() override;
};