#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::Load()
{
}

void Projectile::Update(float deltaTime)
{
}

void Projectile::Render()
{
}

void Projectile::Unload()
{
}

void SetActive(const X::Math::Vector2& pos, float rotation, float lifeTime = 0.5f)
{
    //XLOG("BULLET ACTIVE");
    //mPosition = pos;
    //mRotation = rotation;
    //mLifeTime = lifeTime;

    //float halfWidth = X::GetSpriteWidth(mImageID) * 0.25f;
    //float halfHeight = X::GetSpriteHeight(mImageID) * 0.25f;
    //X::Math::Rect newRect;
    //newRect.left = -halfWidth;
    //newRect.right = halfWidth;
    //newRect.top = -halfHeight;
    //newRect.bottom = halfHeight;
    //mBulletRect = newRect;

    //SetRect(newRect);
    //SetCollisionFilter(ET_ENEMY);
    //CollisionManager::Get()->AddCollidable(this);
}

bool Projectile::IsActive() const
{
    return true;
}
