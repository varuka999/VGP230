#include "UnitPool.h"
#include "Infantry.h"
#include "Unit.h"
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
    const int infantryPool = 25;
    //mUnitsPool.reserve(poolSize);
    //mInfantryPool.reserve(poolSize);

    for (int i = 0; i < infantryPool; ++i)
    {
        Infantry* infantry = new Infantry();
        infantry->Load();

        mUnitsPool.push_back(infantry);
        mInfantryPool.push_back(infantry);
    }

    // Ranged Pool
}

void UnitPool::Update(float deltaTime)
{
    //for (Unit* u : mUnitsPool)
    //{
    //    if (u)
    //    {
    //        u->Update(deltaTime);
    //    }
    //}
}

void UnitPool::Render()
{
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
    mUnitsPool.clear();
    mNextAvailableIndex = 0;
}

Unit* UnitPool::GetUnit(UnitEnum type)
{
    //if (mUnitsPool.empty())
    //{
    //    return nullptr;
    //}

    //// Start search from next index for circular behavior
    //int size = (int)mUnitsPool.size();
    //int start = mNextAvailableIndex;
    //for (int i = 0; i < size; ++i)
    //{
    //    int idx = (start + i) % size;
    //    Unit* u = mUnitsPool[idx];
    //    if (!u)
    //        continue;

    //    // skip active units
    //    if (u->IsActive())
    //        continue;

    //    // match requested concrete type by dynamic_cast
    //    switch (type)
    //    {
    //    case INFANTRY:
    //        if (dynamic_cast<Infantry*>(u) != nullptr)
    //        {
    //            mNextAvailableIndex = (idx + 1) % size;
    //            return u;
    //        }
    //        break;
    //    case ARCHER:
    //        // add dynamic_cast<Archer*> check when Archer exists
    //        break;
    //    case RAM:
    //        // add dynamic_cast<Ram*> check when Ram exists
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

// Not exactly the intented pooling behavior, but should avoid running out of units
Infantry* UnitPool::GetInfantry()
{
    Infantry* infantry = mInfantryPool[mNextAvailableIndex];
    if (infantry->IsActive())
    {
        Infantry* newInfantry = new Infantry();
        newInfantry->Load();

        mUnitsPool.push_back(newInfantry);
        mInfantryPool.push_back(newInfantry);

        infantry = newInfantry;
    }

    mNextAvailableIndex = (mNextAvailableIndex + 1) % mInfantryPool.size();

    return infantry;
}