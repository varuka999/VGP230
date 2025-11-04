#include "Enemy.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "Ship.h"
#include "AnimSpriteSheet.h"

Enemy::Enemy()
	: Entity(), Collidable(30.0f), mBulletPool(nullptr), mShip(nullptr), mExplosion(nullptr), mImageID(0), mPosition(0.0f, 0.0f), mRotation(0.0f), mHealth(100)
{
}

Enemy::~Enemy()
{
}

void Enemy::Load()
{
	mImageID = X::LoadTexture("carrier_01.png");
	XASSERT(mImageID > 0, "Enemy image did not loard");

	mPosition = X::Math::Vector2::Zero();
	mRotation = 0.0f;

	SetCollisionFilter(ET_BULLET_PLAYER | ET_SHIP);

	mExplosion = new AnimSpriteSheet();
	mExplosion->Load();
}

void Enemy::Update(float deltaTime)
{
	if (IsAlive() == true)
	{

	}
	mExplosion->Update(deltaTime);
}

void Enemy::Render()
{
	if (IsAlive() == true)
	{
		X::DrawSprite(mImageID, mPosition, mRotation);
		X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::DarkRed);
	}
	mExplosion->Render();
}

void Enemy::Unload()
{
	mExplosion->Unload();
	delete mExplosion;
	mExplosion = nullptr;
}

int Enemy::GetType() const
{
	return ET_ENEMY;
}

const X::Math::Vector2& Enemy::GetPosition() const
{
	return mPosition;
}

void Enemy::OnCollision(Collidable* collidable)
{
	if (IsAlive() == true)
	{
		int damage = 0;

		if (collidable->GetType() == ET_SHIP)
		{
			damage = mHealth;
		}
		else // collidable->GetType() == ET_BULLET_PLAYER doesnt work because bullet type is all, no way to distinguish enemy/player bullet yet
		{
			damage = 10;
		}

		mHealth -= damage;

		if (IsAlive() == false)
		{
			SetCollisionFilter(0);
			mExplosion->SetActive(mPosition);
		}
	}
}

void Enemy::SetBulletPool(BulletPool* bulletPool)
{
	mBulletPool = bulletPool;
}

void Enemy::SetShip(Ship* ship)
{
	mShip = ship;
}

void Enemy::SetPosition(const X::Math::Vector2& position)
{
	mPosition = position;
}

void Enemy::SetRotation(float rotation)
{
	mRotation = rotation;
}

bool Enemy::IsAlive() const
{
	return mHealth > 0;
}

