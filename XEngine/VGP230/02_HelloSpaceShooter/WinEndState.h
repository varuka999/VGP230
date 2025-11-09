#pragma once
#include "GameState.h"

class WinEndState : public GameState
{
public:
	WinEndState();
	~WinEndState() override;

	void Load() override;
	State Update(float deltaTime) override;
	void Render() override;
	void Unload() override;
};
