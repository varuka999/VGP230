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
    mAttack(-1, mPosition);

    // Randomize attack interval
    mAttackInterval = (float)X::Random(5, 15) / 10.0f; // 0.5-1.5s
    mAttackTimer = mAttackInterval;
}

void Defender::SetAttackCallback(std::function<void(int, X::Math::Vector2)> callback)
{
    mAttack = callback;
}