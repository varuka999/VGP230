#pragma once
#include "Entity.h"
#include "Enum.h"

class Unit;
class Defender;
class Attacker;
class Infantry;
//class Archer;
//class Ram;

class UnitPool : public Entity
{
public:
    ~UnitPool() override;
    static UnitPool* Get();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    // Acquire a Unit of the requested concrete type (returns nullptr if none available)
    Unit* GetUnit(UnitEnum type);

    // Access to internal pool if needed
    std::vector<Unit*>& GetUnitsPool();

    Infantry* GetInfantry();

private:
    UnitPool();
    static UnitPool* mInstance;

    int mNextAvailableIndex;
    std::vector<Unit*> mUnitsPool;
    std::vector<Infantry*> mInfantryPool;
};