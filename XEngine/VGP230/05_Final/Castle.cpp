#include "Castle.h"
#include "Zone.h"

Castle* Castle::mInstance = nullptr;

Castle::Castle()
    : Entity(),
    mHealth(0),
    mTotalZones(0)
{

}

Castle::~Castle()
{
}

Castle* Castle::Get()
{
    if (mInstance == nullptr)
    {
        mInstance = new Castle();
    }

    return mInstance;
}

void Castle::Load()
{
    mHealth = 1000;
    mTotalZones = 5;

    for (int i = 0; i < mTotalZones; ++i)
    {
        Zone* newZone = new Zone();
        newZone->Load();

        // Callback
        std::function<void(int)> attackCallback = std::bind(&Castle::UpdateHP, this, std::placeholders::_1);
        newZone->SetAttackCastleCallback(attackCallback);
        mZones.push_back(newZone);
    }

    for (Zone* zone : mZones)
    {
        zone->SetActive();
    }
}

void Castle::Update(float deltaTime)
{
    for (Zone* zone : mZones)
    {
        zone->Update(deltaTime);
    }
}

void Castle::Render()
{
    for (Zone* zone : mZones)
    {
        zone->Render();
    }
}

void Castle::Unload()
{
}

void Castle::UpdateHP(int value)
{
    mHealth += value;

    if (mHealth <= 0)
    {
        mHealth = 0;
        // Zone destroyed logic
    }

    XLOG("Castle HP: %i", mHealth);
}