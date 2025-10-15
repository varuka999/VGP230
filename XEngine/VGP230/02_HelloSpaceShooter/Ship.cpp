#include "Ship.h";
#include "Bullet.h"

Ship::Ship()
	: Entity(), mImageID(0), mPosition(0.0f), mRotation(0.0f)
{

}

Ship::~Ship()
{

}

void Ship::Load()
{
	mImageID = X::LoadTexture("fighter.png");
	XASSERT(mImageID != 0, "Ship: Image did not load");

	mPosition.x = X::GetScreenWidth() * 0.5f;
	mPosition.y = X::GetScreenHeight() * 0.5f;

	mBulletPool.Load();
}

void Ship::Update(float deltaTime)
{
	const float speed = 300.0f;
	const float turnSpeed = X::Math::kPiByTwo;
	if (X::IsKeyDown(X::Keys::W))
	{
		mPosition += X::Math::Vector2::Forward(mRotation) * speed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::S))
	{
		mPosition -= X::Math::Vector2::Forward(mRotation) * speed * deltaTime;
	}

	if (X::IsKeyDown(X::Keys::A))
	{
		mRotation -= turnSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::D))
	{
		mRotation += turnSpeed * deltaTime;
	}

	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		X::Math::Vector2 spawnPosition = mPosition + X::Math::Vector2::Forward(mRotation) * 50.0f;
		Bullet* bullet = mBulletPool.GetBullet();
		bullet->SetActive(spawnPosition, mRotation);
	}

	mBulletPool.Update(deltaTime);
}

void Ship::Render()
{
	X::DrawSprite(mImageID, mPosition, mRotation);
	mBulletPool.Render();
}

void Ship::Unload()
{
	mBulletPool.Unload();
}
