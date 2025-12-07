#include "Attacker.h"

Attacker::Attacker()
    : Unit()
{
}

Attacker::~Attacker()
{
}

void Attacker::Load()
{
}

void Attacker::Update(float deltaTime)
{
}

void Attacker::Render()
{
}

void Attacker::Unload()
{
}

void Attacker::Action()
{
}

void Attacker::Move()
{
}

void Attacker::Attack()
{
    XLOG("Attacked");
    mAttackCastle(-1);
}

void Attacker::TakeDamage(int value)
{
}

bool Attacker::IsActive()
{
    return false;
}
