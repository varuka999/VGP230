#include "Enemy.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "Ship.h"
#include "AnimSpriteSheet.h"

Enemy::Enemy()
	: Entity(), Collidable(30.0f), mBulletPool(nullptr), mShip(nullptr), mExplosion(nullptr), mImageID(0), mPosition(0.0f, 0.0f), mRotation(0.0f), 
	mHealth(100), mCenterPoint(0.0f, 0.0f), mTargetPosition(0.0f, 0.0f), mTargetPositionUpdate(0.0f), mFireRate(0.0f)
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

	mTargetPositionUpdate = 0.0f;
	mFireRate = 1.0f;
}

void Enemy::Update(float deltaTime)
{
	if (IsAlive() == true)
	{
		const float speed = 70.0f;
		const float rotationSpeed = X::Math::kPiByTwo;
		const float offsetDistance = 200.0f;

		mTargetPositionUpdate -= deltaTime;
		if (mTargetPositionUpdate <= 0.0f || X::Math::MagnitudeSqr(mTargetPosition - mPosition) <= 100.0f)
		{
			mTargetPosition = mCenterPoint + (X::RandomUnitCircle() * offsetDistance);
			mTargetPositionUpdate = X::RandomFloat(3.0f, 5.0f);
		}

		X::Math::Vector2 moveDirection = X::Math::Normalize(mTargetPosition - mPosition);
		mPosition += moveDirection * speed * deltaTime;

		if (mShip != nullptr && mShip->IsAlive() == true)
		{
			moveDirection = X::Math::Normalize(mShip->GetPosition() - mPosition);
			float targetRotation = atan2(moveDirection.x, -moveDirection.y);
			mRotation = targetRotation;

			mFireRate -= deltaTime;
			if (mFireRate <= 0.0f)
			{
				Bullet* bullet = mBulletPool->GetBullet(); 
				if (bullet != nullptr)
				{
					X::Math::Vector2 spawnPos = mPosition + X::Math::Vector2::Forward(mRotation) * 50.0f;
					bullet->SetEntityType(ET_BULLET_ENEMY);
					bullet->SetActive(spawnPos, mRotation, 3.0f);
					mFireRate = X::RandomFloat(3.0f, 5.0f);
				}
			}
		}
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
		else
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
	mCenterPoint = position;
	mTargetPosition = position;
	mTargetPositionUpdate = 0.0f;
}

void Enemy::SetRotation(float rotation)
{
	mRotation = rotation;
}

bool Enemy::IsAlive() const
{
	return mHealth > 0;
}

