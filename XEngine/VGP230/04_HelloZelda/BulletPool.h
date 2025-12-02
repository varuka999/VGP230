#pragma once
#include "Entity.h"

class Bullet; // Forward declare for the Pointer

class BulletPool : public Entity
{
public:
	~BulletPool() override;
	static BulletPool* Get();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	Bullet* GetBullet();
	std::vector<Bullet*>& GetBulletsPool();

private:
	BulletPool();
	static BulletPool* mInstance;

	int mNextAvailableIndex;
	std::vector<Bullet*> mBulletsPool;
};
