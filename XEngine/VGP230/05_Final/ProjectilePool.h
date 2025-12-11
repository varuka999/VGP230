#pragma once
#include "Entity.h"

class Projectile;

class ProjectilePool : public Entity
{
public:
	~ProjectilePool() override;
	static Projectile* Get();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	Projectile* GetProjectile();
	std::vector<Projectile*>& GetProjectilesPool();

private:
	ProjectilePool();
	static Projectile* mInstance;

	int mNextAvailableIndex;
	std::vector<Projectile*> mProjectilesPool;
};
