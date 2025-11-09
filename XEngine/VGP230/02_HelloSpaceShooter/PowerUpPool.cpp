#include "PowerUpPool.h"
#include "PowerUp.h"

PowerUpPool::PowerUpPool()
	: Entity(), mNextAvailableIndex(0)
{
}

PowerUpPool::~PowerUpPool()
{
	XASSERT(mPowerUpPool.empty(), "BulletPool: Unload must be called");
}

void PowerUpPool::Load()
{
	const int maxBullets = 50;
	for (int i = 0; i < maxBullets; ++i)
	{
		PowerUp* newPowerUp = new PowerUp();
		newPowerUp->Load();
		mPowerUpPool.push_back(newPowerUp);
	}
}

void PowerUpPool::Update(float deltaTime)
{
	for (int i = 0; i < mPowerUpPool.size(); i++)
	{
		mPowerUpPool[i]->Update(deltaTime);
	}
}

void PowerUpPool::Render()
{
	for (int i = 0; i < mPowerUpPool.size(); i++)
	{
		mPowerUpPool[i]->Render();
	}
}

void PowerUpPool::Unload()
{
	for (int i = 0; i < mPowerUpPool.size(); i++)
	{
		mPowerUpPool[i]->Unload();
		delete mPowerUpPool[i];
		mPowerUpPool[i] = nullptr;
	}

	mPowerUpPool.clear();
}

PowerUp* PowerUpPool::GetPowerUp()
{
	PowerUp* powerUp = mPowerUpPool[mNextAvailableIndex];
	mNextAvailableIndex = (mNextAvailableIndex + 1) % mPowerUpPool.size();

	return powerUp;
}

std::vector<PowerUp*>& PowerUpPool::GetPowerUpPool()
{
	return mPowerUpPool;
}
