#include "Archer.h"
#include "ProjectilePool.h"
#include "Projectile.h"

Archer::Archer()
    : Attacker(),
    mAttackWindupInterval(0.0f),
    mAttackWindupTimer(0.0f),
    mState(UNIT_STATE_INACTIVE)
{
}

void Archer::Load()
{
    mImageID = X::LoadTexture("scv_16.png");
    mType = UnitEnum::ARCHER;
    mAttackMinInterval = 9.0f;
    mAttackMaxInterval = 13.0f;
    mAttackWindupInterval = 0.5f;
}

void Archer::Update(float deltaTime)
{
    if (IsActive())
    {
        if (!mInAttackRange && ReturnDistanceToDestination() <= 500.0f)
        {
            mInAttackRange = true;
            mAttackRangeCallback(this);
        }

        if (mAttackTimer > 0.0f)
        {
            mAttackTimer -= deltaTime;
            mState = UNIT_STATE_MOVING;
        }
        else if (mAttackTimer <= 0.0f && mAttackWindupTimer <= 0.0f && mState != UNIT_STATE_WINDUP && mState != UNIT_STATE_ATTACKING && X::Math::Distance(mDestination, mPosition) < 600.0f)
        {
            mAttackTimer = 0.0f;
            mAttackWindupTimer = mAttackWindupInterval;
            mState = UNIT_STATE_WINDUP;
        }

        switch (mState)
        {
        case UNIT_STATE_MOVING:
        {
            if (IsMoveAvailable())
            {
                Move(deltaTime);
            }
            break;
        }
        case UNIT_STATE_WINDUP:
        {
            mAttackWindupTimer -= deltaTime;

            if (mAttackWindupTimer <= 0.0f)
            {
                mAttackWindupTimer = 0.0f;
                mState = UNIT_STATE_ATTACKING;
            }
        }
        break;
        case UNIT_STATE_ATTACKING:
        {
            Attack();
        }
        break;
        default:
            break;
        }
    }
}

bool Archer::IsMoveAvailable() const
{
    return X::Math::Distance(mDestination, mPosition) > 100.0f;
}

void Archer::Attack()
{
    X::Math::Vector2 outIntercept;

    bool canHit = X::Math::ComputeInterceptPoint(mPosition, 1200.0f, mDestination, 0, outIntercept);
    float rotation = 0.0f;
    X::Math::Vector2 direction = outIntercept - mPosition;
    if (!X::Math::IsZero(direction)) // Avoid normalizing a zero vector
    {
        direction = X::Math::Normalize(direction);
        rotation = std::atan2(direction.y, direction.x) - X::Math::kPiByTwo;
    }

    Projectile* projectile = ProjectilePool::Get()->GetProjectile();
    projectile->SetHitCallback(mAttackZoneWallCallback);
    projectile->SetActive(mPosition, outIntercept, rotation, 1200.0f, -mAttack);

    mAttackInterval = (float)X::Random(mAttackMinInterval, mAttackMaxInterval) / 10.0f;
    mAttackTimer = mAttackInterval;
}

void Archer::SetActive(const X::Math::Vector2 position, const X::Math::Vector2 destination)
{
    Attacker::SetActive(position, destination);

    mAttackInterval = (float)X::Random(9, 13) / 10.0f; // 0.9-1.3s
    mAttackTimer = mAttackInterval;
    mAttackWindupTimer = 0.0f;
    mState = UNIT_STATE_MOVING;
    mHealth = 3;
    mAttack = 1;
    mMoveSpeed = 30.0f;
}