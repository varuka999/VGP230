#pragma once
#include "XEngine.h"

struct BouncingSprite
{
	X::TextureId imageID = 0;
	X::Math::Vector2 imagePos = { 0.0f, 0.0f };
	float spriteWidth = 0.0f;
	float spriteHeight = 0.0f;
	float moveSpeedX = 0.0f;
	float moveSpeedY = 0.0f;

	struct BouncingSprite* next = nullptr;

	BouncingSprite(const char* fileName)
		: imageID(X::LoadTexture(fileName))
	{
		spriteWidth = X::GetSpriteWidth(imageID);
		spriteHeight = X::GetSpriteHeight(imageID);
		
		int marginX = X::GetScreenWidth() - (spriteWidth * 2);
		int marginY = X::GetScreenWidth() - (spriteHeight * 2);

		imagePos.x = spriteWidth + rand() % marginX;
		imagePos.y = spriteHeight + rand() % marginY;

		moveSpeedX = 100 + rand() % 401;
		moveSpeedY = moveSpeedX;

		int flip = rand() % 2;

		if (flip == 0)
		{
			moveSpeedX = -moveSpeedX;
		}
		else if (flip == 1)
		{
			moveSpeedY = -moveSpeedY;
		}
	}
};