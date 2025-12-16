#include "Castle.h"
#include "Zone.h"

Castle* Castle::mInstance = nullptr;

Castle::Castle()
    : Entity(),
    mHealth(0),
    mTotalZones(0),
    mPrimedAttackerKey('n'),
    mAttackerResource(0),
    mAttackerResourceCooldown(0.0f),
    mAttackerResourceTimer(0.0f)
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
        std::function<void(int)> deductResourceCallback = std::bind(&Castle::UpdateAttackerResource, this, std::placeholders::_1);
        newZone->SetDeductResourceCallback(deductResourceCallback);
        mZones.push_back(newZone);
    }

    mAttackerResource = 5;
    mAttackerResourceCooldown = 0.5f;
    mAttackerResourceTimer = 0.0f;

    for (Zone* zone : mZones)
    {
        zone->SetActive(mHealth);
    }
}

void Castle::Update(float deltaTime)
{
    mAttackerResourceTimer += deltaTime;

    if (mAttackerResourceTimer >= mAttackerResourceCooldown)
    {
        ++mAttackerResource;
        mAttackerResourceTimer = 0.0f;
    }

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
    else if (X::IsKeyPressed(X::Keys::P)) // Test unit
    {
        mPrimedAttackerKey = 'p';
    }

    if (X::IsKeyPressed(X::Keys::ONE))
    {
        mZones[0]->SpawnAttacker(GetPrimedAttackerType());
    }
    else if (X::IsKeyPressed(X::Keys::TWO))
    {
        mZones[1]->SpawnAttacker(GetPrimedAttackerType());
    }
    else if (X::IsKeyPressed(X::Keys::THREE))
    {
        mZones[2]->SpawnAttacker(GetPrimedAttackerType());
    }
    else if (X::IsKeyPressed(X::Keys::FOUR))
    {
        mZones[3]->SpawnAttacker(GetPrimedAttackerType());
    }
    else if (X::IsKeyPressed(X::Keys::FIVE))
    {
        mZones[4]->SpawnAttacker(GetPrimedAttackerType());
    }

    for (Zone* zone : mZones)
    {
        zone->Update(deltaTime);
    }
}

UnitEnum Castle::GetPrimedAttackerType()
{
    switch (mPrimedAttackerKey)
    {
    case 'q':
        if (HasEnoughResourceForAttacker(INFANTRY)) // current resource - unit resource >= 0, return key, otherwise return default non-spawning key
        {
            return INFANTRY;
        }
        else
        {
            return INVALID;
        }
    case 'w':
        if (HasEnoughResourceForAttacker(ARCHER))
        {
            return ARCHER;
        }
        else
        {
            return INVALID;
        }
    case 'e':
        if (HasEnoughResourceForAttacker(RAM))
        {
            return RAM;
        }
        else
        {
            return INVALID;
        }
    default:
        return INVALID;
    }
}

bool Castle::HasEnoughResourceForAttacker(UnitEnum unitType) const
{
    return mAttackerResource - unitType >= 0;
}

void Castle::Render()
{
    for (Zone* zone : mZones)
    {
        zone->Render();
    }

    CastleUI();
}

void Castle::CastleUI()
{
    // HP
    std::string healthText = std::string(std::to_string(mHealth));
    const float textSize = 45.0f;
    float textWidth = X::GetTextWidth(healthText.c_str(), textSize);
    float screenX = X::GetScreenWidth() * 0.5;
    float screenY = 25.0f;
    X::DrawScreenText(healthText.c_str(), screenX, screenY, textSize, X::Colors::Yellow);
    X::DrawScreenText(std::to_string(mPrimedAttackerKey).c_str(), screenX, screenY + 40, textSize, X::Colors::Yellow);

    // Resource
    std::string resourceText = "Resource: " + std::to_string(mAttackerResource);
    const float textSize2 = 25.0f;
    float resourceTextWidth = X::GetTextWidth(resourceText.c_str(), textSize);
    float resourceScreenX = 50.0f;
    float resourceScreenY = X::GetScreenHeight() * 0.9f;
    X::DrawScreenText(resourceText.c_str(), resourceScreenX, resourceScreenY, textSize2, X::Colors::OrangeRed);

    // Attacker Types
    std::string attackerTypeText = "Q:Infantry (" + std::to_string(INFANTRY) +
        ")      W: Archer (" + std::to_string(ARCHER) +
        ")      E: Shield Infantry (" + std::to_string(SHIELD) +
        ")      R: Farmer (" + std::to_string(FARMER) +
        ")      T: Ram (" + std::to_string(RAM) + ")";
    const float textSize3 = 20.0f;
    float attackerTypeTextWidth = X::GetTextWidth(attackerTypeText.c_str(), textSize3);
    float attackerScreenX = 50.0f;
    float attackerScreenY = X::GetScreenHeight() * 0.95f;
    X::DrawScreenText(attackerTypeText.c_str(), attackerScreenX, attackerScreenY, textSize3, X::Colors::OrangeRed);
}

void Castle::Unload()
{
    for (Zone* zone : mZones)
    {
        zone->Unload();
        delete zone;
        zone = nullptr;
    }

    mZones.clear();
}

void Castle::UpdateHP(int value)
{
    mHealth += value;

    if (mHealth <= 0)
    {
        mHealth = 0;
        // Castle destroyed logic
    }

    XLOG("Castle HP: %i", mHealth);
}

void Castle::UpdateAttackerResource(int value)
{
    mAttackerResource = X::Math::Max(0, mAttackerResource + value);
}
