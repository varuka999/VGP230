#include "Infantry.h"

void Infantry::Load()
{
    mImageID = X::LoadTexture("scv_01.png");
    mHealth = 5;
    mAttack = 1;
    mMoveSpeed = 50.0f;
}