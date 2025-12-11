#include "ProjectilePool.h"

ProjectilePool::ProjectilePool()
    : Entity(),
    mNextAvailableIndex(0)
{
}

ProjectilePool::~ProjectilePool()
{
}

void ProjectilePool::Load()
{
}

void ProjectilePool::Update(float deltaTime)
{
}

void ProjectilePool::Render()
{
}

void ProjectilePool::Unload()
{
}

Projectile* ProjectilePool::GetProjectile()
{
    return nullptr;
}

std::vector<Projectile*>& ProjectilePool::GetProjectilesPool()
{
    return mProjectilesPool;
}