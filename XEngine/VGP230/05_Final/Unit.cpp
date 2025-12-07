#include "Unit.h"

Unit::Unit()
    : Entity(),
    mImageID(0),
    mPosition(0.0f, 0.0f),
    mHealth(0),
    mAttack(0),
    mMoveSpeed(0),
    mAttackInterval(0),
    mAttackTimer(0)
{
}

Unit::~Unit()
{
}

void Unit::Load()
{
}

void Unit::Update(float deltaTime)
{
}

void Unit::Render()
{
}

void Unit::Unload()
{
}

void Unit::Action()
{
}

void Unit::Move()
{
}

void Unit::Attack()
{
}

void Unit::TakeDamage(int value)
{
}

void Unit::SetAttackCastleCallback(std::function<void(int)> callback)
{
    mAttackCastle = callback;
}

bool Unit::IsActive()
{
    return mHealth > 0;
}