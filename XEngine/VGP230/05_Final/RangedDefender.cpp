#include "RangedDefender.h"

RangedDefender::RangedDefender()
    : Entity(), Unit()
{
}

RangedDefender::~RangedDefender()
{
}

void RangedDefender::Load()
{
}

void RangedDefender::Update(float deltaTime)
{
    
}

void RangedDefender::Render()
{
}

void RangedDefender::Unload()
{
}

void RangedDefender::TakeDamage(int value)
{
}

bool RangedDefender::IsActive()
{
    Unit::IsActive();
}
