#include "RunGameState.h"
#include <XEngine.h>
#include "Game.h"

RunGameState::RunGameState()
	: GameState(State::RunGame), mGame(nullptr)
{
}

RunGameState::~RunGameState()
{
}

void RunGameState::Load()
{
	mGame = new Game();
	mGame->Load();
}

State RunGameState::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		return State::RunGame;
	}

	mGame->Update(deltaTime);

	if (mGame->IsGameOverLoss())
	{
		return State::EndLoss;
	}
	else if (mGame->IsGameOverWin())
	{
		return State::EndWin;
	}

	return State::RunGame;
}

void RunGameState::Render()
{
	//const float textSize = 100.0f;
	//const char* text = "RUN SCREEN\n<PRESS ENTER>";
	//float textWidth = X::GetTextWidth(text, textSize);
	//float screenX = (X::GetScreenWidth() - textWidth) * 0.5f;
	//float screenY = X::GetScreenHeight() * 0.5f;
	//X::DrawScreenText(text, screenX, screenY, textSize, X::Colors::Yellow);

	mGame->Render();
}

void RunGameState::Unload()
{
	mGame->Unload();
	delete mGame;
	mGame = nullptr;
}
