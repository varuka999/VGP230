#include "UnitDatabase.h"
#include "Infantry.h"
// #include "Archer.h"
// #include "Ram.h"

Attacker* UnitDatabase::ReturnAttackerUnit(UnitEnum unit) // Consider changing to enum
{
    switch (unit)
    {
    case INFANTRY:
        return new Infantry();
    case ARCHER:
        // return std::make_unique<Archer>();
        break;
    case RAM:
        // return std::make_unique<Ram>();
        break;
    default:
        return nullptr;
    }

    return new Attacker(); // remove later i think
}