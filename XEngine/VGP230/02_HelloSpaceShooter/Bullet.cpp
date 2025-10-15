#include "Bullet.h"

Bullet::Bullet()
	: Entity(), mImageID(0), mPosition(0.0f), mRotation(0.0f), mLifeTime(0)
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
	if (IsActive())
	{
		mLifeTime -= deltaTime;
		const float speed = 700.0f;
		mPosition += X::Math::Vector2::Forward(mRotation) * speed * deltaTime;
	}
}

void Bullet::Render()
{
	if (IsActive())
	{
		X::DrawSprite(mImageID, mPosition, mRotation);
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

bool Bullet::IsActive() const
{
	return mLifeTime > 0.0f;
}
