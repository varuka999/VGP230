#include "Zone.h"
#include "Attacker.h"
#include "Defender.h"
#include "UnitDatabase.h"
#include "ProjectilePool.h"
#include "Projectile.h"

int Zone::mTotalZones = 0;

Zone::Zone()
    : Entity(),
    mImageID(0),
    mPosition(0.0f, 0.0f),
    mState(WALL_STATE_INACTIVE),
    mZoneID(0),
    mHealth(0),
    mAttackersInSpawnQueue(0),
    mAttackerSpawnTimer(0.0f),
    mSpawnAllAttackersInQueue(false)
{
    ++mTotalZones;
}

Zone::~Zone()
{
}

void Zone::Load()
{
    mZoneID = mTotalZones;
    mImageID = X::LoadTexture("WallIntact.png");
}

void Zone::Update(float deltaTime)
{
    for (Unit* defender : mDefenders)
    {
        defender->Update(deltaTime);
    }
}

void Zone::Render()
{
    X::DrawSprite(mImageID, mPosition);

    for (Unit* defender : mDefenders)
    {
        defender->Render();
    }

    // Health
    std::string text = std::string(std::to_string(mHealth));
    const float textSize = 30.0f;
    float textOffset = X::GetTextWidth(text.c_str(), textSize) * 0.5f;
    float screenX = mPosition.x - textOffset;
    float screenY = mPosition.y + 25.0f;
    X::DrawScreenText(text.c_str(), screenX, screenY, textSize, X::Colors::Orange);

    // Lane Selection
    std::string text2 = std::string(std::to_string(mZoneID));
    const float textSize2 = 20.0f;
    float textOffset2 = X::GetTextWidth(text2.c_str(), textSize2) * 0.5f;
    float screenX2 = mPosition.x - textOffset2;
    float screenY2 = mPosition.y + 85.0f;
    X::DrawScreenText(text2.c_str(), screenX2, screenY2, textSize2, X::Colors::OrangeRed);
}

void Zone::Unload()
{
    mAttackersInRange.clear();

    for (Unit* defender : mDefenders)
    {
        if (defender)
        {
            defender->Unload();
            delete defender;
            defender = nullptr;
        }
    }

    mDefenders.clear();
}

void Zone::AddAttackerInRange(Attacker* attacker)
{
    mAttackersInRange.push_back(attacker);
}

void Zone::DefenderAttack(int value, X::Math::Vector2 startPosition)
{
    Attacker* target = ReturnRandomAttackerInRange();

    if (target != nullptr)
    {
        // Calculate intercept point (not my own logic/function. it takes the address of variables and modifies it within the function)
        X::Math::Vector2 outIntercept;
        X::Math::Vector2 attackerVel = X::Math::Normalize(target->GetDestination() - target->GetPosition()) * target->GetMoveSpeed();
        bool canHit = X::Math::ComputeInterceptPoint(startPosition, 1200, target->GetPosition(), attackerVel, outIntercept); // unused bool because I'm assuming it will always hit for now
        float rotation = 0.0f;
        X::Math::Vector2 direction = outIntercept - startPosition;
        if (!X::Math::IsZero(direction)) // Avoid normalizing a zero vector
        {
            direction = X::Math::Normalize(direction);
            rotation = std::atan2(direction.y, direction.x) + X::Math::kPiByTwo;
        }

        Projectile* projectile = ProjectilePool::Get()->GetProjectile();

        std::function<void(int)> hitCallback = std::bind(&Attacker::UpdateHealth, target, std::placeholders::_1);
        projectile->SetHitCallback(hitCallback);

        projectile->SetActive("Arrow2.png", startPosition, outIntercept, rotation, 1200, value);
    }
}

Attacker* Zone::ReturnRandomAttackerInRange() const
{
    if (!mAttackersInRange.empty())
    {
        int randomIndex = X::Random(0, mAttackersInRange.size() - 1);
        return mAttackersInRange[randomIndex];
    }

    return nullptr;
}

void Zone::RemoveAttackerFromInRange(Attacker* attacker)
{
    auto it = std::find(mAttackersInRange.begin(), mAttackersInRange.end(), attacker);

    if (it != mAttackersInRange.end())
    {
        mAttackersInRange.erase(it);
    }
}

void Zone::UpdateHP(int value)
{
    switch (mState)
    {
    case WALL_STATE_INTACT:
    {
        mHealth += value;

        if (mHealth <= 0)
        {
            mHealth = 0;
            mState = WALL_STATE_DESTROYED;

            mImageID = X::LoadTexture("WallDestroyed.png");
            for (Unit* defender : mDefenders)
            {
                defender->UpdateHealth(-999);
            }
        }
    }
    break;
    case WALL_STATE_DESTROYED:
        return; // Wall destroyed, do nothing
    default:
        break;
    }

    mAttackCastleCallback(value);
}

void Zone::SpawnDefenders(int value)
{
    for (int i = 0; i < value; ++i)
    {
        //Creation
        Defender* newDefender = new Defender();
        newDefender->Load();

        // Callbacks
        std::function<void(int, X::Math::Vector2)> attackCallback = std::bind(&Zone::DefenderAttack, this, std::placeholders::_1, std::placeholders::_2);
        newDefender->SetAttackCallback(attackCallback);
        mDefenders.push_back(newDefender);

        // Position
        X::Math::Vector2 defenderPosition = mPosition;
        float rangeX = (float)X::GetScreenWidth() / (float)mTotalZones;
        float rangeXOffset = rangeX * 0.5f;
        float rangeStep = rangeX / (float)(value);
        defenderPosition.x += rangeStep * (float)(i + 0.5f) - rangeXOffset;
        defenderPosition.y -= 50.0f;

        // Destination
        X::Math::Vector2 defenderDestination = defenderPosition;

        newDefender->SetActive(defenderPosition, defenderDestination);
    }
}

void Zone::SpawnAttacker(UnitEnum unitType)
{
    Attacker* newAttacker = UnitDatabase::ReturnAttackerUnit(unitType);
    if (newAttacker == nullptr)
    {
        XLOG("Failed to spawn, invalid attacker");
        return;
    }
    mDeductResourceCallback(-unitType);
    newAttacker->Load();

    // Callbacks
    std::function<void(int)> attackCallback = std::bind(&Zone::UpdateHP, this, std::placeholders::_1);
    newAttacker->SetAttackZoneWallCallback(attackCallback);

    std::function<void(Attacker*)> inRangeCallback = std::bind(&Zone::AddAttackerInRange, this, std::placeholders::_1);
    newAttacker->SetInRangeCallBack(inRangeCallback);

    std::function<void(Attacker*)> outOfRangeCallback = std::bind(&Zone::RemoveAttackerFromInRange, this, std::placeholders::_1);
    newAttacker->SetOutOfRangeCallBack(outOfRangeCallback);

    // Position
    X::Math::Vector2 attackerPosition = mPosition;
    float rangeX = (float)X::GetScreenWidth() / (float)mTotalZones;
    float rangeXOffset = rangeX * 0.5f;
    attackerPosition.x = X::RandomFloat(-rangeXOffset, rangeXOffset) + attackerPosition.x;

    float screenOffset = X::GetScreenHeight() - 50.0f;
    attackerPosition.y = screenOffset;

    // Destination
    X::Math::Vector2 attackerDestination = mPosition;
    rangeX = (float)X::GetScreenWidth() / (float)mTotalZones;
    rangeXOffset = rangeX * 0.5f;
    attackerDestination.x = X::RandomFloat(-rangeXOffset, rangeXOffset) + attackerDestination.x;
    attackerDestination.y += 120.f;

    newAttacker->SetActive(attackerPosition, attackerDestination);
}

void Zone::SetActive(int castleHP)
{
    mHealth = castleHP / mTotalZones * 1.25f; // Total HP of all walls is more than total castle HP (Don't need to destroy every wall to win)
    mAttackerSpawnTimer = 1.0f;

    mState = WALL_STATE_INTACT;

    X::Math::Vector2 zonePosition = X::Math::Vector2::Zero();
    float zoneXOffset = (float)X::GetScreenWidth() / (float)mTotalZones;
    float screenXOffset = zoneXOffset * 0.5f;

    zonePosition.x = zoneXOffset * mZoneID - screenXOffset;
    zonePosition.y = (float)X::GetScreenHeight() * 0.2f;
    mPosition = zonePosition;

    SpawnDefenders(5);
}

void Zone::SetAttackCastleCallback(std::function<void(int)> callback)
{
    mAttackCastleCallback = callback;
}

void Zone::SetDeductResourceCallback(std::function<void(int)> callback)
{
    mDeductResourceCallback = callback;
}