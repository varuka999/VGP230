#include "Projectile.h"

Projectile::Projectile()
    : Entity(),
    mImageID(0),
    mPosition(0.0f, 0.0f),
    mDestination(0.0f, 0.0f),
    mRotation(0.0f),
    mMoveSpeed(0.0f),
    mDamage(0),
    mActiveTarget(false),
    mHitEffect(nullptr)
{
}

Projectile::~Projectile()
{
}

void Projectile::Load()
{
    mImageID = X::LoadTexture("Arrow.png");
    mHitEffect = new AnimSpriteSheet();
    mHitEffect->Load();
}

void Projectile::Update(float deltaTime)
{
    if (IsActive())
    {
        X::Math::Vector2 direction = X::Math::Normalize(mDestination - mPosition);
        mPosition += direction * mMoveSpeed * deltaTime;
    }
    else if (mActiveTarget)
    {
        mActiveTarget = false;
        mHitCallback(mDamage);
        mHitEffect->SetActive(mPosition);
    }

    mHitEffect->Update(deltaTime);
}

void Projectile::Render()
{
    if (IsActive())
    {
        X::DrawSprite(mImageID, mPosition, mRotation);
    }

    mHitEffect->Render();
}

void Projectile::Unload()
{
    mHitEffect->Unload();
    delete mHitEffect;
    mHitEffect = nullptr;
}

void Projectile::SetHitCallback(std::function<void(int)> callback)
{
    mHitCallback = callback;
}

void Projectile::SetActive(std::string imageID, const X::Math::Vector2& position, const X::Math::Vector2 destination, float rotation, float speed, int damage)
{
    mImageID = X::LoadTexture(imageID.c_str());
    mActiveTarget = true;
    mPosition = position;
    mDestination = destination;
    mRotation = rotation;
    mMoveSpeed = speed;
    mDamage = damage;
}

bool Projectile::IsActive() const
{
    return X::Math::Distance(mDestination, mPosition) > 5.0f;
}
