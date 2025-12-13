#include "ProjectilePool.h"
#include "Projectile.h"

ProjectilePool* ProjectilePool::mInstance = nullptr;

ProjectilePool::ProjectilePool()
    : Entity(),
    mNextAvailableIndex(0)
{
}

ProjectilePool::~ProjectilePool()
{
}

ProjectilePool* ProjectilePool::Get()
{
    if (mInstance == nullptr)
    {
        mInstance = new ProjectilePool();
    }

    return mInstance;
}

void ProjectilePool::Load()
{
    const int projectilePool = 50;

    for (int i = 0; i < projectilePool; ++i)
    {
        Projectile* projectile = new Projectile();
        projectile->Load();

        mProjectilesPool.push_back(projectile);
    }
}

void ProjectilePool::Update(float deltaTime)
{
    for (Projectile* projectiles : mProjectilesPool)
    {
        if (projectiles)
        {
            projectiles->Update(deltaTime);
        }
    }
}

void ProjectilePool::Render()
{
    for (Projectile* projectiles : mProjectilesPool)
    {
        if (projectiles)
        {
            projectiles->Render();
        }
    }
}

void ProjectilePool::Unload()
{
    for (Projectile* projectiles : mProjectilesPool)
    {
        if (projectiles)
        {
            projectiles->Unload();
            delete projectiles;
            projectiles = nullptr;
        }
    }

    mProjectilesPool.clear();
}

Projectile* ProjectilePool::GetProjectile()
{
    Projectile* projectile = mProjectilesPool[mNextAvailableIndex];
    if (projectile->IsActive())
    {
        Projectile* newProjectile = new Projectile();
        newProjectile->Load();

        mProjectilesPool.push_back(newProjectile);

        projectile = newProjectile;
    }

    mNextAvailableIndex = (mNextAvailableIndex + 1) % mProjectilesPool.size();

    return projectile;
}

std::vector<Projectile*>& ProjectilePool::GetProjectilesPool()
{
    return mProjectilesPool;
}