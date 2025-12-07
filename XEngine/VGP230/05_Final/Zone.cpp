#include "Zone.h"
#include "Castle.h"
#include "Attacker.h"

Zone::Zone()
    : Entity()
{
}

Zone::~Zone()
{
}

void Zone::Load()
{
    SpawnAttackers();
}

void Zone::Update(float deltaTime)
{
    //Test
    for (Unit* attacker : mAttackers)
    {
        attacker->Attack();
    }
}

void Zone::Render()
{
}

void Zone::Unload()
{
}

void Zone::SpawnDefenders()
{
}

void Zone::SpawnAttackers()
{
    Attacker* newAttacker = new Attacker();
    std::function<void(int)> attackCallback = std::bind(&Castle::UpdateHP, Castle::Get(), std::placeholders::_1);
    newAttacker->SetAttackCastleCallback(attackCallback);
    mAttackers.push_back(newAttacker);
}