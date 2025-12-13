#pragma once
#include "Entity.h"

class Projectile;

class ProjectilePool : public Entity
{
public:
	~ProjectilePool() override;
	static ProjectilePool* Get();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	Projectile* GetProjectile();
	std::vector<Projectile*>& GetProjectilesPool();

private:
	ProjectilePool();
	static ProjectilePool* mInstance;

	int mNextAvailableIndex;
	std::vector<Projectile*> mProjectilesPool;
};
