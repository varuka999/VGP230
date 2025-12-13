#include "Castle.h"
#include "Zone.h"
#include "Enum.h"

Castle* Castle::mInstance = nullptr;

Castle::Castle()
    : Entity(),
    mHealth(0),
    mTotalZones(0),
    mPrimedAttackerKey('n')
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
        zone->SetActive(mHealth);
    }
}

void Castle::Update(float deltaTime)
{
    if (X::IsKeyPressed(X::Keys::Q))
    {
        mPrimedAttackerKey = 'q';
    }
    else if (X::IsKeyPressed(X::Keys::W))
    {
        mPrimedAttackerKey = 'w';
    }
    else if (X::IsKeyPressed(X::Keys::E))
    {
        mPrimedAttackerKey = 'e';
    }
    else if (X::IsKeyPressed(X::Keys::P))
    {
        mPrimedAttackerKey = 'p';
    }

    if (X::IsKeyPressed(X::Keys::ONE))
    {
        mZones[0]->SpawnAttacker(GetPrimedAttackerType());
    }
    else if (X::IsKeyPressed(X::Keys::TWO))
    {

    }
    else if (X::IsKeyPressed(X::Keys::THREE))
    {

    }
    else if (X::IsKeyPressed(X::Keys::FOUR))
    {

    }
    else if (X::IsKeyPressed(X::Keys::FIVE))
    {

    }

    for (Zone* zone : mZones)
    {
        zone->Update(deltaTime);
    }
}

UnitEnum Castle::GetPrimedAttackerType() const
{
    switch (mPrimedAttackerKey)
    {
    case 'p':
        return TESTING;
    case 'q':
        return INFANTRY;
    case 'w':
        return ARCHER;
    case 'e':
        return RAM;
    default:
        return INVALID;
    }
}

void Castle::Render()
{
    for (Zone* zone : mZones)
    {
        zone->Render();
    }

    std::string text = std::string(std::to_string(mHealth));
    const float textSize = 45.0f;
    float textWidth = X::GetTextWidth(text.c_str(), textSize);
    float screenX = X::GetScreenWidth() * 0.5;
    float screenY = 25.0f;
    X::DrawScreenText(text.c_str(), screenX, screenY, textSize, X::Colors::Yellow);
    X::DrawScreenText(std::to_string(mPrimedAttackerKey).c_str(), screenX, screenY + 20, textSize, X::Colors::Yellow);
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