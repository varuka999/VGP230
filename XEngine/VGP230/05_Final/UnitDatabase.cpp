#include "UnitDatabase.h"
#include "UnitPool.h"
#include "Infantry.h"
// #include "Archer.h"
// #include "Ram.h"

Attacker* UnitDatabase::ReturnAttackerUnit(UnitEnum unit)
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
    case INVALID:
        return nullptr;
    default:
        return nullptr;
    }

    return nullptr;
}