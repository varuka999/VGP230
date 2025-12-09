#pragma once
#include "Entity.h"
#include "Unit.h"

class Attacker : public Unit
{
public:
    Attacker();
    ~Attacker();

    void Load() override;
    void Unload() override;
    void Attack() override;
};