#include "WinEndState.h"
#include <XEngine.h>

WinEndState::WinEndState()
	: GameState(State::EndWin)
{
}

WinEndState::~WinEndState()
{
}

void WinEndState::Load()
{
}

State WinEndState::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		return State::Start;
	}

	return GetState();
}

void WinEndState::Render()
{
	const float textSize = 70.0f;
	const char* text = "	 YOU WIN\nENTER TO RESTART";
	float textWidth = X::GetTextWidth(text, textSize);
	float screenX = (X::GetScreenWidth() - textWidth) * 0.5f;
	float screenY = X::GetScreenHeight() * 0.2f;
	X::DrawScreenText(text, screenX, screenY, textSize, X::Colors::LightGreen);
}

void WinEndState::Unload()
{
}
