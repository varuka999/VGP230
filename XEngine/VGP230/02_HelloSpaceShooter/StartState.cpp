#include "StartState.h"
#include "AnimSpriteArray.h"

StartState::StartState()
	: GameState(State::Start), mAnimSpriteArray(nullptr)
{
}

StartState::~StartState()
{
}

void StartState::Load()
{
	//mAnimSpriteArray = new AnimSpriteArray();
	//mAnimSpriteArray->Load();

	//std::vector<std::string> sprites;
	//std::string textureName;
	//int numSprites = 16;
	//for (int i = 0; i < numSprites; ++i)
	//{
	//	if (i < 9)
	//	{
	//		textureName = "scv_0";
	//	}
	//	else
	//	{
	//		textureName = "scv_";
	//	}

	//	textureName += std::to_string(i + 1) + ".png";
	//	sprites.push_back(textureName);
	//}

	//mAnimSpriteArray->LoadSprites(sprites);

	//X::Math::Vector2 position = X::Math::Vector2::Zero();
	//position.x = X::GetScreenWidth() * 0.5f;
	//position.y = X::GetScreenHeight() * 0.5f;
	//mAnimSpriteArray->SetPosition(position);
	//mAnimSpriteArray->SetActive(true);
}

State StartState::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		return State::RunGame;
	}

	//mAnimSpriteArray->Update(deltaTime);

	return GetState();
}

void StartState::Render()
{
	//mAnimSpriteArray->Render();

	const float textSize = 70.0f;
	const char* text = "PRESS ENTER TO START";
	float textWidth = X::GetTextWidth(text, textSize);
	float screenX = (X::GetScreenWidth() - textWidth) * 0.5f;
	float screenY = X::GetScreenHeight() * 0.2f;
	X::DrawScreenText(text, screenX, screenY, textSize, X::Colors::Green);
}

void StartState::Unload()
{
	//mAnimSpriteArray->Unload();
	//delete mAnimSpriteArray;
	//mAnimSpriteArray = nullptr;
}
