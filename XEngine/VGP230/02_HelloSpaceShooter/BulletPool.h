#pragma once
#include "Entity.h"

class Bullet; // Forward declare for the Pointer

class BulletPool : public Entity
{
public:
	BulletPool();
	~BulletPool() override;

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	Bullet* GetBullet();
	std::vector<Bullet*>& GetBulletsPool();

private:
	int mNextAvailableIndex;
	std::vector<Bullet*> mBulletsPool;
};
