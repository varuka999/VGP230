#pragma once
#include "GameState.h"

class AnimSpriteArray;

class StartState : public GameState
{
public:
	StartState();
	~StartState() override;

	void Load() override;
	State Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

private:
	AnimSpriteArray* mAnimSpriteArray;
};
