#pragma once

#include "StateManager.h"

class GameState : public StateManager
{
private:

public:
	GameState();
	~GameState();

	void Init() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void HandleInput() override;
};