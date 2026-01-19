#include "GameState.h"
#include "../Application.h"

#include <iostream>
#include <cstdlib>

GameState::GameState(Window* window)
	:m_Window(window)
{
	m_SkyColor = glm::vec4(0.3f, 0.6f, 0.9f, 1.0f);
	m_Window->SetClearColor(m_SkyColor.x, m_SkyColor.y, m_SkyColor.z, m_SkyColor.w);

	m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);

	m_Camera = new Camera(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

	// Terrain
	m_TerrainShader = new Shader("res/shaders/terrain/vs.glsl", "res/shaders/terrain/fs.glsl");
	m_TerrainShader->Use();
	m_TerrainShader->SetUniformMat4f("u_Projection", m_ProjectionMatrix);

	m_GrassTexture = new Texture("res/images/terrain/grass.png");
	m_GrassTexture->Bind(0);

	m_Terrains.emplace_back(new Terrain(0, 0));
	m_Terrains.emplace_back(new Terrain(-1, 0));
	m_Terrains.emplace_back(new Terrain(-1, 1));
	m_Terrains.emplace_back(new Terrain(0, 1));

	// Models
	m_TreeTexture = new Texture("res/images/tree_atlas.png");

	m_DefaultShader = new Shader("res/shaders/vs.glsl", "res/shaders/fs.glsl");
	m_DefaultShader->Use();
	m_DefaultShader->SetUniformMat4f("u_Projection", m_ProjectionMatrix);

	m_TreeModel = new Model("res/models/Tree.obj");

	for (int i = 0; i < m_NumTrees; i++)
	{
		float x = (rand() % 600) - 300; // -300 -> 300
		float z = (rand() % 600) - 300; // -300 -> 300

		glm::vec3 treePosition = glm::vec3(x, 0.0f, z);
		m_TreeTranslations[i] = glm::mat4(1.0f);
		m_TreeTranslations[i] = glm::translate(m_TreeTranslations[i], treePosition);
	}

	// Objects
	m_GrassShader = new Shader("res/shaders/grass/vs.glsl", "res/shaders/grass/fs.glsl");
	m_GrassShader->Use();
	m_GrassShader->SetUniformMat4f("u_Projection", m_ProjectionMatrix);
	m_Grass = new Grass(5000);

	// Lighting
	m_LightColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

	m_DirectionalLight = glm::vec3(-1.0f, -1.0f, -1.0f);
	m_DirectionalLight = glm::normalize(m_DirectionalLight);

	m_DefaultShader->Use();
	m_DefaultShader->SetUniformVec4f("u_LightColor", m_LightColor);
	m_DefaultShader->SetUniformVec3f("u_DirectionalLight", m_DirectionalLight);
	m_DefaultShader->SetUniformVec4f("u_SkyColor", m_SkyColor);

	m_TerrainShader->Use();
	m_TerrainShader->SetUniformVec4f("u_LightColor", m_LightColor);
	m_TerrainShader->SetUniformVec3f("u_DirectionalLight", m_DirectionalLight);
	m_TerrainShader->SetUniformVec4f("u_SkyColor", m_SkyColor);

	m_GrassShader->Use();
	m_GrassShader->SetUniformVec4f("u_LightColor", m_LightColor);
	m_GrassShader->SetUniformVec3f("u_DirectionalLight", m_DirectionalLight);
	m_GrassShader->SetUniformVec4f("u_SkyColor", m_SkyColor);

	glEnable(GL_DEPTH_TEST);
}

GameState::~GameState()
{
	delete m_Camera;
	
	delete m_DefaultShader;
	delete m_TreeModel;

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

	m_DefaultShader->Use();
	m_DefaultShader->SetUniformMat4f("u_View", m_Camera->GetViewMatrix());

	m_GrassShader->Use();
	m_GrassShader->SetUniformMat4f("u_View", m_Camera->GetViewMatrix());

	m_TerrainShader->Use();
	m_TerrainShader->SetUniformMat4f("u_View", m_Camera->GetViewMatrix());
}

void GameState::FixedUpdate()
{
}

void GameState::Render()
{
	m_GrassTexture->Bind(0);
	m_TerrainShader->Use();
	for (auto& terrain : m_Terrains)
		terrain->Render();
	
	m_TreeTexture->Bind(0);
	for (int i = 0; i < m_NumTrees; i++)
	{
		m_DefaultShader->Use();
		m_DefaultShader->SetUniformMat4f("u_Model", m_TreeTranslations[i]);

		m_TreeModel->Render(m_DefaultShader);
	}
	
	m_GrassShader->Use();
	m_Grass->Render();
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

	if (glfwGetKey(m_Window->GetWindowInstance(), GLFW_KEY_M) == GLFW_PRESS)
	{
		if (m_IsCursorActive)
		{
			m_IsCursorActive = false;
			glfwSetInputMode(m_Window->GetWindowInstance(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else {
			m_IsCursorActive = true;
			glfwSetInputMode(m_Window->GetWindowInstance(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
}
