#include "Attacker.h"

Attacker::Attacker()
    : Unit(),
    mInAttackRange(false)
{
}

Attacker::~Attacker()
{
}

void Attacker::Update(float deltaTime)
{
    if (IsActive())
    {
        if (!mInAttackRange && ReturnDistanceToDestination() <= 300.0f) // really need to change this.. the 300 should be based on defender attack range, and not something attacker knows
        {
            mInAttackRange = true;
            mAttackRangeCallback(this);
        }

        Unit::Update(deltaTime);
    }
}

void Attacker::Load()
{
    mImageID = X::LoadTexture("scv_09.png");
}

void Attacker::Unload()
{

}

void Attacker::Attack()
{
    mAttackZoneWallCallback(-1);

    mAttackInterval = (float)X::Random(5, 10) / 10.0f; // 0.5-1.0s
    mAttackTimer = mAttackInterval;
}

float Attacker::ReturnDistanceToDestination() const
{
    return X::Math::Distance(mDestination, mPosition);
}

void Attacker::SetInRangeCallBack(std::function<void(Attacker*)> callback)
{
    mAttackRangeCallback = callback;
}