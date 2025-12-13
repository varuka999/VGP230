#include "UnitDatabase.h"
#include "UnitPool.h"
#include "Infantry.h"
// #include "Archer.h"
// #include "Ram.h"

Attacker* UnitDatabase::ReturnAttackerUnit(UnitEnum unit) // Consider changing to enum
{
    switch (unit)
    {
    case INFANTRY:
        return UnitPool::Get()->GetInfantry();
    case ARCHER:
        // return std::make_unique<Archer>();
        break;
    case RAM:
        // return std::make_unique<Ram>();
        break;
    case TESTING:
        return nullptr;
    default:
        return nullptr;
    }

    return nullptr;
}