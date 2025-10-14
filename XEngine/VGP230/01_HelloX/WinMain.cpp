#include "XEngine.h"
#include "BouncingSprite.h";

X::TextureId imageID1 = 0;
X::Math::Vector2 image1Pos = { 100.0f, 100.0f };
float screenWidth = 0.0f;
float screenHeight = 0.0f;
BouncingSprite* sprite1Ptr = nullptr;
BouncingSprite* sprite2Ptr = nullptr;
BouncingSprite* sprite3Ptr = nullptr;

void GameInit()
{
	XLOG("Game Init");
	screenWidth = X::GetScreenWidth();
	screenHeight = X::GetScreenHeight();

	sprite1Ptr = new BouncingSprite("DVD_logo.png");
	sprite2Ptr = new BouncingSprite("DVD_logo2.png");
	sprite3Ptr = new BouncingSprite("DVD_logo3.png");
	
}

void GameRender()
{
	X::DrawSprite(sprite1Ptr->imageID, sprite1Ptr->imagePos);
	X::DrawSprite(sprite2Ptr->imageID, sprite2Ptr->imagePos);
	X::DrawSprite(sprite3Ptr->imageID, sprite3Ptr->imagePos);
}

bool GameLoop(float deltaTime)
{
	sprite1Ptr->imagePos.x += sprite1Ptr->moveSpeedX * deltaTime;
	sprite1Ptr->imagePos.y += sprite1Ptr->moveSpeedY * deltaTime;

	if (sprite1Ptr->imagePos.x + (sprite1Ptr->spriteWidth / 2) >= screenWidth || (sprite1Ptr->imagePos.x - sprite1Ptr->spriteWidth / 2) <= 0)
	{
		sprite1Ptr->moveSpeedX = -sprite1Ptr->moveSpeedX;
	}
	if (sprite1Ptr->imagePos.y + (sprite1Ptr->spriteHeight / 2) >= screenHeight || (sprite1Ptr->imagePos.y - sprite1Ptr->spriteHeight / 2) <= 0)
	{
		sprite1Ptr->moveSpeedY = -sprite1Ptr->moveSpeedY;
	}

	sprite2Ptr->imagePos.x += sprite2Ptr->moveSpeedX * deltaTime;
	sprite2Ptr->imagePos.y += sprite2Ptr->moveSpeedY * deltaTime;

	if (sprite2Ptr->imagePos.x + (sprite2Ptr->spriteWidth / 2) >= screenWidth || (sprite2Ptr->imagePos.x - sprite2Ptr->spriteWidth / 2) <= 0)
	{
		sprite2Ptr->moveSpeedX = -sprite2Ptr->moveSpeedX;
	}
	if (sprite2Ptr->imagePos.y + (sprite2Ptr->spriteHeight / 2) >= screenHeight || (sprite2Ptr->imagePos.y - sprite2Ptr->spriteHeight / 2) <= 0)
	{
		sprite2Ptr->moveSpeedY = -sprite2Ptr->moveSpeedY;
	}

	sprite3Ptr->imagePos.x += sprite3Ptr->moveSpeedX * deltaTime;
	sprite3Ptr->imagePos.y += sprite3Ptr->moveSpeedY * deltaTime;

	if (sprite3Ptr->imagePos.x + (sprite3Ptr->spriteWidth / 2) >= screenWidth || (sprite3Ptr->imagePos.x - sprite3Ptr->spriteWidth / 2) <= 0)
	{
		sprite3Ptr->moveSpeedX = -sprite3Ptr->moveSpeedX;
	}
	if (sprite3Ptr->imagePos.y + (sprite3Ptr->spriteHeight / 2) >= screenHeight || (sprite3Ptr->imagePos.y - sprite3Ptr->spriteHeight / 2) <= 0)
	{
		sprite3Ptr->moveSpeedY = -sprite3Ptr->moveSpeedY;
	}

	GameRender();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	XLOG("Game Cleanup");
	delete sprite1Ptr;
	delete sprite2Ptr;
	delete sprite3Ptr;
	sprite1Ptr = nullptr;
	sprite2Ptr = nullptr;
	sprite3Ptr = nullptr;
}


int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	srand(time(NULL));
	X::Start("xconfig.json");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();

	return 0;
}