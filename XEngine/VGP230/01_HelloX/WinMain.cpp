#include "XEngine.h"

X::TextureId imageID = 0;
X::Math::Vector2 imagePos = { 0.0f, 0.0f };
float imageRot = 0.0f;

void GameInit()
{
	XLOG("Game Init");
	imageID = X::LoadTexture("mario.png");
	imagePos.x = X::GetScreenWidth() * 0.5f;
	imagePos.y = X::GetScreenHeight() * 0.5f;

	float spriteWidth = X::GetSpriteWidth(imageID);
	float spriteHeight = X::GetSpriteHeight(imageID);
}

void GameRender()
{
	X::DrawSprite(imageID, imagePos, imageRot);
}

bool GameLoop(float deltaTime)
{
	//XLOG("Game Loop");
	//std::cout << "Game Loop";
	const float moveSpeed = 500.0f;
	const float rotSpeed = 20.0f;
	if (X::IsKeyDown(X::Keys::UP))
	{
		imagePos.y -= moveSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::RIGHT))
	{
		imagePos.x += moveSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		imagePos.x -= moveSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::DOWN))
	{
		imagePos.y += moveSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::E))
	{
		imageRot += rotSpeed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::Q))
	{
		imageRot -= rotSpeed * deltaTime;
	}

	GameRender();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	XLOG("Game Cleanup");
}


int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();

	return 0;
}