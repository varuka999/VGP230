#include "Bullet.h"
#include "AnimSpriteSheet.h"

Bullet::Bullet()
	: Entity(), Collidable(10.0f), mImageID(0), mPosition(0.0f), mRotation(0.0f), mLifeTime(0), mBulletType(ET_ALL)
{

}

Bullet::~Bullet()
{

}

void Bullet::Load()
{
	mImageID = X::LoadTexture("bullet1.png");
	XASSERT(mImageID != 0, "Bullet: Image did not load");
}

void Bullet::Update(float deltaTime)
{
	if (IsActive() == true)
	{
		mLifeTime -= deltaTime;
		const float speed = 700.0f;
		mPosition += X::Math::Vector2::Forward(mRotation) * speed * deltaTime;

		if (IsActive() == false)
		{
			SetCollisionFilter(ET_NONE);
		}
	}
}

void Bullet::Render()
{
	if (IsActive() == true)
	{
		X::DrawSprite(mImageID, mPosition, mRotation);
		X::DrawScreenCircle(mPosition, GetRadius(), X::Colors::HotPink);
	}
}

void Bullet::Unload()
{

}

void Bullet::SetActive(const X::Math::Vector2& pos, float rotation, float lifeTime)
{
	mPosition = pos;
	mRotation = rotation;
	mLifeTime = lifeTime;
}

void Bullet::SetEntityType(EntityType entityType)
{
	mBulletType = entityType;
}

bool Bullet::IsActive() const
{
	return mLifeTime > 0.0f;
}

int Bullet::GetType() const
{
	return mBulletType;
}

const X::Math::Vector2& Bullet::GetPosition() const
{
	return mPosition;
}

void Bullet::OnCollision(Collidable* collidable)
{
	mLifeTime = 0.0f;
	SetCollisionFilter(ET_NONE);
}
