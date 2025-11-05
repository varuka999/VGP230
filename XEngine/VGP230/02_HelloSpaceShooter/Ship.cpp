#include "Ship.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "AnimSpriteSheet.h"

Ship::Ship()
	: Entity(), Collidable(30.0f), mImageID(0), mPosition(0.0f), mRotation(0.0f), mHealth(0), mMaxHealth(100), mBulletPool(nullptr), mExplosion(nullptr)
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

	SetCollisionFilter(ET_ENEMY | ET_BULLET_ENEMY);

	mHealth = mMaxHealth;
	mExplosion = new AnimSpriteSheet();
	mExplosion->Load();
}

void Ship::Update(float deltaTime)
{
	if (IsAlive() == true)
	{
		const float speed = 300.0f;
		const float turnSpeed = X::Math::kPiByTwo;
		if (X::IsKeyDown(X::Keys::W) || X::IsKeyDown(X::Keys::UP))
		{
			mPosition += X::Math::Vector2::Forward(mRotation) * speed * deltaTime;
		}
		else if (X::IsKeyDown(X::Keys::S) || X::IsKeyDown(X::Keys::DOWN))
		{
			mPosition -= X::Math::Vector2::Forward(mRotation) * speed * deltaTime;
		}

		if (X::IsKeyDown(X::Keys::A) || X::IsKeyDown(X::Keys::LEFT))
		{
			mRotation -= turnSpeed * deltaTime;
		}
		else if (X::IsKeyDown(X::Keys::D) || X::IsKeyDown(X::Keys::RIGHT))
		{
			mRotation += turnSpeed * deltaTime;
		}

		if (X::IsKeyPressed(X::Keys::SPACE) || X::IsMousePressed(0))
		{
			X::Math::Vector2 spawnPosition = mPosition + X::Math::Vector2::Forward(mRotation) * 50.0f;
			Bullet* bullet = mBulletPool->GetBullet();
			bullet->SetEntityType(ET_BULLET_PLAYER);
			bullet->SetActive(spawnPosition, mRotation);
		}
	}

	mExplosion->Update(deltaTime);
}

void Ship::Render()
{
	if (IsAlive() == true)
	{
		X::DrawSprite(mImageID, mPosition, mRotation);
		X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::DodgerBlue);
	}

	mExplosion->Render();
}

void Ship::Unload()
{
	mExplosion->Unload();
	delete mExplosion;
	mExplosion = nullptr;
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
	if (IsAlive() == true)
	{
		if (collidable->GetType() == ET_POWER_UP)
		{

		}

		int damage = 0;

		if (collidable->GetType() == ET_ENEMY)
		{
			damage = 10;
		}
		else
		{
			damage = 2;
		}

		mHealth -= damage;

		if (IsAlive() == false)
		{
			mExplosion->SetActive(mPosition);
			SetCollisionFilter(0);
		}
	}
}

void Ship::SetBulletPool(BulletPool* bulletPool)
{
	mBulletPool = bulletPool;
}

int Ship::GetHealth() const
{
	return mHealth;
}

int Ship::GetMaxHealth() const
{
	return mMaxHealth;
}

bool Ship::IsAlive() const
{
	return mHealth > 0;
}
