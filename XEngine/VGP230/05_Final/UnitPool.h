#pragma once
#include "Entity.h"
#include "Enum.h"

class Unit;
class Defender;
class Attacker;
class Infantry;
class Archer;
class ShieldInfantry;
class Farmer;
class Ram;

class UnitPool : public Entity
{
public:
    ~UnitPool() override;
    static UnitPool* Get();

    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Unload() override;

    std::vector<Unit*>& GetUnitsPool();

    Infantry* GetInfantry();
    Archer* GetArcher();
    ShieldInfantry* GetShieldInfantry();
    Farmer* GetFarmer();
    Ram* GetRam();

private:
    UnitPool();
    static UnitPool* mInstance;

    int mNextAvailableIndex;
    std::vector<Unit*> mUnitsPool;
    std::vector<Infantry*> mInfantryPool; // Would have preferred to use one pool but there was some logic stuff I couldnt figure out in reasonable time
    std::vector<Archer*> mArcherPool;
    std::vector<ShieldInfantry*> mShieldInfantryPool;
    std::vector<Farmer*> mFarmerPool;
    std::vector<Ram*> mRamPool;
};