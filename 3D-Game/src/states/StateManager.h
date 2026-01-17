#pragma once

class StateManager
{
private:
	static StateManager* m_CurrentScene;

public:
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Render() = 0;
	virtual void HandleInput() = 0;

	static void SetCurrentScene(StateManager* scene);

	inline static StateManager* const GetCurrentScene() { return m_CurrentScene; }
};

