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
    mImageID = X::LoadTexture("scv_03.png");
    mAttackInterval = 0.5f;
    mAttackTimer = 0.0f;
}

void Unit::Update(float deltaTime)
{
    if (IsActive())
    {
        if (IsMoveAvailable())
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
}

void Unit::Render()
{
    if (IsActive())
    {
        X::DrawSprite(mImageID, mPosition);

        std::string text = std::string(std::to_string(mHealth));
        const float textSize = 25.0f;
        float textWidth = X::GetTextWidth(text.c_str(), textSize);
        float screenX = mPosition.x - 8.0f;
        float screenY = mPosition.y - 40.0f;
        X::DrawScreenText(text.c_str(), screenX, screenY, textSize, X::Colors::Red);
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
    mAttackZoneWallCallback = callback;
}

void Unit::SetDestination(const X::Math::Vector2 destination)
{
    mDestination = destination;
}

void Unit::SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination)
{
    mPosition = position;
    SetDestination(destination);
    mHealth = 5;
    mAttack = 5;
    mMoveSpeed = 300.0f;
}

bool Unit::IsActive() const
{
    return mHealth > 0.0f;
}

float Unit::GetMoveSpeed() const
{
    return mMoveSpeed;
}

X::Math::Vector2 Unit::GetPosition() const
{
    return mPosition;
}

X::Math::Vector2 Unit::GetDestination() const
{
    return mDestination;
}