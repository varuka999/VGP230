#include "Projectile.h"

Projectile::Projectile()
    : Entity(),
    mImageID(0),
    mPosition(0.0f, 0.0f),
    mDestination(0.0f, 0.0f),
    mRotation(0.0f),
    mMoveSpeed(0.0f)
{
}

Projectile::~Projectile()
{
}

void Projectile::Load()
{
    mImageID = X::LoadTexture("bullet1.png");
}

void Projectile::Update(float deltaTime)
{
    if (IsActive())
    {
        X::Math::Vector2 direction = X::Math::Normalize(mDestination - mPosition);
        mPosition += direction * mMoveSpeed * deltaTime;
    }
}

void Projectile::Render()
{
    if (IsActive())
    {
        X::DrawSprite(mImageID, mPosition, mRotation);
    }
}

void Projectile::Unload()
{
}

void Projectile::SetActive(const X::Math::Vector2& position, const X::Math::Vector2 destination, float rotation, float speed)
{
    mPosition = position;
    mDestination = destination;
    mRotation = rotation;
    mMoveSpeed = speed;
}

bool Projectile::IsActive() const
{
    return X::Math::Distance(mDestination, mPosition) > 5.0f;
}
