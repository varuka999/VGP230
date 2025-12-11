#include "Bullet.h"
#include "TileMap.h"
#include "CollisionManager.h"

Bullet::Bullet()
    : Entity(), Collidable(), mImageID(0), mPosition(0.0f), mBulletRect(0.0f, 0.0f, 0.0f, 0.0f),
    mRotation(0.0f), mLifeTime(0), mBulletType(ET_NONE), mRemoveCollider(false)
{

}

Bullet::~Bullet()
{

}

void Bullet::Load()
{
    XLOG("Loaded Bullet");
    mImageID = X::LoadTexture("bullet1.png");

    mRemoveCollider = false;
}

void Bullet::Update(float deltaTime)
{
    if (IsActive())
    {
        mLifeTime -= deltaTime;
        const float speed = 800.0f;
        mPosition += X::Math::Vector2::Forward(mRotation) * speed * deltaTime;

        X::Math::Vector2 direction = X::Math::Vector2::Zero();

        if (mRotation == 0)
        {
            direction.y = -1.0f;
        }
        else if (mRotation == X::Math::kPi)
        {
            direction.y = 1.0f;
        }
        else if (mRotation == (-X::Math::kPi) / 2)
        {
            direction.x = -1.0f;
        }
        else if (mRotation == X::Math::kPi / 2)
        {
            direction.x = 1.0f;
        }

        direction = X::Math::Normalize(direction);
        X::Math::Vector2 displacement = direction * speed * deltaTime;
        X::Math::Vector2 maxDisplacement = displacement;
        X::Math::Rect currentRect = mBulletRect;
        currentRect.min += mPosition;
        currentRect.max += mPosition;

        if (TileMap::Get()->HasCollision(currentRect, maxDisplacement, displacement))
        {
            mLifeTime = -1;
            return;
        }

        currentRect = mBulletRect;
        currentRect.min += mPosition;
        currentRect.max += mPosition;
        SetRect(currentRect);
    }
    else
    {
        if (mLifeTime < 0.0f)
        {
            mLifeTime = 0.0f;
            mRemoveCollider = true;
        }

        if (mRemoveCollider)
        {
            CollisionManager::Get()->RemoveCollidable(this);
            mRemoveCollider = false;
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
    XLOG("BULLET ACTIVE");
    mPosition = pos;
    mRotation = rotation;
    mLifeTime = lifeTime;

    float halfWidth = X::GetSpriteWidth(mImageID) * 0.25f;
    float halfHeight = X::GetSpriteHeight(mImageID) * 0.25f;
    X::Math::Rect newRect;
    newRect.left = -halfWidth;
    newRect.right = halfWidth;
    newRect.top = -halfHeight;
    newRect.bottom = halfHeight;
    mBulletRect = newRect;

    SetRect(newRect);
    SetCollisionFilter(ET_ENEMY);
    CollisionManager::Get()->AddCollidable(this);
}

bool Bullet::IsActive() const
{
    return mLifeTime > 0.0f;
}

int Bullet::GetType() const
{
    return IsActive() ? ET_BULLET_PLAYER : 0;
}

const X::Math::Vector2& Bullet::GetPosition() const
{
    return mPosition;
}

void Bullet::OnCollision(Collidable* collidable)
{
    if (IsActive())
    {
        XLOG("BULLET COLLIDED");

        mLifeTime = -1;
    }
}
