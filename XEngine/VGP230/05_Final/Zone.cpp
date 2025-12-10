#include "Zone.h"
#include "Attacker.h"


int Zone::mTotalZones = 0;

Zone::Zone()
    : Entity(),
    mImageID(0),
    mPosition(0.0f, 0.0f),
    mState(WALL_STATE_INACTIVE),
    mZoneID(0),
    mHealth(0)
{
    ++mTotalZones;
}

Zone::~Zone()
{
}

void Zone::Load()
{
    mZoneID = mTotalZones;
    std::string textureName = "zone";
    textureName += std::to_string(mZoneID) + ".jpg";;
    mImageID = X::LoadTexture(textureName.c_str());
}

void Zone::Update(float deltaTime)
{
    for (Unit* attacker : mAttackers)
    {
        attacker->Update(deltaTime);
    }

    // Timer between attacker load/spawn
}

void Zone::Render()
{
    X::DrawSprite(mImageID, mPosition);

    for (Unit* attacker : mAttackers)
    {
        attacker->Render();
    }
    //for (Defender* defender : mDefenders)
    //{
    //    defender->Render();
    //}
}

void Zone::Unload()
{
}

void Zone::UpdateHP(int value)
{
    // For when states are implemented
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

    mAttackCastle(value);
}

void Zone::SpawnDefenders()
{
}

void Zone::SpawnAttackers()
{
    // Creation
    Attacker* newAttacker = new Attacker();
    newAttacker->Load();

    // Callbacks
    std::function<void(int)> attackCallback = std::bind(&Zone::UpdateHP, this, std::placeholders::_1);
    newAttacker->SetAttackZoneWallCallback(attackCallback);
    mAttackers.push_back(newAttacker);

    // Position
    float screenOffset = X::GetScreenHeight() - 50.0f;
    X::Math::Vector2 enemyPosition = mPosition;
    enemyPosition.y = screenOffset;

    // Enemy Stats
    // Based on something?
    std::string enemyTexture = "scv_09.png"; // Use Switch later or something??

    // Destination
    X::Math::Vector2 enemyDestination = mPosition;
    enemyDestination.y += 32.f; //Temp
    // Give the enemy the correct destination later. More tweaks and stuff.

    newAttacker->SetActive(enemyPosition, enemyDestination, enemyTexture, 5, 5, 100.0f); // change the values to some kind of database later
}

void Zone::SetActive(int castleHP)
{
    mHealth = castleHP / mTotalZones * 0.75f; // Total HP of all walls is less than total castle HP

    mState = WALL_STATE_INTACT;

    X::Math::Vector2 zonePosition = X::Math::Vector2::Zero();
    float zoneXOffset = (float)X::GetScreenWidth() / (float)mTotalZones;
    float screenXOffset = zoneXOffset * 0.5f;

    zonePosition.x = zoneXOffset * mZoneID - screenXOffset;
    zonePosition.y = (float)X::GetScreenHeight() * 0.2f;
    mPosition = zonePosition;

    SpawnDefenders();
    SpawnAttackers();
}

void Zone::SetAttackCastleCallback(std::function<void(int)> callback)
{
    mAttackCastle = callback;
}
