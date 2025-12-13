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
    //mZoneID = X::Math::Clamp(mTotalZones, 1, 5); // TEMP Clamp to 5 zones max for visual purposes
    std::string textureName = "zone";
    //textureName += std::to_string(mZoneID) + ".jpg";
    textureName += "1.jpg"; // TEMP DELETE LATER
    mImageID = X::LoadTexture(textureName.c_str());
}

void Zone::Update(float deltaTime)
{
    for (Unit* attacker : mAttackers)
    {
        attacker->Update(deltaTime);
    }
    for (Unit* defender : mDefenders)
    {
        defender->Update(deltaTime);
    }
}

void Zone::Render()
{
    X::DrawSprite(mImageID, mPosition);

    for (Unit* attacker : mAttackers)
    {
        attacker->Render();
    }
    for (Unit* defender : mDefenders)
    {
        defender->Render();
    }

    std::string text = std::string(std::to_string(mHealth));
    const float textSize = 45.0f;
    float textWidth = X::GetTextWidth(text.c_str(), textSize);
    float screenX = mPosition.x;
    float screenY = mPosition.y - 50.0f;
    X::DrawScreenText(text.c_str(), screenX, screenY, textSize, X::Colors::Orange);
}

void Zone::Unload()
{
    for (Unit* attacker : mAttackers)
    {
        if (attacker)
        {
            attacker->Unload();
            //delete attacker;
            //attacker = nullptr;
        }
    }

    mAttackersInRange.clear();
    mAttackers.clear();

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
    Attacker* targetAttacker = ReturnRandomAttackerInRange();

    if (targetAttacker != nullptr)
    {
        // spawn projectile
        // calculate destination based on attacker movespeed and its destination and the defenders(start) position ('predictive' aiming, not using collidables so the projectile must pretend to hit the target)
        // do ^ later, for now replaced with simple movement
        Projectile* projectile = ProjectilePool::Get()->GetProjectile();
        projectile->SetActive(startPosition, targetAttacker->GetPosition(), 0.0f, 1000.0f);
        targetAttacker->UpdateHealth(value); // Replace with actual projectile later
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
        }
    }
    break;
    case WALL_STATE_DESTROYED:
    {
        value *= 2; // Double damage to castle if wall is destroyed
    }
    break;
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
        //float rangeCenter = mPosition.x;
        float rangeStep = rangeX / (float)(value);
        //defenderPosition.x = X::RandomFloat(-rangeXOffset, rangeXOffset) + defenderPosition.x;
        defenderPosition.x += rangeStep * (float)(i + 0.5f) - rangeXOffset; // Temp to align defenders

        // Enemy Stats
        // Temp
        std::string enemyTexture = "interceptor_01.png";

        // Destination
        X::Math::Vector2 defenderDestination = defenderPosition;

        newDefender->SetActive(defenderPosition, defenderDestination); // change the values to some kind of database later
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
    newAttacker->Load();

    // Callbacks
    std::function<void(int)> attackCallback = std::bind(&Zone::UpdateHP, this, std::placeholders::_1);
    newAttacker->SetAttackZoneWallCallback(attackCallback);

    std::function<void(Attacker*)> inRangeCallback = std::bind(&Zone::AddAttackerInRange, this, std::placeholders::_1);
    newAttacker->SetInRangeCallBack(inRangeCallback);

    mAttackers.push_back(newAttacker);

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

    attackerDestination.y += 32.f; //Temp
    // Give the enemy the correct destination later. More tweaks and stuff.

    newAttacker->SetActive(attackerPosition, attackerDestination);
}

void Zone::SetActive(int castleHP)
{
    mHealth = castleHP / mTotalZones * 0.75f; // Total HP of all walls is less than total castle HP
    mAttackerSpawnTimer = 1.0f;

    mState = WALL_STATE_INTACT;

    X::Math::Vector2 zonePosition = X::Math::Vector2::Zero();
    float zoneXOffset = (float)X::GetScreenWidth() / (float)mTotalZones;
    float screenXOffset = zoneXOffset * 0.5f;

    zonePosition.x = zoneXOffset * mZoneID - screenXOffset;
    zonePosition.y = (float)X::GetScreenHeight() * 0.2f;
    mPosition = zonePosition;

    SpawnDefenders(5);
    //SpawnAttacker();
}

void Zone::SetAttackCastleCallback(std::function<void(int)> callback)
{
    mAttackCastleCallback = callback;
}