#include "EndState.h"
#include <XEngine.h>

EndState::EndState()
	: GameState(State::EndLoss)
{
}

EndState::~EndState()
{
}

void EndState::Load()
{
}

State EndState::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		return State::Start;
	}

	return GetState();
}

void EndState::Render()
{
	const float textSize = 70.0f;
	const char* text = "	YOU LOST\nENTER TO RESTART";
	float textWidth = X::GetTextWidth(text, textSize);
	float screenX = (X::GetScreenWidth() - textWidth) * 0.5f;
	float screenY = X::GetScreenHeight() * 0.2f;
	X::DrawScreenText(text, screenX, screenY, textSize, X::Colors::Red);
}

void EndState::Unload()
{
}
