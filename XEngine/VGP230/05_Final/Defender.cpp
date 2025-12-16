#include "Defender.h"

Defender::Defender()
    : Unit()
{
}

Defender::~Defender()
{
}

void Defender::Load()
{
    mImageID = X::LoadTexture("Defender.png");
    mAttackMinInterval = 8.0f;
    mAttackMaxInterval = 15.0f;
}

void Defender::Unload()
{
}

void Defender::Attack()
{
    mAttackCallback(-mAttack, mPosition);

    mAttackInterval = X::RandomFloat(mAttackMinInterval, mAttackMaxInterval) / 10.0f;
    mAttackTimer = mAttackInterval;
}

void Defender::SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination)
{
    mPosition = position;
    SetDestination(destination);

    mHealth = 10;
    mAttack = 1;
    mMoveSpeed = 10.0f;
}

void Defender::SetAttackCallback(std::function<void(int, X::Math::Vector2)> callback)
{
    mAttackCallback = callback;
}