#include "Ship.h";
#include "Bullet.h"
#include "BulletPool.h"
#include "Enemy.h"

Ship::Ship()
	: Entity(), Collidable(30.0f), mImageID(0), mPosition(0.0f), mRotation(0.0f), mBulletPool(nullptr)
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

	SetCollisionFilter(ET_ENEMY | ET_BULLET_PLAYER);
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
		Bullet* bullet = mBulletPool->GetBullet();
		bullet->SetCollisionFilter(ET_BULLET_PLAYER);
		bullet->SetActive(spawnPosition, mRotation);
	}
}

void Ship::Render()
{
	X::DrawSprite(mImageID, mPosition, mRotation);
	X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::DodgerBlue);
}

void Ship::Unload()
{

}

int Ship::GetType() const
{
	return ET_SHIP;
}

const X::Math::Vector2& Ship::GetPosition() const
{
	return mPosition;
}

void Ship::OnCollision(Collidable* collidable)
{
	XLOG("Ship Hit Something");
}

void Ship::SetBulletPool(BulletPool* bulletPool)
{
	mBulletPool = bulletPool;
}