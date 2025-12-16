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
        if (!mInAttackRange && ReturnDistanceToDestination() <= 500.0f) // would love to change this to something defender does
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

void Attacker::SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination)
{
    mInAttackRange = false;
    mPosition = position;
    SetDestination(destination);
}

void Attacker::Attack()
{
    mAttackZoneWallCallback(-mAttack);

    mAttackInterval = (float)X::Random(7, 10) / 10.0f; // 0.7-1.0s
    mAttackTimer = mAttackInterval;
}

void Attacker::UpdateHealth(int value)
{
    mHealth += value;

    if (mHealth <= 0.0f)
    {
        mHealth = 0.0f;
        mOutOfRangeCallback(this);
        Reset();
    }
}

float Attacker::ReturnDistanceToDestination() const
{
    return X::Math::Distance(mDestination, mPosition);
}

void Attacker::SetInRangeCallBack(std::function<void(Attacker*)> callback)
{
    mAttackRangeCallback = callback;
}

void Attacker::SetOutOfRangeCallBack(std::function<void(Attacker*)> callback)
{
    mOutOfRangeCallback = callback;
}
