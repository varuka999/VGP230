#include "Ram.h"

void Ram::Load()
{
    mImageID = X::LoadTexture("scv_09.png");
    mType = UnitEnum::RAM;
    mAttackMinInterval = 30.0f;
    mAttackMaxInterval = 40.0f;
}

void Ram::SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination)
{
    Attacker::SetActive(position, destination);

    mHealth = 100;
    mAttack = 50;
    mMoveSpeed = 10.0f;
}