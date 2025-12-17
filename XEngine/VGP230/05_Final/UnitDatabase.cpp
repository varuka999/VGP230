#include "UnitDatabase.h"
#include "UnitPool.h"
#include "Infantry.h"
#include "Archer.h"
#include "ShieldInfantry.h"
#include "Farmer.h"
#include "Ram.h"

Attacker* UnitDatabase::ReturnAttackerUnit(UnitEnum unit)
{
    switch (unit)
    {
    case INFANTRY:
        return UnitPool::Get()->GetInfantry();
    case ARCHER:
        return UnitPool::Get()->GetArcher();
    case SHIELD:
        return UnitPool::Get()->GetShieldInfantry();
    case FARMER:
        return UnitPool::Get()->GetFarmer();
    case RAM:
        return UnitPool::Get()->GetRam();
    case INVALID:
        return nullptr;
    default:
        return nullptr;
    }

    return nullptr;
}