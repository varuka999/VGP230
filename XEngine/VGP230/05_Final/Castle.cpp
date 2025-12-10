#include "Castle.h"
#include "Zone.h"

Castle* Castle::mInstance = nullptr;

Castle::Castle()
    : Entity(),
    mHealth(0),
    mTotalZones(5)
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

    for (int i = 0; i < mTotalZones; ++i)
    {
        Zone* newZone = new Zone();
        newZone->Load();
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
    XLOG("Castle HP: %i", mHealth);
}
