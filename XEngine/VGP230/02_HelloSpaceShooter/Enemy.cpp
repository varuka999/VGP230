#include "Enemy.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "Ship.h"
#include "PowerUpPool.h";
#include "PowerUp.h"
#include "AnimSpriteSheet.h"
#include "AnimSpriteArray.h"

Enemy::Enemy()
	: Entity(), Collidable(30.0f), mBulletPool(nullptr), mPowerUpPool(nullptr), mShip(nullptr), mExplosion(nullptr), mImage(nullptr), mPowerUp(nullptr),
	mPosition(0.0f, 0.0f), mRotation(0.0f), mHealth(100), mCenterPoint(0.0f, 0.0f), mTargetPosition(0.0f, 0.0f), mTargetPositionUpdate(0.0f), mFireRate(0.0f), mDistanceFromTarget(0.0f)
{
}

Enemy::~Enemy()
{
}

void Enemy::Load()
{
	//mImageID = X::LoadTexture("carrier_01.png");
	mImage = new AnimSpriteArray();
	mImage->Load();

	std::vector<std::string> sprites;
	std::string textureName;
	int numSprites = 32;
	for (int i = 0; i < numSprites; ++i)
	{
		if (i < 9)
		{
			textureName = "carrier_0";
		}
		else
		{
			textureName = "carrier_";
		}

		textureName += std::to_string(i + 1) + ".png";
		sprites.push_back(textureName);

	}

	mImage->LoadSprites(sprites);
	XASSERT(mImage->GetFrameCount() > 0, "Enemy: Image did not load");
	mImage->SetFrameRate(0.0f);

	//XASSERT(mImageID > 0, "Enemy image did not loard");

	mPosition = X::Math::Vector2::Zero();
	mRotation = 0.0f;

	SetCollisionFilter(ET_BULLET_PLAYER | ET_SHIP);

	mExplosion = new AnimSpriteSheet();
	mExplosion->Load();

	mTargetPositionUpdate = 0.1f;
	mFireRate = 1.0f;
}

void Enemy::Update(float deltaTime)
{
	if (IsAlive() == true)
	{
		const float speed = 100.0f;
		const float rotationSpeed = X::Math::kPiByTwo;
		const float offsetDistance = 200.0f;

		mTargetPositionUpdate -= deltaTime;

		mDistanceFromTarget = X::Math::Abs((mShip->GetPosition().x + mShip->GetPosition().y) - (mPosition.x + mPosition.y));
		XLOG("Distance is: %f", mDistanceFromTarget);

		// Something here is not working :(
		// Ship is too far from enemy
		if (mDistanceFromTarget >= 500.0f)
		{
			mTargetPosition = mShip->GetPosition();
		}
		// Ship is too close to enemy
		else if (mDistanceFromTarget <= 300.0f)
		{
			X::Math::Vector2 newTarget = X::Math::Normalize(mPosition - mShip->GetPosition());
			mTargetPosition = mShip->GetPosition() + (newTarget * 350.0);
			//mTargetPositionUpdate = X::RandomFloat(0.5f, 1.0f);
		}
		else if (mTargetPositionUpdate <= 0.0f || X::Math::MagnitudeSqr(mTargetPosition - mPosition) <= 100.0f)
		{
			mCenterPoint = mPosition;
			mTargetPosition = mCenterPoint + (X::RandomUnitCircle() * offsetDistance);
			mTargetPositionUpdate = X::RandomFloat(0.5f, 1.0f);
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

			mImage->SetPosition(mPosition);
			mImage->Update(deltaTime);

			const X::Math::Vector2 fwd = X::Math::Vector2::Forward(mRotation);
			const float angle = atan2(-fwd.x, fwd.y) + X::Math::kPi;
			const float percent = angle / X::Math::kTwoPi;
			const float fframeCount = static_cast<float>(mImage->GetFrameCount());
			const int currentFrame = static_cast<int>(percent * fframeCount) % mImage->GetFrameCount();
			mImage->SetFrameIndex(currentFrame);
		}
	}

	mExplosion->Update(deltaTime);
}

void Enemy::Render()
{
	if (IsAlive() == true)
	{
		//X::DrawSprite(mImageID, mPosition, mRotation);
		mImage->Render();
		X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::DarkRed);

		//const float textSize = 50.0f;
		//const char* text = "DISTANCE";
		//float textWidth = X::GetTextWidth(text, textSize);
		//float screenX = (X::GetScreenWidth() - textWidth) * 0.5f;
		//float screenY = X::GetScreenHeight() * 0.1f;
		//X::DrawScreenText(text, screenX, screenY, textSize, X::Colors::Green);
	}

	mExplosion->Render();

	if (mPowerUp != nullptr)
	{
		mPowerUp->Render();
	}
}

void Enemy::Unload()
{
	mImage->Unload();
	delete mImage;
	mImage = nullptr;

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
			damage = mShip->GetDamage();
		}

		mHealth -= damage;

		if (IsAlive() == false)
		{
			SetCollisionFilter(0);
			mExplosion->SetActive(mPosition);

			if (mPowerUp != nullptr)
			{
				mPowerUp = nullptr;
			}

			mPowerUp = mPowerUpPool->GetPowerUp();

			if (mPowerUp != nullptr)
			{
				mPowerUp->SetActive(mPosition);
			}
		}
	}
}

void Enemy::SetBulletPool(BulletPool* bulletPool)
{
	mBulletPool = bulletPool;
}

void Enemy::SetPowerUpPool(PowerUpPool* powerUpPool)
{
	mPowerUpPool = powerUpPool;
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

