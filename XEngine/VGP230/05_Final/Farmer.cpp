#include "Farmer.h"

void Farmer::Load()
{
    mImageID = X::LoadTexture("scv_12.png");
    mType = UnitEnum::FARMER;
    mAttackMinInterval = 8.0f;
    mAttackMaxInterval = 10.0f;
}

void Farmer::Update(float deltaTime)
{
    if (IsActive())
    {
        if (mGatherTimer < 1.0f)
        {
            mGatherTimer += deltaTime;
        }
        else
        {
            mResourceCallback(1);
            mGatherTimer = 0.0f;
        }
    }

    Attacker::Update(deltaTime);
}

void Farmer::SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination)
{
    Attacker::SetActive(position, destination);

    mHealth = 1;
    mAttack = 1;
    mMoveSpeed = 65.0f;
}

void Farmer::SetResourceCallback(std::function<void(int)> callback)
{
    mResourceCallback = callback;
}