#pragma once
#include "Attacker.h"
#include "Enum.h"

static class UnitDatabase
{
public:
    static Attacker* ReturnAttackerUnit(UnitEnum unit);
};