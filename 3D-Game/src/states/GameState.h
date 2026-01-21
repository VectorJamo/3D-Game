#pragma once
#include "StateManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../terrain/Terrain.h"

#include "../graphics/Window.h"
#include "../graphics/Texture.h"
#include "../graphics/Camera.h"
#include "../models/Model.h"
#include "../objects/Grass.h"
#include "../entities/Player.h"

#include <vector>

class GameState : public StateManager
{
private:
	Window* m_Window;
	glm::mat4 m_ProjectionMatrix;
	
	// Entities
	Player* m_Player;

	// Terrain
	Shader* m_TerrainShader;
	Texture* m_BlendMapTexture, *m_GrassTexture, *m_GrassFlowersTexture, *m_MudTexture, *m_PathTexture;

	std::vector<Terrain*> m_Terrains;

	// Models
	Texture* m_TreeTexture;
	Shader* m_DefaultShader;
	
	Model* m_TreeModel;

	static constexpr int m_NumTrees = 200;
	glm::mat4 m_TreeTranslations[m_NumTrees];

	// Objects
	Shader* m_GrassShader;
	Grass* m_Grass;

	// Misc
	bool m_IsCursorActive = false;

	// Lighting
	glm::vec4 m_SkyColor;
	glm::vec4 m_LightColor;
	glm::vec3 m_DirectionalLight;

public:
	GameState(Window* window);
	~GameState();

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void HandleInput() override;
};