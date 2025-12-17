#include "ShieldInfantry.h"

void ShieldInfantry::Load()
{
    mImageID = X::LoadTexture("ShieldInfantry.png");
    mType = UnitEnum::SHIELD;
    mAttackMinInterval = 12.0f;
    mAttackMaxInterval = 15.0f;
}

void ShieldInfantry::SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination)
{
    Attacker::SetActive(position, destination);

    mHealth = 75;
    mAttack = 5;
    mMoveSpeed = 30.0f;
}