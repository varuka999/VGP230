#include "Infantry.h"

void Infantry::Load()
{
    mImageID = X::LoadTexture("scv_01.png");
}

void Infantry::SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination)
{
    mPosition = position;
    SetDestination(destination);
    mHealth = 5;
    mAttack = 1;
    mMoveSpeed = 50.0f;
}