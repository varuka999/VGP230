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
    mAttackCastle(-1);

    mAttackTimer = mAttackInterval;
}