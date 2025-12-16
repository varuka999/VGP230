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
    mImageID = X::LoadTexture("interceptor_01.png");
}

void Defender::Unload()
{
}

void Defender::Attack()
{
    mAttackCallback(-mAttack, mPosition);

    mAttackInterval = (float)X::Random(5, 15) / 10.0f; // 0.5-1.5s
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