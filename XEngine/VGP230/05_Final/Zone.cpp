#include "Zone.h"
#include "Castle.h"
#include "Attacker.h"
#include "Enum.h"

int Zone::mTotalZones = 0;

Zone::Zone()
    : Entity(),
    mImageID(0),
    mPosition(0.0f, 0.0f),
    mZoneID(0)
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
    //Test
    //for (Unit* attacker : mAttackers)
    //{
    //    attacker->Attack();
    //}
}

void Zone::Render()
{
    X::DrawSprite(mImageID, mPosition);

    for (Attacker* attacker : mAttackers)
    {
        attacker->Render();
    }
    //for (Unit* defender : mDefenders)
    //{
    //    defender->Render();
    //}
}

void Zone::Unload()
{
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
    std::function<void(int)> attackCallback = std::bind(&Castle::UpdateHP, Castle::Get(), std::placeholders::_1);
    newAttacker->SetAttackCastleCallback(attackCallback);
    mAttackers.push_back(newAttacker);

    newAttacker->SetActive(mPosition.y - 500.0f, "white.jpg", 5);
}

void Zone::SetActive()
{
    X::Math::Vector2 zonePosition = X::Math::Vector2::Zero();
    float zoneOffset = (float)X::GetScreenWidth() / (float)mTotalZones;
    float screenOffset = zoneOffset * 0.5f;

    zonePosition.x = zoneOffset * mZoneID - screenOffset;
    zonePosition.y = 250;
    mPosition = zonePosition;

    SpawnAttackers();
}