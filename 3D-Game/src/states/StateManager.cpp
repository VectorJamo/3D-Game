#include "StateManager.h"

// YES, this is OK!
StateManager* StateManager::m_CurrentScene = nullptr;

void StateManager::SetCurrentScene(StateManager* scene)
{
	m_CurrentScene = scene;
}
