#include "Ship.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "AnimSpriteSheet.h"

Ship::Ship()
	: Entity(), Collidable(30.0f), mImageID(0), mPosition(0.0f), mRotation(0.0f), mScale(1.0f), mHealth(0), mMaxHealth(100), mDamage(10), mBulletPool(nullptr), mExplosion(nullptr), mIsPowerUp(false), mPowerUpTimer(5.0f)
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
		const float turnSpeed = X::Math::kPiByTwo * 1.5f;

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

	if (mIsPowerUp == true)
	{
		mPowerUpTimer -= deltaTime;

		if (mPowerUpTimer <= 0.0f)
		{
			mIsPowerUp = false;
			mPowerUpTimer = 5;
			mDamage = 10;
		}
	}

	mExplosion->Update(deltaTime);
}

void Ship::Render()
{
	if (IsAlive() == true)
	{
		std::string text = std::string("Attack: ") + std::to_string(mDamage);
		const float textSize = 30.0f;
		float textWidth = X::GetTextWidth(text.c_str(), textSize);
		float screenX = 20.0f;
		float screenY = 20.0f;

		if (mIsPowerUp == true)
		{
			mScale = 1.5f;
			const char* powerText = "Powered Up!";
			std::string powerTimerText = std::to_string(mPowerUpTimer);
			X::DrawScreenDiamond(mPosition, GetRadius() * (mScale + 0.2f), X::Colors::OrangeRed);
			X::DrawScreenText(powerText, X::GetScreenWidth() - 200, screenY, textSize, X::Colors::OrangeRed);
			X::DrawScreenText(powerTimerText.c_str(), X::GetScreenWidth() - 200, screenY * 3, textSize, X::Colors::OrangeRed);
		}
		else
		{
			mScale = 1.0f;
		}

		X::DrawSprite(mImageID, mPosition, mRotation, mScale);
		X::DrawScreenCircle(mPosition, GetRadius() * mScale, X::Colors::DodgerBlue);
		X::DrawScreenText(text.c_str(), screenX, screenY, textSize, X::Colors::Green);
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
			mIsPowerUp = true;
			mPowerUpTimer = 5;
			mDamage = 20;
		}
		else
		{
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
		}

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

int Ship::GetDamage() const
{
	return mDamage;
}

bool Ship::IsAlive() const
{
	return mHealth > 0;
}
