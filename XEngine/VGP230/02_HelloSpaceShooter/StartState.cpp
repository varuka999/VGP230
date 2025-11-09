#include "StartState.h"
#include "AnimSpriteArray.h"

StartState::StartState()
	: GameState(State::Start)
{
}

StartState::~StartState()
{
}

void StartState::Load()
{

}

State StartState::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		return State::RunGame;
	}

	return GetState();
}

void StartState::Render()
{
	const float textSize = 70.0f;
	const char* text = "PRESS ENTER TO START";
	float textWidth = X::GetTextWidth(text, textSize);
	float screenX = (X::GetScreenWidth() - textWidth) * 0.5f;
	float screenY = X::GetScreenHeight() * 0.2f;
	X::DrawScreenText(text, screenX, screenY, textSize, X::Colors::Green);
}

void StartState::Unload()
{

}
