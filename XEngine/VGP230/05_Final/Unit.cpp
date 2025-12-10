#include "Unit.h"

Unit::Unit()
    : Entity(),
    mImageID(0),
    mPosition(0.0f, 0.0f),
    mDestination(0.0f, 0.0f),
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
    mImageID = X::LoadTexture("scv_09.png");
}

void Unit::Update(float deltaTime)
{
    if (IsMoveAvailable()) // Implement States to make it so we dont need to check this every frame
    {
        Move(deltaTime);
    }
    else
    {
        if (mAttackTimer > 0.0f)
        {
            mAttackTimer -= deltaTime;
        }
        else
        {
            Attack();
        }
    }
}

void Unit::Render()
{
    if (IsActive())
    {
        X::DrawSprite(mImageID, mPosition);
    }
}

void Unit::Unload()
{
}

bool Unit::IsMoveAvailable() const
{
    return X::Math::Distance(mDestination, mPosition) > 1.0f;
}

void Unit::Move(float deltaTime)
{
    X::Math::Vector2 direction = X::Math::Normalize(mDestination - mPosition);
    mPosition += direction * mMoveSpeed * deltaTime;
}

void Unit::Attack()
{
    XLOG("Default Unit Attack: ERROR MISSING ATTACK");
}

void Unit::UpdateHealth(int value)
{
    mHealth += value;

    if (mHealth <= 0.0f)
    {
        mHealth = 0.0f;
    }
}

void Unit::SetAttackZoneWallCallback(std::function<void(int)> callback)
{
    mAttackZoneWall = callback;
}

void Unit::SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination, std::string image, int health, int attack, float moveSpeed)
{
    mPosition = position;
    mDestination = destination;
    mImageID = X::LoadTexture(image.c_str());
    mHealth = health;
    mAttack = attack;
    mMoveSpeed = moveSpeed;
    mAttackInterval = 1.0f;
    mAttackTimer = 0.0f;
}

bool Unit::IsActive() const
{
    return mHealth > 0.0f;
}