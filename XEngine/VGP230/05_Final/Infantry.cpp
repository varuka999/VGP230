#include "Infantry.h"

void Infantry::Load()
{
    mImageID = X::LoadTexture("Infantry.png");
    mType = UnitEnum::INFANTRY;
    mAttackMinInterval = 7.0f;
    mAttackMaxInterval = 10.0f;
}

void Infantry::SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination)
{
    Attacker::SetActive(position, destination);

    mHealth = 5;
    mAttack = 2;
    mMoveSpeed = 50.0f;
}