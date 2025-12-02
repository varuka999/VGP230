#include "Bullet.h"
#include "CollisionManager.h"

Bullet::Bullet()
	: Entity(), Collidable(), mImageID(0), mPosition(0.0f), mRotation(0.0f), mLifeTime(0), mBulletType(ET_NONE), mRemoveCollider(false)
{

}

Bullet::~Bullet()
{

}

void Bullet::Load()
{
	mImageID = X::LoadTexture("bullet1.png");
	XASSERT(mImageID != 0, "Bullet: Image did not load");
	SetRect(mBulletRect);
	SetCollisionFilter(ET_BULLET_PLAYER);
	mRemoveCollider = false;
	CollisionManager::Get()->AddCollidable(this);
}

void Bullet::Update(float deltaTime)
{
	if (IsActive())
	{
		mLifeTime -= deltaTime;
		const float speed = 700.0f;
		mPosition += X::Math::Vector2::Forward(mRotation) * speed * deltaTime;

		if (!IsActive())
		{
			if (mRemoveCollider == true)
			{
				CollisionManager::Get()->RemoveCollidable(this);
				mRemoveCollider = false;
			}
		}
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

void Bullet::SetEntityType(EntityType entityType)
{
	mBulletType = entityType;

	if (entityType == ET_BULLET_PLAYER)
	{
		mImageID = X::LoadTexture("bullet1.png");
		SetCollisionFilter(ET_ENEMY);
	}
	else
	{
		SetCollisionFilter(0);
	}
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
	mRemoveCollider = true;
	SetCollisionFilter(ET_NONE);
}
