#include "PowerUp.h"

PowerUp::PowerUp()
	: Entity(), Collidable(20.0f), mImageID(0), mPosition(0.0f, 0.0f), mPowerUpType(ET_ALL), mIsActive(false)
{
}

PowerUp::~PowerUp()
{

}

void PowerUp::Load()
{
	mImageID = X::LoadTexture("mushroom.png");
	XASSERT(mImageID != 0, "PowerUp: Image did not load");
}

void PowerUp::Update(float deltaTime)
{

}

void PowerUp::Render()
{
	if (IsActive() == true)
	{
		X::DrawSprite(mImageID, mPosition);
		X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::Green);
	}
}

void PowerUp::Unload()
{

}

void PowerUp::SetActive(const X::Math::Vector2& pos)
{
	mPosition = pos;
	mIsActive = true;
	SetEntityType();
}

void PowerUp::SetEntityType()
{
	if (mPowerUpType != ET_POWER_UP)
	{
		mPowerUpType = ET_POWER_UP;
		SetCollisionFilter(mPowerUpType);
	}
}

bool PowerUp::IsActive() const
{
	return mIsActive;
}

int PowerUp::GetType() const
{
	return mPowerUpType;
}

const X::Math::Vector2& PowerUp::GetPosition() const
{
	return mPosition;
}

void PowerUp::OnCollision(Collidable* collidable)
{
	if (collidable->GetType() == ET_SHIP)
	{
		mIsActive = false;
		SetCollisionFilter(ET_NONE);
	}
}

