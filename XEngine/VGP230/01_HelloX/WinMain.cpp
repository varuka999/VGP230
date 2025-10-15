#include "XEngine.h"
#include "BouncingSprite.h";

X::TextureId imageID1 = 0;
X::Math::Vector2 image1Pos = { 100.0f, 100.0f };
float screenWidth = 0.0f;
float screenHeight = 0.0f;
BouncingSprite* head = nullptr;
BouncingSprite* current = nullptr;
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

	sprite1Ptr->next = sprite2Ptr;
	sprite2Ptr->next = sprite3Ptr;

	head = sprite1Ptr;
	current = head;
}

void GameRender()
{
	X::DrawSprite(sprite1Ptr->imageID, sprite1Ptr->imagePos);
	X::DrawSprite(sprite2Ptr->imageID, sprite2Ptr->imagePos);
	X::DrawSprite(sprite3Ptr->imageID, sprite3Ptr->imagePos);
}

bool GameLoop(float deltaTime)
{
	for (int i = 0; i < 3; ++i)
	{
		current->imagePos.x += current->moveSpeedX * deltaTime;
		current->imagePos.y += current->moveSpeedY * deltaTime;

		if (current->imagePos.x + (current->spriteWidth / 2) >= screenWidth || (current->imagePos.x - current->spriteWidth / 2) <= 0)
		{
			current->moveSpeedX = -current->moveSpeedX;
		}
		if (current->imagePos.y + (current->spriteHeight / 2) >= screenHeight || (current->imagePos.y - current->spriteHeight / 2) <= 0)
		{
			current->moveSpeedY = -current->moveSpeedY;
		}

		if (i < 2)
		{
			current = current->next;
		}
	}

	current = head;

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
	head = nullptr;
	current = nullptr;
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