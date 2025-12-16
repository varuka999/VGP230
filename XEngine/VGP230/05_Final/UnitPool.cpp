#include "UnitPool.h"
#include "Unit.h"
#include "Infantry.h"
#include "Archer.h"
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
    const int infantryPool = 2;

    for (int i = 0; i < infantryPool; ++i)
    {
        Infantry* infantry = new Infantry();
        infantry->Load();

        mUnitsPool.push_back(infantry);
        mInfantryPool.push_back(infantry);
    }

    // Archer Pool
    const int archerPool = 2;

    for (int i = 0; i < archerPool; ++i)
    {
        Archer* archer = new Archer();
        archer->Load();

        mUnitsPool.push_back(archer);
        mArcherPool.push_back(archer);
    }
}

void UnitPool::Update(float deltaTime)
{
    for (Unit* u : mUnitsPool)
    {
        if (u)
        {
            u->Update(deltaTime);
        }
    }
}

void UnitPool::Render()
{
    for (Unit* u : mUnitsPool)
    {
        if (u)
        {
            u->Render();
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
    mUnitsPool.clear();
    mNextAvailableIndex = 0;
}

Unit* UnitPool::GetUnit(UnitEnum type)
{
    //if (mUnitsPool.empty())
    //{
    //    return nullptr;
    //}

    //int size = (int)mUnitsPool.size();
    //int start = mNextAvailableIndex;
    //for (int i = 0; i < size; ++i)
    //{
    //    int idx = (start + i) % size;
    //    Unit* unit = mUnitsPool[idx];
    //    if (!unit)
    //    {
    //        continue;
    //    }

    //    if (unit->IsActive())
    //    {
    //        continue;
    //    }

    //    switch (type)
    //    {
    //    case INFANTRY:
    //        if (dynamic_cast<Infantry*>(unit) != nullptr)
    //        {
    //            mNextAvailableIndex = (idx + 1) % size;
    //            return unit;
    //        }
    //        break;
    //    case ARCHER:
    //        break;
    //    case RAM:
    //        break;
    //    default:
    //        break;
    //    }
    //}

    return nullptr;
}

std::vector<Unit*>& UnitPool::GetUnitsPool()
{
    return mUnitsPool;
}

Infantry* UnitPool::GetInfantry()
{
    Infantry* infantry = mInfantryPool[mNextAvailableIndex];

    while (infantry->IsActive())
    {
        if (mNextAvailableIndex != mInfantryPool.size() - 1)
        {
            ++mNextAvailableIndex;
            infantry = mInfantryPool[mNextAvailableIndex];
            continue;
        }
        else
        {
            Infantry* newInfantry = new Infantry();
            newInfantry->Load();

            mUnitsPool.push_back(newInfantry);
            mInfantryPool.push_back(newInfantry);

            infantry = newInfantry;
            break;
        }
    }

    mNextAvailableIndex = 0;
    return infantry;
}

Archer* UnitPool::GetArcher()
{
    Archer* archer = mArcherPool[mNextAvailableIndex];

    while (archer->IsActive())
    {
        if (mNextAvailableIndex != mArcherPool.size() - 1)
        {
            ++mNextAvailableIndex;
            archer = mArcherPool[mNextAvailableIndex];
            continue;
        }
        else
        {
            Archer* newArcher = new Archer();
            newArcher->Load();

            mUnitsPool.push_back(newArcher);
            mArcherPool.push_back(newArcher);

            archer = newArcher;
            break;
        }
    }

    mNextAvailableIndex = 0;
    return archer;
}