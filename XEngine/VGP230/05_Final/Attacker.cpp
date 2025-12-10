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
    mImageID = X::LoadTexture("scv_09.png");
}

void Attacker::Unload()
{

}

void Attacker::Attack()
{
    mAttackZoneWall(-1);

    mAttackTimer = mAttackInterval;
}