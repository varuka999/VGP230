#include "UnitPool.h"
#include "Unit.h"
#include "Castle.h"
#include "Infantry.h"
#include "Archer.h"
#include "ShieldInfantry.h"
#include "Farmer.h"
#include "Ram.h"
#include <XEngine.h>
#include <algorithm>
#include <typeinfo>

UnitPool* UnitPool::mInstance = nullptr;

UnitPool::UnitPool()
    : mNextAvailableIndex(0)
{
}

UnitPool::~UnitPool()
{
    XASSERT(mUnitsPool.empty(), "UnitPool: Unload must be called");
}

UnitPool* UnitPool::Get()
{
    if (mInstance == nullptr)
    {
        mInstance = new UnitPool();
    }

    return mInstance;
}

void UnitPool::Load()
{
    // Infantry Pool
    const int infantryPool = 10;

    for (int i = 0; i < infantryPool; ++i)
    {
        Infantry* infantry = new Infantry();
        infantry->Load();

        mUnitsPool.push_back(infantry);
        mInfantryPool.push_back(infantry);
    }

    // Archer Pool
    const int archerPool = 5;

    for (int i = 0; i < archerPool; ++i)
    {
        Archer* archer = new Archer();
        archer->Load();

        mUnitsPool.push_back(archer);
        mArcherPool.push_back(archer);
    }

    // Shield Infantry Pool
    const int shieldInfantryPool = 5;

    for (int i = 0; i < shieldInfantryPool; ++i)
    {
        ShieldInfantry* shieldInfantry = new ShieldInfantry();
        shieldInfantry->Load();

        mUnitsPool.push_back(shieldInfantry);
        mShieldInfantryPool.push_back(shieldInfantry);
    }

    // Farm Pool
    const int farmerPool = 5;

    for (int i = 0; i < farmerPool; ++i)
    {
        Farmer* farmer = new Farmer();
        farmer->Load();
        std::function<void(int)> resourceCallback = std::bind(&Castle::UpdateAttackerResource, Castle::Get(), std::placeholders::_1);
        farmer->SetResourceCallback(resourceCallback);

        mUnitsPool.push_back(farmer);
        mFarmerPool.push_back(farmer);
    }

    // Ram Pool
    const int ramPool = 2;

    for (int i = 0; i < ramPool; ++i)
    {
        Ram* ram = new Ram();
        ram->Load();

        mUnitsPool.push_back(ram);
        mRamPool.push_back(ram);
    }
}

void UnitPool::Update(float deltaTime)
{
    for (Unit* units : mUnitsPool)
    {
        if (units)
        {
            units->Update(deltaTime);
        }
    }
}

void UnitPool::Render()
{
    for (Unit* units : mUnitsPool)
    {
        if (units)
        {
            units->Render();
        }
    }
}

void UnitPool::Unload()
{
    for (Unit* unit : mUnitsPool)
    {
        if (unit)
        {
            unit->Unload();
            delete unit;
            unit = nullptr;
        }
    }

    mInfantryPool.clear();
    mArcherPool.clear();
    mShieldInfantryPool.clear();
    mFarmerPool.clear();
    mRamPool.clear();
    mUnitsPool.clear();
    mNextAvailableIndex = 0;
}

std::vector<Unit*>& UnitPool::GetUnitsPool()
{
    return mUnitsPool;
}

Infantry* UnitPool::GetInfantry()
{
    Infantry* unit = mInfantryPool[mNextAvailableIndex];

    while (unit->IsActive())
    {
        if (mNextAvailableIndex != mInfantryPool.size() - 1)
        {
            ++mNextAvailableIndex;
            unit = mInfantryPool[mNextAvailableIndex];
            continue;
        }
        else
        {
            Infantry* newUnit = new Infantry();
            newUnit->Load();

            mUnitsPool.push_back(newUnit);
            mInfantryPool.push_back(newUnit);

            unit = newUnit;
            break;
        }
    }

    mNextAvailableIndex = 0;
    return unit;
}

Archer* UnitPool::GetArcher()
{
    Archer* unit = mArcherPool[mNextAvailableIndex];

    while (unit->IsActive())
    {
        if (mNextAvailableIndex != mArcherPool.size() - 1)
        {
            ++mNextAvailableIndex;
            unit = mArcherPool[mNextAvailableIndex];
            continue;
        }
        else
        {
            Archer* newUnit = new Archer();
            newUnit->Load();

            mUnitsPool.push_back(newUnit);
            mArcherPool.push_back(newUnit);

            unit = newUnit;
            break;
        }
    }

    mNextAvailableIndex = 0;
    return unit;
}

ShieldInfantry* UnitPool::GetShieldInfantry()
{
    ShieldInfantry* unit = mShieldInfantryPool[mNextAvailableIndex];

    while (unit->IsActive())
    {
        if (mNextAvailableIndex != mShieldInfantryPool.size() - 1)
        {
            ++mNextAvailableIndex;
            unit = mShieldInfantryPool[mNextAvailableIndex];
            continue;
        }
        else
        {
            ShieldInfantry* newUnit = new ShieldInfantry();
            newUnit->Load();

            mUnitsPool.push_back(newUnit);
            mShieldInfantryPool.push_back(newUnit);

            unit = newUnit;
            break;
        }
    }

    mNextAvailableIndex = 0;
    return unit;
}

Farmer* UnitPool::GetFarmer()
{
    Farmer* unit = mFarmerPool[mNextAvailableIndex];

    while (unit->IsActive())
    {
        if (mNextAvailableIndex != mFarmerPool.size() - 1)
        {
            ++mNextAvailableIndex;
            unit = mFarmerPool[mNextAvailableIndex];
            continue;
        }
        else
        {
            Farmer* newUnit = new Farmer();
            newUnit->Load();
            std::function<void(int)> resourceCallback = std::bind(&Castle::UpdateAttackerResource, Castle::Get(), std::placeholders::_1);
            newUnit->SetResourceCallback(resourceCallback);

            mUnitsPool.push_back(newUnit);
            mFarmerPool.push_back(newUnit);

            unit = newUnit;
            break;
        }
    }

    mNextAvailableIndex = 0;
    return unit;
}

Ram* UnitPool::GetRam()
{
    Ram* unit = mRamPool[mNextAvailableIndex];

    while (unit->IsActive())
    {
        if (mNextAvailableIndex != mRamPool.size() - 1)
        {
            ++mNextAvailableIndex;
            unit = mRamPool[mNextAvailableIndex];
            continue;
        }
        else
        {
            Ram* newUnit = new Ram();
            newUnit->Load();

            mUnitsPool.push_back(newUnit);
            mRamPool.push_back(newUnit);

            unit = newUnit;
            break;
        }
    }

    mNextAvailableIndex = 0;
    return unit;
}